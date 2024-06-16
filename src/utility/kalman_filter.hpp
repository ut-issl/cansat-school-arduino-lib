// #pragma once

// #include "filter_base.hpp"


// namespace Utility
// {

//     template <class T>
//     class KalmanFilter : public FilterBase<T>
//     {
//       public:
//         KalmanFilter(volatile T& estimated_value, uint8_t disp_v = 1, uint8_t disp_w = 30)
//             : FilterBase<T>{estimated_value}, covariance_{0}, disp_v_{disp_v}, disp_w_{disp_w}
//         {
//         }

//       private:
//         void update(const volatile T& raw_value) override
//         {
//             covariance_ += disp_v_;
//             T kalman_gain = covariance_ / (covariance_ + disp_w_);
//             this->estimated_value_ += kalman_gain * (raw_value - this->estimated_value_);
//             covariance_ *= (1 - kalman_gain);
//         }

//         volatile T covariance_;
//         uint8_t disp_v_;
//         uint8_t disp_w_;
//     };

// }  // namespace Utility