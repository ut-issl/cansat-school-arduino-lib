#include "ultrasonic_distance_sensor.hpp"

#include "../utility/logger.hpp"

namespace Device
{

    UltrasonicDistanceSensor::UltrasonicDistanceSensor(uint8_t trigger_pin, uint8_t echo_pin)
        : trigger_pin_{trigger_pin}, echo_pin_{echo_pin}
    {
    }

    UltrasonicDistanceSensor::UltrasonicDistanceSensor(uint8_t trigger_pin, uint8_t echo_pin, const float& temperature)
        : trigger_pin_{trigger_pin}, echo_pin_{echo_pin}, sound_speed_{0.020068 * sqrt(temperature + 273.15)}
    {
    }

    void UltrasonicDistanceSensor::init()
    {
        Utility::logger.info(F("[UltrasonicDistanceSensor] Initializing..."));

        pinMode(trigger_pin_, OUTPUT);
        pinMode(echo_pin_, INPUT);

        Utility::logger.info(F("[UltrasonicDistanceSensor] Initialized"));
    }

    float UltrasonicDistanceSensor::read()
    {
        digitalWrite(trigger_pin_, LOW);
        delayMicroseconds(2);
        digitalWrite(trigger_pin_, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger_pin_, LOW);

        float distance = (pulseIn(echo_pin_, HIGH) / 2) * sound_speed_ / 1e3;
        if (distance > min_range_ && distance < max_range_) {
            return distance;
        } else {
            return -1;
        }
    }

    void UltrasonicDistanceSensor::setMinRange(const float& min_range)
    {
        min_range_ = min_range;
        Utility::logger.info(F("[UltrasonicDistanceSensor] Set min range to"), min_range_, F("[m]"));
    }

    void UltrasonicDistanceSensor::setMaxRange(const float& max_range)
    {
        max_range_ = max_range;
        Utility::logger.info(F("[UltrasonicDistanceSensor] Set max range to"), max_range_, F("[m]"));
    }

    void UltrasonicDistanceSensor::setTemperature(const float& temperature)
    {
        sound_speed_ = 0.020068 * sqrt(temperature + 273.15);
        Utility::logger.info(F("[UltrasonicDistanceSensor] Update sound speed to"), sound_speed_ * 1e3, F("[m/s]"));
    }

}  // namespace Device
