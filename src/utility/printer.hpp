#pragma once

#include <Arduino.h>

#include "../device/baro_thermo_hygrometer.hpp"

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
        Serial.println(F(" [%] "));
        print_impl(args...);
    }

    template <class... Args>
    void print(Args... args)
    {
        Printer::print(args...);
    }

}  // namespace Utility
