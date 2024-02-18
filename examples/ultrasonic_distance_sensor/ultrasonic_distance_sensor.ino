#include <CanSatSchool.h>

// 超音波距離センサーのピンを指定
#define PIN_TRIGGER 9
#define PIN_ECHO 17

// 超音波距離センサーを宣言
UltrasonicDistanceSensor distance_sensor{PIN_TRIGGER, PIN_ECHO};

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // 超音波距離センサーを初期化
    distance_sensor.init();

    delay(300);
}

void loop()
{
    // 超音波距離センサーの値を取得してシリアルモニタに表示
    print(distance_sensor.read());

    // 超音波距離センサーの値を取得して変数に代入したい場合
    // float distance = distance_sensor.read();

    // 1s 待つ
    delay(1000);
}
