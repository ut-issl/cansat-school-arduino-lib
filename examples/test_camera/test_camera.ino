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

    // 画像のサイズを変えたい場合
    // OV2640_160x120    // 160x120
    // OV2640_176x144    // 176x144
    // OV2640_320x240    // 320x240（デフォルト）
    // OV2640_352x288    // 352x288
    // OV2640_640x480    // 640x480
    // OV2640_800x600    // 800x600
    // OV2640_1024x768   // 1024x768
    // OV2640_1280x1024  // 1280x1024
    // OV2640_1600x1200  // 1600x1200
    // camera.setSize(OV2640_640x480);

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
