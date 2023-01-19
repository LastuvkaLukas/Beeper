#include "Beeper_WiFiManager.h"

/// @brief [INTERNAL] Buffer
char *_wifi_manager_buffer;

/// @brief [INTERNAL] Save to buffer AP Name
void _wifi_manager_createAPName()
{
    uint32_t chipId = 0;
    for (int i = 0; i < 17; i = i + 8)
    {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    free(_wifi_manager_buffer);
    _wifi_manager_buffer = (char *)malloc((sizeof(WIFI_MANAGER_AP_NAME) + sizeof(chipId) * 2));
    sprintf(_wifi_manager_buffer, "%s%u", WIFI_MANAGER_AP_NAME, chipId);
    return;
}

/// @brief Defined WiFiManager client - default: {}
WiFiManager wifi_manager_client = {};

/// @brief Start WiFiManager via auto connect
/// @return Connection status - 1 (success), 0 (Fail)
uint8_t wifi_manager_connect()
{
    uint8_t res;
    _wifi_manager_createAPName();
    wifi_manager_client.setTitle(WIFI_MANAGER_TITLE);
    wifi_manager_client.setHostname(_wifi_manager_buffer);
    res = wifi_manager_client.autoConnect(_wifi_manager_buffer, WIFI_MANAGER_AP_PASS);
    free(_wifi_manager_buffer);
    return res;
}

/// @brief Get AP Name
/// @return AP Name
char *wifi_manager_getAPName()
{
    _wifi_manager_createAPName();
    return _wifi_manager_buffer;
}

/// @brief Clear save wifi data in nvc_flash
void wifi_manager_clear()
{
    wifi_manager_client.resetSettings();
}

//* -------------------------------
//* END