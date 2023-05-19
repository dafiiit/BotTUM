// #include "datentypen.h"

//deklaration
#ifndef HALLSENSOR_H
#define HALLSENSOR_H
class HALLSENSOR {
  private: 
    volatile bool state = false;    //Variable for reading the hall status
    int pin;                        //beim ESP32 Interrupt pin = Physikalischer Pin
    int anz_magneten;               //Anzahl der Magneten(wahrscheinlich 2)
    float rpm = 0;
    float phi_punkt_scheibe = 0;
    volatile double time_trig = 0;
    volatile double time_now = 0;
    volatile double time_delta = 0;
    int abtastrate;        //Abtastrate für die serielle Kommunikation
  
  public:
    HALLSENSOR();
    void hall_setup();
    float get_hall_phi_punkt_scheibe();  
    float get_hall_rpm();     
  private:
    static void hall_isr();
};
#endif

//Konstruktormethode, in welcher die Attribute anz_magneten, abtastrate und pin gesetzt werden
HALLSENSOR::HALLSENSOR(
  int anz_magneten = 2, 
  int abtastrate = 115200, 
  int pin
  ) : anz_magneten(anz_magneten), abtastrate(abtastrate), pin(pin) {}

void HALLSENSOR::hall_setup(){
  pinMode(self.pin, INPUT);
  Serial.begin(self.abtastrate);
  attachInterrupt(digitalPinToInterrupt(self.pin), hall_ISR, RISING); 
}
void HALLSENSOR::hall_isr(){       
  self.state = !self.state;
  time_delta = time_now - time_trig;
  time_trig = time_now;
}
float HALLSENSOR::get_hall_phi_punkt_scheibe(){
  time_now = millis();
  if (time_delta)
  {
    self.phi_punkt_scheibe = (1 /(time_delta / 1000))/self.anz_magneten;
    return self.phi_punkt_scheibe;
  }
}
float HALLSENSOR::get_hall_rpm(){
  time_now = millis();
  if (time_delta)
  {
    self.rpm = (1 /( (time_delta / 1000) * 60) )/self.anz_magneten;
    return self.rpm;
  }
}
