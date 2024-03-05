#pragma once

#include <CanSatSchool.h>

#include "port_config.hpp"

// 気圧・温湿度計を宣言
BaroThermoHygrometer bth;
// 光センサを宣言
CdS cds{PIN_CDS};
// GPS を宣言
GPSReceiver gps{PIN_GPS_TX};

// サーボモーターを宣言
ServoMotor servo{PIN_SERVO};

// カメラを宣言
Camera camera{PIN_CAMERA_SS};

void initDevice()
{
    // Wire (Arduino-I2C) を初期化
    Wire.begin();
    // SPI を初期化
    SPI.begin();

    // 気圧・温湿度計を初期化
    bth.init();
    // 光センサを初期化
    cds.init();
    // GPS を初期化
    gps.init();

    // サーボモーターを初期化
    servo.init();

    // カメラを初期化
    camera.init();
}
