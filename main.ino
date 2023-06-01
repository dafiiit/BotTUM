//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
//#include <cmath>
#include <Wire.h>
//#include <tgmath.h>
#include <Arduino.h>

//#include "datentypen.h"
#include "mqtt_wifi.h"
//#include "hall.h"
#include "imu.h"
//#include "quadrat.h"

//HALLSENSOR hallSensor;   // Instanziierung der HALLSENSOR-Klasse
mqtt_wifi mqtt_wifi;
IMU_6DOF imu;


void setup(){
  Serial.begin(115200);
  //hallSensor.hall_setup();   // Initialisierung des Hallsensors
  mqtt_wifi.setup();
  imu.setup();

}

float lastPublishTime = 0;
void loop(){
  //alle loops der Klassen aufrufen
  mqtt_wifi.loop();
  imu.loop();
  
  if (millis() - lastPublishTime >= 2000) {
    // Sende eine Nachricht an das Topic "RoboTUM/steuerung"
    mqtt_wifi.publishMessage("RoboTUM/steuerung", "Hello World");
    lastPublishTime = millis(); // Aktualisiere den Zeitpunkt des letzten Publish

    // Ausgabe der Winkel
    Serial.print("Roll: ");
    Serial.print(imu.roll_x);
    Serial.print("   Pitch: ");
    Serial.print(imu.pitch_y);
    Serial.print("   Yaw: ");
    Serial.println(imu.yaw_z);
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