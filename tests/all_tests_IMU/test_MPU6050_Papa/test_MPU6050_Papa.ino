#include <Wire.h>

class mpu6050 {
private:
  int mpu_address = 0x68; // MPU6050 I2C-Adresse

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
    Wire.requestFrom(mpu_address, 1, true);
    if (Wire.available()) {
      return Wire.read();
    }
    return 0;
  }

  float accel_bias[3] = {0.0, 0.0, 0.0}; // Beschleunigungssensor-Bias
  float gyro_bias[3] = {0.0, 0.0, 0.0}; // Gyroskop-Bias

public:
  void set_i2c_address(int address)
  {
    mpu_address = address;
  }

  void initialize() 
  {
    Wire.begin();
    // Initialisierung des MPU6050
    write_register(0x6B, 0x00); // Stromversorgung aktivieren (Reset)
    write_register(0x1A, 0x03); // DLPF-Konfiguration (Gyroskop)
    write_register(0x1B, 0x18); // Gyroskop-Bereich: ±2000 °/s
    write_register(0x1C, 0x08); // Beschleunigungssensor-Bereich: ±4g
  }

  void read_raw_data(int16_t accel[3], int16_t gyro[3]) 
  {
    accel[0] = (int16_t)((read_register(0x3B) << 8) | read_register(0x3C));
    accel[1] = (int16_t)((read_register(0x3D) << 8) | read_register(0x3E));
    accel[2] = (int16_t)((read_register(0x3F) << 8) | read_register(0x40));
    gyro[0] = (int16_t)((read_register(0x43) << 8) | read_register(0x44));
    gyro[1] = (int16_t)((read_register(0x45) << 8) | read_register(0x46));
    gyro[2] = (int16_t)((read_register(0x47) << 8) | read_register(0x48));
  }

  void read_data(float accel[3], float gyro[3]) 
  {
    int16_t accel_raw[3], gyro_raw[3];
    read_raw_data(accel_raw, gyro_raw);

    for (int i = 0; i < 3; i++) {
      accel[i] = ((float)accel_raw[i] - accel_bias[i]) * (4.0 / 32768.0);
      gyro[i] = ((float)gyro_raw[i] - gyro_bias[i]) * (2000.0 / (131.0 * 250.0));
    }
  }

  void calibrate(int num_samples = 200) {
    // Führe eine Kalibrierung durch, um den Bias zu bestimmen
    int16_t accel_raw[3] = {0, 0, 0};
    int16_t gyro_raw[3] = {0, 0, 0};
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

};

mpu6050 mpu;

void setup() {
  Serial.begin(9600);
  mpu.set_i2c_address(0x68);
  mpu.initialize();
  mpu.calibrate(); // Führe die Kalibrierung aus
}

void loop() {
  float accel[3], gyro[3];
  mpu.read_data(accel, gyro);

  // Verarbeite die Sensorwerte
  Serial.print("Beschleunigung: X = ");
  Serial.print(accel[0]);
  Serial.print(" Y = ");
  Serial.print(accel[1]);
  Serial.print(" Z = ");
  Serial.print(accel[2]);

  Serial.print(" | Gyroskop: X = ");
  Serial.print(gyro[0]);
  Serial.print(" Y = ");
  Serial.print(gyro[1]);
  Serial.print(" Z = ");
  Serial.println(gyro[2]);

  delay(1000);
}
