#include <CanSatSchool.h>

// 超音波距離センサーのピンを指定
#define PIN_USD_TRIGGER 9
#define PIN_USD_ECHO 17

// 超音波距離センサーを宣言
UltrasonicDistanceSensor distance_sensor{PIN_USD_TRIGGER, PIN_USD_ECHO};

// 気圧・温湿度計を宣言
BaroThermoHygrometer bth;

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // Wire (Arduino-I2C) を初期化
    Wire.begin();

    // 超音波距離センサーを初期化
    distance_sensor.init();

    // 気圧・温湿度計を初期化
    bth.init();

    // 1s 待つ
    delay(1000);

    // 温度を取得
    float temperature = bth.read().temperature;
    logger.info("Temperature:", temperature, "°C");
    // 超音波センサーに温度を設定
    distance_sensor.setTemperature(temperature);

    delay(500);
}

void loop()
{
    // 超音波距離センサーの値を取得してシリアルモニタに表示
    // このようなフォーマットで出力することで，シリアルプロッタでグラフを描画することもできる
    print("Distance:", distance_sensor.read());

    // 1s 待つ
    delay(500);
}
