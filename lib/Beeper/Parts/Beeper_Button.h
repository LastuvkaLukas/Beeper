#pragma once
/**
 * Beeper_Button.h
 *
 * Work with encoder button
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>

//* -------------------------------
//* Default parameters

#define BTN_PIN GPIO_NUM_33
#define BTN_DEBOUNCE 1500

void btn_begin(void);
uint8_t btn_press(void);
void btn_start(void);
void btn_stop(void);