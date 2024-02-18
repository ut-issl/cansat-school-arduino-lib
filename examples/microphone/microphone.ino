#include <CanSatSchool.h>

#define PIN_MIC A2

Microphone microphone(PIN_MIC);

void setup()
{
    Computer::init(9600);

    // Wire(Arduino-I2C)の初期化
    Wire.begin();

    microphone.init();

    delay(300);
}

void loop()
{
    print(microphone.read());

    delay(1000);
}
