#include "datentypen.h"
//Code für das Quadrat
#ifndef QUADRAT_H
#define QUADRAT_H
class QUADRAT {
  private:
    double hoehe_schwerpunkt = 0.1; //m über dem Boden
    double gewicht_body = 0.6;      //kg von allen Elementen außer der Scheibe
    double gewicht_scheibe = 0.1;   //kg pro Scheibe
    POSITION position;              //Position des Quadrats
    INERTIA inertia;                // Inertia als Attribut von Quadrat
    HALLSENSOR hall_sensor;         // HallSensor als Attribut von Quadrat
    IMU imu;                        // IMU als Attribut von Quadrat
    IMU_6DOF imu_6dof;              // IMU_6DOF als Attribut von Quadrat
    IMU_9DOF imu_9dof;              // IMU_9DOF als Attribut von Quadrat
  
  public:
    //Konstruktor Methode
    QUADRAT();
    //Methoden zum bewegen
    void stand_up(){
      Serial.println("stand_up");
      };
    void balance(){
      Serial.println("balance");
      };
    void KannteAufFlaeche(){
      Serial.println("KannteAufFlaeche");
      };
    void FlaecheAufKannte(){
      Serial.println("FlaecheAufKannte");
      };
    void EckeAufKannte(){
      Serial.println("EckeAufKannte");
      };
    void KannteAufEcke(){
      Serial.println("KannteAufEcke");
      };
    void EckeAufFlaeche(){
      Serial.println("EckeAufFlaeche");
      };
    void FlaecheAufEcke(){
      Serial.println("FlaecheAufEcke");
      };
    void turn_left(){
      Serial.println("turn_left");
      };
    void turn_right(){
      Serial.println("turn_right");
      };
};
#endif

QUADRAT::QUADRAT(double hoehe_schwerpunkt, double gewicht_body, double gewicht_scheibe, POSITION position, INERTIA inertia, HALLSENSOR hall_sensor, IMU imu, IMU_6DOF imu_6dof, IMU_9DOF imu_9dof);{
  this->hoehe_schwerpunkt = Quadrat_hoehe_schwerpunkt;
  this->gewicht_body = Quadrat_gewicht_body;
  this->gewicht_scheibe = Quadrat_gewicht_scheibe;
}
