#include <Arduino.h>
#include <math.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#ifndef imu_6DOF_with_lib_H
#define imu_6DOF_with_lib_H

Adafruit_MPU6050 mpu;

class imu_6DOF_with_lib {
  private: 
    float acc_x, acc_y, acc_z;
    float gyro_x, gyro_y, gyro_z;
    float acc_x_winkel, acc_y_winkel, acc_z_winkel;

  public: 
      void setup() {

          if (!mpu.begin()) {
              Serial.println("Failed to find MPU6050 chip");
              while (1) {
                  delay(10);
              }
          }
          Serial.println("MPU6050 Found!");

          mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
          mpu.setGyroRange(MPU6050_RANGE_500_DEG);
          mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
      }

      void loop() {
          sensors_event_t a, g, temp;
          mpu.getEvent(&a, &g, &temp);

          acc_x = a.acceleration.x;
          acc_y = a.acceleration.y;
          acc_z = a.acceleration.z;

          /*
          // Ausgabe der Winkel
          Serial.print("acc_x_2: ");
          Serial.print(a.acceleration.x);
          Serial.print("   acc_y: ");
          Serial.print(a.acceleration.y);
          Serial.print("   acc_z: ");
          Serial.println(a.acceleration.z);
          */

          gyro_x = g.gyro.x;
          gyro_y = g.gyro.y;
          gyro_z = g.gyro.z;

          acc_x_winkel = atan2(acc_x , sqrt(pow(acc_y, 2) + pow(acc_z, 2))) * 180 / PI;
          acc_y_winkel = atan2(acc_y , sqrt(pow(acc_x, 2) + pow(acc_z, 2))) * 180 / PI;
      }

      float get_acc_x() { return acc_x; }
      float get_acc_y() { return acc_y; }
      float get_acc_z() { return acc_z; }
      float get_gyro_x() { return gyro_x; }
      float get_gyro_y() { return gyro_y; }
      float get_gyro_z() { return gyro_z; }
      float get_acc_x_winkel() { return acc_x_winkel; }
      float get_acc_y_winkel() { return acc_y_winkel; }
      float get_acc_z_winkel() { return acc_z_winkel; }
};

#endif
