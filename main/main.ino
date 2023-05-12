//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
#include <cmath>
//#include <Wire.h>
#include <tgmath.h>

//#include "datentypen.h"
#include "hall.h"
//#include "imu.h"
#include "quadrat.h"

void setup(){
  q.HALLSENSOR.hall_setup()
  //q.IMU.imu_setup()
}

void loop() {

  //define Objects
  Quadrat q();      //Die Werte werden dem Objekt q durch die implementierung gegeben

  //add sth. new
  // sollte das gleiche machen, wie das Programm einzeln
  q.HALLSENSOR.hall_loop()
  Serial.println(q.HALLSENSOR.get_hall_RPM());

  // sollte das gleiche machen, wie das Programm einzeln
  //q.IMU.imu_loop()

  return 0;
}