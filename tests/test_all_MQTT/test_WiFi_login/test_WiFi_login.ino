//Das Ziel ist es, dass der ESP32 WiFi AccessPoint wird.
//Der PC soll sich mit diesem Verbinden, wodurch ihm eine IP adresse zugeteilt wird. 
//Auf dem PC läuft Mosquitto auf dem Port :1883
//Evtl. benötige ich so etwas wie Portfreigabe/weiterleitung auf dem Mac, damit der ESP darauf zugreifen kann. 
//Der ESP32 muss zudem die IP Adresse, welche er dem Mac zugeteilt herausfinden(kann sie mit Serieller Kommunikation ausgeben)
//letztendlich sollte es so möglich sein, dass der ESP32 auf ein Topic postet und der PC diese Daten empfängt und umgekehrt.

//Dieser Code funktioniert!!!

#include <WiFi.h>
#include "secure.h"

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your code here
}
