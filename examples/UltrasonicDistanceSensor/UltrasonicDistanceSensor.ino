#include "UltrasonicDistanceSensor.h"

#define PIN_TRIGGER 9
#define PIN_ECHO 17

UltrasonicDistanceSensor distance_sensor{PIN_TRIGGER, PIN_ECHO};

void setup()
{
    Serial.begin(9600);
    while (!Serial) {
    }
    delay(1000);

    distance_sensor.init();
    delay(300);
}

void loop()
{
    Serial.println(distance_sensor.read());

    delay(1000);
}
