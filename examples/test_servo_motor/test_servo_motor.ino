#include <CanSatSchool.h>

// サーボモーターの入力ピンを指定
#define PIN_SERVO 4

// サーボモーターを宣言
ServoMotor servo{PIN_SERVO};

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // サーボモーターを初期化
    servo.init();

    delay(300);
}

void loop()
{
    // サーボモーターを1度に回転
    // 角度は1度から180度まで指定できる
    servo.rotateTo(1);
    // 500ms 待つ
    delay(500);
    // サーボモーターの角度を取得してシリアルモニタに表示
    print(servo.read());

    // サーボモーターを90度に回転
    servo.rotateTo(90);
    // 500ms 待つ
    delay(500);
    // サーボモーターの角度を取得してシリアルモニタに表示
    print(servo.read());

    // サーボモーターを180度に回転
    servo.rotateTo(180);
    // 500ms 待つ
    delay(500);
    // サーボモーターの角度を取得してシリアルモニタに表示
    print(servo.read());

    // 1s 待つ
    delay(1000);
}
