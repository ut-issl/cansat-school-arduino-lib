#pragma once

#include <Wire.h>

#include "sensor_base.hpp"

namespace Device
{

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

        IMU();
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

        coordinate accel_offset_;
        coordinate gyro_offset_;
        coordinate mag_offset_;
    };

}  // namespace Device
