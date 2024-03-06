#include <CanSatSchool.h>

#include "port_config.h"

// 気圧・温湿度計を宣言
BaroThermoHygrometer bth;
// 光センサを宣言
CdS cds{PIN_CDS};
// 超音波距離センサーを宣言
UltrasonicDistanceSensor distance_sensor{PIN_USD_TRIGGER, PIN_USD_ECHO};
// IMU の宣言
IMU imu;
// マイクを宣言
Microphone microphone{PIN_MIC};
// GPS を宣言
GPSReceiver gps{PIN_GPS_TX};

// サーボモーターを宣言
ServoMotor servo{PIN_SERVO};
// DCモーターを宣言
DCMotor dc_motor{PIN_DC_MOTER_1, PIN_DC_MOTER_2};

// カメラを宣言
Camera camera{PIN_CAMERA_SS};

void setup()
{
    // ロガーを初期化
    logger.enableComputer();
    String file_name = "log.txt";  // 記録するファイル名
    logger.enableSDCard(file_name, PIN_SD_SS);
    logger.setDebug();

    // Wire (Arduino-I2C) を初期化
    Wire.begin();
    // SPI を初期化
    SPI.begin();

    // 気圧・温湿度計を初期化
    bth.init();
    // 光センサを初期化
    cds.init();
    // 超音波距離センサーを初期化
    distance_sensor.init();
    // IMU を初期化
    imu.init();
    // マイクを初期化
    microphone.init();
    // GPS を初期化
    gps.init();

    // サーボモーターを初期化
    servo.init();
    // DCモーターを初期化
    dc_motor.init();

    // カメラを初期化
    camera.init();

    delay(500);
}

void loop()
{
    // 気圧・温湿度計の値を取得して記録
    logger.info(F("[BaroThermoHygrometer]"), bth.read());
    delay(500);

    // 光センサの値を取得して記録
    logger.info(F("[CdS]"), cds.read());
    delay(500);

    // 超音波距離センサーの値を取得して記録
    logger.info(F("Distance:"), distance_sensor.read(), "[m]");
    delay(500);

    // IMU の値を取得して記録
    logger.info(F("[IMU]"), imu.read());
    delay(500);

    // マイクの値を取得して記録
    logger.info(microphone.read());
    delay(500);

    // GPS から取得した情報を記録
    logger.info(F("[GPSReceiver]"), gps.read());
    delay(500);

    // サーボモーターを動かす
    servo.rotateTo(1);  // 1度に回転
    delay(500);
    logger.info(F("[Servo]"), servo.read(), "[deg]");
    servo.rotateTo(90);  // 90度に回転
    delay(500);
    logger.info(F("[Servo]"), servo.read(), "[deg]");
    servo.rotateTo(180);  // 180度に回転
    delay(500);
    logger.info(F("[Servo]"), servo.read(), "[deg]");
    delay(500);

    // DCモーターを動かす
    dc_motor.forward();  // 正転
    delay(5000);
    dc_motor.free();  // 空転
    delay(5000);
    dc_motor.reverse();  // 逆転
    delay(5000);
    dc_motor.brake();  // 停止
    delay(500);

    // カメラで写真を撮影してSDカードに保存する
    camera.takePictureAndSaveAs(String(millis()) + ".jpg");
    delay(500);
}
