#include <Wire.h>
#include <Arduino.h>
#include <math.h>

#ifndef imu_3DOF_H
#define imu_3DOF_H
class IMU_3DOF {
  protected: 
    const int mpu = 0x68; // MPU6050 I2C address
    float elapsed_time, current_time, previous_time = 0.0;

    std::vector<float> acc = {0.0 , 0.0 , 0.0};
    std::vector<float> acc_angle = {0.0 , 0.0 , 0.0};
    std::vector<float> acc_bias = {0.0 , 0.0 , 0.0};

    int num_samples = 200;

    float acc_lsb = 4096.0; //+-8g
  public:
    IMU_3DOF() {}; // Konstruktor

    float get_acc(int richtung) const { return acc[richtung]; }
    float get_acc_angle(int richtung) const { return acc_angle[richtung]; }
    float get_acc_bias(int richtung) const { return acc_bias[richtung]; }

    void setup(){
      Wire.begin();
      Wire.beginTransmission(mpu);
      Wire.write(0x6B);     //Power management aufwachen
      Wire.write(0x00);     
      Wire.endTransmission(true);

      // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
      Wire.beginTransmission(mpu);
      Wire.write(0x1C);     //
      Wire.write(0x10);     //
      Wire.endTransmission(true);

      //Perform accelerometer bias estimation
      for (int i = 0; i < num_samples; i++)
        {
        Wire.beginTransmission(mpu);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(static_cast<uint16_t>(mpu), static_cast<size_t>(6), true);
        acc[0] = (Wire.read() << 8 | Wire.read())/acc_lsb;
        acc[1] = (Wire.read() << 8 | Wire.read())/acc_lsb;
        acc[2] = (Wire.read() << 8 | Wire.read())/acc_lsb;
        acc_bias[0] += acc[0];
        acc_bias[1] += acc[1];
        acc_bias[2] += acc[2];
        }

      acc_bias[0] /= num_samples;
      acc_bias[1] /= num_samples;
      acc_bias[2] /= num_samples;

    delay(3);
   }
    void loop(){
      previous_time = current_time;
      current_time = millis();
      elapsed_time = (current_time - previous_time) / 1000.0;

      // Read accelerometer data
      Wire.beginTransmission(mpu);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(static_cast<uint16_t>(mpu), static_cast<size_t>(6), true);

      //Wire.requestFrom(mpu, 6, true);

      acc[0] = (Wire.read() << 8 | Wire.read())/acc_lsb;
      acc[1] = (Wire.read() << 8 | Wire.read())/acc_lsb;
      acc[2] = (Wire.read() << 8 | Wire.read())/acc_lsb;

      acc[0] -= acc_bias[0];
      acc[1] -= acc_bias[1];
      acc[2] -= acc_bias[2]-1;

      // Convert accelerometer values to degrees
      acc_angle[0] = atan2(acc[1], sqrt(pow(acc[0], 2) + pow(acc[2], 2))) * 180.0 / M_PI;
      acc_angle[1] = atan2(-acc[0], sqrt(pow(acc[1], 2) + pow(acc[2], 2))) * 180.0 / M_PI;
      acc_angle[2] = 0;
    }
};
#endif

#ifndef IMU_6DOF_H
#define IMU_6DOF_H
class IMU_6DOF : public IMU_3DOF {
  private: 

    //Postitionsvektor der imu
    std::vector<float> position = {0.0 , 0.0, 0.0};
    std::vector<float> gyro_omega = {0.0 , 0.0 , 0.0};
    std::vector<float> gyro_angle = {0.0 , 0.0 , 0.0};
    std::vector<float> gyro_complementary_angle = {0.0 , 0.0 , 0.0};
    std::vector<float> gyro_fancy_angle = {0.0 , 0.0 , 0.0};
    std::vector<float> gyro_bias = {0.0 , 0.0 , 0.0};

    float gyro_lsb = 32.8; // =1000°/s
    
  public:
    IMU_6DOF() {};

    float get_gyro_omega(int richtung) const { return gyro_omega[richtung]; }
    float get_gyro_angle(int richtung) const { return gyro_angle[richtung]; }
    float get_gyro(int richtung) const { return gyro_complementary_angle[richtung]; }
    float get_fancy_angle(int richtung) const { return gyro_complementary_angle[richtung]; }

    void setup(){
      IMU_3DOF::setup(); // Call the setup function of the base class

      // Configure Gyro Sensitivity - Full Scale Range (default +/- 1000deg/s)
      Wire.beginTransmission(mpu);
      Wire.write(0x1B);
      Wire.write(0x10);
      Wire.endTransmission(true);
      delay(20);

      // Perform gyro bias estimation
      for (int i = 0; i < num_samples; i++) {
        Wire.beginTransmission(mpu);
        Wire.write(0x43);
        Wire.endTransmission(false);
        //Wire.requestFrom(mpu, 6, true);
        Wire.requestFrom(static_cast<uint16_t>(mpu), static_cast<size_t>(6), true);

        gyro_omega[0] = (Wire.read() << 8 | Wire.read()) / gyro_lsb;
        gyro_omega[1] = (Wire.read() << 8 | Wire.read()) / gyro_lsb;
        gyro_omega[2] = (Wire.read() << 8 | Wire.read()) / gyro_lsb;

        gyro_bias[0] += gyro_omega[0];
        gyro_bias[1] += gyro_omega[1];
        gyro_bias[2] += gyro_omega[2];

        delay(3); // Add a small delay between samples
      }

      gyro_bias[0] /= num_samples;
      gyro_bias[1] /= num_samples;
      gyro_bias[2] /= num_samples;
    }
    void loop(){
      IMU_3DOF::loop(); // Call the loop function of the base class

      // Read gyroscope data
      Wire.beginTransmission(mpu);
      Wire.write(0x43);
      Wire.endTransmission(false);
      Wire.requestFrom(static_cast<uint16_t>(mpu), static_cast<size_t>(6), true);

      //Wire.requestFrom(mpu, 6, true);

      gyro_omega[0] = (Wire.read() << 8 | Wire.read()) / gyro_lsb;
      gyro_omega[1] = (Wire.read() << 8 | Wire.read()) / gyro_lsb;
      gyro_omega[2] = (Wire.read() << 8 | Wire.read()) / gyro_lsb;

      // Apply gyro bias compensation
      gyro_omega[0] -= gyro_bias[0];
      gyro_omega[1] -= gyro_bias[1];
      gyro_omega[2] -= gyro_bias[2];

      // Update gyro angles
      gyro_angle[0] += ((gyro_omega[0] + gyro_angle[0]) * elapsed_time )/2;
      gyro_angle[1] += ((gyro_omega[1] + gyro_angle[1]) * elapsed_time )/2;
      gyro_angle[2] += ((gyro_omega[2] + gyro_angle[2]) * elapsed_time )/2;
      
      // Complementary filter - combine accelerometer and gyro angles
      gyro_complementary_angle[0] = 0.96 * gyro_angle[0] + 0.04 * acc_angle[0];
      gyro_complementary_angle[1] = 0.96 * gyro_angle[1] + 0.04 * acc_angle[1];
      gyro_complementary_angle[2] = gyro_angle[2];

      //noch einbauen: setzen mancher gyro_omega werte auf 0 je nachdem um welche Achse wir rotieren

      acc_zentral[0] = gyro_omega[1] (gyro_omega[0] * position[1]- gyro_omega[1]*position[0]) - gyro_omega[2]*(gyro_omega[2]*position[0] - gyro_omega[0]*position[2]);
      acc_zentral[1] = gyro_omega[2] (gyro_omega[1] * position[2]- gyro_omega[2]*position[1]) - gyro_omega[0]*(gyro_omega[0]*position[1] - gyro_omega[1]*position[0]);
      acc_zentral[2] = gyro_omega[0] (gyro_omega[2] * position[0]- gyro_omega[0]*position[2]) - gyro_omega[1]*(gyro_omega[1]*position[2] - gyro_omega[2]*position[1]);

      acc_g[0] = acc[0] - acc_zentral[0];
      acc_g[1] = acc[1] - acc_zentral[1];
      acc_g[2] = acc[2] - acc_zentral[2];

      fancy_angle[0] = atan2(acc_g[1], sqrt(pow(acc_g[0], 2) + pow(acc_g[2], 2))) * 180.0 / M_PI;
      fancy_angle[1] = atan2(-acc_g[0], sqrt(pow(acc_g[1], 2) + pow(acc_g[2], 2))) * 180.0 / M_PI;
      fancy_angle[2] = gyro_angle[2];
    }
};
#endif