#include "Beeper_Encoder.h"

/// @brief [INTERNAL] State encoder task - 1 (running), 0 (stoped); default: 0
uint8_t _enc_taskRunning = 0;

/// @brief [INTERNAL] Task handle of encoder - default: NULL
TaskHandle_t _enc_taskHandle = NULL;

/// @brief [INTERNAL] Defined encoder - default: {}
ESP32Encoder _enc_encoder = {};

/// @brief [INTERNAL] Encoder callback type
void (*_enc_onChangeFn)(enc_state_t p);

/// @brief [INTERNAL] Task of encoder
/// @param p NULL
void _enc_taskEncoder(void *p)
{
    while (1)
    {
        int8_t pos = (int8_t)_enc_encoder.getCount();

        if (pos == 0)
            continue;

        enc_state_t state = pos < 0 ? encUp : encDown;
        if (_enc_onChangeFn != NULL)
            _enc_onChangeFn(state);
        delay(ENC_DEBOUNCE);

        _enc_encoder.clearCount();
    }
}

/// @brief Encoder initialize
void enc_begin()
{
    ESP32Encoder::useInternalWeakPullResistors = UP;
    _enc_encoder.attachHalfQuad(ENC_ENCODER_A_PIN, ENC_ENCODER_B_PIN);
    _enc_encoder.setCount(0);
}

/// @brief Set encoder callback
/// @param fn Callback function
void enc_onChange(void (*fn)(enc_state_t p))
{
    _enc_onChangeFn = fn;
}

/// @brief Start task of encoder
void enc_start()
{
    if (_enc_taskRunning)
        return;

    _enc_encoder.clearCount();
    _enc_taskRunning = 1;
    xTaskCreate(
        _enc_taskEncoder,
        "Encoder",
        2000,
        NULL,
        0,
        &_enc_taskHandle);
}

/// @brief Stop task of encoder
void enc_stop()
{
    if (!_enc_taskRunning)
        return;

    _enc_taskRunning = 0;
    vTaskDelete(_enc_taskHandle);
}

//* -------------------------------
//* END