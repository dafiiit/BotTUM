//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
//#include <cmath>
#include <Wire.h>
//#include <tgmath.h>
#include <Arduino.h>

//#include "datentypen.h"
#include "mqtt_wifi.h"
//#include "hall.h"
//#include "imu.h"
//#include "quadrat.h"

//HALLSENSOR hallSensor;   // Instanziierung der HALLSENSOR-Klasse
mqtt_wifi mqtt_wifi;


void setup(){
  Serial.begin(115200);
  //hallSensor.hall_setup();   // Initialisierung des Hallsensors
  mqtt_wifi.setup();

}

float lastPublishTime = 0;
void loop(){
  mqtt_wifi.loop();
  
  // Überprüfe, ob 0,5 Sekunden seit dem letzten Publish vergangen sind
  if (millis() - lastPublishTime >= 2000) {
    mqtt_wifi.publishMessage("RoboTUM/steuerung", "Hello World");
    lastPublishTime = millis(); // Aktualisiere den Zeitpunkt des letzten Publish
  }

  /*
  float rpm = hallSensor.get_hall_rpm();      // RPM abrufen
  float phiPS = hallSensor.get_hall_phi_punkt_scheibe();  // PhiPS abrufen

  Serial.print("PhiPS: ");
  Serial.println(phiPS);
  Serial.print("RPM: ");
  Serial.println(rpm);   // RPM ausgeben
  */

}