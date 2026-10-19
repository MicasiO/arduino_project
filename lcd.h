#pragma once

extern char screen_buf[2][16];

void init_lcd(LiquidCrystal *lcd)
{
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 16; x++) {
			screen_buf[y][x] = ' ';
		}
	}
	// set number of cols and rows of lcd
	lcd->begin(16, 2);
	lcd->noBlink();
	lcd->cursor();
	lcd->setCursor(0, 0);
}

void lcd_move_cursor(LiquidCrystal *lcd, int x, int y)
{
	lcd->setCursor(x, y);
}

void lcd_print_char(LiquidCrystal *lcd, int x, int y)
{
	lcd->write(screen_buf[y][x]);
	lcd->setCursor(x, y);
}

void lcd_refresh(LiquidCrystal *lcd, int x, int y)
{
	for (int y = 0; y < 2; y++) {
		lcd->setCursor(0, y);
		for (int x = 0; x < 16; x++) {
			lcd->write(screen_buf[y][x]);
		}
	}
	lcd->setCursor(x, y);
}
