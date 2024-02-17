#include <CanSatHighSchool.h>

#define PIN_DC_MOTER_1 5
#define PIN_DC_MOTER_2 6

DCMotor dc_motor{PIN_DC_MOTER_1, PIN_DC_MOTER_2};

void setup()
{
    Computer::init(9600);

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
