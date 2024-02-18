#include "cds.hpp"

#include "computer.hpp"

namespace Device
{

    CdS::CdS(const uint8_t& output_pin)
        : output_pin_(output_pin)
    {
    }

    void CdS::init()
    {
        print(F("Init CdS"));
    }

    uint16_t CdS::read()
    {
        return (uint16_t)(analogRead(output_pin_) / 1024.0 * 100);
    }

}  // namespace Device
