#include <Arduino.h>
#include "sensor.h"
#include "ui_server.h"

TaskHandle_t h_sensorLoop = NULL;
TaskHandle_t h_serverLoop = NULL;

void setup(){
  initSensor();
  initServer();

  delay(300);

  xTaskCreate(sensorLoop, "sensor loop", 1024, NULL, 1, &h_sensorLoop);
  xTaskCreate(serverLoop, "server loop", 4096, NULL, 1, &h_serverLoop);
}

void loop(){

}