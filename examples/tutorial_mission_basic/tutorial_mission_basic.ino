// ミッション例：高度30mで蓋を開ける
// 使うデバイス：
// - 光センサ：放出されたかどうかを判断する（ピン A1）
// - 気圧・温湿度計：気圧を読んで高度を計算する（ピン A4, A5）
// - サーボモーター：蓋を開ける（ピン 4）


#include <CanSatSchool.h>

#define PIN_SERVO 4  // サーボモーターの入力ピン
#define PIN_CDS A1   // 光センサの出力ピン

// 気圧・温湿度計を宣言
BaroThermoHygrometer bth;
// 光センサを宣言
CdS cds{PIN_CDS};
// サーボモーターを宣言
ServoMotor servo{PIN_SERVO};


float altitude_at_ground;  // 地表の高度 [m]

// 気圧の差から海抜高度を計算する関数
float calculateAltitudeFromPressure(float pressure)
{
    float pressure_at_sea_level = 1013.250;  // 海抜 0m での大気圧 [hPa]

    float altitude = (pressure_at_sea_level - pressure) * 10;  // ざっくり 10m 上昇すると 1hPa 下がるとする
    return altitude;
}

void setup()
{
    // ロガーを初期化
    String file_name = "log.txt";  // 記録するファイル名
    logger.enableSDCard(file_name);
    // logger.setDebug();

    // Wire (Arduino-I2C) を初期化
    Wire.begin();

    // 気圧・温湿度計を初期化
    bth.init();
    // 光センサを初期化
    cds.init();
    // サーボモーターを初期化
    servo.init();

    // 蓋を閉じる
    servo.rotateTo(1);

    // 安定するまで待つ
    delay(10000);

    // キャリブレーションのためにセンサーを地表に置いておく
    logger.info("Calibrating sensors...");
    // 地表の気圧を取得する
    float pressure_at_ground = bth.read().pressure;
    logger.info("Pressure at ground:", pressure_at_ground, "[hPa]");
    // 地表の海抜高度を計算する
    altitude_at_ground = calculateAltitudeFromPressure(pressure_at_ground);
    logger.info("Altitude at ground:", altitude_at_ground, "[m]");
    logger.info("Calibration completed!");

    delay(10000);

    // CanSatをロケットに搭載するまで待つ
    logger.info("Waiting for loading to the rocket");
    int light_threshold = 30;  // 搭載されたと判断する明るさの閾値
    while (true) {
        // 光センサの値を読む
        int light = cds.read();
        logger.debug(F("Light:"), light);

        // 明るさが閾値を下回ったら搭載されたと判断
        if (light < light_threshold) {
            logger.info(F("Loaded"));
            break;
        }

        delay(100);
    }
}

void loop()
{
    // =========== 放出されるまで待つ ===========
    logger.info(F("Waiting for release"));
    int light_threshold = 60;  // 放出されたと判断する明るさの閾値
    while (true) {
        // 光センサの値を読む
        int light = cds.read();
        logger.debug(F("Light:"), light);

        // 明るさが閾値を超えたら放出されたと判断
        if (light > light_threshold) {
            logger.info(F("Released!"));
            break;
        }

        delay(100);
    }

    // =========== 30mまで降りる ===========
    logger.info(F("Waiting for descending to 30m"));
    float pressure;
    float height;
    while (true) {
        // 気圧を読む
        pressure = bth.read().pressure;
        // 気圧から高度を計算する
        height = calculateAltitudeFromPressure(pressure) - altitude_at_ground;
        // 高度を記録する
        logger.info(F("Height:"), height, F("[m]"));

        // 30mまで降りたかどうか判定
        if (height <= 30) {
            logger.info(F("Reached 30m"));
            break;
        }

        delay(100);
    }

    // =========== 蓋を開ける ===========
    logger.info(F("Opening the lid"));
    servo.rotateTo(90);

    // =========== 着陸するまで待つ ===========
    while (true) {
        // 気圧を読む
        pressure = bth.read().pressure;
        // 気圧から高度を計算する
        height = calculateAltitudeFromPressure(pressure) - altitude_at_ground;
        // 高度を記録する
        logger.info(F("Height:"), height, F("[m]"));

        // 高度が 50cm 以下になったら着陸したと判断
        if (height <= 0.5) {
            logger.info(F("Landed!"));
            break;
        }

        delay(100);
    }

    // =========== 終了 ===========
    logger.info(F("Mission completed!"));
    while (true) {
        delay(1000);
    }
}
