#pragma once
/**
 * Beeper_WiFiManager.h
 *
 * Work with WiFiManager
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 * @library tzapu/WiFiManager
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>
#include <WiFiManager.h>

//* -------------------------------
//* Default parameters

#define WIFI_MANAGER_TITLE "Beeper"     // Default wifi manager title
#define WIFI_MANAGER_AP_NAME "Beeper_"  // Default wifi manager AP name prefix
#define WIFI_MANAGER_AP_PASS "00000000" // Default wifi manager AP password

// Main client
extern WiFiManager wifi_manager_client;

uint8_t wifi_manager_connect(void);
char *wifi_manager_getAPName(void);
void wifi_manager_clear(void);