// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float positionX = 0.0;
float velocityX = 0.0;
float accelerationX = 0.0;
float positionY = 0.0;
float velocityY = 0.0;
float accelerationY = 0.0;
float positionZ = 0.0;
float velocityZ = 0.0;
float accelerationZ = 0.0;
unsigned long lastUpdateTime = 0;

void setup(void)
{
    Serial.begin(115200);
    while (!Serial)
        delay(10); // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit MPU6050 test!");

    // Try to initialize!
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange())
    {
    case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
    case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
    case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
    case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
    }
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange())
    {
    case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
    case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
    case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
    case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
    }

    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth())
    {
    case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
    case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
    case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
    case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
    case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
    case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
    case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
    }

    Serial.println("");
    delay(100);
}
void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Integrate acceleration to obtain velocity 
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastUpdateTime) / 1000.0; // Convert milliseconds to seconds
  lastUpdateTime = currentTime;

  static float prevVelocityX = 0;
  float prevAccelerationX = accelerationX;
  accelerationX = a.acceleration.x;
  velocityX += (accelerationX + prevAccelerationX) * deltaTime / 2.0;
  positionX += (velocityX + prevVelocityX) * deltaTime / 2.0;
  prevVelocityX = velocityX;

  static float prevVelocityY = 0;
  float prevAccelerationY = accelerationY;
  accelerationY = a.acceleration.y;
  velocityY += (accelerationY + prevAccelerationY) * deltaTime / 2.0;
  positionY += (velocityY + prevVelocityY) * deltaTime / 2.0;
  prevVelocityY = velocityY;

  static float prevVelocityZ = 0;
  float prevAccelerationZ = accelerationZ;
  accelerationZ = a.acceleration.z;
  velocityZ += (accelerationZ + prevAccelerationZ) * deltaTime / 2.0;
  positionZ += (velocityZ + prevVelocityZ) * deltaTime / 2.0;
  prevVelocityZ = velocityZ;
    */

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(accelerationX);
  Serial.print(", Y: ");
  Serial.print(accelerationY);
  Serial.print(", Z: ");
  Serial.print(accelerationZ);
  Serial.println(" m/s^2");
/*
  Serial.print("Velocity X: ");
  Serial.print(velocityX);
  Serial.print(", Y: ");
  Serial.print(velocityY);
  Serial.print(", Z: ");
  Serial.print(velocityZ);
  Serial.println(" m/s");

  Serial.print("Position X: ");
  Serial.print(positionX);
  Serial.print(", Y: ");
  Serial.print(positionY);
  Serial.print(", Z: ");
  Serial.print(positionZ);
  Serial.println(" m");
*/
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
/*
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");
*/
//Ich will die  Winkel berechnen
  float angle_calc_x = (atan2(a.acceleration.x, a.acceleration.z) * 180) / PI;
  float angle_calc_y = (atan2(a.acceleration.y, a.acceleration.z) * 180) / PI;
  float angle_calc_z = (atan2(a.acceleration.x, a.acceleration.y) * 180) / PI;

  Serial.println("");
  delay(500);
}

