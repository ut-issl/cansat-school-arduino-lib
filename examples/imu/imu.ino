#include <CanSatSchool.h>

IMU imu;

void setup()
{
    Computer::init(9600);

    // Wire(Arduino-I2C)の初期化
    Wire.begin();

    imu.init();

    delay(300);
}

void loop()
{
    imu.read().print();

    delay(1000);
}
