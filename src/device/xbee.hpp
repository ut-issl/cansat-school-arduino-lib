#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

namespace Device
{

    class XBee : public SoftwareSerial
    {
      public:

        XBee(const uint8_t& tx_pin, const uint8_t& rx_pin);
        ~XBee() = default;

        void init() const;

      private:

        uint8_t tx_pin_;
        uint8_t rx_pin_;
    };

}  // namespace Device
