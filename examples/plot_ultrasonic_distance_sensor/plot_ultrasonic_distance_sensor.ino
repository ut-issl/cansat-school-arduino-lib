#include <CanSatSchool.h>

// 超音波距離センサーのピンを指定
#define PIN_USD_TRIGGER 9
#define PIN_USD_ECHO 17

// 超音波距離センサーを宣言
UltrasonicDistanceSensor distance_sensor{PIN_USD_TRIGGER, PIN_USD_ECHO};

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // 超音波距離センサーを初期化
    distance_sensor.init();

    // 温度を設定する場合
    // 距離の計算時に使う音速の値を設定した温度基準に合わせることができる
    // distance_sensor.setTemperature(20);

    delay(500);
}

void loop()
{
    // 超音波距離センサーの値を取得して変数に代入
    float distance = distance_sensor.read();  // [m]

    // 取得した値をシリアルプロッタに表示
    print(distance);

    // 1s 待つ
    delay(1000);
}
