#include <Arduino.h>
#include <M5Stack.h>

#include "DJBeepTimer.hpp"
#include "DJDiscEncoder.hpp"
#include "DJButton.hpp"

void setup()
{

  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("DJ Player");

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

  delay(1000);

  while (digitalRead(DJ_BUTTON_PIN_3) == HIGH)
  {
    delay(10);
  }

}

void loop()
{

  static uint16_t oldMosquit = DJ_MOSQUIT_NO_HUMAN;

  static String tagId = "";
    while (Serial2.available()) {
        char receivedChar = Serial2.read();
        if (receivedChar == '\n') {
          disableDJTimer();
          // M5.Lcd.clear();
          M5.Lcd.setCursor(0, 0);
          M5.Lcd.println(tagId);
          enableDJTimer();
        } else {
            tagId += receivedChar;
        }
    }

  if (digitalRead(DJ_BUTTON_PIN_1) == HIGH)
  {
    updateDJTimer(DJ_MOSQUIT_20_OLD);

    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);

    updateDJTimer(oldMosquit);
  }
  
  if (digitalRead(DJ_BUTTON_PIN_2) == HIGH)
  {
    updateDJTimer(DJ_MOSQUIT_40_OLD);

    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);

    updateDJTimer(oldMosquit);
  }

  if (digitalRead(DJ_BUTTON_PIN_3) == HIGH)
  {
    updateDJTimer(DJ_MOSQUIT_ALL_OLD);

    timerStart(DJTimer);
    delay(10);
    timerStop(DJTimer);
    digitalWrite(MOSQUIT_PIN, LOW);

    updateDJTimer(oldMosquit);
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