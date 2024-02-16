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

        void init() const;

        virtual Ret read() const;
        Ret operator()() const;
    };

    template <class Ret>
    SensorBase<Ret>::SensorBase()
    {
    }

    template <class Ret>
    void SensorBase<Ret>::init() const
    {
    }

    template <class Ret>
    Ret SensorBase<Ret>::operator()() const
    {
        return this->read();
    }

}  // namespace Device
