#pragma once

#include <EEPROM.h>

#define EEPROM_MAGIC 0xAB
#define EEPROM_VERSION 0x01

#define SLOT_SIZE 35
#define SLOT_ADDR(slot) (2 + ((slot) * SLOT_SIZE))

extern char screen_buf[2][16];

void save_slot(uint8_t slot)
{
	EEPROM.update(0, EEPROM_MAGIC);
	EEPROM.update(1, EEPROM_VERSION);

	int start = SLOT_ADDR(slot);
	EEPROM.update(start, EEPROM_MAGIC);

	int addr = start + 1;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 16; x++) {
			EEPROM.update(addr, screen_buf[y][x]);
			addr += 1;
		}
	}
}

bool load_slot(uint8_t slot)
{
	int start = SLOT_ADDR(slot);

	if (EEPROM.read(0) != EEPROM_MAGIC ||
	    EEPROM.read(1) != EEPROM_VERSION ||
	    EEPROM.read(start) != EEPROM_MAGIC) {
		return false;
	}

	int addr = start + 1;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 16; x++) {
			screen_buf[y][x] = (char)EEPROM.read(addr);
			addr += 1;
		}
	}
	return true;
}
