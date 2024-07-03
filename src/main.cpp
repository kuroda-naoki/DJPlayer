#include <Arduino.h>

#include "DJBeepTimer.hpp"

void setup()
{

  pinMode(MOSQUIT_PIN, OUTPUT);

  // タイマー開始
  initDJTimer();
  enableDJTimer();

}

void loop()
{

}