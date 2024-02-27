#pragma once

#include "sensor_base.hpp"

namespace Device
{

    class CdS : public SensorBase<uint16_t>
    {
      public:

        CdS(uint8_t output_pin);
        ~CdS() = default;

        void init();
        uint16_t read() override;

      private:

        uint8_t output_pin_;
    };

}  // namespace Device
