#include <CanSatSchool.h>

// DCモーターの入力ピンを指定
#define PIN_DC_MOTER_1 5
#define PIN_DC_MOTER_2 6

// DCモーターを宣言
DCMotor dc_motor{PIN_DC_MOTER_1, PIN_DC_MOTER_2};

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // DCモーターを初期化
    dc_motor.init();

    delay(300);
}

void loop()
{
    print(F("Forward"));
    dc_motor.forward();  // 正転
    delay(5000);

    print(F("Free"));
    dc_motor.free();  // 空転
    delay(5000);

    print(F("Reverse"));
    dc_motor.reverse();  // 逆転
    delay(5000);

    print(F("Brake"));
    dc_motor.brake();  // 停止
    delay(5000);
}
