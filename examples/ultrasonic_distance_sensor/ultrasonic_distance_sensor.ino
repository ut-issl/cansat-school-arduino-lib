#include <CanSatHighSchool.h>

#define PIN_TRIGGER 9
#define PIN_ECHO 17

UltrasonicDistanceSensor distance_sensor{PIN_TRIGGER, PIN_ECHO};

void setup()
{
    // デバック用シリアル通信は9600bps
    Computer::init(9600);

    distance_sensor.init();
    delay(300);
}

void loop()
{
    print(distance_sensor.read());

    delay(1000);
}
