#include <CanSatHighSchool.h>

BaroThermoHygrometer bth;

void setup()
{
    // デバック用シリアル通信は9600bps
    Computer::init(9600);

    bth.init();
    delay(300);
}

void loop()
{
    bth.read().print();

    delay(1000);  // 1000 ms 待つ
}
