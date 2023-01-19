/**
 * BEEPER
 *
 * Semester work IAM2E
 *
 * @author Laštůvka Lukáš
 * @version 0.1.0
 *
 * @year 2022
 * @licence MIT
 **/

#include <Arduino.h>
#include <esp_task_wdt.h>
#include <Beeper.h>

#define DEBUG 1
#include "BrownoutOFF.h"

void setup()
{
  brownoutOFF();
  Serial.begin(115200);
  beeper_begin();
  esp_task_wdt_init(5, true);
  esp_task_wdt_add(NULL);
}

void loop()
{
  beeper_loop();
  esp_task_wdt_reset();
}