#include <CanSatSchool.h>

// サーボモーターの入力ピンを指定
#define PIN_SERVO 4

// サーボモーターを宣言
ServoMotor servo{PIN_SERVO};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();
    // logger.setDebug();  // デバッグ出力を有効にする

    // サーボモーターを初期化
    servo.init();

    delay(500);
}

void loop()
{
    static uint16_t loop_count = 0;
    logger.debug(F("Loop count:"), loop_count);

    // カウンターが 10 の倍数のとき
    if (loop_count % 10 == 0) {
        logger.info(F("Move Up!"));
        // 1度から180度まで 30度ずつ回転
        for (uint8_t angle = 0; angle <= 180; angle += 30) {
            // サーボモーターを指定した角度に回転
            servo.rotateTo(angle);  // 0度のときは1度になる
            delay(100);
            // サーボモーターの角度を取得してシリアルモニタに表示
            logger.info(F("Angle:"), servo.read(), F("[deg]"));
            delay(500);
        }
    }

    // カウンターが 10 の倍数 + 5 のとき
    if (loop_count % 10 == 5) {
        logger.info(F("Move Down!"));
        // 180度から1度まで 1度ずつ回転
        for (uint8_t angle = 180; angle > 0; --angle) {
            // サーボモーターを指定した角度に回転
            servo.rotateTo(angle);
            // サーボモーターの角度を取得してシリアルモニタに表示
            logger.debug(F("Angle:"), servo.read(), F("[deg]"));
            delay(10);
        }
    }

    // カウンターをインクリメント
    ++loop_count;

    // 1s 待つ
    delay(1000);
}
