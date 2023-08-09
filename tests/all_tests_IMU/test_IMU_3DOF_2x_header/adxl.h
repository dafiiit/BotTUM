// header file for ADXL345
#ifndef ADXL_H
#define ADXL_H

#include <Wire.h>
#include <Arduino.h>
#include <ADXL345_WE.h>

#define I2C_SDA1 21
#define I2C_SCL1 22

#define I2C_SDA2 32
#define I2C_SCL2 33

class ADXL_COMBO
{
private:
    ADXL345_WE adxl;

public:
    void setup()
    {
        Serial.begin(9600);
        Serial.println("ADXL_SETUP");

        Wire.begin(I2C_SDA1, I2C_SCL1);
        Wire.setClock(100000);

        // Überprüfen, ob der ADXL345 erkannt wird
        if (adxl.detect())
        {
            Serial.println("ADXL345 detected");
            adxl.powerOn();
            adxl.setRangeSetting(16); // Einstellung der Messbereichs auf +/-16g
            adxl.setSpiBit(0);        // I2C-Modus aktivieren
        }
        else
        {
            Serial.println("ADXL345 not detected");
        }
    }

    void loop()
    {
        Serial.println("ADXL_LOOP");
        // Daten vom Beschleunigungssensor lesen
        int x, y, z;
        adxl.readAccel(&x, &y, &z);
        Serial.print("X: ");
        Serial.print(x);
        Serial.print(" Y: ");
        Serial.print(y);
        Serial.print(" Z: ");
        Serial.println(z);

        delay(1000); // Eine Sekunde warten, bevor die nächste Messung durchgeführt wird
    }
};

#endif
