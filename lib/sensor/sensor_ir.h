// THIS FILE IS AUTO-GENERATED

#ifndef _SENSOR_IR_H_
#define _SENSOR_IR_H_
#include <Arduino.h>
#define NUM_SENSORS 7
#define TRIG_PIN 15
void IRAM_ATTR pin18_ISR(void);
void IRAM_ATTR pin19_ISR(void);
void IRAM_ATTR pin21_ISR(void);
void IRAM_ATTR pin34_ISR(void);
void IRAM_ATTR pin35_ISR(void);
void IRAM_ATTR pin37_ISR(void);
void IRAM_ATTR pin33_ISR(void);
void init_ISRs(void);
uint32_t trigger(uint32_t len);

extern uint32_t timings[NUM_SENSORS];
#endif