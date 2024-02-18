#include <CanSatSchool.h>

#define PIN_SERVO 4

ServoMotor servo{PIN_SERVO};

void setup()
{
    Computer::init(9600);

    servo.init();

    delay(300);
}

void loop()
{
    static uint16_t loop_count = 0;

    if (loop_count % 10 == 0) {
        print(F("Move Up!"));
        for (uint8_t pos = 1; pos <= 180; pos += 30) {
            servo.rotateTo(pos);
            delay(100);
            print(F("pos:"), servo.read());
            delay(500);
        }
    }
    if (loop_count % 10 == 5) {
        print(F("Move Down!"));
        for (uint8_t pos = 180; pos > 0; --pos) {
            servo.rotateTo(pos);
            print(F("pos:"), servo.read());
            delay(10);
        }
    }

    ++loop_count;
    delay(1000);
}
