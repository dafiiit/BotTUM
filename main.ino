//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
//#include <cmath>
#include <Wire.h>
//#include <tgmath.h>
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include "datentypen.h"
//#include "mqtt_wifi.h"
//#include "hall.h"
#include "imu.h"
//#include "quadrat.h"
//#include "imu_with_libary.h"

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
  //imu_6DOF_with_lib().setup();

  //zum setzen des Ab Position der imu (hier beispielhaft auf 1,2,3 gesetzt)
  //imu.position = Eigen::Vector3d(1.0, 2.0, 3.0);

}

float lastPublishTime = 0;
void loop(){
  //alle loops der Klassen aufrufen
  //mqtt_wifi.loop();
  imu.loop();
  //imu_6DOF_with_lib().loop();
  
  if (millis() - lastPublishTime >= 2000) {
    /*
    // Sende eine Nachricht an das Topic "RoboTUM/steuerung"
    mqtt_wifi.publishMessage("RoboTUM/steuerung", "Hello World");
    */

    // Ausgabe der Winkel
    Serial.print("acc_x: ");
    Serial.print(imu.get_acc(0));
    Serial.print("   acc_y: ");
    Serial.print(imu.get_acc(1));
    Serial.print("   acc_z: ");
    Serial.println(imu.get_acc(2));
    
    // Ausgabe der Winkel
    Serial.print("gyro_x: ");
    Serial.print(imu.get_gyro_omega(0));
    Serial.print("   gyro_y: ");
    Serial.print(imu.get_gyro_omega(1));
    Serial.print("   gyro_z: ");
    Serial.println(imu.get_gyro_omega(2));

    // Ausgabe der Winkel
    Serial.print("acc_angle_x: ");
    Serial.print(imu.get_acc_angle(0));
    Serial.print("   acc_angle_y: ");
    Serial.print(imu.get_acc_angle(1));
    Serial.print("   acc_angle_z: ");
    Serial.println(imu.get_acc_angle(2));

    // Ausgabe der Winkel
    Serial.print("complementary_angle_x: ");
    Serial.print(imu.get_complementary_angle(0));
    Serial.print("   complementary_angle_y: ");
    Serial.print(imu.get_complementary_angle(1));
    Serial.print("   complementary_angle_z: ");
    Serial.println(imu.get_complementary_angle(2));
    
    // Ausgabe der Winkel
    Serial.print("fancy_angle_x: ");
    Serial.print(imu.get_fancy_angle(0));
    Serial.print("   fancy_angle_y: ");
    Serial.print(imu.get_fancy_angle(1));
    Serial.print("   fancy_angle_z: ");
    Serial.println(imu.get_fancy_angle(2));
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