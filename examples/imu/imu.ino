#include <CanSatHighSchool.h>

IMU imu;

void setup()
{
    // Wire(Arduino-I2C)の初期化
    Wire.begin();
    // デバック用シリアル通信は9600bps
    Computer::init(9600);

    imu.init();
    delay(300);
}

void loop()
{
    imu.read().print();

    delay(1000);
}
