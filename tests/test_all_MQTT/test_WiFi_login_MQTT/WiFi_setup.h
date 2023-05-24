//const char* mqttServer = "test.mosquitto.org";
//const int mqttPort = 1883;
//const char* mqttTopic = "/RoboTUM";
//const char* mqttClientId = "ESP32Client";


//Dieser Code funktioniert!!!
//da er aber so kurz ist packe ich ihn mit dem MQTT Zeugs in ein File

#include <WiFi.h>
#include "secure.h"

void wifi_setup() {
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
