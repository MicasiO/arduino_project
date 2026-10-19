#include <LiquidCrystal.h>
#include <ezButton.h>

#include "lcd.h"
#include "joystick.h"
#include "storage.h"

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3

#define HOLD_TICKS 8

ezButton button(7);
LiquidCrystal lcd(12, 11, 5, 4, 8, 9);

static int c_pos_x = 0;
static int c_pos_y = 0;

char screen_buf[2][16];

volatile bool timer_tick = false;
volatile bool button1_active = false;
volatile bool button2_active = false;

int button1_ticks = 0;
int button2_ticks = 0;

void handle_save_button(int pin, uint8_t slot, volatile bool *active_flag,
			int *ticks)
{
	if (!(*active_flag)) {
		return;
	}

	if (digitalRead(pin) == LOW) {
		(*ticks)++;
		if (*ticks >= HOLD_TICKS) {
			if (load_slot(slot)) {
				lcd_refresh(&lcd, c_pos_x, c_pos_y);
			}

			*ticks = 0;
			*active_flag = false;
		}
	} else {
		if (*ticks > 0) {
			save_slot(slot);
		}

		*ticks = 0;
		*active_flag = false;
	}
}

void setup()
{
	Serial.begin(9600);

	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), ISR_BUTTON1,
			FALLING);
	attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), ISR_BUTTON2,
			FALLING);

	init_lcd(&lcd);
	init_joystick();
}

void loop()
{
	button.loop();

	if (timer_tick) {
		timer_tick = false;

		handle_save_button(BUTTON1_PIN, 0, &button1_active,
				   &button1_ticks);
		handle_save_button(BUTTON2_PIN, 1, &button2_active,
				   &button2_ticks);

		bool moved = handle_move(&c_pos_x, &c_pos_y);
		bool wrote = handle_write(c_pos_x, c_pos_y);

		if (wrote) {
			lcd_print_char(&lcd, c_pos_x, c_pos_y);
		} else if (moved) {
			lcd_move_cursor(&lcd, c_pos_x, c_pos_y);
		}
	}

	if (button.isPressed()) {
		handle_delete(c_pos_x, c_pos_y);
		lcd_print_char(&lcd, c_pos_x, c_pos_y);
	}
}

void ISR_BUTTON1()
{
	button1_active = true;
}

void ISR_BUTTON2()
{
	button2_active = true;
}
