//dies ist der Code von Zlatina
#include <Wire.h>

const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float gyroAngleX_map, gyroAngleY_map;
float roll, pitch, yaw;
float elapsedTime, currentTime, previousTime;
int c = 0;

// Gyroscope bias estimation variables
const int numSamples = 200;
float gyroBiasX = 0.0, gyroBiasY = 0.0, gyroBiasZ = 0.0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission(true);

  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x10);
  Wire.endTransmission(true);
  delay(20);

  // Perform gyro bias estimation
  for (int i = 0; i < numSamples; i++) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

    gyroBiasX += GyroX;
    gyroBiasY += GyroY;
    gyroBiasZ += GyroZ;

    delay(3); // Add a small delay between samples
  }

  gyroBiasX /= numSamples;
  gyroBiasY /= numSamples;
  gyroBiasZ /= numSamples;
} 
void loop() {
  // Read accelerometer data
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AccX = (Wire.read() << 8 | Wire.read())/4096.0;
  AccY = (Wire.read() << 8 | Wire.read())/4096.0;
  AccZ = (Wire.read() << 8 | Wire.read())/4096.0;

  // Convert accelerometer values to degrees
  accAngleX = atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180.0 / PI;
  accAngleY = atan(-AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180.0 / PI;

  // Read gyroscope data
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

  // Apply gyro bias compensation
  GyroX -= gyroBiasX;
  GyroY -= gyroBiasY;
  GyroZ -= gyroBiasZ;

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0;
  // Update gyro angles
  gyroAngleX += GyroX * elapsedTime;
  gyroAngleX_map=gyroAngleX*4;
  gyroAngleY += GyroY * elapsedTime;
  gyroAngleY_map=gyroAngleY*4;
  yaw += GyroZ * elapsedTime;

  // Complementary filter - combine accelerometer and gyro angles
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("   Pitch: ");
  Serial.print(pitch);
  Serial.print("   Yaw: ");
  Serial.println(yaw);
}
