#include <ESP8266WiFi.h>
#define SSID "totolink"
#define PSWD "12345678"

#include <WebSocketsServer.h>
WebSocketsServer webSockets(80);

#include <ArduinoJson.h>
#define CMD_GET_WEIGHT "get_weight"
#define CMD_SET_FRUIT_NAME "set_fruit_name"
StaticJsonDocument<200> message;
DeserializationError error;

String command;

String weight = "0";
void onWebSocketsEvent(uint8_t client_num, WStype_t type, uint8_t* payload, size_t length);

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  webSockets.begin();
  webSockets.onEvent(onWebSocketsEvent);
}

void loop() {
  webSockets.loop();
  if (Serial.available()) {
    weight = Serial.readStringUntil('\n');
  }
}

// Callback: receiving any WebSocket message
void onWebSocketsEvent(uint8_t client_num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      {
        
        error = deserializeJson(message, (char *)payload);
        if (!error) {
          command = message["command"].as<String>();
          if (command == CMD_GET_WEIGHT)
            webSockets.sendTXT(client_num, weight);
          else if (command == CMD_SET_FRUIT_NAME)
            Serial.print(message["fruit_name"].as<String>() + String(";"));
        }
      }
      break;

    default:
      break;
  }
}