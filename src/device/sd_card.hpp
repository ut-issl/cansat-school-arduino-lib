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
    };

    template <class... Args>
    void SDCard::write(const String& file_name, Args... args)
    {
        File file = SD.open(file_name, FILE_WRITE);
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

}  // namespace Device
