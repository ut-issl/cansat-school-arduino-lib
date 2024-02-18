#include <CanSatSchool.h>

#define PIN_GPS_TX 8

GPSReceiver gps{PIN_GPS_TX};

void setup()
{
    Computer::init(9600);

    gps.init();

    delay(300);
}

void loop()
{
    // GPSから取得した情報をシリアルモニタに表示
    gps.read().print();

    delay(1000);
}
