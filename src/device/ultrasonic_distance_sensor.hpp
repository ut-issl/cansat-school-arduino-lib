#pragma once

#include "sensor_base.hpp"

namespace Device
{

    class UltrasonicDistanceSensor : public SensorBase<float>
    {
      public:

        UltrasonicDistanceSensor(const uint8_t& trigger_pin, const uint8_t& echo_pin);
        UltrasonicDistanceSensor(const uint8_t& trigger_pin, const uint8_t& echo_pin, const float& temperature);
        ~UltrasonicDistanceSensor() = default;

        void init() const;
        float read() const override;

        void setMinRange(const float& min_range);
        void setMaxRange(const float& max_range);

      private:

        uint8_t trigger_pin_;
        uint8_t echo_pin_;

        float min_range_ = 40;    // [mm]
        float max_range_ = 4000;  // [mm]

        float sound_speed_ = 0.342;  // [mm/µs]
    };

}  // namespace Device
