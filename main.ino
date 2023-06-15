//Dies ist das Hauptprogramm für die Ansteuerung des Quadrats
#include <iostream>
//#include <cmath>
#include <Wire.h>
//#include <tgmath.h>
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "datentypen.h"
//#include "mqtt_wifi.h"
//#include "hall.h"
#include "imu.h"
#include "vektorrechnung.h"
//#include "quadrat.h"
//#include "imu_with_libary.h"

//Instanziierung der Klassen
//HALLSENSOR hallSensor;   // Instanziierung der HALLSENSOR-Klasse
//mqtt_wifi mqtt_wifi;

STEUERUNG steuerung;
IMU_6DOF imu;
ZUSTAND aktueller_zustand;
USER_ZUSTAND user_zustand;

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
    
    //Bias acc
    Serial.print("acc_bias_x");
    Serial.print(imu.get_acc_bias(0));
    Serial.print("acc_bias_y");
    Serial.print(imu.get_acc_bias(1));
    Serial.print("acc_bias_z");
    Serial.println(imu.get_acc_bias(2));

    // Ausgabe der Winkel
    Serial.print("acc_x: ");
    Serial.print(imu.get_acc(0));
    Serial.print("   acc_y: ");
    Serial.print(imu.get_acc(1));
    Serial.print("   acc_z: ");
    Serial.println(imu.get_acc(2));
    
    // Ausgabe bias Gyroskop
    Serial.print("gyro_bias_x: ");
    Serial.print(imu.get_gyro_bias(0));
    Serial.print("   gyro__bias_y: ");
    Serial.print(imu.get_gyro_omega(1));
    Serial.print("   gyro_bias_z: ");
    Serial.println(imu.get_gyro_bias(2));

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
    Serial.println("");
    lastPublishTime = millis(); // Aktualisiere den Zeitpunkt des letzten Publish


    std::sort(zustands_array, zustands_array + 2);

    void entferne_wert(int vector[], int wert)
    {
      for (int i = 0; i < vector.size; i++)
      {
        if (vector[i] == wert)
        {
          vector.erase(i);
        }
      }
    }
    std::kombi_vector gib_kombis_nuller_und_wert(int nullen, int wert)
    {
      for (int i = 0; i < 24; i++)
      {
        if (alle_zustaende_array[0]==wert or alle_zustaende_array[1]==wert or alle_zustaende_array[2]==wert){
          null_counter = 0;
          for (int j = 0; j < 3; j++)
          {
            if (alle_zustaende_array[i,j]==0)
            {
              null_counter++;
            }
          }
          if (null_counter==nullen)
          {
            alle_zustaende_array[i, i+1, i+2];
          }
        }
      }
      
    
  
    }

    if (zustands_array[0] = 0 && zustands_array[1] = 0) //wir befinden uns auf Fläche
      Serial.println("Robo befindet sich auf Fläche %i", zustands_array[2]);
      std::auswahl_array[6] = {1, 2, 3, 4, 5, 6, 7};
      //das element mit dem Wert zustands_array[2] wird aus dem array auswahl_array gelöscht
      entferne_wert(std::auswahl_array, zustands_array[2]);
      //das element mit dem Wert 7-zustands_array[2] wird aus dem array auswahl_array gelöscht
      entferne_wert(std::auswahl_array, (7-zustands_array[2]));
      Serial.println("Zum aufstehen auf Kante gebe eine Zahl eine der folgenden Zahlen ein: (%i, %i, %i, %i)", auswahl_array[0], auswahl_array[1], auswahl_array[2], auswahl_array[3]);

      Serial.println("Zum aufstehen auf eine Ecke gebe eine der folgenden Zahlenkombinationen ein:(%i%i, %i%i, %i%i, %i%i)", zustands_array[0], zustands_array[1], zustands_array[2], zustands_array[3]);
      //hier user input lesen
      if (user_input = k)
        {
        Serial.println("zum aufstehen auf die vordere Kante gebe v ein (rechts = r, links = l, hinten = h)");
        //hier user input lesen
        switch (user_input) 
        {
          case v: steuerung.flaeche_auf_kante(/*hier muss noch die zielkante mitgegeben werden*/);
          break;
          case r: steuerung.flaeche_auf_kante();
          break;
          case l: steuerung.flaeche_auf_kante();
          break;
          case h: steuerung.flaeche_auf_kante();
          break;
          default: 
          Serial.print("kein gültiges unser_input");
          break;
        }
      elsif(user_input = e)
        {
        Serial.println("zum aufstehen auf die vordere rechte Ecke gebe vr ein (hintenrechts = hr, hintenlinks = hl, vornelinks = vl)")
        }
        //hier user input lesen
        switch (user_input) 
        {
          case v: steuerung.flaeche_auf_ecke(/*hier muss noch die zielecke mitgegeben werden*/);
          break;
          case r: steuerung.flaeche_auf_ecke();
          break;
          case l: steuerung.flaeche_auf_ecke();
          break;
          case h: steuerung.flaeche_auf_ecke();
          break;
          default: 
          Serial.print("kein gültiges unser_input");
          break;
        }
      }
      break;
    case auf_kante:
      Serial.println("Robo befindet sich auf Kante");
      Serial.println("Zum aufstehen auf Ecke gebe e ein, zum herunterfallen auf eine Fläche f");
      //hier user input lesen
      if (user_input = e)
        {
        Serial.println("zum aufstehen auf die vordere Ecke gebe v ein (hinten = h)")
        //hier user input lesen
        switch (user_input) 
        {
          case v: steuerung.kante_auf_ecke(/*hier muss noch die zielecke mitgegeben werden*/);
          break;
          case h: steuerung.kante_auf_ecke();
          break;
          default: 
          Serial.print("kein gültiges unser_input");
          break;
        }
      elsif(user_input = f)
        {
        Serial.println("zum herunterfallen auf die rechte Fläche gebe r ein (linke Fläche = l)")
        }
        //hier user input lesen
        switch (user_input) 
        {
          case r: steuerung.kante_auf_flaeche(/*hier muss noch die zielecke mitgegeben werden*/);
          break;
          case l: steuerung.kante_auf_flaeche();
          break;
          default: 
          Serial.print("kein gültiges unser_input");
          break;
        }
      break;
    case auf_ecke:
      Serial.print("Robo befindet sich auf Ecke");
      Serial.println("Zum herunterfallen auf Kante gebe k ein, zum herunterfallen auf eine Fläche f");
      //hier user input lesen
      if (user_input = k)
        {
        Serial.println("Herabfallen auf Kante aktiviert!")
        Serial.println("zum herabfallen auf die vordere Kante gebe v ein (hinten = h, rechts = r, links = l)")
        //hier user input lesen
        switch (user_input) 
          {
          case v: steuerung.ecke_auf_kante(/*hier muss noch die zielkante mitgegeben werden*/);
          break;
          case hr: steuerung.ecke_auf_kante();
          break;
          case hl: steuerung.ecke_auf_kante(/*hier muss noch die zielkante mitgegeben werden*/);
          break;
          default: 
          Serial.print("kein gültiges unser_input");
          break;
          }
        }
      elsif(user_input = f)
        {
        Serial.println("Herabfallen auf Fläche aktiviert!")
        Serial.println("zum herunterfallen auf die rechte Fläche gebe r ein (linke = l, vorne = v, hinten = h)")

        //hier user input lesen
        switch (user_input) 
          {
          case r: steuerung.ecke_auf_flaeche(/*hier muss noch die zielecke mitgegeben werden*/);
          break;
          case l: steuerung.ecke_auf_flaeche();
          break;
          case h: steuerung.ecke_auf_flaeche();
          break;
          case v: steuerung.ecke_auf_flaeche();
          break;
          default: 
          Serial.print("kein gültiges unser_input");
          break;
          }
        }
      break;
    case
      
    default: 
      Serial.print("kein gültiger user_zustand");
      break;
    }

  }

  /*
  float rpm = hallSensor.get_hall_rpm();      // RPM abrufen
  float phiPS = hallSensor.get_hall_phi_punkt_scheibe();  // PhiPS abrufen

  Serial.print("PhiPS: ");
  Serial.println(phiPS);
  Serial.print("RPM: ");
  Serial.println(rpm);   // RPM ausgeben
  */

//Switch case struktur, welche die verschiedenen Modi des Quadrats abarbeitet
/* Idee: 
Der Würfel weiß in welchem Modus er sich befindet
Der User kann zwischen den Modi wechseln
*/