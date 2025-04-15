#pragma once

#include <SD.h>

#include "../utility/printer.hpp"

namespace Device
{

    class SDCard
    {
      public:

        static bool init(uint8_t ss_pin);

        template <class... Args>
        static void write(const String& file_name, Args... args);

      private:

        template <class Last>
        static void write_impl(File& file, Last last);
        template <class Head, class... Args>
        static void write_impl(File& file, Head head, Args... args);

        static void write_impl(File& file, coordinate last);
        template <class... Args>
        static void write_impl(File& file, coordinate head, Args... args);

        static void write_impl(File& file, BaroThermoHygrometer_t last);
        template <class... Args>
        static void write_impl(File& file, BaroThermoHygrometer_t head, Args... args);

        static void write_impl(File& file, GPS_t last);
        template <class... Args>
        static void write_impl(File& file, GPS_t head, Args... args);

        static void write_impl(File& file, IMU_t last);
        template <class... Args>
        static void write_impl(File& file, IMU_t head, Args... args);
    };

    template <class... Args>
    void SDCard::write(const String& file_name, Args... args)
    {
        File file = SD.open(file_name.c_str(), FILE_WRITE);
        if (!file) {
            float sec = float(millis()) / 1000.0;
            char buffer[9];
            dtostrf(sec, 7, 2, buffer);
            Utility::print(String(buffer), F("[ERROR]"), F("[SDCard] Failed to open file"));
            return;
        }

        write_impl(file, args...);

        file.close();
    }

    template <class Last>
    void SDCard::write_impl(File& file, Last last)
    {
        file.println(last);
    }

    template <class Head, class... Args>
    void SDCard::write_impl(File& file, Head head, Args... args)
    {
        file.print(head);
        file.print(" ");
        write_impl(file, args...);
    }

    template <class... Args>
    void SDCard::write_impl(File& file, coordinate head, Args... args)
    {
        file.print(F("("));
        file.print(head.x);
        file.print(F(", "));
        file.print(head.y);
        file.print(F(", "));
        file.print(head.z);
        file.print(F(") "));
        write_impl(file, args...);
    }

    template <class... Args>
    void SDCard::write_impl(File& file, BaroThermoHygrometer_t head, Args... args)
    {
        file.print(F("Pressure: "));
        file.print(head.pressure);
        file.print(F(" [hPa], Temperature: "));
        file.print(head.temperature);
        file.print(F(" [°C], Humidity: "));
        file.print(head.humidity);
        file.print(F(" [%] "));
        write_impl(file, args...);
    }

    template <class... Args>
    void SDCard::write_impl(File& file, GPS_t head, Args... args)
    {
        file.print(F("Time: "));
        file.print(head.time);
        file.print(F(" [s], Latitude: "));
        file.print(head.lat);
        file.print(F(" [°], Longitude: "));
        file.print(head.lon);
        file.print(F(" [°], Altitude: "));
        file.print(head.alt);
        file.print(F(" [m] "));
        write_impl(file, args...);
    }

    template <class... Args>
    void SDCard::write_impl(File& file, IMU_t head, Args... args)
    {
        file.print(F("Acc: ("));
        file.print(head.acc.x);
        file.print(F(", "));
        file.print(head.acc.y);
        file.print(F(", "));
        file.print(head.acc.z);
        file.print(F("), Gyro: ("));
        file.print(head.gyro.x);
        file.print(F(", "));
        file.print(head.gyro.y);
        file.print(F(", "));
        file.print(head.gyro.z);
        file.print(F("), Mag: ("));
        file.print(head.mag.x);
        file.print(F(", "));
        file.print(head.mag.y);
        file.print(F(", "));
        file.print(head.mag.z);
        file.print(F(") "));
        write_impl(file, args...);
    }

}  // namespace Device
