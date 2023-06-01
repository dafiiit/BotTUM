#ifndef mqtt_wifi_H
#define mqtt_wifi_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "secure.h"

extern void callback(char* topic, byte* payload, unsigned int length); // Deklariere die Callback-Funktion

class mqtt_wifi {
public:
  mqtt_wifi() : client(espClient) {}
  void setup() {
    WiFi.begin(ssid, password);
    // Connect to Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
      //WiFi.begin(ssid, password);
      delay(2000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // ab hier hat der Rest nichts mehr mit Wlan sondern nur noch mit MQTT zu tun

    // Set up MQTT server and callback function
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    // Connect to MQTT broker
    reconnect();
  }

  void loop() {
    if (!client.connected()) {
      reconnect();
      Serial.print(client.state());
    }
    client.loop();
  }

  void publishMessage(const char* topic, const char* message) {
    if (client.connected()) {
      // Publish the message with QoS 2
      client.publish(topic, reinterpret_cast<const uint8_t*>(message), strlen(message), true);
    }
  }


private:
  const char* mqttServer = "test.mosquitto.org";
  const int mqttPort = 1883;
  const char* mqttClientId = "ESP32Client";

  WiFiClient espClient;
  PubSubClient client;

  void reconnect() {
    while (!client.connected()) {
    //Serial.println("Connecting to MQTT broker...");
    if (client.connect(mqttClientId)) {
      //Serial.println("Connected to MQTT broker");

      // hier allen Toppics subscriben
      client.subscribe("RoboTUM/steuerung");  
      client.subscribe("RoboTUM/pid_values");
      client.subscribe("RoboTUM/on_off");

    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
    }
  }
};

// Define the free function outside the class
void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Received message: ");
  Serial.println(message);
}

#endif
