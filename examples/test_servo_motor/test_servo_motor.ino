#include <CanSatSchool.h>

// サーボモーターの入力ピンを指定
#define PIN_SERVO 4

// サーボモーターを宣言
ServoMotor servo{PIN_SERVO};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // サーボモーターを初期化
    servo.init();

    delay(500);
}

void loop()
{
    // サーボモーターを1度に回転
    // 角度は1度から180度まで指定できる
    // 1度未満の角度を指定すると1度に，180度より大きな角度を指定すると180度になる
    servo.rotateTo(1);
    // 500ms 待つ
    delay(500);
    // サーボモーターの角度を取得してシリアルモニタに表示
    logger.info(servo.read(), "[deg]");

    // サーボモーターを90度に回転
    servo.rotateTo(90);
    // 500ms 待つ
    delay(500);
    // サーボモーターの角度を取得してシリアルモニタに表示
    logger.info(servo.read(), "[deg]");

    // サーボモーターを180度に回転
    servo.rotateTo(180);
    // 500ms 待つ
    delay(500);
    // サーボモーターの角度を取得してシリアルモニタに表示
    logger.info(servo.read(), "[deg]");

    // 1s 待つ
    delay(1000);
}
