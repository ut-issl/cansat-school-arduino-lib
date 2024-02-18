#include <CanSatSchool.h>

// 気圧・温湿度計を宣言
BaroThermoHygrometer bth;

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
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // Wire (Arduino-I2C) を初期化
    Wire.begin();

    // 気圧・温湿度計を初期化
    bth.init();

    // 安定するまで待つ
    delay(10000);

    // キャリブレーションのためにセンサーを地表に置いておく
    // 地表の気圧を取得する
    float pressure_at_ground = bth.read().pressure;
    print("Pressure at ground:", pressure_at_ground, "hPa");
    // 地表の海抜高度を計算する
    altitude_at_ground = calculateAltitudeFromPressure(pressure_at_ground);
    print("Altitude at ground:", altitude_at_ground, "m\n");
}

void loop()
{
    // 気圧を取得する
    float pressure = bth.read().pressure;
    print("Pressure:", pressure, "hPa");

    // 気圧から絶対高度を計算する
    float absolute_altitude = calculateAltitudeFromPressure(pressure);
    print("Absolute altitude:", absolute_altitude, "m");

    // 地表の海抜高度を引いて相対高度を計算する
    float relative_altitude = absolute_altitude - altitude_at_ground;
    print("Relative altitude:", relative_altitude, "m\n");

    // 1s 待つ
    delay(1000);
}
