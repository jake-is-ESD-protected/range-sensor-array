#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>

#define TRIGGER_PIN 22
#define ECHO_PIN 23
#define SWITCH_PIN 15

#define LOW_MAP 0
#define HIGH_MAP 250

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 600  

void initSensor(void);
void sensorLoop(void* param);

extern int lastSensorMeasurement;

#endif