#pragma once

#include <CanSatSchool.h>

#include "device.hpp"

enum MissionPhase {
    LOADING,     // 準備
    LAUNCHING,   // 打ち上げ
    DESCENDING,  // 降下
    LANDED,      // 着地
    FINISHED,    // 終了
};

MissionPhase phase = LOADING;  // ミッションのフェーズ

float altitude_at_ground;  // 地表の高度 [m]
float height;              // 高度 [m]
int light;                 // 光センサの値

// 気圧の差から相対高度を計算する関数
float calculateHeightFromPressure(float pressure)
{
    float pressure_at_sea_level = 1013.250;  // 海抜 0m での大気圧 [hPa]

    float altitude = (pressure_at_sea_level - pressure) * 10;  // ざっくり 10m 上昇すると 1hPa 下がるとする
    return altitude - altitude_at_ground;
}

void calibratePressureSensor()
{
    // 安定するまで待つ
    logger.info(F("Waiting for stabilization..."));
    unsigned long wait_start = millis();
    while (millis() - wait_start < 10000)
    {
        // 気圧を取得する
        float pressure = bth.read().pressure;
        logger.debug(F("Pressure:"), pressure, F("[hPa]"));
        delay(1000);
    }

    logger.info(F("Calibrating pressure sensor..."));

    // 地表の気圧を取得する
    float pressure_at_ground = bth.read().pressure;
    logger.info(F("Pressure at ground:"), pressure_at_ground, F("[hPa]"));

    // 地表の海抜高度を計算する
    float pressure_at_sea_level = 1013.250;  // 海抜 0m での大気圧 [hPa]
    altitude_at_ground = (pressure_at_sea_level - pressure_at_ground) * 10;  // ざっくり 10m 上昇すると 1hPa 下がるとする
    logger.info(F("Altitude at ground:"), altitude_at_ground, F("[m]"));

    logger.info(F("Calibration completed"));
}

// 高頻度で実行する共通のタスク
void commonTask()
{
    // 高度を取得する
    height = calculateHeightFromPressure(bth.read().pressure);

    // 光センサの値を取得する
    light = cds.read();
}

// 低頻度で実行する定期タスク
void commonTaskLowFreq()
{
    // 現在のフェーズを記録する
    switch (phase) {
        case LOADING:
            logger.debug(F("Phase: LOADING"));
            break;
        case LAUNCHING:
            logger.debug(F("Phase: LAUNCHING"));
            break;
        case DESCENDING:
            logger.debug(F("Phase: DESCENDING"));
            break;
        case LANDED:
            logger.debug(F("Phase: LANDED"));
            break;
        case FINISHED:
            logger.debug(F("Phase: FINISHED"));
            break;
    }

    // 高度を記録する
    logger.info(F("Height:"), height, F("[m]"));

    // 光センサの値を記録する
    logger.debug(F("Light:"), light);

    // 位置を取得して記録する
    logger.info(gps.read());
}

// LOADING フェーズのタスク
void loadingTask()
{
    int light_threshold = 30;    // 搭載されたと判断する明るさの閾値
    static bool loaded = false;  // 搭載されたかどうか

    // 明るさが閾値を下回ったら搭載されたと判断
    if (!loaded && light < light_threshold) {
        logger.info(F("Loaded"));
        loaded = true;
    }

    // 搭載後に高度が 10m 以上になったら打ち上げられたと判断
    if (loaded && height >= 10) {
        logger.info(F("Launched!"));
        phase = LAUNCHING;
    }
}

// LAUNCHING フェーズのタスク
void launchingTask()
{
    int light_threshold = 60;  // 放出されたと判断する明るさの閾値

    // 明るさが閾値を超えたら放出されたと判断
    if (light > light_threshold) {
        logger.info(F("Released!"));
        phase = DESCENDING;
    }
}

// DESCENDING フェーズのタスク
void descendingTask()
{
    float lid_open_height = 30;      // 蓋を開ける高度 [m]
    static bool lid_opened = false;  // 蓋が開いたかどうか

    // 目標高度に達したら蓋を開ける
    if (!lid_opened && height <= lid_open_height) {
        logger.info(F("Opening the lid"));
        servo.rotateTo(90);
        lid_opened = true;
    }

    // 10回以上連続で高度が 1.5m 未満になったら着陸したと判断
    static int count = 0;
    if (height <= 1.5) {
        count++;
    } else {
        count = 0;
    }
    if (count >= 10) {
        logger.info(F("Landed!"));
        phase = LANDED;
    }
}

// LANDED フェーズのタスク
void landedTask()
{
    // 10秒ごとに3回カメラで写真を撮る
    static unsigned long last_time_ms = 0;
    static int count = 0;
    unsigned long current_time_ms = millis();
    unsigned long interval_ms = 10000;
    if (current_time_ms - last_time_ms > interval_ms) {
        camera.takePictureAndSaveAs(String(current_time_ms) + ".jpg");
        last_time_ms = current_time_ms;
        count++;
    }
    if (count >= 3) {
        logger.info(F("Finished!"));
        phase = FINISHED;
    }
}
