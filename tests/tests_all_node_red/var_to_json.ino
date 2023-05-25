#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);

  // Create variables x, y, z and assign values
  double x = 0.1234;
  double y = 0.5678;
  double z = 0.9123;

  // Create a JSON object and set the variables
  DynamicJsonDocument jsonDoc(200);
  jsonDoc["Ax"] = x;
  jsonDoc["Ay"] = y;
  jsonDoc["Az"] = z;

  // Serialize JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Print the JSON string
  Serial.println(jsonString);
}

void loop() {
  // Your code here
}
