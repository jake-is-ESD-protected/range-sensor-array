#include <Arduino.h>
#include "sensor_ir.h"
#include "process.h"

TaskHandle_t h_sensorLoop = NULL;

void setup(){
  xTaskCreate(sensorLoop, "sensor loop", 1024, NULL, 1, &h_sensorLoop);
}

void loop(){

}