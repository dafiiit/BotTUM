#include "datentypen.h"

//deklaration
#ifndef HALLSENSOR_H
#define HALLSENSOR_H
class HALLSENSOR {
  private: 
    double HallSensor_phi_p_s;
    int HallSensor_pin;
    unsigned long HallSensor_previous_time = 0;
    int HallSensor_anz_magneten = 2;
  
  public:
    HALLSENSOR(double HallSensor_phi_p_s, int HallSensor_pin);
    void hall_setup();
    double getHallPhiPS();
    
  private:
    static void pin_ISR();
    double calculateAngularVelocity(int x, double timeInSeconds);
};
#endif
//implementierung
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
  attachInterrupt(digitalPinToInterrupt(HallSensor_interrupt_pin),pin_ISR,FALLING);    
}
void HALLSENSOR::pin_ISR(){       //Interrupt Service Routine
  //HallSensor_state = digitalRead(HallSensor_pin);
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