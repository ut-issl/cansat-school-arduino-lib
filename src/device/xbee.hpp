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
        void writeData(char* write_data, uint8_t data_length) const;
        void readData();
        void print() const;

      private:

        uint8_t tx_pin_;
        uint8_t rx_pin_;

        static const uint8_t max_length_ = 32;
        uint8_t received_data_length_;
        char received_data_[max_length_];
    };

}  // namespace Device
