#include <CanSatHighSchool.h>

BaroThermoHygrometer bth;

void setup()
{
    Computer::init(9600);

    // Wire(Arduino-I2C)の初期化
    Wire.begin();

    bth.init();

    delay(300);
}

void loop()
{
    // 気圧、温度、湿度を取得してシリアルモニタに表示
    bth.read().print();

    delay(1000);  // 1000 ms 待つ
}
