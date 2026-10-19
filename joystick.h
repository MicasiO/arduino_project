#pragma once

extern volatile bool timer_tick;
extern char screen_buf[2][16];

void init_joystick()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	// CTC mode: reset ticks on compare
	TCCR1B &= ~(1 << WGM13);
	TCCR1B |= (1 << WGM12);

	// 64 prescaler
	TCCR1B |= (1 << CS11) | (1 << CS10);

	// converts to 50ms
	OCR1A = 29999;

	// enable Timer1 compare interrupt
	TIMSK1 = (1 << OCIE1A);

	sei();
}

bool handle_move(int *pos_x, int *pos_y)
{
	int j_val_y = analogRead(A0);
	if (j_val_y >= 1020) {
		if (*pos_x == 15 && *pos_y == 1) {
			return false;
		} else if (*pos_x == 15 && *pos_y == 0) {
			*pos_x = 0;
			*pos_y = 1;
		} else {
			*pos_x += 1;
		}
		return true;

	} else if (j_val_y <= 20) {
		if (*pos_x == 0 && *pos_y == 0) {
			return false;
		} else if (*pos_x == 0 && *pos_y == 1) {
			*pos_x = 15;
			*pos_y = 0;
		} else {
			*pos_x -= 1;
		}
		return true;
	}

	return false;
}

bool handle_write(int pos_x, int pos_y)
{
	int j_val_x = analogRead(A1);
	char c = screen_buf[pos_y][pos_x];

	if (j_val_x <= 20) {
		if (c == ' ')
			c = 'A';
		else if (c >= 'Z')
			c = 'A';
		else
			c += 1;

		screen_buf[pos_y][pos_x] = c;
		return true;
	} else if (j_val_x >= 1020) {
		if (c == ' ')
			c = 'Z';
		else if (c <= 'A')
			c = 'Z';
		else
			c -= 1;

		screen_buf[pos_y][pos_x] = c;
		return true;
	}
	return false;
}

void handle_delete(int pos_x, int pos_y)
{
	char c = screen_buf[pos_y][pos_x];
	c = ' ';
	screen_buf[pos_y][pos_x] = c;
}

ISR(TIMER1_COMPA_vect)
{
	timer_tick = true;
}
