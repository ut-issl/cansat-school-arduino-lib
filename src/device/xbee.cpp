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

}  // namespace Device