#include "sd_card.hpp"

#include <SPI.h>
#include <Wire.h>

#include "../utility/logger.hpp"

namespace Device
{

    bool SDCard::init(uint8_t ss_pin)
    {
        Utility::logger.info(F("[SDCard] Initializing..."));

        pinMode(ss_pin, OUTPUT);
        if (!SD.begin(ss_pin)) {
            Utility::logger.error(F("[SDCard] Failed to initialize"));
            return false;
        }

        Utility::logger.info(F("[SDCard] Initialized"));
        return true;
    }

    void SDCard::write_impl(File& file, coordinate last)
    {
        file.print(F("("));
        file.print(last.x);
        file.print(F(", "));
        file.print(last.y);
        file.print(F(", "));
        file.print(last.z);
        file.println(F(")"));
    }

    void SDCard::write_impl(File& file, BaroThermoHygrometer_t last)
    {
        file.print(F("Pressure: "));
        file.print(last.pressure);
        file.print(F(" [hPa], Temperature: "));
        file.print(last.temperature);
        file.print(F(" [°C], Humidity: "));
        file.print(last.humidity);
        file.println(F(" [%]"));
    }

    void SDCard::write_impl(File& file, GPS_t last)
    {
        file.print(F("Time: "));
        file.print(last.time);
        file.print(F(" [s], Latitude: "));
        file.print(last.lat);
        file.print(F(" [°], Longitude: "));
        file.print(last.lon);
        file.print(F(" [°], Altitude: "));
        file.print(last.alt);
        file.println(F(" [m]"));
    }

    void SDCard::write_impl(File& file, IMU_t last)
    {
        file.print(F("Acc: ("));
        file.print(last.acc.x);
        file.print(F(", "));
        file.print(last.acc.y);
        file.print(F(", "));
        file.print(last.acc.z);
        file.print(F("), Gyro: ("));
        file.print(last.gyro.x);
        file.print(F(", "));
        file.print(last.gyro.y);
        file.print(F(", "));
        file.print(last.gyro.z);
        file.print(F("), Mag: ("));
        file.print(last.mag.x);
        file.print(F(", "));
        file.print(last.mag.y);
        file.print(F(", "));
        file.print(last.mag.z);
        file.println(F(")"));
    }

}  // namespace Device