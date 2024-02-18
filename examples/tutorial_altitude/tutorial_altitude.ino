#include <CanSatSchool.h>

// 気圧/温度/湿度センサを定義
BaroThermoHygrometer bth;

float altitude_at_ground;  // 地表の標高 [m]

// 気圧の差から海抜高度を計算する関数
float calculateAltitudeFromPressure(float pressure)
{
    float pressure_at_sea_level = 1013.250;  // 海抜 0m での大気圧 [hPa]

    float altitude = (pressure_at_sea_level - pressure) * 10;  // ざっくり 10m 上昇すると 1hPa 下がるとする
    return altitude;
}

void setup()
{
    Computer::init(9600);

    // Wire(Arduino-I2C)の初期化
    Wire.begin();

    // 気圧/温度/湿度センサの初期化
    bth.init();

    // 安定するまで待つ
    delay(10000);

    float pressure_at_ground = bth.read().pressure;
    altitude_at_ground = calculateAltitudeFromPressure(pressure_at_ground);
    print("Pressure at ground:", pressure_at_ground, "hPa");
    print("Altitude at ground:", altitude_at_ground, "m\n");
}

void loop()
{
    float pressure = bth.read().pressure;
    print("Pressure:", pressure, "hPa");

    float altitude = calculateAltitudeFromPressure(pressure);
    float relative_altitude = altitude - altitude_at_ground;
    print("Altitude:", altitude, "m");
    print("Relative Altitude:", relative_altitude, "m\n");

    // 1s 待つ
    delay(1000);
}
