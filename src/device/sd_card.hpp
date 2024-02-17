#pragma once

#include <SD.h>

namespace Device
{

    namespace SDCard
    {

        void init(const uint8_t& ss_pin);
        void write(const String& file_name, const String& data);  // ファイル名に `_` を含んではいけない

    }  // namespace SDCard

}  // namespace Device