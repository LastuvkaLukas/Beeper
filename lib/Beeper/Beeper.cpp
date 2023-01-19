#include "Beeper.h"

/// @brief Set main menu
menu_items_t menu = {
    menu_items,
    sizeof(menu_items) / sizeof(menu_item_t),
    0, 0};

/// @brief [INTERNAL] Callback if the encoder scroll in menu
/// @param p State of encored - encDown, encUp
void _onScroll(enc_state_t p)
{
    beeper_resetSleepTimer();
    display_scroll(&menu, p == encUp ? 0 : 1);
}

/// @brief [INTERNAL] Callback if the encoder scroll in start screen; LEFT - restart, RIGHT - sleep
/// @param p State of encored - encDown, encUp
void _onScrollWiFiManager(enc_state_t p)
{
    if (p == encDown)
    {
        esp_sleep_enable_ext0_wakeup(BTN_PIN, 0);
        display_off();
        esp_deep_sleep_start();
    }

    esp_restart();
}

/// @brief [INTERNAL] Callback if WiFiManager started
/// @param wm Self WiFiManger
void _onWifiManagerStarted(WiFiManager *wm)
{
    wifi_manager_client.setTimeout(120);
    display_terminal(text_startingWifiManager, 1);
    display_terminal2Lines(text_apName, wifi_manager_getAPName(), 1);
}

/// @brief [INTERNAL] Last wake time from scroll or click
uint64_t _lastWake = 0;

/// @brief Reset sleep time
void beeper_resetSleepTimer()
{
    _lastWake = millis();
}

/// @brief Check if time go to the sleep
void beeper_checkSleepTimer()
{
    if ((_lastWake + BEEPER_TIME_TO_GO_SLEEP) <= millis())
    {
        menu_dashboardStop();
        menu_infoStop();
        beeper_sleep();
    }
}

/// @brief Beeper initialize
void beeper_begin()
{
    eeprom_begin();
    btn_begin();
    enc_begin();
    buzzer_begin();
    display_begin();

    enc_onChange(&_onScrollWiFiManager);
    enc_start();

    display_terminal(text_starting, 1);
    display_terminal(text_testConnection, 1, 0, 0);
    wifi_manager_client.setAPCallback(&_onWifiManagerStarted);
    wifi_manager_client.setTimeout(5);

    if (!wifi_manager_connect())
    {
        enc_stop();
        display_terminal(text_notConnection, 1);
        beeper_sleep();
    }

    display_terminal(text_connected, 1);

    enc_onChange(&_onScroll);
    menu_buzzerChange(&menu);
    display_renderMenu(&menu);
}

/// @brief Beeper loop
void beeper_loop()
{
    beeper_checkSleepTimer();
    if (btn_press())
        beeper_semaphore(&menu);
}

/// @brief Clear all data from WiFiManager and restart Beeper
void beeper_reconnect()
{
    btn_stop();
    display_terminal(text_clearWifiData, 1);
    wifi_manager_clear();
    display_terminal(text_restart, 1);
    esp_restart();
}

/// @brief Beeper goes to the sleep
void beeper_sleep()
{
    btn_stop();
    esp_sleep_enable_ext0_wakeup(BTN_PIN, 0);
    buzzer_stop();
    display_terminal(text_goingToSleep, 1);
    display_off();
    esp_deep_sleep_start();
}

/// @brief Beeper semaphore for menu of items
/// @param menu Menu of items
void beeper_semaphore(menu_items_t *menu)
{
    beeper_resetSleepTimer();
    enc_stop();

    switch (menu->getSelectedId())
    {
    case menuDashboard:
        menu_renderDashboard(menu);
        break;

    case menuBeep:
        buzzer_toggleSaveState(menu);
        break;

    case menuInfo:
        menu_renderInfo(menu);
        break;

    case menuReconnect:
        beeper_reconnect();
        break;

    case menuSleep:
        beeper_sleep();
        break;
    }
}

//* -------------------------------
//* END