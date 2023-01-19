#include "Beeper_Button.h"

/// @brief [INTERNAL] Timer handler - default: NULL
hw_timer_t *_btn_timer = NULL;

/// @brief [INTERNAL] Button state press - 1 (pressed), 0 (not pressed); default: 0
volatile uint8_t _btn_pressed = 0;

/// @brief [INTERNAL] Timer callback interrupt
void IRAM_ATTR _btn_onTimer()
{
    timerAlarmDisable(_btn_timer);
    btn_start();
}

/// @brief [INTERNAL] Button callback interrupt
void IRAM_ATTR _btn_onPress()
{
    detachInterrupt(BTN_PIN);
    _btn_pressed = 1;
    timerAlarmEnable(_btn_timer);
}

/// @brief Button initialize
void btn_begin()
{
    pinMode(BTN_PIN, INPUT_PULLUP);
    _btn_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(_btn_timer, &_btn_onTimer, true);
    timerAlarmWrite(_btn_timer, BTN_DEBOUNCE * 1000, true);
}

/// @brief Get button last state and clear if last state was pressed
/// @return Last state button - 1 (pressed), 0 (not presset)
uint8_t btn_press()
{
    if (!_btn_pressed)
        return 0;

    _btn_pressed = 0;
    return 1;
}

/// @brief Start button interrupt flag
void btn_start()
{
    attachInterrupt(BTN_PIN, &_btn_onPress, FALLING);
}

/// @brief Stop button interrupt flag
void btn_stop()
{
    detachInterrupt(BTN_PIN);
    timerAlarmDisable(_btn_timer);
}

//* -------------------------------
//* END