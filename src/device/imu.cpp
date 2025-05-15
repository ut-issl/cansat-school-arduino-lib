#include "imu.hpp"

#include "../utility/logger.hpp"

namespace Device
{

    IMU::IMU(IMUType type)
        : type_(type), accel_offset_({0.0, 0.0, 0.0}), gyro_offset_({0.0, 0.0, 0.0}), mag_offset_({0.0, 0.0, 0.0})
    {
    }

    void IMU::init(TwoWire* i2c)
    {
        Utility::logger.info(F("[IMU] Initializing..."));

        i2c_ = i2c;

        switch (type_)
        {
            case BMX055:
                initBMX055_();
                break;
            case BNO055:
                initBNO055_();
                break;
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                return;
        }

        delay(100);

        Utility::logger.info(F("[IMU] Initialized"));
    }

    IMU_t IMU::read()
    {
        switch (type_)
        {
            case BMX055:
                return IMU_t{readAccel(), readGyro(), readMag(), euler(), quaternion(), type_};
            case BNO055:
                return IMU_t{readAccel(), readGyro(), readMag(), readEuler(), readQuaternion(), type_};
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                return IMU_t{readAccel(), readGyro(), readMag(), euler(), quaternion(), type_};
        }
    }

    coordinate IMU::readAccel() const
    {
        coordinate accel;

        uint8_t data[6];
        switch (type_)
        {
            case BMX055:
                for (uint8_t i = 0; i < 6; i++) {
                    i2c_->beginTransmission(BMX055_ADDR_ACCL);
                    i2c_->write((2 + i));  // Select data register
                    i2c_->endTransmission();
                    i2c_->requestFrom(BMX055_ADDR_ACCL, 1);  // Request 1 byte of data
                    // Read 6 bytes of data
                    if (i2c_->available() == 1) {
                        data[i] = i2c_->read();
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
                break;
            case BNO055:
                i2c_->beginTransmission(BNO055_ADDR);
                i2c_->write(BNO055_ACCEL_DATA);
                i2c_->endTransmission();
                i2c_->requestFrom(BNO055_ADDR, 6);
                for (int i = 0; i < 6 && i2c_->available(); i++) {
                    data[i] = i2c_->read();
                }
                /* 1m/s^2 = 100 LSB */
                accel.x = (int16_t)((data[1] << 8) | data[0]) / 100.0f - accel_offset_.x;
                accel.y = (int16_t)((data[3] << 8) | data[2]) / 100.0f - accel_offset_.y;
                accel.z = (int16_t)((data[5] << 8) | data[4]) / 100.0f - accel_offset_.z;
                break;
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                break;
        }

        return accel;
    }

    coordinate IMU::readGyro() const
    {
        coordinate gyro;

        uint8_t data[6];
        switch (type_)
        {
            case BMX055:
                for (uint8_t i = 0; i < 6; i++) {
                    i2c_->beginTransmission(BMX055_ADDR_GYRO);
                    i2c_->write((2 + i));  // Select data register
                    i2c_->endTransmission();
                    i2c_->requestFrom(BMX055_ADDR_GYRO, 1);  // Request 1 byte of data
                    // Read 6 bytes of data
                    if (i2c_->available() == 1) {
                        data[i] = i2c_->read();
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
                break;
            case BNO055:
                i2c_->beginTransmission(BNO055_ADDR);
                i2c_->write(BNO055_GYRO_DATA);
                i2c_->endTransmission();
                i2c_->requestFrom(BNO055_ADDR, 6);
                for (int i = 0; i < 6 && i2c_->available(); i++) {
                    data[i] = i2c_->read();
                }
                /* 1dps = 16 LSB */
                gyro.x = (int16_t)((data[1] << 8) | data[0]) / 16.0f - gyro_offset_.x;
                gyro.y = (int16_t)((data[3] << 8) | data[2]) / 16.0f - gyro_offset_.y;
                gyro.z = (int16_t)((data[5] << 8) | data[4]) / 16.0f - gyro_offset_.z;
                break;
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                break;
        }

        return gyro;
    }

    coordinate IMU::readMag() const
    {
        coordinate mag;

        uint8_t data[8];
        switch (type_)
        {
            case BMX055:
                for (uint8_t i = 0; i < 8; i++) {
                    i2c_->beginTransmission(BMX055_ADDR_MAG);
                    i2c_->write((0x42 + i));  // Select data register
                    i2c_->endTransmission();
                    i2c_->requestFrom(BMX055_ADDR_MAG, 1);  // Request 1 byte of data
                    // Read 8 bytes of data
                    if (i2c_->available() == 1) {
                        data[i] = i2c_->read();
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
                break;
            case BNO055:
                i2c_->beginTransmission(BNO055_ADDR);
                i2c_->write(BNO055_MAG_DATA);
                i2c_->endTransmission();
                i2c_->requestFrom(BNO055_ADDR, 6);
                for (int i = 0; i < 6 && i2c_->available(); i++) {
                    data[i] = i2c_->read();
                }
                /* 1uT = 16 LSB */
                mag.x = (int16_t)((data[1] << 8) | data[0]) / 16.0f - mag_offset_.x;
                mag.y = (int16_t)((data[3] << 8) | data[2]) / 16.0f - mag_offset_.y;
                mag.z = (int16_t)((data[5] << 8) | data[4]) / 16.0f - mag_offset_.z;
                break;
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                return mag;
        }

        return mag;
    }

    euler IMU::readEuler() const
    {
        euler euler;

        uint8_t data[6];
        switch (type_)
        {
            case BMX055:
                Utility::logger.error(F("[IMU] Euler angles are not supported for BMX055"));
                break;
            case BNO055:
                i2c_->beginTransmission(BNO055_ADDR);
                i2c_->write(BNO055_EULER_DATA);
                i2c_->endTransmission();
                i2c_->requestFrom(BNO055_ADDR, 6);
                for (int i = 0; i < 6 && i2c_->available(); i++) {
                    data[i] = i2c_->read();
                }
                /* 1° = 16 LSB */
                euler.yaw = (int16_t)((data[1] << 8) | data[0]) / 16.0f;
                euler.pitch = (int16_t)((data[3] << 8) | data[2]) / 16.0f;
                euler.roll = (int16_t)((data[5] << 8) | data[4]) / 16.0f;
                break;
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                break;
        }

        return euler;
    }

    quaternion IMU::readQuaternion() const
    {
        quaternion quaternion;

        uint8_t data[8];
        switch (type_)
        {
            case BMX055:
                Utility::logger.error(F("[IMU] Quaternion data is not supported for BMX055"));
                break;
            case BNO055:
                i2c_->beginTransmission(BNO055_ADDR);
                i2c_->write(BNO055_QUATERNION_DATA);
                i2c_->endTransmission();
                i2c_->requestFrom(BNO055_ADDR, 8);
                for (int i = 0; i < 8 && i2c_->available(); i++) {
                    data[i] = i2c_->read();
                }
                /* 1 = 16384 LSB */
                quaternion.w = (int16_t)((data[1] << 8) | data[0]) / 16384.0f;
                quaternion.x = (int16_t)((data[3] << 8) | data[2]) / 16384.0f;
                quaternion.y = (int16_t)((data[5] << 8) | data[4]) / 16384.0f;
                quaternion.z = (int16_t)((data[7] << 8) | data[6]) / 16384.0f;
                break;
            default:
                Utility::logger.error(F("[IMU] Unknown IMU type"));
                break;
        }

        return quaternion;
    }

    void IMU::setAccelOffset(const coordinate& offset)
    {
        accel_offset_ = offset;
        Utility::logger.info(F("[IMU] Accel offset set to ("), accel_offset_.x, ",", accel_offset_.y, ",", accel_offset_.z, ")");
    }

    void IMU::setAccelOffset(float x, float y, float z)
    {
        accel_offset_ = {x, y, z};
        Utility::logger.info(F("[IMU] Accel offset set to ("), accel_offset_.x, ",", accel_offset_.y, ",", accel_offset_.z, ")");
    }

    void IMU::setGyroOffset(const coordinate& offset)
    {
        gyro_offset_ = offset;
        Utility::logger.info(F("[IMU] Gyro offset set to ("), gyro_offset_.x, ",", gyro_offset_.y, ",", gyro_offset_.z, ")");
    }

    void IMU::setGyroOffset(float x, float y, float z)
    {
        gyro_offset_ = {x, y, z};
        Utility::logger.info(F("[IMU] Gyro offset set to ("), gyro_offset_.x, ",", gyro_offset_.y, ",", gyro_offset_.z, ")");
    }

    void IMU::setMagOffset(const coordinate& offset)
    {
        mag_offset_ = offset;
        Utility::logger.info(F("[IMU] Mag offset set to ("), mag_offset_.x, ",", mag_offset_.y, ",", mag_offset_.z, ")");
    }

    void IMU::setMagOffset(float x, float y, float z)
    {
        mag_offset_ = {x, y, z};
        Utility::logger.info(F("[IMU] Mag offset set to ("), mag_offset_.x, ",", mag_offset_.y, ",", mag_offset_.z, ")");
    }

    void IMU::initBMX055_()
    {
        i2c_->beginTransmission(BMX055_ADDR_ACCL);
        i2c_->write(0x0F);  // Select PMU_Range register
        i2c_->write(0x03);  // Range = +/- 2g
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_ACCL);
        i2c_->write(0x10);  // Select PMU_BW register
        i2c_->write(0x08);  // Bandwidth = 7.81 Hz
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_ACCL);
        i2c_->write(0x11);  // Select PMU_LPW register
        i2c_->write(0x00);  // Normal mode, Sleep duration = 0.5ms
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_GYRO);
        i2c_->write(0x0F);  // Select Range register
        i2c_->write(0x04);  // Full scale = +/- 125 degree/s
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_GYRO);
        i2c_->write(0x10);  // Select Bandwidth register
        i2c_->write(0x07);  // ODR = 100 Hz
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_GYRO);
        i2c_->write(0x11);  // Select LPM1 register
        i2c_->write(0x00);  // Normal mode, Sleep duration = 2ms
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_MAG);
        i2c_->write(0x4B);  // Select Mag register
        i2c_->write(0x83);  // Soft reset
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_MAG);
        i2c_->write(0x4B);  // Select Mag register
        i2c_->write(0x01);  // Soft reset
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_MAG);
        i2c_->write(0x4C);  // Select Mag register
        i2c_->write(0x00);  // Normal Mode, ODR = 10 Hz
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_MAG);
        i2c_->write(0x4E);  // Select Mag register
        i2c_->write(0x84);  // X, Y, Z-Axis enabled
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_MAG);
        i2c_->write(0x51);  // Select Mag register
        i2c_->write(0x04);  // No. of Repetitions for X-Y Axis = 9
        i2c_->endTransmission();
        delay(100);

        i2c_->beginTransmission(BMX055_ADDR_MAG);
        i2c_->write(0x52);  // Select Mag register
        i2c_->write(0x16);  // No. of Repetitions for Z-Axis = 15
        i2c_->endTransmission();
    }

    void IMU::initBNO055_()
    {
        // リセット
        i2c_->beginTransmission(BNO055_ADDR);
        i2c_->write(BNO055_SYS_TRIGGER);
        i2c_->write(0x20);
        i2c_->endTransmission();
        delay(650);

        i2c_->beginTransmission(BNO055_ADDR);
        i2c_->write(BNO055_PWR_MODE);  // Select PWR_MODE register
        i2c_->write(0x00);             // Normal power mode
        i2c_->endTransmission();
        delay(20);

        // 加速度単位設定（m/s^2）、角速度（dps）、角度（deg）、磁気（uT）
        i2c_->beginTransmission(BNO055_ADDR);
        i2c_->write(BNO055_UNIT_SEL);  // Select UNIT_SEL register
        i2c_->write(0x00);             // Set units to default
        i2c_->endTransmission();
        delay(10);

        i2c_->beginTransmission(BNO055_ADDR);
        i2c_->write(BNO055_OPR_MODE);  // Select OPR_MODE register
        i2c_->write(0x0C);             // Set operation mode to NDOF
        i2c_->endTransmission();
        delay(20);
    }

}  // namespace Device
