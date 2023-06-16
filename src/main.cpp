#include <Arduino.h>
#include "sensor.h"

TaskHandle_t h_sensorLoop = NULL;

void setup(){
  initSensor();

  delay(300);

  xTaskCreate(sensorLoop, "sensor loop", 1024, NULL, 1, &h_sensorLoop);
}

void loop(){

}