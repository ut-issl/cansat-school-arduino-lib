#include <CanSatHighSchool.h>

#define PIN_CDS A1

CdS cds(PIN_CDS);

void setup()
{
    Computer::init(9600);

    // Wire(Arduino-I2C)の初期化
    Wire.begin();

    cds.init();

    delay(300);
}

void loop()
{
    print(cds.read());

    delay(1000);
}
