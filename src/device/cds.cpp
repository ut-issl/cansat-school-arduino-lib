#include "cds.hpp"

#include "../utility/printer.hpp"

namespace Device
{

    CdS::CdS(uint8_t output_pin)
        : output_pin_(output_pin)
    {
    }

    void CdS::init()
    {
        Utility::print(F("[CdS] Initialized"));
    }

    uint16_t CdS::read()
    {
        return (uint16_t)(analogRead(output_pin_) / 1024.0 * 100);
    }

}  // namespace Device
