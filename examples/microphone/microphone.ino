#include <CanSatHighSchool.h>

#define PIN_MIC A2

Microphone microphone(PIN_MIC);

void setup()
{
    // Wire(Arduino-I2C)の初期化
    Wire.begin();
    // デバック用シリアル通信は9600bps
    Computer::init(9600);

    microphone.init();
    delay(300);
}

void loop()
{
    print(microphone.read());

    delay(1000);
}
