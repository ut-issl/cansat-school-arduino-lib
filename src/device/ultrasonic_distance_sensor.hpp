#pragma once

#include "sensor_base.hpp"

namespace Device
{

    class UltrasonicDistanceSensor : public SensorBase<float>
    {
      public:

        UltrasonicDistanceSensor(uint8_t trigger_pin, uint8_t echo_pin);
        UltrasonicDistanceSensor(uint8_t trigger_pin, uint8_t echo_pin, const float& temperature);
        ~UltrasonicDistanceSensor() = default;

        void init();
        float read() override;  // distance [m]

        void setMinRange(const float& min_range);  // [m]
        void setMaxRange(const float& max_range);  // [m]

        void setTemperature(const float& temperature);  // [°C]

      private:

        uint8_t trigger_pin_;
        uint8_t echo_pin_;

        float min_range_ = 0.04;  // [m]
        float max_range_ = 4.0;   // [m]

        float sound_speed_ = 0.342;  // [mm/µs]
    };

}  // namespace Device
