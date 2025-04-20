#include "baro_thermo_hygrometer.hpp"

#include "../utility/logger.hpp"

#define BME280_ADDR_ 0x76
#define CONFIG_ 0xF5
#define CTRL_MEAS_ 0xF4
#define CTRL_HUM_ 0xF2

namespace Device
{

    BaroThermoHygrometer::BaroThermoHygrometer()
    {
    }

    void BaroThermoHygrometer::init(TwoWire* i2c)
    {
        Utility::logger.info(F("[BaroThermoHygrometer] Initializing..."));

        i2c_ = i2c;
        
        // BME280の設定
        // BME280動作設定
        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(CONFIG_);  // 動作設定
        i2c_->write(0x00);     // 「単発測定」，「フィルタなし」，「SPI 4線式」
        i2c_->endTransmission();

        // BME280測定条件設定
        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(CTRL_MEAS_);  // 測定条件設定
        i2c_->write(0x24);        // 「温度・気圧オーバーサンプリングx1」，「スリープモード」
        i2c_->endTransmission();

        // BME280温度測定条件設定
        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(CTRL_HUM_);  // 湿度測定条件設定
        i2c_->write(0x01);       // 「湿度オーバーサンプリングx1」
        i2c_->endTransmission();

        // BME280補正データ取得
        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(0x88);  // 出力データバイトを「補正データ」のアドレスに指定
        i2c_->endTransmission();

        i2c_->requestFrom(BME280_ADDR_, 26);
        for (uint8_t i = 0; i < 26; i++) {
            while (!i2c_->available()) {
                Utility::logger.warning(F("[BaroThermoHygrometer] Waiting for receiving data..."));
                delay(1000);
            }
            buffer_[i] = i2c_->read();
        }

        dig_t1_ = ((uint16_t)((buffer_[1] << 8) | buffer_[0]));
        dig_t2_ = ((int16_t)((buffer_[3] << 8) | buffer_[2]));
        dig_t3_ = ((int16_t)((buffer_[5] << 8) | buffer_[4]));

        dig_p1_ = ((uint16_t)((buffer_[7] << 8) | buffer_[6]));
        dig_p2_ = ((int16_t)((buffer_[9] << 8) | buffer_[8]));
        dig_p3_ = ((int16_t)((buffer_[11] << 8) | buffer_[10]));
        dig_p4_ = ((int16_t)((buffer_[13] << 8) | buffer_[12]));
        dig_p5_ = ((int16_t)((buffer_[15] << 8) | buffer_[14]));
        dig_p6_ = ((int16_t)((buffer_[17] << 8) | buffer_[16]));
        dig_p7_ = ((int16_t)((buffer_[19] << 8) | buffer_[18]));
        dig_p8_ = ((int16_t)((buffer_[21] << 8) | buffer_[20]));
        dig_p9_ = ((int16_t)((buffer_[23] << 8) | buffer_[22]));

        dig_h1_ = ((uint8_t)(buffer_[25]));

        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(0xE1);  // 出力データバイトを「補正データ」のアドレスに指定
        i2c_->endTransmission();

        i2c_->requestFrom(BME280_ADDR_, 7);
        for (uint8_t i = 0; i < 7; i++) {
            while (!i2c_->available()) {
                Utility::logger.warning(F("[BaroThermoHygrometer] Waiting for receiving data..."));
                delay(1000);
            }
            buffer_[i] = i2c_->read();
        }

        dig_h2_ = ((int16_t)((buffer_[1] << 8) | buffer_[0]));
        dig_h3_ = ((uint8_t)(buffer_[2]));
        dig_h4_ = ((int16_t)((buffer_[3] << 4) + (buffer_[4] & 0x0F)));
        dig_h5_ = ((int16_t)((buffer_[5] << 4) + ((buffer_[4] >> 4) & 0x0F)));
        dig_h6_ = ((int8_t)buffer_[6]);

        this->read();  // 1回測定しておく

        Utility::logger.info(F("[BaroThermoHygrometer] Initialized"));
    }

    BaroThermoHygrometer_t BaroThermoHygrometer::read()
    {
        BaroThermoHygrometer_t data;

        uint32_t pres_cal, humi_cal;
        int32_t temp_cal;

        // BME280測定条件設定 (1回測定後，スリープモード)
        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(CTRL_MEAS_);  // 測定条件設定
        i2c_->write(0x25);        // 「温度・気圧オーバーサンプリングx1」，「1回測定後，スリープモード」
        i2c_->endTransmission();
        delay(1);

        // 測定データ取得
        i2c_->beginTransmission(BME280_ADDR_);
        i2c_->write(0xF7);  // 出力データバイトを「気圧データ」のアドレスに指定
        i2c_->endTransmission();

        i2c_->requestFrom(BME280_ADDR_, 8);
        for (uint8_t i = 0; i < 8; i++) {
            if (!i2c_->available()) {
                Utility::logger.error(F("[BaroThermoHygrometer] Cannot receive data"));
                return data;
            }
            buffer_[i] = i2c_->read();
        }

        int32_t adc_p = ((uint32_t)buffer_[0] << 12) | ((uint32_t)buffer_[1] << 4) | ((buffer_[2] >> 4) & 0x0F);
        int32_t adc_t = ((uint32_t)buffer_[3] << 12) | ((uint32_t)buffer_[4] << 4) | ((buffer_[5] >> 4) & 0x0F);
        int32_t adc_h = ((uint32_t)buffer_[6] << 8) | ((uint32_t)buffer_[7]);

        pres_cal = compensate_p_(adc_p);  // 気圧データ補正計算
        temp_cal = compensate_t_(adc_t);  // 温度データ補正計算
        humi_cal = compensate_h_(adc_h);  // 湿度データ補正計算

        data.pressure = (float)pres_cal / 100.0;
        data.temperature = (float)temp_cal / 100.0;
        data.humidity = (float)humi_cal / 1024.0;

        return data;
    }

    uint32_t BaroThermoHygrometer::compensate_p_(int32_t adc_p)
    {
        int32_t var1, var2;
        uint32_t pres;
        var1 = (((int32_t)t_fine_) >> 1) - (int32_t)64000;
        var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)dig_p6_);
        var2 = var2 + ((var1 * ((int32_t)dig_p5_)) << 1);
        var2 = (var2 >> 2) + (((int32_t)dig_p4_) << 16);
        var1 = (((dig_p3_ * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) + ((((int32_t)dig_p2_) * var1) >> 1)) >> 18;
        var1 = ((((32768 + var1)) * ((int32_t)dig_p1_)) >> 15);
        if (var1 == 0) {
            return 0;  // avoid exception caused by division by zero
        }
        pres = (((uint32_t)(((int32_t)1048576) - adc_p) - (var2 >> 12))) * 3125;
        if (pres < 0x80000000) {
            pres = (pres << 1) / ((uint32_t)var1);
        } else {
            pres = (pres / (uint32_t)var1) * 2;
        }
        var1 = (((int32_t)dig_p9_) * ((int32_t)(((pres >> 3) * (pres >> 3)) >> 13))) >> 12;
        var2 = (((int32_t)(pres >> 2)) * ((int32_t)dig_p8_)) >> 13;
        pres = (uint32_t)((int32_t)pres + ((var1 + var2 + dig_p7_) >> 4));
        return pres;
    }

    int32_t BaroThermoHygrometer::compensate_t_(int32_t adc_t)
    {
        int32_t var1, var2, temp;
        var1 = ((((adc_t >> 3) - ((int32_t)dig_t1_ << 1))) * ((int32_t)dig_t2_)) >> 11;
        var2 = (((((adc_t >> 4) - ((int32_t)dig_t1_)) * ((adc_t >> 4) - ((int32_t)dig_t1_))) >> 12) * ((int32_t)dig_t3_)) >> 14;
        t_fine_ = var1 + var2;
        temp = (t_fine_ * 5 + 128) >> 8;
        return temp;
    }

    uint32_t BaroThermoHygrometer::compensate_h_(int32_t adc_h)
    {
        int32_t v_x1_u32r;
        v_x1_u32r = (t_fine_ - ((int32_t)76800));
        v_x1_u32r = (((((adc_h << 14) - (((int32_t)dig_h4_) << 20) - (((int32_t)dig_h5_) * v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_h6_)) >> 10) * (((v_x1_u32r * ((int32_t)dig_h3_)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_h2_) + 8192) >> 14));
        v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_h1_)) >> 4));
        v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
        v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
        return (uint32_t)(v_x1_u32r >> 12);
    }

}  // namespace Device