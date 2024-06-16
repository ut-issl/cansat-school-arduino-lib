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

    // IMU の値を取得して変数に代入したい場合
    // auto acc = imu.readAccel();  // 加速度
    // auto gyro = imu.readGyro();  // 角速度
    // auto mag = imu.readMag();    // 地磁気

    // x, y, z それぞれの値を取り出したい場合
    // float acc_x = acc.x;  // 加速度 x 方向
    // float acc_y = acc.y;  // 加速度 y 方向
    // float acc_z = acc.z;  // 加速度 z 方向
    // float gyro_x = gyro.x;  // 角速度 x 方向
    // float gyro_y = gyro.y;  // 角速度 y 方向
    // float gyro_z = gyro.z;  // 角速度 z 方向
    // float mag_x = mag.x;    // 地磁気 x 方向
    // float mag_y = mag.y;    // 地磁気 y 方向
    // float mag_z = mag.z;    // 地磁気 z 方向

    // 1s 待つ
    delay(1000);
}
