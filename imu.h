#include <Wire.h>
#include <Arduino.h>
#include <math.h>
#include "datentypen.h"

#ifndef imu_3DOF_H
#define imu_3DOF_H
class IMU_3DOF {
  private: 
    const int mpu = 0x68; // MPU6050 I2C address
    float acc_x, acc_y, acc_z = 0.0;
    float acc_angle_x, acc_angle_y, acc_angle_z = 0.0; 
    float roll_x, pitch_y, yaw_z = 0.0; // was ist der Unterschied zum Winkel obendrüber?
    float elapsed_time, current_time, previous_time = 0;

  public:
    IMU_3DOF(): {}; // Konstruktor
    void setup(){
      Wire.begin();
      Wire.beginTransmission(mpu);
      Wire.write(0x6B);
      Wire.write(0x00);
      Wire.endTransmission(true);

      // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
      Wire.beginTransmission(mpu);
      Wire.write(0x1C);
      Wire.write(0x10);
      Wire.endTransmission(true);

      // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
      Wire.beginTransmission(mpu);
      Wire.write(0x1B);
      Wire.write(0x10);
      Wire.endTransmission(true);
      delay(20);

      //Perform accelerometer bias estimation
      for (int i = 0; i < numSamples; i++)
        {
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 6, true);
        acc_x = (Wire.read() << 8 | Wire.read())/4096.0;
        acc_y = (Wire.read() << 8 | Wire.read())/4096.0;
        acc_z = (Wire.read() << 8 | Wire.read())/4096.0;
        acc_bias_x += acc_x;
        acc_bias_y += acc_y;
        acc_bias_z += acc_z;
        }

      acc_bias_x /= numSamples;
      acc_bias_y /= numSamples;
      acc_bias_z /= numSamples;

    delay(3);
   }

    };
    void loop(){
      previous_time = current_time;
      current_time = millis();
      elapsed_time = (current_time - previous_time) / 1000.0;

      // Read accelerometer data
      Wire.beginTransmission(mpu);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(mpu, 6, true);

      acc_x = (Wire.read() << 8 | Wire.read())/4096.0;
      acc_y = (Wire.read() << 8 | Wire.read())/4096.0;
      acc_z = (Wire.read() << 8 | Wire.read())/4096.0;

      acc_x -= acc_bias_x;
      acc_y -= acc_bias_y;
      acc_z -= acc_bias_z-1;

      // Convert accelerometer values to degrees
      acc_angle_x = atan2(acc_y, sqrt(pow(acc_x, 2) + pow(acc_z, 2))) * 180.0 / M_PI;
      acc_angle_y = atan2(-acc_x, sqrt(pow(acc_y, 2) + pow(acc_z, 2))) * 180.0 / M_PI;
      acc_angle_z = 0;
    }
};
#endif

#ifndef IMU_6DOF_H
#define IMU_6DOF_H
class IMU_6DOF : public IMU_3DOF {
  private: 
    float gyro_omega_x, gyro_omega_y, gyro_omega_z = 0.0;
    float gyro_angle_x, gyro_angle_y, gyro_angle_z = 0.0;

    // Gyroscope bias estimation variables
    const int num_samples = 200;
    float gyro_bias_x, gyro_bias_y, gyro_bias_z = 0.0;

    //Postitionsvektor der imu
    Eigen::Vector3d position(0.0, 0.0, 0.0); //Abstand der IMU vom Boden in x,y,z Richtung
    
  public:
    IMU_6DOF(): {};

    void setup(){
      IMU_3DOF::setup(); // Call the setup function of the base class

      // Perform gyro bias estimation
      for (int i = 0; i < num_samples; i++) {
        Wire.beginTransmission(mpu);
        Wire.write(0x43);
        Wire.endTransmission(false);
        Wire.requestFrom(mpu, 6, true);

        gyro_omega_x = (Wire.read() << 8 | Wire.read()) / 131;
        gyro_omega_y = (Wire.read() << 8 | Wire.read()) / 131;
        gyro_omega_z = (Wire.read() << 8 | Wire.read()) / 131;

        gyro_bias_x += gyro_omega_x;
        gyro_bias_y += gyro_omega_y;
        gyro_bias_z += gyro_omega_z;

        delay(3); // Add a small delay between samples
      }

      gyro_bias_x /= num_samples;
      gyro_bias_y /= num_samples;
      gyro_bias_z /= num_samples;
    }
    void loop(){
      IMU_3DOF::loop(); // Call the loop function of the base class

      // Read gyroscope data
      Wire.beginTransmission(mpu);
      Wire.write(0x43);
      Wire.endTransmission(false);
      Wire.requestFrom(mpu, 6, true);

      gyro_omega_x = (Wire.read() << 8 | Wire.read()) / 131;
      gyro_omega_y = (Wire.read() << 8 | Wire.read()) / 131;
      gyro_omega_z = (Wire.read() << 8 | Wire.read()) / 131;

      // Apply gyro bias compensation
      gyro_omega_x -= gyro_bias_x;
      gyro_omega_y -= gyro_bias_y;
      gyro_omega_z -= gyro_bias_z;

      // Update gyro angles
      gyro_angle_x += ((gyro_omega_x + gyro_angle_x) * elapsed_time )/2;
      gyro_angle_y += ((gyro_omega_y + gyro_angle_y) * elapsed_time )/2;
      gyro_angle_z += ((gyro_omega_z + gyro_angle_z) * elapsed_time )/2;

      // Complementary filter - combine accelerometer and gyro angles
      roll_x = 0.96 * gyro_angle_x + 0.04 * acc_angle_x;
      pitch_y = 0.96 * gyro_angle_y + 0.04 * acc_angle_y;
      yaw_z = gyro_angle_z;
    }
};
#endif