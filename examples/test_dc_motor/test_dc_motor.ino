#include <CanSatSchool.h>

// DCモーターの入力ピンを指定
#define PIN_DC_MOTER_1 5
#define PIN_DC_MOTER_2 6

// DCモーターを宣言
DCMotor dc_motor{PIN_DC_MOTER_1, PIN_DC_MOTER_2};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // DCモーターを初期化
    dc_motor.init();

    delay(500);
}

void loop()
{
    // 正転
    dc_motor.forward();
    delay(5000);

    // 空転
    dc_motor.free();
    delay(5000);

    // 逆転
    dc_motor.reverse();
    delay(5000);

    // 停止
    dc_motor.brake();
    delay(5000);
}
