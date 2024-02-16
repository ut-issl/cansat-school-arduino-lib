#ifndef BMP_H
#define BMP_H

#include <Wire.h>

#include "./Adafruit_BMP280.h"
#include "./PIN_ASSIGN.h"

/*

http://okiraku-camera.tokyo/blog/?p=5291
*/

// #################### Barometer ####################


void BMP_Init();
void BMP_Update();

typedef struct
{
} Barometer_t;


#endif
