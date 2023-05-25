/*
  Example from WiFi > WiFiScan
  Complete details at https://RandomNerdTutorials.com/esp32-useful-wi-fi-functions-arduino/
*/

#include "WiFi.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}
//@BayernWLAN is WIFI_AUTH_OPEN
//lrz is WIFI_AUTH_OPEN
//eduroam is WIFI_AUTH_WPA2_ENTERPRISE
//eduroam-IPv6only is WIFI_AUTH_WPA2_ENTERPRISE
//mwn-events is WIFI_AUTH_WPA2_ENTERPRISE
//nobody: WIFI_AUTH_WEP; WIFI_AUTH_WPA_PSK; WIFI_AUTH_WPA2_PSK; WIFI_AUTH_WPA_WPA2_PSK; 
void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_WPA2_ENTERPRISE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}