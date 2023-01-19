#pragma once
/**
 * Beeper_Buzzer.h
 *
 * Work with buzzer
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

#define BUZZER_PIN GPIO_NUM_17
#define BUZZER_MIN_BEEP_FAST 200
#define BUZZER_FREQ 2100

typedef enum
{
    buzzerVeryGood = BUZZER_MIN_BEEP_FAST,
    buzzerGood = BUZZER_MIN_BEEP_FAST * 2,
    buzzerWeak = BUZZER_MIN_BEEP_FAST * 4,
    buzzerPoor = BUZZER_MIN_BEEP_FAST * 8,
    buzzerNormal = BUZZER_MIN_BEEP_FAST * 32
} buzzer_fast_t;

void buzzer_begin(void);
buzzer_fast_t buzzer_getFastFromRSSI(int8_t rssi);
void buzzer_changeFast(buzzer_fast_t fast);
void buzzer_start(void);
void buzzer_stop(void);