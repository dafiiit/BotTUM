//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
#include <cmath>
//#include <Wire.h>
#include <tgmath.h>
#include <Serial.h>

#include "datentypen.h"
#include "hall.h"
//#include "imu.h"
//#include "quadrat.h"

HALLSENSOR hallSensor;   // Instanziierung der HALLSENSOR-Klasse

void setup(){
  Serial.begin(hallSensor.HallSensor_Abtastrate);
  hallSensor.hall_setup();   // Initialisierung des Hallsensors
  //IMU.imu_setup()
}

void loop() {

  float rpm = hallSensor.get_hall_RPM();      // RPM abrufen
  float phiPS = hallSensor.get_hall_PhiPS();  // PhiPS abrufen

  Serial.print("PhiPS: ");
  Serial.println(phiPS);
  Serial.print("RPM: ");
  Serial.println(rpm);   // RPM ausgeben

}