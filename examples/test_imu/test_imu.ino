#include <CanSatSchool.h>

// IMU の宣言
IMU imu;

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // Wire (Arduino-I2C) を初期化
    // IMU は I2C を使用するためこれが必要
    Wire.begin();

    // IMU を初期化
    imu.init();

    delay(500);
}

void loop()
{
    // IMU の値を取得してシリアルモニタに表示
    logger.info(imu.read());

    // 1s 待つ
    delay(1000);

    // IMU の値を取得して変数に代入したい場合
    // auto acc = imu.readAccel();  // 加速度
    // auto gyro = imu.readGyro();  // 角速度
    // auto mag = imu.readMag();    // 地磁気

    // 取得した値をシリアルモニタに表示
    // logger.info(F("Acc:"), acc);
    // logger.info(F("Gyro:"), gyro);
    // logger.info(F("Mag:"), mag);

    // 1s 待つ
    delay(1000);
}
