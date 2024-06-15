#include <CanSatSchool.h>

// 気圧・温湿度計を宣言
BaroThermoHygrometer bth;

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // Wire (Arduino-I2C) を初期化
    // 気圧・温湿度計は I2C を使用するためこれが必要
    Wire.begin();

    // 気圧・温湿度計を初期化
    bth.init();

    delay(500);
}

void loop()
{
    // 気圧を取得して変数に代入
    float pressure = bth.read().pressure;  // [hPa]

    // 温度を取得して変数に代入
    float temperature = bth.read().temperature;  // [°C]

    // 湿度を取得して変数に代入
    float humidity = bth.read().humidity;  // [%]

    // 取得した値をシリアルプロッタに表示
    print(F("Pressure:"), pressure, F(" Temperature:"), temperature, F("Humidity:"), humidity);

    // 1s 待つ
    delay(1000);
}
