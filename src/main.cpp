#include <Arduino.h>

#include "DJBeepTimer.hpp"
#include "DJDiscEncoder.hpp"
#include "DJButton.hpp"

void setup()
{

  Serial.begin(115200);

  pinMode(MOSQUIT_PIN, OUTPUT);
  pinMode(ENCODER_PIN, INPUT);

  pinMode(DJ_BUTTON_PIN_1, INPUT);
  pinMode(DJ_BUTTON_PIN_2, INPUT);
  pinMode(DJ_BUTTON_PIN_3, INPUT);
  pinMode(DJ_BUTTON_PIN_4, INPUT);

  digitalWrite(MOSQUIT_PIN, LOW);

  // タイマー開始
  initDJTimer();
  enableDJTimer();

  timerStop(DJTimer);

  digitalWrite(MOSQUIT_PIN, LOW);

}

void loop()
{

  if (digitalRead(DJ_BUTTON_PIN_1) == HIGH)
  {
    Serial.println("DJ_BUTTON_PIN_1");
    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);
  }
  
  if (digitalRead(DJ_BUTTON_PIN_2) == HIGH)
  {
    Serial.println("DJ_BUTTON_PIN_2");
    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);
  }

  if (digitalRead(DJ_BUTTON_PIN_3) == HIGH)
  {
    Serial.println("DJ_BUTTON_PIN_3");
    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);
  }

  // if (digitalRead(DJ_BUTTON_PIN_4) == HIGH)
  // {
  //   Serial.println("DJ_BUTTON_PIN_4");
  //   timerStart(DJTimer);
  //   delay(10);
  //   timerStop(DJTimer);
  //   digitalWrite(MOSQUIT_PIN, LOW);
  // }

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