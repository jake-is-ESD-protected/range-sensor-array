#include <Arduino.h>
#include "sensor_ir.h"
#include "process.h"

TaskHandle_t h_sensorLoop = NULL;

void setup(){
  xTaskCreate(sensorLoop, "sensor loop", 4096, NULL, 1, &h_sensorLoop);
}

void loop(){

}