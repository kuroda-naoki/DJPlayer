#pragma once

#include <Arduino.h>

#define MOSQUIT_PIN 2

/**
 * モスキート音の周波数マクロ定数
 * 1M / 周波数 = 設定値
 */
#define DJ_MOSQUIT_ALL_OLD  111  // 1M / 9000  = 111.1111...
#define DJ_MOSQUIT_60_OLD   100  // 1M / 10000 = 100
#define DJ_MOSQUIT_50_OLD   83   // 1M / 12000 = 83.3333...
#define DJ_MOSQUIT_40_OLD   71   // 1M / 14000 = 71.4285...
#define DJ_MOSQUIT_30_OLD   67   // 1M / 15000 = 66.6666...
#define DJ_MOSQUIT_20_OLD   62   // 1M / 16000 = 62.5
#define DJ_MOSQUIT_NO_HUMAN 56   // 1M / 18000 = 55.5555...

hw_timer_t* DJTimer = timerBegin(0, getApbFrequency() / 1000000, true);
portMUX_TYPE DJTimerMux = portMUX_INITIALIZER_UNLOCKED;
extern volatile SemaphoreHandle_t DJTimerSemaphore;

volatile uint8_t hzCounter = 0;

void IRAM_ATTR DJTimerISR();  // 高音～モスキート音を鳴らす割り込みハンドラ
void initDJTimer();                  // DJTimerの初期化
void updateDJTimer(uint64_t sound);  // DJTimerの音の高さ更新
void enableDJTimer();                // DJTimerの有効化
void disableDJTimer();               // DJTimerの無効化

void IRAM_ATTR DJTimerISR() {
    // 割り込み禁止を開始する関数
    portENTER_CRITICAL_ISR(&DJTimerMux);

    hzCounter++;

    if (hzCounter % 2 == 1) {
        digitalWrite(MOSQUIT_PIN, HIGH);
    } else {
        digitalWrite(MOSQUIT_PIN, LOW);
    }

    // // 何故かこれだと常にHIGHになる
    // if (hzCounter & 0x01) {
    //     digitalWrite(MOSQUIT_PIN, HIGH);
    // } else {
    //     digitalWrite(MOSQUIT_PIN, LOW);
    // }

    // 割り込み禁止を終了する関数
    portEXIT_CRITICAL_ISR(&DJTimerMux);
    // xSemaphoreGiveFromISR(DJTimerSemaphore, NULL);
}

void initDJTimer() {
    // DJTimer = timerBegin(0, getApbFrequency() / 1000000, true);
    DJTimer = timerBegin(0, 80, true);
    // DJTimerSemaphore = xSemaphoreCreateBinary();
    timerAttachInterrupt(DJTimer, &DJTimerISR, true);
    timerAlarmWrite(DJTimer, DJ_MOSQUIT_NO_HUMAN, true);
}

void updateDJTimer(uint64_t sound) {
    timerAlarmWrite(DJTimer, sound, true);
}

void enableDJTimer() {
    timerAlarmEnable(DJTimer);
}

void disableDJTimer() {
    timerAlarmDisable(DJTimer);
}