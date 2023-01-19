#include "Beeper_Buzzer.h"

/// @brief [INTERNAL] State buzzer task - 1 (running), 0 (stoped); default: 0
uint8_t _buzzer_taskRunning = 0;

/// @brief [INTERNAL] Task handle of buzzer - default: NULL
TaskHandle_t _buzzer_taskHandle = NULL;

/// @brief [INTERNAL] State fast of buzzer - default: buzzerNormal
buzzer_fast_t _buzzer_fast = buzzerNormal;

/// @brief [INTERNAL] Task of buzzer
/// @param p NULL
void _buzzer_taskBuzzer(void *p)
{
    while (1)
    {
        tone(BUZZER_PIN, BUZZER_FREQ, 100);
        delay(_buzzer_fast / 2);
        noTone(BUZZER_PIN);
        delay(_buzzer_fast);
    }
}

/// @brief Buzzer initialize
void buzzer_begin()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

/// @brief Calculate buzzer fast from RSSI
/// @param rssi WiFi RSSI
/// @return Buzzer fast - default: buzzerNormal
buzzer_fast_t buzzer_getFastFromRSSI(int8_t rssi)
{
    if (rssi >= -50)
        return buzzerVeryGood;

    if (rssi < -50 && rssi >= -63)
        return buzzerGood;

    if (rssi < -63 && rssi >= -75)
        return buzzerWeak;

    if (rssi < -75 && rssi >= -88)
        return buzzerPoor;

    return buzzerNormal;
}

/// @brief Change buzzer fast
/// @param fast Fast buzzer
void buzzer_changeFast(buzzer_fast_t fast)
{
    _buzzer_fast = fast;
}

/// @brief Start task of buzzer
void buzzer_start()
{
    if (_buzzer_taskRunning)
        return;

    _buzzer_taskRunning = 1;
    xTaskCreate(
        _buzzer_taskBuzzer,
        "Buzzer",
        1023,
        NULL,
        0,
        &_buzzer_taskHandle);
}

/// @brief Stop task of buzzer
void buzzer_stop()
{
    if (!_buzzer_taskRunning)
        return;

    _buzzer_taskRunning = 0;
    vTaskDelete(_buzzer_taskHandle);
}

//* -------------------------------
//* END