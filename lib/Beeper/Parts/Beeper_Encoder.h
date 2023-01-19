#pragma once
/**
 * Beeper_Encoder.h
 *
 * Work with encoder
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 * @library madhephaestus/ESP32Encoder@^0.10.1
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>
#include <ESP32Encoder.h>

//* -------------------------------
//* Default parameters

#define ENC_ENCODER_A_PIN GPIO_NUM_18
#define ENC_ENCODER_B_PIN GPIO_NUM_19
#define ENC_DEBOUNCE 50

typedef enum
{
    encNull,
    encUp,
    encDown
} enc_state_t;

void enc_begin(void);
void enc_onChange(void (*fn)(enc_state_t p));
void enc_start(void);
void enc_stop(void);