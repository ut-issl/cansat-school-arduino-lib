#include <CanSatSchool.h>

// 光センサの出力ピンを指定
#define PIN_CDS A1

// 光センサを宣言
CdS cds{PIN_CDS};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // Wire (Arduino-I2C) を初期化
    // 光センサは I2C を使用するためこれが必要
    Wire.begin();

    // 光センサを初期化
    cds.init();

    delay(500);
}

void loop()
{
    // 光センサの値を取得してシリアルモニタに表示
    // 明るさが 0 ~ 100 の値で表示される
    logger.info(cds.read());

    // 光センサの値を取得して変数に代入したい場合
    // int cds_value = cds.read();  // 明るさ [0 ~ 100]

    // 1s 待つ
    delay(1000);
}
