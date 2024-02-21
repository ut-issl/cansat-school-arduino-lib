#include <CanSatSchool.h>

// 超音波距離センサーのピンを指定
#define PIN_TRIGGER 9
#define PIN_ECHO 17

// 超音波距離センサーを宣言
UltrasonicDistanceSensor distance_sensor{PIN_TRIGGER, PIN_ECHO};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // 超音波距離センサーを初期化
    distance_sensor.init();

    // 温度を設定する場合
    // 距離の計算時に使う音速の値を設定した温度基準に合わせることができる
    // distance_sensor.setTemperature(20);

    delay(500);
}

void loop()
{
    // 超音波距離センサーの値を取得してシリアルモニタに表示
    logger.info(distance_sensor.read(), "[m]");

    // 超音波距離センサーの値を取得して変数に代入したい場合
    // float distance = distance_sensor.read();  // [m]

    // 1s 待つ
    delay(1000);
}
