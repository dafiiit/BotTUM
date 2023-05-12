#include "datentypen.h"

//Datentypen nochmal überprüfen und Sinnvoll anpassen (Rückgabedatentypen von Funktionen) und so

//deklaration
#ifndef HALLSENSOR_H
#define HALLSENSOR_H
class HALLSENSOR {
  private: 
    volatile bool HallSensor_state = false;   //Variable for reading the hall status
    int HallSensor_pin = 19;                  //beim ESP32 Interrupt pin = Physikalischer Pin
    int HallSensor_anz_magneten = 2;
    double HallSensor_rpm = 0;
    double HallSensor_PhiPS = 0;
    volatile double time_trig = 0;
    volatile double time_now = 0;
    volatile float time_delta = 0;
    int HallSensor_Abtastrate = 115200;
  
  public:
    HALLSENSOR();
    void hall_setup();
    double get_hall_PhiPS();  
    double get_hall_RPM();     
  private:
    static void hall_ISR();
};
#endif

HALLSENSOR::HALLSENSOR() {}

void HALLSENSOR::hall_setup(){
  pinMode(HallSensor_pin, INPUT);
  Serial.begin(HallSensor_Abtastrate);
  attachInterrupt(digitalPinToInterrupt(HallSensor_pin), hall_ISR, RISING); 
}
void HALLSENSOR::hall_ISR(){       
  HallSensor_state = !HallSensor_state;
  time_delta = time_now - time_trig;
  time_trig = time_now;
}
double HALLSENSOR::get_hall_PhiPS(){
  time_now = millis();
  if (time_delta)
  {
    double HallSensor_PhiPS = (1 /(time_delta / 1000))/HallSensor_anz_magneten;
    return HallSensor_PhiPS;
  }
}
double HALLSENSOR::get_hall_RPM(){
  time_now = millis();
  if (time_delta)
  {
    HallSensor_rpm = (1 /( (time_delta / 1000) * 60) )/HallSensor_anz_magneten;
    return HallSensor_rpm;
  }
}
