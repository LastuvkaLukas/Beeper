#pragma once
/**
 * Beeper.h
 *
 * Scan and beep wifi via Beeper with include WiFiManager, oled display and rotary encoder
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 * @library tzapu/WiFiManager
 * @library madhephaestus/ESP32Encoder@^0.10.1
 * @library olikraus/U8g2@^2.34.13
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>

//* -------------------------------
//* Include Parts

#include "Parts/Beeper_Button.h"
#include "Parts/Beeper_Encoder.h"
#include "Parts/Beeper_Buzzer.h"
#include "Parts/Beeper_Display.h"
#include "Parts/Beeper_EEPROM.h"
#include "Parts/Beeper_Menu.h"
#include "Parts/Beeper_WiFiManager.h"

//* -------------------------------
//* Include X-Bitmaps and Texts

#include "Bitmaps/Bitmaps.h"
#include "Texts/lang/en-US.h"

//* -------------------------------
//* Include Custom menu

#include "MenuItems.h"

//* -------------------------------
//* Include Extended

#include "Extended/Extended.h"

//* -------------------------------
//* Default parameters

#define BEEPER_TIME_TO_GO_SLEEP 180000 // (180 000ms) - 3 minutes

// Main menu
extern menu_items_t menu;

void beeper_resetSleepTimer(void);
void beeper_checkSleepTimer(void);
void beeper_begin(void);
void beeper_loop(void);
void beeper_reconnect(void);
void beeper_sleep(void);
void beeper_semaphore(menu_items_t *menu);