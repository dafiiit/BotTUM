//main
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "adxl.h"

ADXL_COMBO adxl;


void setup(){
    Serial.begin(115200);
    adxl.setup();
}
void loop {
    adxl.loop(){
        Serial.println("ADXL_LOOP");
        
    };
}