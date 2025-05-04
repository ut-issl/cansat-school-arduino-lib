#pragma once

#include <Wire.h>

#include "sensor_base.hpp"

// BMX055 加速度センサのI2Cアドレス
#define BMX055_ADDR_ACCL 0x19  // (JP1,JP2,JP3 = Openの時)
// BMX055 ジャイロセンサのI2Cアドレス
#define BMX055_ADDR_GYRO 0x69  // (JP1,JP2,JP3 = Openの時)
// BMX055 磁気センサのI2Cアドレス
#define BMX055_ADDR_MAG 0x13  // (JP1,JP2,JP3 = Openの時)

// BNO055のI2Cアドレス
#define BNO055_ADDR         0x28  // (COM3_STATEがLOWの時)
#define BNO055_OPR_MODE     0x3D
#define BNO055_UNIT_SEL     0x3B
#define BNO055_PWR_MODE     0x3E
#define BNO055_SYS_TRIGGER  0x3F

// 各種データレジスタ（16bit, LSB→MSB）
#define BNO055_ACCEL_DATA   0x08
#define BNO055_GYRO_DATA    0x14
#define BNO055_MAG_DATA     0x0E

namespace Device
{

    enum IMUType
    {
        BMX055 = 0,
        BNO055,
    };

    struct coordinate
    {
        float x;
        float y;
        float z;
    };

    struct IMU_t
    {
        coordinate acc;
        coordinate gyro;
        coordinate mag;
    };

    class IMU : public SensorBase<IMU_t>
    {
      public:

        IMU(IMUType type = BMX055);
        ~IMU() = default;

        void init(TwoWire* i2c = &Wire);
        IMU_t read() override;
        coordinate readAccel() const;
        coordinate readGyro() const;
        coordinate readMag() const;

        void setAccelOffset(const coordinate& offset);
        void setAccelOffset(float x, float y, float z);
        void setGyroOffset(const coordinate& offset);
        void setGyroOffset(float x, float y, float z);
        void setMagOffset(const coordinate& offset);
        void setMagOffset(float x, float y, float z);

      private:

        IMUType type_;
        coordinate accel_offset_;
        coordinate gyro_offset_;
        coordinate mag_offset_;

        void initBMX055_();
        void initBNO055_();
    };

}  // namespace Device
