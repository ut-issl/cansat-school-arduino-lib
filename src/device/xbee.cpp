#include "xbee.hpp"

#include "computer.hpp"

namespace Device
{

    XBee::XBee(const uint8_t& tx_pin, const uint8_t& rx_pin)
        : SoftwareSerial(tx_pin, rx_pin), tx_pin_(tx_pin), rx_pin_(rx_pin)
    {
    }

    void XBee::init() const
    {
        this->begin(9600);
        print(F("Xbee init done"));
    }
    

    void XBee::write(char* write_data, uint8_t data_length) const
    {
        for (uint8_t i = 0; i < max_length_; ++i)
        {
            if (i >= data_length) break;
            this->write(write_data);
        }
    }

    void XBee::read()
    {
        received_data_length_ = XbeeSerial.available();

        if (received_data_length_ == 0) return;
        
        for (uint8_t i = 0; i < max_length_; ++i)
        {
            if (i >= received_data_length_) break;
            this->readBytes(received_data_[i], i);
        }

    }

    void XBee::print() const
    {
        for (uint8_t i = 0; i < max_length_; ++i)
        {
            print(received_data_[i]);
        }
        print("\n");
    }

}  // namespace Device
