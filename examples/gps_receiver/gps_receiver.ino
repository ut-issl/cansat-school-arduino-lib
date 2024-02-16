#include <CanSatHighSchool.h>

#define PIN_GPS_TX 8
#define PIN_GPS_RX 9

GPSReceiver gps{PIN_GPS_TX, PIN_GPS_RX};

void setup()
{
    // デバック用シリアル通信は9600bps
    Computer::init(9600);

    gps.init();
    delay(300);
}

void loop()
{
    gps.read().print();

    delay(1000);
}
