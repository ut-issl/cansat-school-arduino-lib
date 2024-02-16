#include "cds.hpp"

#include "computer.hpp"

namespace Device
{

    CdS::CdS(const uint8_t& input_pin)
        : input_pin_(input_pin)
    {
    }

    void CdS::init()
    {
        print(F("Init CdS"));
    }

    uint16_t CdS::read()
    {
        return analogRead(input_pin_);
    }

}  // namespace Device
