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

    delay(500);
}

void loop()
{
    // GPS から取得した情報を変数に代入
    auto gps_data = gps.read();
    float latitude = gps_data.lat;   // 緯度 [°]
    float longitude = gps_data.lon;  // 経度 [°]
    float altitude = gps_data.alt;   // 高度 [m]
    uint16_t time = gps_data.time;   // 最後にデータを取得した時間 [s]

    // 取得した値をシリアルプロッタに表示
    print(latitude, longitude, altitude, time);

    // 1s 待つ
    delay(1000);
}
