#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>

// #define TRIGGER_PIN 22
// #define ECHO_PIN 23
#define SWITCH_PIN 15

#define LOW_MAP 0
#define HIGH_MAP 200

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 200

// #define NUM_OF_SENSORS 1
// const int TRIG_PINS[NUM_OF_SENSORS] = {22};
// const int ECHO_PINS[NUM_OF_SENSORS] = {23};
#define NUM_OF_SENSORS 2
const int TRIG_PINS[NUM_OF_SENSORS] = {22, 18};
const int ECHO_PINS[NUM_OF_SENSORS] = {23, 19};

void initSensor(void);
void sensorLoop(void* param);
int findMin(int arr[], int len);

extern int lastSensorMeasurement;

#endif