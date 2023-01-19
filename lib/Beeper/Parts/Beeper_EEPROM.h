#pragma once
/**
 * Beeper_EEPROM.h
 *
 * Work with EEPROM
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>
#include <EEPROM.h>

//* -------------------------------
//* Default parameters

#define EEPROM_START_ADDR 0

void eeprom_begin(void);
void eeprom_write(uint8_t byte);
uint8_t eeprom_read(void);