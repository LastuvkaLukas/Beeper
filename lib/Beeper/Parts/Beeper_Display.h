#pragma once
/**
 * Beeper_Display.h
 *
 * Work with oled display
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 * @library olikraus/U8g2@^2.34.13
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

//* -------------------------------
//* Include Parts and X-Bitmaps

#include "Parts/Beeper_Menu.h"
#include "Parts/Beeper_Button.h"
#include "Parts/Beeper_Encoder.h"
#include "Parts/Beeper_Buzzer.h"
#include "Bitmaps/Bitmaps.h"

//* -------------------------------
//* Default parameters

#define DISPLAY_W_SCREEN 128
#define DISPLAY_H_SCREEN 64
#define DISPLAY_MAX_LINES 3
#define DISPLAY_Y_OFFSET 22

#define DISPLAY_X_POS_ICON 4
#define DISPLAY_Y_POS_ICON 2
#define DISPLAY_W_SIZE_ICON 14
#define DISPLAY_H_SIZE_ICON DISPLAY_W_SIZE_ICON

#define DISPLAY_X_POS_SELECT_RECTANGLE 0
#define DISPLAY_W_SIZE_SELECT_RECTANGLE 121
#define DISPLAY_H_SIZE_SELECT_RECTANGLE 20

#define DISPLAY_X_POS_SCROLL_POINTS 125
#define DISPLAY_Y_POS_SCROLL_POINTS 0
#define DISPLAY_W_SIZE_SCROLL_POINTS 1
#define DISPLAY_H_SIZE_SCROLL_POINTS 61

#define DISPLAY_X_POS_SCROLL_RECTANGLE 123
#define DISPLAY_W_SIZE_SCROLL_RECTANGLE 5
#define DISPLAY_H_SIZE_SCROLL_RECTANGLE 12
#define DISPLAY_Y_OFFSET_SCROLL_RECTANGLE (DISPLAY_H_SCREEN - DISPLAY_H_SIZE_SCROLL_RECTANGLE)
#define DISPLAY_ROUND_SCROLL_RECTANGLE 2

#define DISPLAY_FONT_STYLE u8g_font_9x15B
#define DISPLAY_FONT_SIZE 1
#define DISPLAY_X_POS_FONT 25
#define DISPLAY_Y_OFFSET_FONT 12

// Main display client
extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display_oled;

void display_begin(void);
void display_center(const char *message, uint8_t onlyHorizontal = 0, int8_t y = 0);
void display_terminal(const char *message, uint8_t center = 0, uint8_t onlyHorizontal = 0, uint32_t delayMS = 2000);
void display_terminal2Lines(const char *message1, const char *message2, uint8_t center = 0, uint8_t onlyHorizontal = 0, uint32_t delayMS = 2000);
void display_renderMenu(menu_items_t *items);
void display_scroll(menu_items_t *items, uint8_t decending);
void display_off(void);