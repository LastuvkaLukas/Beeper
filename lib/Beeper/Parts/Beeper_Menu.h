#pragma once
/**
 * Beeper_Menu.h
 *
 * Defines structures of menu and menu items
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
//* Structure menu item

typedef struct
{
    char name[15];
    const unsigned char *icon;
    uint8_t open;
} menu_item_t;

//* -------------------------------
//* Structure menu of items

typedef struct
{
    menu_item_t *items;
    uint8_t length;
    uint8_t start_pos;
    uint8_t select_pos;
    uint8_t getSelectedId() { return start_pos + select_pos; }
} menu_items_t;