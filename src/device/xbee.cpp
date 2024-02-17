// #include "xbee.hpp"

// #include "computer.hpp"

// namespace Device
// {

// XBee::XBee(const uint8_t& tx_pin, const uint8_t& rx_pin)
//     : SoftwareSerial(tx_pin, rx_pin), tx_pin_(tx_pin), rx_pin_(rx_pin)
// {
// }

// void XBee::init() const
// {
//     this->begin(9600);
//     Computer::print(F("Xbee init done"));
// }

// void XBee::writeData(char* write_data, uint8_t data_length) const
// {
//     for (uint8_t i = 0; i < max_length_; ++i) {
//         if (i >= data_length)
//             break;
//         this->write(write_data);
//     }
// }

// void XBee::readData()
// {
//     received_data_length_ = this->available();

// if (received_data_length_ == 0)
//     return;

// for (uint8_t i = 0; i < max_length_; ++i) {
//     if (i >= received_data_length_)
//         break;
//     this->readBytes(received_data_[i], i);
// }}

// void XBee::print() const
// {
//     for (uint8_t i = 0; i < max_length_; ++i) {
//         Computer::print(received_data_[i]);
//     }
//     Computer::print("\n");
// }

// }  // namespace Device
