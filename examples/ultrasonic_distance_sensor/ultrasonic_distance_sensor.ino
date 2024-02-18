#include <CanSatSchool.h>

#define PIN_TRIGGER 9
#define PIN_ECHO 17

UltrasonicDistanceSensor distance_sensor{PIN_TRIGGER, PIN_ECHO};

void setup()
{
    Computer::init(9600);

    distance_sensor.init();

    delay(300);
}

void loop()
{
    print(distance_sensor.read());

    delay(1000);
}
