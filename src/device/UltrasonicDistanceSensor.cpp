#include "UltrasonicDistanceSensor.h"

UltrasonicDistanceSensor::UltrasonicDistanceSensor(const uint8_t& trigger_pin, const uint8_t& echo_pin)
    : trigger_pin_{trigger_pin}, echo_pin_{echo_pin}
{
}

UltrasonicDistanceSensor::UltrasonicDistanceSensor(const uint8_t& trigger_pin, const uint8_t& echo_pin, const float& temperature)
    : trigger_pin_{trigger_pin}, echo_pin_{echo_pin}, sound_speed_{0.020068 * sqrt(temperature + 273.15)}
{
}

void UltrasonicDistanceSensor::init() const
{
    pinMode(trigger_pin_, OUTPUT);
    pinMode(echo_pin_, INPUT);
}

float UltrasonicDistanceSensor::read() const
{
    digitalWrite(trigger_pin_, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin_, LOW);

    float distance = (pulseIn(echo_pin_, HIGH) / 2) * sound_speed_;
    if (distance > min_range_ && distance < max_range_) {
        return distance;
    } else {
        return -1;
    }
}

float UltrasonicDistanceSensor::operator()() const
{
    return this->read();
}

void UltrasonicDistanceSensor::setMinRange(const float& min_range)
{
    min_range_ = min_range;
}

void UltrasonicDistanceSensor::setMaxRange(const float& max_range)
{
    max_range_ = max_range;
}
