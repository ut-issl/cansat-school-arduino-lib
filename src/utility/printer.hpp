#pragma once

#include <Arduino.h>

#include "../device/baro_thermo_hygrometer.hpp"
#include "../device/gps_receiver.hpp"
#include "../device/imu.hpp"

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

        static void print_impl(Device::coordinate last);
        template <class... Args>
        static void print_impl(Device::coordinate head, Args... args);

        static void print_impl(Device::BaroThermoHygrometer_t last);
        template <class... Args>
        static void print_impl(Device::BaroThermoHygrometer_t head, Args... args);

        static void print_impl(Device::GPS_t last);
        template <class... Args>
        static void print_impl(Device::GPS_t head, Args... args);

        static void print_impl(Device::IMU_t last);
        template <class... Args>
        static void print_impl(Device::IMU_t head, Args... args);
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

    inline void Printer::print_impl(Device::coordinate last)
    {
        Serial.print(F("("));
        Serial.print(last.x);
        Serial.print(F(", "));
        Serial.print(last.y);
        Serial.print(F(", "));
        Serial.print(last.z);
        Serial.println(F(")"));
    }

    template <class... Args>
    void Printer::print_impl(Device::coordinate head, Args... args)
    {
        Serial.print(F("("));
        Serial.print(head.x);
        Serial.print(F(", "));
        Serial.print(head.y);
        Serial.print(F(", "));
        Serial.print(head.z);
        Serial.print(F(") "));
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

    inline void Printer::print_impl(Device::IMU_t last)
    {
        switch (last.type)
        {
            case IMUType::BMX055: {
                Serial.print(F("Acc: ("));
                Serial.print(last.acc.x);
                Serial.print(F(", "));
                Serial.print(last.acc.y);
                Serial.print(F(", "));
                Serial.print(last.acc.z);
                Serial.print(F("), Gyro: ("));
                Serial.print(last.gyro.x);
                Serial.print(F(", "));
                Serial.print(last.gyro.y);
                Serial.print(F(", "));
                Serial.print(last.gyro.z);
                Serial.print(F("), Mag: ("));
                Serial.print(last.mag.x);
                Serial.print(F(", "));
                Serial.print(last.mag.y);
                Serial.print(F(", "));
                Serial.print(last.mag.z);
                Serial.println(F(")"));
                break;
            }
            case IMUType::BNO055: {
                Serial.print(F("Acc: ("));
                Serial.print(last.acc.x);
                Serial.print(F(", "));
                Serial.print(last.acc.y);
                Serial.print(F(", "));
                Serial.print(last.acc.z);
                Serial.print(F("), Gyro: ("));
                Serial.print(last.gyro.x);
                Serial.print(F(", "));
                Serial.print(last.gyro.y);
                Serial.print(F(", "));
                Serial.print(last.gyro.z);
                Serial.print(F("), Mag: ("));
                Serial.print(last.mag.x);
                Serial.print(F(", "));
                Serial.print(last.mag.y);
                Serial.print(F(", "));
                Serial.print(last.mag.z);
                Serial.print(F("), Euler: ("));
                Serial.print(last.euler.roll);
                Serial.print(F(", "));
                Serial.print(last.euler.pitch);
                Serial.print(F(", "));
                Serial.print(last.euler.yaw);
                Serial.print(F("), Quaternion: ("));
                Serial.print(last.quaternion.x);
                Serial.print(F(", "));
                Serial.print(last.quaternion.y);
                Serial.print(F(", "));
                Serial.print(last.quaternion.z);
                Serial.print(F(", "));
                Serial.print(last.quaternion.w);
                Serial.println(F(")"));
                break;
            }
        }
    }

    template <class... Args>
    void Printer::print_impl(Device::IMU_t head, Args... args)
    {
        Serial.print(F("Acc: ("));
        Serial.print(head.acc.x);
        Serial.print(F(", "));
        Serial.print(head.acc.y);
        Serial.print(F(", "));
        Serial.print(head.acc.z);
        Serial.print(F("), Gyro: ("));
        Serial.print(head.gyro.x);
        Serial.print(F(", "));
        Serial.print(head.gyro.y);
        Serial.print(F(", "));
        Serial.print(head.gyro.z);
        Serial.print(F("), Mag: ("));
        Serial.print(head.mag.x);
        Serial.print(F(", "));
        Serial.print(head.mag.y);
        Serial.print(F(", "));
        Serial.print(head.mag.z);
        Serial.print(F(") "));
        print_impl(args...);
    }

    template <class... Args>
    void print(Args... args)
    {
        Printer::print(args...);
    }

}  // namespace Utility
