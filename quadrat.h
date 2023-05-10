#include "datentypen.h"
//Code für das Quadrat
#ifndef QUADRAT_H
#define QUADRAT_H
class QUADRAT {
  private:
    static const double hoehe_schwerpunkt; 
    static const double gewicht_body;      
    static const double gewicht_scheibe;   
    POSITION position;              //Position des Quadrats
    INERTIA inertia;                // Inertia als Attribut von Quadrat
    HALLSENSOR hall_sensor;         // HallSensor als Attribut von Quadrat
    IMU imu;                        // IMU als Attribut von Quadrat
    IMU_6DOF imu_6dof;              // IMU_6DOF als Attribut von Quadrat
    IMU_9DOF imu_9dof;              // IMU_9DOF als Attribut von Quadrat
  
  public:
    // Konstruktor Methode
    QUADRAT(double hoehe_schwerpunkt = 0.1, double gewicht_body = 0.6, double gewicht_scheibe = 0.1, POSITION position = POSITION(), INERTIA inertia = INERTIA(), HALLSENSOR hall_sensor = HALLSENSOR(), IMU imu = IMU(), IMU_6DOF imu_6dof = IMU_6DOF(), IMU_9DOF imu_9dof = IMU_9DOF())
      : hoehe_schwerpunkt(hoehe_schwerpunkt),
        gewicht_body(gewicht_body),
        gewicht_scheibe(gewicht_scheibe),
        position(position),
        inertia(inertia),
        hall_sensor(hall_sensor),
        imu(imu),
        imu_6dof(imu_6dof),
        imu_9dof(imu_9dof) {}
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

// Definition der Klassenkonstanten
const double QUADRAT::hoehe_schwerpunkt = 0.1;  //m über dem Boden
const double QUADRAT::gewicht_body = 0.6;       //kg von allen Elementen außer der Scheibe
const double QUADRAT::gewicht_scheibe = 0.1;    //kg pro Scheibe

#endif
