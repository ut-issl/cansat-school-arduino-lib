#include "microphone.hpp"

#include "../utility/printer.hpp"

namespace Device
{

    Microphone::Microphone(uint8_t output_pin)
        : output_pin_(output_pin)
    {
    }

    void Microphone::init()
    {
        Utility::print(F("[Microphone] Initializing..."));

        pinMode(output_pin_, INPUT);

        Utility::print(F("[Microphone] Initialized"));
    }

    int Microphone::read()
    {
        uint32_t sum = 0;
        for (int8_t i = 0; i < sampling_num_; ++i) {
            uint32_t value = abs(analogRead(output_pin_) - median_);
            sum += value;
        }
        uint8_t average = sum / sampling_num_;
        return average;
    }

}  // namespace Device
