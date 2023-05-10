#include "datentypen.h"
//deklaration
#ifndef IMU_H
#define IMU_H
class IMU {
  private: 
    double x;
    double y;
    double z;
    double pin_SCL;
    double pin_SCA;
  
  public:
    IMU(double x, double y, double z, double pin_SCL, double pin_SCA);
    void imu_setup();
};

#endif

#ifndef IMU_6DOF_H
#define IMU_6DOF_H
class IMU_6DOF : public IMU {
  private: 
    double gyro_x;
    double gyro_y;
    double gyro_z;
  public:
      IMU_6DOF(double x, double y, double z, double gyro_x, double gyro_y, double gyro_z, double pin_SCL, double pin_SCA);
};
#endif

#ifndef IMU_9DOF_H
#define IMU_9DOF_H
class IMU_9DOF : public IMU_6DOF {
    private: 
        double mag_x;
        double mag_y;
        double mag_z;
    
    public:
        IMU_9DOF(double x, double y, double z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z, , double pin_SCL, double pin_SCA);
};
#endif
//implementierung
// Hier implementieren wir die Klasse IMU mit den privaten Attributen x, y und z
const int IMU_pin_SCL = 22;
const int IMU_pin_SCA = 21;
const int IMU_baudrate = 9600;
const int IMU_pin_pullup = 19;
const int IMU_pin_output = 2;
//Register Map:
#define ADXL345 0x53 //Adress chosen by grounding SDO
#define DATAx0 0x32
#define DATAx1 0x33
#define DATAy0 0x34
#define DATAy1 0x35
#define DATAz0 0x36
#define DATAz1 0x37
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define FULLRES_2g B00001000
#define FULLRES_16g B00001011
#define WRITE 0xA6
#define READ 0xA7
IMU::IMU(double x, double y, double z, double pin_SCL, double pin_SCA) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->pin_SCL = IMU_pin_SCL;
  this->pin_SCA = IMU_pin_SCA;
}
void imu_setup(){
  Serial.begin(IMU_baudrate);
  Serial.println();         
  Serial.println();         
  Serial.println("Start");
  delay(5);
  Wire.begin(esp32_SDA, esp32_SCL, 100000);       //Warum 100000???

  pinMode(IMU_pin_pullup, INPUT_PULLUP); 
  pinMode(IMU_pin_output, OUTPUT);           
  attachInterrupt(digitalPinToInterrupt(19),)

  //Setup power management  

  Wire.beginTransmission(ADXL345);
  Wire.write(POWER_CTL);
  Wire.write(8); //15 to binary: 1111, corresponds to 3200Hz data rate and 1600Hz Bandwidth
  Wire.endTransmission(true);
  Serial.println("Powermode & BW_RATE written");
  delay(20);

  //Setup range

  Wire.beginTransmission(ADXL345);
  Wire.write(DATA_FORMAT);
  Wire.write(FULLRES_2g);
  Wire.endTransmission(true);
  Serial.println("Range set to 2g");
  delay(20);

  //

  Serial.println("Setup complete");
  delay(1000);
}
void imu_loop(){
  byte buff[2];
 
  Wire.beginTransmission(ADXL345);
  Wire.write(DATAx1);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);
  int n = 0;

  while(Wire.available())
    {

      buff[n] = Wire.read();
      n++;    
    }
  
  Wire.beginTransmission(ADXL345);
  Wire.write(DATAx0);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);

  while(Wire.available())
  {
    buff[n]=Wire.read();
    n++;
  }
  //Refer to fig.49 of Datasheet
  //Format Datatype from byte to 10bit int number

  Wire.endTransmission();

  DATA=(int16_t)(buff[0]<<8|buff[1]);

  /*
  if(abs(DATA-lastDATA)>=250)
  {
    err++;
    Serial.print("Error caught, n° ");
    Serial.print(err);
    Serial.print("  ");
    Serial.print(DATA-lastDATA);
    Serial.println();
    }  
  lastDATA=DATA;
  */
  Serial.println(DATA);
  delay(10); //100Hz data rate
}

// Hier implementieren wir die Klasse IMU_6DOF mit den privaten Attributen gyro_x, gyro_y und gyro_z
IMU_6DOF::IMU_6DOF(double x, double y, double z, double gyro_x, double gyro_y, double gyro_z, double pin_SCL, double pin_SCA) : IMU(x, y, z, pin_SCL, pin_SCA) {
  this->gyro_x = gyro_x;
  this->gyro_y = gyro_y;
  this->gyro_z = gyro_z;
}

// Hier implementieren wir die Klasse IMU_9DOF mit den privaten Attributen mag_x, mag_y und mag_z
IMU_9DOF::IMU_9DOF(double x, double y, double z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z, double pin_SCL, double pin_SCA) : IMU_6DOF(x, y, z, gyro_x, gyro_y, gyro_z, pin_SCL, pin_SCA) {
  this->mag_x = mag_x;
  this->mag_y = mag_y;
  this->mag_z = mag_z;
}