#include "microphone.hpp"

#include "computer.hpp"

namespace Device
{

    Microphone::Microphone(const uint8_t& input_pin)
        : input_pin_(input_pin)
    {
    }

    void Microphone::init()
    {
        pinMode(input_pin_, INPUT);

        print(F("Init Microphone"));
    }

    int Microphone::read()
    {
        uint32_t sum = 0;
        for (int8_t i = 0; i < sampling_num_; ++i) {
            uint32_t value = abs(analogRead(input_pin_) - median_);
            sum += value;
        }
        uint8_t average = sum / sampling_num_;
        return average;
    }

}  // namespace Device
