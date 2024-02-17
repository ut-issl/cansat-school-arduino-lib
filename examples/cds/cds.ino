#include <CanSatHighSchool.h>

#define PIN_CDS A1

CdS cds(PIN_CDS);

void setup()
{
    // Wire(Arduino-I2C)の初期化
    Wire.begin();
    // デバック用シリアル通信は9600bps
    Computer::init(9600);

    cds.init();
    delay(300);
}

void loop()
{
    print(cds.read());

    delay(1000);
}
