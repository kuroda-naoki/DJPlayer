#pragma once

#include <Arduino.h>

#define ENCODER_PIN 34

bool isScratched();

bool isScratched()
{

    static int new_encoderValue = 0;
    static int old_encoderValue = 0;
    static int encoderValue = 0;

    new_encoderValue = analogRead(ENCODER_PIN);
    encoderValue = new_encoderValue - old_encoderValue;
    old_encoderValue = new_encoderValue;

    // 規定外の値が入力された場合はエラーとして扱う
    if (encoderValue > 1000 || encoderValue < -1000)
    {
        return false;
    }

    // 一定以上の値が入力された場合はスクラッチとして扱う
    if (encoderValue > 10 || encoderValue < -10)
    {
        return true;
    }

    return false;
    
}