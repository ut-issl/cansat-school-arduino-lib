#include <CanSatSchool.h>

// 光センサの出力ピンを指定
#define PIN_CDS A1

// 光センサを宣言
CdS cds(PIN_CDS);

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // Wire (Arduino-I2C) を初期化
    // 光センサは I2C を使用するためこれが必要
    Wire.begin();

    // 光センサを初期化
    cds.init();

    delay(300);
}

void loop()
{
    // 光センサの値を取得してシリアルモニタに表示
    print(cds.read());

    // 1s 待つ
    delay(1000);
}
