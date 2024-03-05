#pragma once

#include <Arduino.h>

#include "../device/baro_thermo_hygrometer.hpp"
#include "../device/gps_receiver.hpp"

namespace Utility
{

    class Printer
    {

      public:

        template <class... Args>
        static void print(Args... args);

      private:

        template <class Last>
        static void print_impl(Last last);
        template <class Head, class... Args>
        static void print_impl(Head head, Args... args);

        static void print_impl(Device::BaroThermoHygrometer_t last);
        template <class... Args>
        static void print_impl(Device::BaroThermoHygrometer_t head, Args... args);

        static void print_impl(Device::GPS_t last);
        template <class... Args>
        static void print_impl(Device::GPS_t head, Args... args);
    };

    template <class... Args>
    void Printer::print(Args... args)
    {
        print_impl(args...);
    }

    template <class Last>
    void Printer::print_impl(Last last)

    {
        Serial.println(last);
    }

    template <class Head, class... Args>
    void Printer::print_impl(Head head, Args... args)
    {
        Serial.print(head);
        Serial.print(F(" "));
        print_impl(args...);
    }

    inline void Printer::print_impl(Device::BaroThermoHygrometer_t last)
    {
        Serial.print(F("Pressure: "));
        Serial.print(last.pressure);
        Serial.print(F(" [hPa], Temperature: "));
        Serial.print(last.temperature);
        Serial.print(F(" [°C], Humidity: "));
        Serial.print(last.humidity);
        Serial.println(F(" [%]"));
    }

    template <class... Args>
    void Printer::print_impl(Device::BaroThermoHygrometer_t head, Args... args)
    {
        Serial.print(F("Pressure: "));
        Serial.print(head.pressure);
        Serial.print(F(" [hPa], Temperature: "));
        Serial.print(head.temperature);
        Serial.print(F(" [°C], Humidity: "));
        Serial.print(head.humidity);
        Serial.print(F(" [%] "));
        print_impl(args...);
    }

    inline void Printer::print_impl(Device::GPS_t last)
    {
        Serial.print(F("Time: "));
        Serial.print(last.time);
        Serial.print(F(" [s], Latitude: "));
        Serial.print(last.lat);
        Serial.print(F(" [°], Longitude: "));
        Serial.print(last.lon);
        Serial.print(F(" [°], Altitude: "));
        Serial.print(last.alt);
        Serial.println(F(" [m]"));
    }

    template <class... Args>
    void Printer::print_impl(Device::GPS_t head, Args... args)
    {
        Serial.print(F("Time: "));
        Serial.print(head.time);
        Serial.print(F(" [s], Latitude: "));
        Serial.print(head.lat);
        Serial.print(F(" [°], Longitude: "));
        Serial.print(head.lon);
        Serial.print(F(" [°], Altitude: "));
        Serial.print(head.alt);
        Serial.print(F(" [m] "));
        print_impl(args...);
    }

    template <class... Args>
    void print(Args... args)
    {
        Printer::print(args...);
    }

}  // namespace Utility
