//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
//#include <cmath>
#include <Wire.h>
//#include <tgmath.h>
#include <Arduino.h>
#include <ArduinoEigen.h>
//#include "datentypen.h"
//#include "mqtt_wifi.h"
//#include "hall.h"
#include "imu.h"
//#include "quadrat.h"

//Instanziierung der Klassen
//HALLSENSOR hallSensor;   // Instanziierung der HALLSENSOR-Klasse
//mqtt_wifi mqtt_wifi;
IMU_6DOF imu;

void setup(){
  Serial.begin(115200);
  /*
  //hallSensor.hall_setup();   // Initialisierung des Hallsensors
  mqtt_wifi.setup();
  */
  imu.setup();

  //zum setzen des Ab Position der imu (hier beispielhaft auf 1,2,3 gesetzt)
  //imu.position = Eigen::Vector3d(1.0, 2.0, 3.0);

}

float lastPublishTime = 0;
void loop(){
  //alle loops der Klassen aufrufen
  //mqtt_wifi.loop();
  //imu.loop();
  
  if (millis() - lastPublishTime >= 2000) {
    /*
    // Sende eine Nachricht an das Topic "RoboTUM/steuerung"
    mqtt_wifi.publishMessage("RoboTUM/steuerung", "Hello World");
    */

    // Ausgabe der Winkel
    Serial.print("acc_x: ");
    Serial.print(imu.get_acc_x());
    Serial.print("   acc_y: ");
    Serial.print(imu.get_acc_y());
    Serial.print("   acc_z: ");
    Serial.println(imu.get_acc_z());

    Serial.print("gyro_omega_x: ");
    Serial.print(imu.get_gyro_omega_x());
    Serial.print("   gyro_omega_y: ");
    Serial.print(imu.get_gyro_omega_y());
    Serial.print("   gyro_omega_z: ");
    Serial.println(imu.get_gyro_omega_z());

    Serial.print("gyro_bias_x: ");
    Serial.print(imu.get_acc_bias_x());
    Serial.print("   gyro_bias_y: ");
    Serial.print(imu.get_acc_bias_y());
    Serial.print("   gyro_bias_z: ");
    Serial.println(imu.get_acc_bias_z());

    Serial.print("Roll: ");
    Serial.print(imu.get_roll_x());
    Serial.print("   Pitch: ");
    Serial.print(imu.get_pitch_y());
    Serial.print("   Yaw: ");
    Serial.println(imu.get_yaw_z());

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