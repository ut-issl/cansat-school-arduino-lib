#include <CanSatSchool.h>

// カメラの SS ピンを指定
#define PIN_CAMERA_SS 7
// SDカードの SS ピンを指定
#define PIN_SD_SS 10

// カメラを宣言
Camera camera{PIN_CAMERA_SS};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();
    // logger.enableSDCard(file_name);  // ロガーを使用してもよい

    // Wire (Arduino-I2C) を初期化
    // カメラは I2C を使用するためこれが必要
    Wire.begin();

    // SPI を初期化
    // カメラは SPI を使用するためこれが必要
    SPI.begin();

    // SDカードを初期化
    // 撮影した画像を保存するためにSDカードを利用する
    SDCard::init(PIN_SD_SS);

    // カメラを初期化
    camera.init();

    delay(500);
}

void loop()
{
    // カメラで写真を撮影してSDカードに保存する
    // ファイル名は撮影時のミリ秒に指定
    camera.takePictureAndSaveAs(String(millis()) + ".jpg");

    // 10s 待つ
    delay(10000);
}
