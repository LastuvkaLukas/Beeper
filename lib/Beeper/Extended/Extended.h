#pragma once
/**
 * Extended.h
 *
 * Extended for Beeper
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 * @year 2022
 * @licence MIT
 **/

#include "Beeper.h"

//* -------------------------------
//* Extended buzzer

//* Buzzer state macros

#define BUZZER_ON 100
#define BUZZER_OFF 200

uint8_t buzzer_isOn(void);
void buzzer_toggleSaveState(menu_items_t *menu);

//* -------------------------------
//* Extended menu

void menu_buzzerChange(menu_items_t *menu);

//* -------------------------------
//* Extended menu item - Dashboard

//* Dashboard display parameters

#define DISPLAY_X_POS_WIFI_POINT 61
#define DISPLAY_Y_POS_WIFI_POINT 39
#define DISPLAY_W_SIZE_WIFI_POINT 5
#define DISPLAY_H_SIZE_WIFI_POINT DISPLAY_W_SIZE_WIFI_POINT

#define DISPLAY_X_POS_WIFI_1 58
#define DISPLAY_Y_POS_WIFI_1 34
#define DISPLAY_W_SIZE_WIFI_1 11
#define DISPLAY_H_SIZE_WIFI_1 4

#define DISPLAY_X_POS_WIFI_2 54
#define DISPLAY_Y_POS_WIFI_2 29
#define DISPLAY_W_SIZE_WIFI_2 19
#define DISPLAY_H_SIZE_WIFI_2 5

#define DISPLAY_X_POS_WIFI_3 50
#define DISPLAY_Y_POS_WIFI_3 23
#define DISPLAY_W_SIZE_WIFI_3 27
#define DISPLAY_H_SIZE_WIFI_3 7

#define DISPLAY_X_POS_WIFI_4 46
#define DISPLAY_Y_POS_WIFI_4 17
#define DISPLAY_W_SIZE_WIFI_4 35
#define DISPLAY_H_SIZE_WIFI_4 9

#define DISPLAY_X_POS_WIFI_LOW 56
#define DISPLAY_Y_POS_WIFI_LOW 16
#define DISPLAY_W_SIZE_WIFI_LOW 18
#define DISPLAY_H_SIZE_WIFI_LOW 25

void menu_renderDashboard(menu_items_t *menu);
void menu_dashboardStart(menu_items_t *menu);
void menu_dashboardStop();

//* -------------------------------
//* Extended menu item - Info

void menu_renderInfo(menu_items_t *menu);
void menu_infoStart(menu_items_t *menu);
void menu_infoStop();