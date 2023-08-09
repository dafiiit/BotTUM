#include "mpu"
#include "Arduino.h"
#include <Wire.h>

MPU mpu;

void setup()
{
    mpu.setup();
}

void loop()
{
    mpu.loop();
    mpu.get_angle(rotation_axis);
}