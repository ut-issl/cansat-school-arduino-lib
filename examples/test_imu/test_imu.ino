#include <CanSatSchool.h>

// IMU の宣言
IMU imu;

void setup()
{
    // シリアル通信 (Arduino-PC) の初期化
    Computer::init(9600);

    // Wire (Arduino-I2C) を初期化
    // IMU は I2C を使用するためこれが必要
    Wire.begin();

    // IMU の初期化
    imu.init();

    delay(500);
}

void loop()
{
    // IMU の値を取得してシリアルモニタに表示
    imu.read().print();

    // 1s 待つ
    delay(1000);

    // IMU の値を取得して変数に代入したい場合
    // auto acc = imu.readAccel();  // 加速度
    // auto gyro = imu.readGyro();  // 角速度
    // auto mag = imu.readMag();    // 地磁気

    // 取得した値をシリアルモニタに表示
    // print(F("Accel:"), acc.x, F(","), acc.y, F(","), acc.z);
    // print(F("Gyro:"), gyro.x, F(","), gyro.y, F(","), gyro.z);
    // print(F("Mag:"), mag.x, F(","), mag.y, F(","), mag.z);

    // 1s 待つ
    delay(1000);
}
