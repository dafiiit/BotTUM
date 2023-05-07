#include "declare.h"
#include <cmath>
#include <Wire.h>
#include <tgmath.h>
#include <vector>
#include <algorithm>

// Implementierung der Konstruktor Funktion und der get-Methoden des Quadrats

// Hier implementieren wir die Klasse Quadrat mit den privaten Attributen hoehe, schwerpunkt und Gewicht
Quadrat_hoehe_schwerpunkt = 0.1 //m über dem Boden
Quadrat_gewicht_body = 0.6 //kg von allem außer der Scheibe/n
Quadrat_gewicht_scheibe = 0.1 //kg pro Scheibe
QUADRAT::QUADRAT(double hoehe_schwerpunkt, double gewicht_body, double gewicht_scheibe, POSITION position, INERTIA inertia, HALLSENSOR hall_sensor, IMU imu, IMU_6DOF imu_6dof, IMU_9DOF imu_9dof);{
  this->hoehe_schwerpunkt = Quadrat_hoehe_schwerpunkt;
  this->gewicht_body = Quadrat_gewicht_body;
  this->gewicht_scheibe = Quadrat_gewicht_scheibe;
}
void QUADRAT::stand_up() {
  Serial.println("stand_up");
}
void QUADRAT::balance() {
  Serial.println("balance");
}
void QUADRAT::KannteAufFlaeche() {
  Serial.println("KannteAufFlaeche");
}
void QUADRAT::FlaecheAufKannte() {
  Serial.println("FlaecheAufKannte");
}
void QUADRAT::EckeAufKannte() {
  Serial.println("EckeAufKannte");
}
void QUADRAT::KannteAufEcke() {
  Serial.println("KannteAufEcke");
}
void QUADRAT::EckeAufFlaeche() {
  Serial.println("EckeAufFlaeche");
}
void QUADRAT::FlaecheAufEcke() {
  Serial.println("FlaecheAufEcke");
}
void QUADRAT::turn_left() {
  Serial.println("turn_left");
}
void QUADRAT::turn_right() {
  Serial.println("turn_right");
}

// Hier implementieren wir die Klasse Inertia
INERTIA::INERTIA(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33){
  this->m11 = m11;
  this->m12 = m11;
  this->m13 = m11;
  this->m21 = m11;
  this->m22 = m11;
  this->m23 = m11;
  this->m31 = m11;
  this->m32 = m11;
  this->m33 = m11;
}// noch mal schauen, ob nicht das andere schon die Implementierung ist. 

// Hier implementieren wir die Klasse Position
POSITION::POSITION(double x, double y){
  this->x = x;
  this->y = y;
}

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

// Hier implementieren wir die Klasse HallSensor
int HallSensor_pin = 3; //Sensor pin
volatile int HallSensor_state = 0;   //Variable for reading the hall status
int HallSensor_interrupt_pin = 0;    //Nicht der Physikalische Pin. Muss man nachschauen.
int HallSensor_anz_magneten = 2;

HALLSENSOR::HALLSENSOR(double HallSensor_phi_p_s, int HallSensor_pin) {
  this->HallSensor_phi_p_s = HallSensor_phi_p_s;
  this->HallSensor_pin = HallSensor_pin;
}
void HALLSENSOR::hall_setup(){
  pinMode(HallSensor_pin, INPUT);
  attachInterrupt(HallSensor_interrupt_pin,pin_ISR,RISING);    
}
void HALLSENSOR::pin_ISR(){       //Interrupt Service Routine
  HallSensor_state = digitalRead(HallSensor_pin);
  getHallPhiPS();     //berechnet die Drehzahl
}
double HALLSENSOR::getHallPhiPS(){

  unsigned long current_time = micros(); // Aktuelle Zeit ermitteln
  unsigned long time_difference = current_time - HallSensor_previous_time; // Zeitdifferenz berechnen
  HallSensor_previous_time = current_time; // Setze den vorherigen Zeitpunkt auf die aktuelle Zeit

  std::vector<int> values(5); // Ein Vector von 5 ganzzahligen Werten
  // Lösche das letzte Element
  values.pop_back();
  // Verschiebe jedes Element um eine Position nach hinten
  for (int i = 3; i >= 0; i--) {
    values[i + 1] = values[i];
  }
  // Hänge das neue Element an die erste Position an
  values[0] = microseconds;

  //berechne den Median der Zeiten
  std::vector<int> sortedVec = values;
  std::sort(sortedVec.begin(), sortedVec.end());
  int median;
  if (sortedVec.size() % 2 == 0) {
    median = (sortedVec[sortedVec.size()/2 - 1] + sortedVec[sortedVec.size()/2]) / 2;
  } else {
    median = sortedVec[sortedVec.size()/2];
  }
  //Wandle die Periodenzeit in die Drehgeschwindigkeit um
  HallSensor.phi_p_s = calculateAngularVelocity(Hall_anz_magneten, median) 
}
double HALLSENSOR::calculateAngularVelocity(int x, double timeInSeconds) {
  double timePerRevolution = timeInSeconds / x;
  double angularVelocity = 1.0 / timePerRevolution;
  return angularVelocity;
}
}




