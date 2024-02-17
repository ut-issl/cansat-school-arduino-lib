#pragma once

#include <Arduino.h>

namespace Device
{

    template <class Ret>
    class SensorBase
    {
      protected:

        SensorBase();
        ~SensorBase() = default;

      public:

        void init();

        virtual Ret read();
        Ret operator()();
    };

    template <class Ret>
    SensorBase<Ret>::SensorBase()
    {
    }

    template <class Ret>
    void SensorBase<Ret>::init()
    {
    }

    template <class Ret>
    Ret SensorBase<Ret>::operator()()
    {
        return this->read();
    }

}  // namespace Device
