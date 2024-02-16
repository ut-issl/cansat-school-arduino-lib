#pragma once

#include <Wire.h>

#include "sensor_base.hpp"

namespace Device
{

    struct BaroThermoHygrometer_t
    {
        float pressure;
        float temperature;
        float humidity;
    };

    class BaroThermoHygrometer : public SensorBase<BaroThermoHygrometer_t>
    {
      public:

        BaroThermoHygrometer();
        ~BaroThermoHygrometer() = default;

        void init();
        BaroThermoHygrometer_t read();

      private:

        uint32_t compensate_p_(int32_t adc_p);
        int32_t compensate_t_(int32_t adc_t);
        uint32_t compensate_h_(int32_t adc_h);

        // 気圧補正データ
        uint16_t dig_p1_;
        int16_t dig_p2_;
        int16_t dig_p3_;
        int16_t dig_p4_;
        int16_t dig_p5_;
        int16_t dig_p6_;
        int16_t dig_p7_;
        int16_t dig_p8_;
        int16_t dig_p9_;

        // 温度補正データ
        uint16_t dig_t1_;
        int16_t dig_t2_;
        int16_t dig_t3_;

        // 湿度補正データ
        uint8_t dig_h1_;
        int16_t dig_h2_;
        uint8_t dig_h3_;
        int16_t dig_h4_;
        int16_t dig_h5_;
        int8_t dig_h6_;

        int32_t t_fine_;

        unsigned char buffer_[26];
    };

}  // namespace Device
