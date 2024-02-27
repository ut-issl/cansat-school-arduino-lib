#pragma once

#include <Arduino.h>

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

    template <class... Args>
    void print(Args... args)
    {
        Printer::print(args...);
    }

}  // namespace Utility
