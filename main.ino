//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
#include "datentypen.h"
#include "hall.cpp"
#include "imu.h"
#include "quadrat.h"
#include <cmath>
#include <Wire.h>
#include <tgmath.h>

void setup(){
  q.HALLSENSOR.hall_setup()
  q.IMU.imu_setup()

}

void loop() {

  //define Objects
  Quadrat q();      //Die Werte werden dem Objekt q durch die implementierung gegeben
  
  //test prints
  std::cout << "Hoehe: " << q.getHoehe() << std::endl;
  std::cout << "Schwerpunkt: " << q.getSchwerpunkt() << std::endl;
  std::cout << "Gewicht: " << q.getGewicht() << std::endl;

  //add sth. new
  // sollte das gleiche machen, wie das Programm einzeln
  q.HALLSENSOR.hall_loop()

  // sollte das gleiche machen, wie das Programm einzeln
  q.IMU.imu_loop()

  return 0;
}