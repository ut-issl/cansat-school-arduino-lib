// #pragma once

// #include <Arduino.h>


// namespace Utility
// {

//     template <class T>
//     class FilterBase
//     {
//       public:
//         FilterBase(volatile T& estimated_value)
//             : estimated_value_{estimated_value}
//         {
//         }

//         void operator()(const volatile T& raw_value)
//         {
//             this->update(raw_value);
//         }

//       protected:
//         volatile T& estimated_value_;

//       private:
//         virtual void update(const volatile T& raw_value) = 0;
//     };

// }  // namespace Utility