#include <Arduino.h>
#include "MQTTHelper.h"

MQTTHelper mqttHelper;

void setup() { 
  Serial.begin(115200);
  mqttHelper.setup();
  //mqttClient.setCallback(callback);

}
float lastPublishTime = 0;
void loop() {
  mqttHelper.loop();
  
  // Überprüfe, ob 0,5 Sekunden seit dem letzten Publish vergangen sind
  if (millis() - lastPublishTime >= 500) {
    mqttHelper.publishMessage("RoboTUM/steuerung", "Hello World");
    lastPublishTime = millis(); // Aktualisiere den Zeitpunkt des letzten Publish
  }
}


