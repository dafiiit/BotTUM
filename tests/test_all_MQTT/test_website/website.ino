#include <WiFi.h>
#include <PubSubClient.h>
#include "secure.h"

const char *mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char *mqttTopic = "/RoboTUM";

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password_wifi);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while (!client.connected())
    {
        if (client.connect("ESP32Client"))
        {
            Serial.println("Connected to MQTT broker");
            client.subscribe(mqttTopic);
        }
        else
        {
            Serial.print("Failed to connect to MQTT broker, retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void loop()
{
    client.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("New message received:");
    String message = "";
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.println(message);
    // Hier kannst du die erhaltenen Daten weiterverarbeiten und an den ESP32 anschließen
}
