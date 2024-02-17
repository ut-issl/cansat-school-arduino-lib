#pragma once

#include "sensor_base.hpp"

namespace Device
{

    class Microphone : public SensorBase<int>
    {
      public:

        Microphone(const uint8_t& input_pin);
        ~Microphone() = default;

        void init();
        int read() override;

      private:

        int input_pin_;

        uint8_t sampling_num_ = 10;
        uint32_t median_ = 512;
    };

}  // namespace Device