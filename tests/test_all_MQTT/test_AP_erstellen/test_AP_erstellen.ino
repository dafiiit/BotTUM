#include <WiFi.h>

const char* ssid = "MeinESP32AP";
const char* password = "password123";

//gibt zudem die IP-Adresse des Access Points aus

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP-Adresse: ");
  Serial.println(IP);

  server.begin();
}
void loop(){
  
}