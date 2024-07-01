#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);  // Set WiFi mode to station (client)

  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  delay(10000);
}