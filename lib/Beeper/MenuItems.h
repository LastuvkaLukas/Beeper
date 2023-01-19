#pragma once
/**
 * MenuItems.h
 *
 * Custom menu for Beeper
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 *
 * @year 2022
 * @licence MIT
 **/

#include "Beeper.h"

//* -------------------------------
//* Custom beep items

static menu_item_t beepON = {"Beep ON", xbm_icon_beep_on_bits, 0};
static menu_item_t beepOFF = {"Beep OFF", xbm_icon_beep_off_bits, 0};

//* -------------------------------
//* Custom list of items

static menu_item_t menu_items[] = {
    {"Dashboard", xbm_icon_dashboard_bits, 0},
    {"Info", xbm_icon_scan_bits, 0},
    {}, // <--- Includes beep items here
    {"Reconnect", xbm_icon_wifi_bits, 0},
    {"Sleep", xbm_icon_sleep_bits, 0}};

//* -------------------------------
//* Custom index name of items
//! MUST BE SAME POSITION INDEX AS ITEMS IN MENU //

typedef enum
{
    menuDashboard,
    menuInfo,
    menuBeep,
    menuReconnect,
    menuSleep
} menu_item_id_t;