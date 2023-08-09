#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <algorithm>
#include "globals.h"

class mpu6050 {
private:
  int mpu_address;  // MPU6050 I2C-Adresse

  void write_register(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(mpu_address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission(true);
  }

  uint8_t read_register(uint8_t reg) {
    Wire.beginTransmission(mpu_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)mpu_address, (size_t)1, (bool)true);
    if (Wire.available()) {
      return Wire.read();
    }
    return 0;
  }

  void read_raw_data(int16_t accel[3], int16_t gyro[3]) {
    accel[0] = (int16_t)((read_register(0x3B) << 8) | read_register(0x3C));
    accel[1] = (int16_t)((read_register(0x3D) << 8) | read_register(0x3E));
    accel[2] = (int16_t)((read_register(0x3F) << 8) | read_register(0x40));
    gyro[0] = (int16_t)((read_register(0x43) << 8) | read_register(0x44));
    gyro[1] = (int16_t)((read_register(0x45) << 8) | read_register(0x46));
    gyro[2] = (int16_t)((read_register(0x47) << 8) | read_register(0x48));
  }

  void cross_product(float v[], float w[], float result[]) {
    result[0] = v[1] * w[2] - v[2] * w[1];
    result[1] = v[2] * w[0] - v[0] * w[2];
    result[2] = v[0] * w[1] - v[1] * w[0];
  }

  float array_abs_sum(float array[3]) {
    float abs_sum = 0;
    for (int i = 0; i < 3; i++) {
        abs_sum += abs(array[i]);
    }
    return abs_sum;
}

  float accel_bias[3] = { 0.0, 0.0, 0.0 };  // Beschleunigungssensor-Bias
  float gyro_bias[3] = { 0.0, 0.0, 0.0 };   // Gyroskop-Bias
  float filter_koeffizient = 0.001;          // Filterkoeffizient ist zwischen 0 und 1 höher führt zu schwächerer Glättung
  float signal_historie[3];

public:
  mpu6050(int mpu_address) {
    this->mpu_address = mpu_address;
  }

  void initialize() {
    Wire.begin();
    // Initialisierung des MPU6050
    write_register(0x6B, 0x00);  // Stromversorgung aktivieren (Reset)
    write_register(0x1A, 0x03);  // DLPF-Konfiguration (Gyroskop)
    write_register(0x1B, 0x18);  // Gyroskop-Bereich: ±2000 °/s
    write_register(0x1C, 0x08);  // Beschleunigungssensor-Bereich: ±4g
  }

  void read_data(float accel[3], float gyro[3]) {
    int16_t accel_raw[3], gyro_raw[3];
    read_raw_data(accel_raw, gyro_raw);

    for (int i = 0; i < 3; i++) {
      accel[i] = ((float)accel_raw[i] - accel_bias[i]) * (4.0 / 32768.0);
      gyro[i] = ((float)gyro_raw[i] - gyro_bias[i]) * (2000.0 / (131.0 * 250.0));

      //exponential_filter(accel);
      //exponential_filter(gyro);
    }
  }

  void get_torque() {
    float vec_to_ground[3];
    vec_to_ground[0] = cc_to_ground[cc_to_ground_current].values[0];
    vec_to_ground[1] = cc_to_ground[cc_to_ground_current].values[1];
    vec_to_ground[2] = cc_to_ground[cc_to_ground_current].values[2];

    float accel[3], gyro[3];
    read_data(accel, gyro);  //später nur noch accel(aber korrigiert um gyro)
    float gravitational_force[3];
    float abs_sum_accel = array_abs_sum(accel);
    gravitational_force[0] = (accel[0]/abs_sum_accel)*9.81*cube_mass;
    gravitational_force[1] = (accel[1]/abs_sum_accel)*9.81*cube_mass;
    gravitational_force[2] = (accel[2]/abs_sum_accel)*9.81*cube_mass;   
     
    cross_product(gravitational_force, vec_to_ground, cube_torque);
  }

  void get_cc_to_ground(float output_cg_ground_vector[3]) {
    float accel[3], gyro[3];
    read_data(accel, gyro);
    float minDistance = INFINITY;
    int minIndex = -1;

    for (int i = 0; i < 26; i++) {
      float distance = 0.0;
      for (int j = 0; j < 3; j++) {
        float diff = cc_to_ground[i].values[j] - accel[j];
        distance += diff * diff;
      }
      if (distance < minDistance) {
        minDistance = distance;
        minIndex = i;
      }
    }
    if (minIndex != -1) {
      printf("Der ähnlichste Array ist: %s\n", cc_to_ground[minIndex].label);
      output_cg_ground_vector[0] = cc_to_ground[minIndex].values[0];
      output_cg_ground_vector[1] = cc_to_ground[minIndex].values[1];
      output_cg_ground_vector[2] = cc_to_ground[minIndex].values[2];
    }
  }

  void calibrate(int num_samples = 200) {
    // Führe eine Kalibrierung durch, um den Bias zu bestimmen
    int16_t accel_raw[3] = { 0, 0, 0 };
    int16_t gyro_raw[3] = { 0, 0, 0 };
    // Sammle Daten für die Kalibrierung
    for (int i = 0; i < num_samples; i++) {
      read_raw_data(accel_raw, gyro_raw);

      for (int j = 0; j < 3; j++) {
        accel_bias[j] += (float)accel_raw[j];
        gyro_bias[j] += (float)gyro_raw[j];
        delay(2);
      }
    }
    // Berechne den Durchschnitt der Bias-Werte
    for (int i = 0; i < 3; i++) {
      accel_bias[i] /= (float)num_samples;
      gyro_bias[i] /= (float)num_samples;
    }
    accel_bias[2] -= (32768.0 / 4.0);
  }

  void exponential_filter(float signal[3]) {
    // Berechnung des gefilterten Ausgangswerts
    for (int i = 0; i < 3; i++) {
      signal[i] = filter_koeffizient * signal[i] + (1 - filter_koeffizient) * signal_historie[i];
      signal_historie[i] = signal[i];
    }
  }
};
#endif