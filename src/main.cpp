#include <Arduino.h>

#include "DJBeepTimer.hpp"
#include "DJDiscEncoder.hpp"

void setup()
{

  pinMode(MOSQUIT_PIN, OUTPUT);
  pinMode(ENCODER_PIN, INPUT);

  digitalWrite(MOSQUIT_PIN, LOW);

  // タイマー開始
  initDJTimer();
  enableDJTimer();

  timerStop(DJTimer);

  digitalWrite(MOSQUIT_PIN, LOW);

}

void loop()
{

  if (isScratched())
  {
    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);
  }
  else
  {
    timerStop(DJTimer);
  }

  delay(10);

  // timerStart(DJTimer);

}