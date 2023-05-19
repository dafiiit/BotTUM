//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
#include <cmath>
//#include <Wire.h>
#include <tgmath.h>
#include <Serial.h>

//#include "datentypen.h"
#include "hall.h"
//#include "imu.h"
//#include "quadrat.h"

HALLSENSOR hallSensor;   // Instanziierung der HALLSENSOR-Klasse

void setup(){
  Serial.begin(hallSensor.abtastrate);
  hallSensor.hall_setup();   // Initialisierung des Hallsensors
  //IMU.imu_setup()
}

void loop() {

  float rpm = hallSensor.get_hall_rpm();      // RPM abrufen
  float phiPS = hallSensor.get_hall_phi_punkt_scheibe();  // PhiPS abrufen

  Serial.print("PhiPS: ");
  Serial.println(phiPS);
  Serial.print("RPM: ");
  Serial.println(rpm);   // RPM ausgeben

}