#include <CanSatSchool.h>

// GPS の TX ピンを指定
#define PIN_GPS_TX 8

// GPS を宣言
GPSReceiver gps{PIN_GPS_TX};

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // GPS を初期化
    gps.init();

    delay(300);
}

void loop()
{
    // GPS から取得した情報をシリアルモニタに表示
    gps.read().print();

    // GPS から取得した情報を変数に代入したい場合
    // float latitude = gps.read().lat;   // 緯度
    // float longitude = gps.read().lon;  // 経度
    // float altitude = gps.read().alt;   // 高度
    // uint16_t time = gps.read().time;   // 最後にデータを取得した時間

    // 1s 待つ
    delay(1000);
}
