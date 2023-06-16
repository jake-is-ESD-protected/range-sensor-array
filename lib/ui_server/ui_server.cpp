#include "ui_server.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "sensor.h"
#include "index_html.h"

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 500;

// Initialize WiFi
void initWiFi() {
    Serial.print("Setting AP (Access Point)…");
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    
    server.begin();
}

String processor(const String& var){
  return String(lastSensorMeasurement);
}

void initServer() {
  initWiFi();

  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
}

void serverLoop(void* param) {
  uint32_t test = 0;
  while(true){
    if ((millis() - lastTime) > timerDelay) {
      // Send Events to the Web Client with the Sensor Readings
      events.send("ping",NULL,millis());
      // DEBUG: Serial.printf("Sending %d to Client\n", lastSensorMeasurement);
      events.send(processor("").c_str(),"distance",millis());
      lastTime = millis();
    }
  }
}