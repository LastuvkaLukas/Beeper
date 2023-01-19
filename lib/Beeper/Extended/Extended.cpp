#include "Extended.h"

//* -------------------------------
//* Extended buzzer

/// @brief Check if buzzer is on (read from EEPROM)
/// @return 1 (buzzer on), 0 (buzzer off)
uint8_t buzzer_isOn()
{
    return eeprom_read() == BUZZER_ON;
}

/// @brief Toggle buzzer state (write to EEPROM)
/// @param menu Menu of items
void buzzer_toggleSaveState(menu_items_t *menu)
{
    btn_stop();
    eeprom_write(eeprom_read() == BUZZER_ON ? BUZZER_OFF : BUZZER_ON);
    menu_buzzerChange(menu);
    display_renderMenu(menu);
}

//* -------------------------------
//* Extended menu

/// @brief Chnge menu item by buzzer state (read from EEPROM)
/// @param menu Menu of items
void menu_buzzerChange(menu_items_t *menu)
{
    menu->items[menuBeep] = eeprom_read() == BUZZER_ON ? beepON : beepOFF;
}

//* -------------------------------
//* Extended menu item - Dashboard

/// @brief [INTERNAL] State dashboard task - 1 (running), 0 (stoped); default: 0
uint8_t _menu_dashboardTaskRunning = 0;

/// @brief [INTERNAL] Task handle of dashboard - default: NULL
TaskHandle_t _menu_dashboardTaskHandle = NULL;

/// @brief [INTERNAL] State connect WiFi - 1 (connect), 0 (disconnect); default: 0
uint8_t _menu_dashboardIsConnected = 0;

/// @brief [INTERNAL] State fast of buzzer - default: buzzerNormal
buzzer_fast_t _menu_dashboardBuzzerFast = buzzerNormal;

/// @brief [INTERNAL] Task of dashboard
/// @param p NULL
void _menu_dashboardTaskDashboard(void *p)
{
    while (1)
    {
        _menu_dashboardIsConnected = WiFi.isConnected();
        _menu_dashboardBuzzerFast = buzzer_getFastFromRSSI(WiFi.RSSI());

        buzzer_changeFast(_menu_dashboardBuzzerFast);

        if (!_menu_dashboardIsConnected)
        {
            buzzer_changeFast(buzzerNormal);
            WiFi.reconnect();
            delay(500);
            // display_terminal(text_disconnect, 1, 0, 500);
            // continue;
        }
        // display_terminal(((String)WiFi.RSSI() + " dBm").c_str(), 1, 0, 1000);

        display_oled.firstPage();
        do
        {
            display_oled.drawXBM(
                DISPLAY_X_POS_WIFI_POINT,
                DISPLAY_Y_POS_WIFI_POINT,
                DISPLAY_W_SIZE_WIFI_POINT,
                DISPLAY_H_SIZE_WIFI_POINT,
                xbm_fn_wifi_point_bits);

            if (!_menu_dashboardIsConnected)
            {
                // wifi low
                display_oled.drawXBM(
                    DISPLAY_X_POS_WIFI_LOW,
                    DISPLAY_Y_POS_WIFI_LOW,
                    DISPLAY_W_SIZE_WIFI_LOW,
                    DISPLAY_H_SIZE_WIFI_LOW,
                    xbm_fn_wifi_low_bits);
            }

            if (!_menu_dashboardIsConnected ||
                _menu_dashboardBuzzerFast == buzzerPoor ||
                _menu_dashboardBuzzerFast == buzzerWeak ||
                _menu_dashboardBuzzerFast == buzzerGood ||
                _menu_dashboardBuzzerFast == buzzerVeryGood)
            {
                // wifi poor
                display_oled.drawXBM(
                    DISPLAY_X_POS_WIFI_1,
                    DISPLAY_Y_POS_WIFI_1,
                    DISPLAY_W_SIZE_WIFI_1,
                    DISPLAY_H_SIZE_WIFI_1,
                    xbm_fn_wifi_1_bits);
            }

            if (!_menu_dashboardIsConnected ||
                _menu_dashboardBuzzerFast == buzzerWeak ||
                _menu_dashboardBuzzerFast == buzzerGood ||
                _menu_dashboardBuzzerFast == buzzerVeryGood)
            {
                // wifi weak
                display_oled.drawXBM(
                    DISPLAY_X_POS_WIFI_2,
                    DISPLAY_Y_POS_WIFI_2,
                    DISPLAY_W_SIZE_WIFI_2,
                    DISPLAY_H_SIZE_WIFI_2,
                    xbm_fn_wifi_2_bits);
            }

            if (!_menu_dashboardIsConnected ||
                _menu_dashboardBuzzerFast == buzzerGood ||
                _menu_dashboardBuzzerFast == buzzerVeryGood)
            {
                // wifi good
                display_oled.drawXBM(
                    DISPLAY_X_POS_WIFI_3,
                    DISPLAY_Y_POS_WIFI_3,
                    DISPLAY_W_SIZE_WIFI_3,
                    DISPLAY_H_SIZE_WIFI_3,
                    xbm_fn_wifi_3_bits);
            }

            if (!_menu_dashboardIsConnected ||
                _menu_dashboardBuzzerFast == buzzerVeryGood)
            {
                // wifi very good
                display_oled.drawXBM(
                    DISPLAY_X_POS_WIFI_4,
                    DISPLAY_Y_POS_WIFI_4,
                    DISPLAY_W_SIZE_WIFI_4,
                    DISPLAY_H_SIZE_WIFI_4,
                    xbm_fn_wifi_4_bits);
            }

            display_oled.setFont(u8g_font_6x10);

            display_oled.setFontPosBottom();
            display_center(((String)WiFi.RSSI() + " dBm").c_str(), 1, 64);
        } while (display_oled.nextPage());

        delay(1500);
    }
}

/// @brief Main dashboard render starter
/// @param menu Menu of items
void menu_renderDashboard(menu_items_t *menu)
{
    btn_stop();

    if (buzzer_isOn())
        buzzer_start();

    if (!menu->items[menuDashboard].open)
    {
        menu->items[menuDashboard].open = 1;
        menu_dashboardStart(menu);
        delay(100);
        btn_start();
        return;
    }

    menu->items[menuDashboard].open = 0;
    menu_dashboardStop();
    display_terminal(" ", 1, 0, 10);
    display_renderMenu(menu);
}

/// @brief Start task of dashboard
/// @param menu Menu of items
void menu_dashboardStart(menu_items_t *menu)
{
    if (_menu_dashboardTaskRunning)
        return;

    _menu_dashboardTaskRunning = 1;
    xTaskCreate(
        _menu_dashboardTaskDashboard,
        "MenuDashboard",
        4096,
        NULL,
        0,
        &_menu_dashboardTaskHandle);
}

/// @brief Stop task of dashboard
void menu_dashboardStop()
{
    if (!_menu_dashboardTaskRunning)
        return;

    buzzer_stop();
    _menu_dashboardTaskRunning = 0;
    vTaskDelete(_menu_dashboardTaskHandle);
}

//* -------------------------------
//* Extended menu item - Info

/// @brief [INTERNAL] State info task - 1 (running), 0 (stoped); default: 0
uint8_t _menu_infoTaskRunning = 0;

/// @brief [INTERNAL] Task handle of info - default: NULL
TaskHandle_t _menu_infoTaskHandle = NULL;

/// @brief [INTERNAL] Task of info
/// @param p NULL
void _menu_infoTaskInfo(void *p)
{
    while (1)
    {
        if (!WiFi.isConnected())
        {
            WiFi.reconnect();
            display_terminal(text_notConnection, 1);
            continue;
        }

        display_terminal2Lines(text_ssid, WiFi.SSID().c_str(), 1);
        display_terminal2Lines(text_localIPv4, WiFi.localIP().toString().c_str(), 1);
        display_terminal2Lines(text_gateway, WiFi.gatewayIP().toString().c_str(), 1);
        display_terminal2Lines(text_mask, WiFi.subnetMask().toString().c_str(), 1);
        display_terminal2Lines(text_broadcast, WiFi.broadcastIP().toString().c_str(), 1);
        display_terminal2Lines(text_mac, WiFi.macAddress().c_str(), 1);
    }
}

/// @brief Main info render starter
/// @param menu Menu of items
void menu_renderInfo(menu_items_t *menu)
{
    btn_stop();
    if (!menu->items[menuInfo].open)
    {
        menu->items[menuInfo].open = 1;
        menu_infoStart(menu);
        delay(100);
        btn_start();
        return;
    }

    menu->items[menuInfo].open = 0;
    menu_infoStop();
    display_terminal(" ", 1, 0, 10);
    display_renderMenu(menu);
}

/// @brief Start task of dashboard
/// @param menu Menu of items
void menu_infoStart(menu_items_t *menu)
{
    if (_menu_infoTaskRunning)
        return;

    _menu_infoTaskRunning = 1;
    xTaskCreate(
        _menu_infoTaskInfo,
        "MenuInfo",
        2096,
        NULL,
        0,
        &_menu_infoTaskHandle);
}

/// @brief Stop task of info
void menu_infoStop()
{
    if (!_menu_infoTaskRunning)
        return;

    buzzer_stop();
    _menu_infoTaskRunning = 0;
    vTaskDelete(_menu_infoTaskHandle);
}

//* -------------------------------
//* END
