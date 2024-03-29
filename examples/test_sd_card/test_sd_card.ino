#include <CanSatSchool.h>

// SDカードの SS ピンを指定
#define PIN_SD_SS 10

// 出力先のファイル名を設定
String file_name = "log.txt";

void setup()
{
    // ロガーを初期化
    logger.enableComputer();

    // SDカードを初期化
    SDCard::init(PIN_SD_SS);

    delay(500);
}

void loop()
{
    // 現在のミリ秒をSDカードに書き込む
    SDCard::write(file_name, String(millis()));

    // 1s 待つ
    delay(1000);
}
