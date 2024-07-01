#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
const char* SSID = "totolink";
const char* PSWD = "12345678";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// weight
String weight = "0";

void setup() {
  Serial.begin(9600);
  WiFi.begin(SSID, PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Web server ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  /*
   * Async WebServer
   */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", weight.c_str());
  });
  server.begin();
}

void loop() {
  if (Serial.available()) {
    weight = Serial.readStringUntil('\n');
  }
}