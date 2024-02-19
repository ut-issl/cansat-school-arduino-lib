#include "imu.hpp"

#include "computer.hpp"

// BMX055 加速度センサのI2Cアドレス
#define IMU_ADDR_ACCL 0x19  // (JP1,JP2,JP3 = Openの時)
// BMX055 ジャイロセンサのI2Cアドレス
#define IMU_ADDR_GYRO 0x69  // (JP1,JP2,JP3 = Openの時)
// BMX055 磁気センサのI2Cアドレス
#define IMU_ADDR_MAG 0x13  // (JP1,JP2,JP3 = Openの時)

namespace Device
{

    void coordinate::print() const
    {
        Computer::print("(", x, ",", y, ",", z, ")");
    }

    void IMU_t::print() const
    {
        Computer::print("Acc: (", acc.x, ",", acc.y, ",", acc.z, ")");
        Computer::print("Gyro: (", gyro.x, ",", gyro.y, ",", gyro.z, ")");
        Computer::print("Mag: (", mag.x, ",", mag.y, ",", mag.z, ")");
    }

    IMU::IMU()
        : accel_offset_({0.0, 0.0, 0.0}), gyro_offset_({0.0, 0.0, 0.0}), mag_offset_({0.0, 0.0, 0.0})
    {
    }

    void IMU::init()
    {
        print(F("[IMU] Initializing..."));

        Wire.beginTransmission(IMU_ADDR_ACCL);
        Wire.write(0x0F);  // Select PMU_Range register
        Wire.write(0x03);  // Range = +/- 2g
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_ACCL);
        Wire.write(0x10);  // Select PMU_BW register
        Wire.write(0x08);  // Bandwidth = 7.81 Hz
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_ACCL);
        Wire.write(0x11);  // Select PMU_LPW register
        Wire.write(0x00);  // Normal mode, Sleep duration = 0.5ms
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_GYRO);
        Wire.write(0x0F);  // Select Range register
        Wire.write(0x04);  // Full scale = +/- 125 degree/s
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_GYRO);
        Wire.write(0x10);  // Select Bandwidth register
        Wire.write(0x07);  // ODR = 100 Hz
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_GYRO);
        Wire.write(0x11);  // Select LPM1 register
        Wire.write(0x00);  // Normal mode, Sleep duration = 2ms
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_MAG);
        Wire.write(0x4B);  // Select Mag register
        Wire.write(0x83);  // Soft reset
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_MAG);
        Wire.write(0x4B);  // Select Mag register
        Wire.write(0x01);  // Soft reset
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_MAG);
        Wire.write(0x4C);  // Select Mag register
        Wire.write(0x00);  // Normal Mode, ODR = 10 Hz
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_MAG);
        Wire.write(0x4E);  // Select Mag register
        Wire.write(0x84);  // X, Y, Z-Axis enabled
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_MAG);
        Wire.write(0x51);  // Select Mag register
        Wire.write(0x04);  // No. of Repetitions for X-Y Axis = 9
        Wire.endTransmission();
        delay(100);

        Wire.beginTransmission(IMU_ADDR_MAG);
        Wire.write(0x52);  // Select Mag register
        Wire.write(0x16);  // No. of Repetitions for Z-Axis = 15
        Wire.endTransmission();
        delay(100);

        print(F("[IMU] Initialized"));
    }

    IMU_t IMU::read()
    {
        return IMU_t{readAccel(), readGyro(), readMag()};
    }

    coordinate IMU::readAccel() const
    {
        coordinate accel;

        uint8_t data[6];
        for (uint8_t i = 0; i < 6; i++) {
            Wire.beginTransmission(IMU_ADDR_ACCL);
            Wire.write((2 + i));  // Select data register
            Wire.endTransmission();
            Wire.requestFrom(IMU_ADDR_ACCL, 1);  // Request 1 byte of data
            // Read 6 bytes of data
            if (Wire.available() == 1) {
                data[i] = Wire.read();
            }
        }
        // Convert the data to 12-bits
        accel.x = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
        if (accel.x > 2047) {
            accel.x -= 4096;
        }
        accel.y = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
        if (accel.y > 2047) {
            accel.y -= 4096;
        }
        accel.z = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
        if (accel.z > 2047) {
            accel.z -= 4096;
        }
        accel.x = accel.x * 0.0098 - accel_offset_.x;  // renge +-2g
        accel.y = accel.y * 0.0098 - accel_offset_.y;  // renge +-2g
        accel.z = accel.z * 0.0098 - accel_offset_.z;  // renge +-2g

        return accel;
    }

    coordinate IMU::readGyro() const
    {
        coordinate gyro;

        uint8_t data[6];
        for (uint8_t i = 0; i < 6; i++) {
            Wire.beginTransmission(IMU_ADDR_GYRO);
            Wire.write((2 + i));  // Select data register
            Wire.endTransmission();
            Wire.requestFrom(IMU_ADDR_GYRO, 1);  // Request 1 byte of data
            // Read 6 bytes of data
            if (Wire.available() == 1) {
                data[i] = Wire.read();
            }
        }
        // Convert the data
        gyro.x = (data[1] * 256) + data[0];
        if (gyro.x > 32767) {
            gyro.x -= 65536;
        }
        gyro.y = (data[3] * 256) + data[2];
        if (gyro.y > 32767) {
            gyro.y -= 65536;
        }
        gyro.z = (data[5] * 256) + data[4];
        if (gyro.z > 32767) {
            gyro.z -= 65536;
        }
        gyro.x = gyro.x * 0.0038 - gyro_offset_.x;  // renge +-125 degree/s
        gyro.y = gyro.y * 0.0038 - gyro_offset_.y;  // renge +-125 degree/s
        gyro.z = gyro.z * 0.0038 - gyro_offset_.z;  // renge +-125 degree/s

        return gyro;
    }

    coordinate IMU::readMag() const
    {
        coordinate mag;

        uint8_t data[8];
        for (uint8_t i = 0; i < 8; i++) {
            Wire.beginTransmission(IMU_ADDR_MAG);
            Wire.write((0x42 + i));  // Select data register
            Wire.endTransmission();
            Wire.requestFrom(IMU_ADDR_MAG, 1);  // Request 1 byte of data
            // Read 8 bytes of data
            if (Wire.available() == 1) {
                data[i] = Wire.read();
            }
        }
        // Convert the data
        mag.x = ((data[1] << 8) | (data[0] >> 3));
        if (mag.x > 4095) {
            mag.x -= 8192;
        }
        mag.y = ((data[3] << 8) | (data[2] >> 3));
        if (mag.y > 4095) {
            mag.y -= 8192;
        }
        mag.z = ((data[5] << 8) | (data[4] >> 3));
        if (mag.z > 16383) {
            mag.z -= 32768;
        }
        mag.x = mag.x - mag_offset_.x;  // renge +-2000uT
        mag.y = mag.y - mag_offset_.y;  // renge +-2000uT
        mag.z = mag.z - mag_offset_.z;  // renge +-2000uT

        return mag;
    }

    void IMU::setAccelOffset(const coordinate& offset)
    {
        accel_offset_ = offset;
        print(F("[IMU] Accel offset set to"), accel_offset_.x, accel_offset_.y, accel_offset_.z);
    }

    void IMU::setAccelOffset(float x, float y, float z)
    {
        accel_offset_ = {x, y, z};
        print(F("[IMU] Accel offset set to"), accel_offset_.x, accel_offset_.y, accel_offset_.z);
    }

    void IMU::setGyroOffset(const coordinate& offset)
    {
        gyro_offset_ = offset;
        print(F("[IMU] Gyro offset set to"), gyro_offset_.x, gyro_offset_.y, gyro_offset_.z);
    }

    void IMU::setGyroOffset(float x, float y, float z)
    {
        gyro_offset_ = {x, y, z};
        print(F("[IMU] Gyro offset set to"), gyro_offset_.x, gyro_offset_.y, gyro_offset_.z);
    }

    void IMU::setMagOffset(const coordinate& offset)
    {
        mag_offset_ = offset;
        print(F("[IMU] Mag offset set to"), mag_offset_.x, mag_offset_.y, mag_offset_.z);
    }

    void IMU::setMagOffset(float x, float y, float z)
    {
        mag_offset_ = {x, y, z};
        print(F("[IMU] Mag offset set to"), mag_offset_.x, mag_offset_.y, mag_offset_.z);
    }

}  // namespace Device