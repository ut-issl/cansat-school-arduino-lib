#include <CanSatSchool.h>

// SDカードの SS ピンを指定する場合
// デフォルトで10に設定されているため，変更する場合のみ記述すればよい
// #define PIN_SD_SS 9

void setup()
{
    // ロガーを初期化

    // パソコンへの出力を有効化する（パソコンを使わない場合は不要）
    logger.enableComputer();

    // SDカードへのログ記録を有効化する（SDカードを使わない場合は不要）
    String file_name = "log.txt";  // 記録するファイル名
    logger.enableSDCard(file_name);
    // logger.enableSDCard(file_name, PIN_SD_SS);  // SDカードの SS ピンを指定する場合

    // デバッグ出力を有効化したい場合
    // logger.setDebug();

    delay(500);
}

void loop()
{
    // 通常のメッセージ
    logger.info(F("Hello, World!"));

    delay(1000);

    // エラーメッセージ
    logger.error(F("This is an error message."));

    delay(1000);

    // ワーニングメッセージ
    logger.warning(F("This is a warning message."));

    delay(1000);

    // デバッグメッセージ
    // 有効化した場合のみ出力される
    logger.debug(F("This is a debug message."));

    delay(1000);

    // メッセージに数値を含める
    logger.info(F("This is a message with a number:"), 123);

    delay(1000);

    // 変数を用いる
    int value = 456;
    String message = F("This is a message with a variable:");
    logger.info(message, value);

    delay(1000);

    float pi = 3.14;
    logger.info(F("pi ="), pi, F("..."));

    delay(1000);

    logger.info(F("End of program."));
    while (true) {
        // プログラム終了
    }
}
