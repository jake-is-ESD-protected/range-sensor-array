// THIS FILE IS AUTO-GENERATED

#ifndef _SENSOR_IR_H_
#define _SENSOR_IR_H_
#include <Arduino.h>
#define NUM_SENSORS 2
#define TRIG_PIN 18
void IRAM_ATTR pin22_ISR(void);
void IRAM_ATTR pin23_ISR(void);
void init_ISRs(void);
uint32_t trigger(uint32_t len);

extern uint32_t timings[NUM_SENSORS];
#endif