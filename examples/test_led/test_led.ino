#include <CanSatSchool.h>

// LEDの出力ピンを指定
#define PIN_LED 20

// LEDを宣言
Led led{PIN_LED};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // LEDを初期化
    led.init();

    delay(500);
}

void loop()
{
    // LEDを点灯
    led.on();

    // 1s 待つ
    delay(1000);

    // LEDを消灯
    led.off();

    // 1s 待つ
    delay(1000);
}
