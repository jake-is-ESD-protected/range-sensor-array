// THIS FILE IS AUTO-GENERATED

#ifndef _SENSOR_IR_H_
#define _SENSOR_IR_H_
#include <Arduino.h>
#define NUM_SENSORS 12
#define TRIG_PIN 16
void IRAM_ATTR pin36_ISR(void);
void IRAM_ATTR pin34_ISR(void);
void IRAM_ATTR pin33_ISR(void);
void IRAM_ATTR pin32_ISR(void);
void IRAM_ATTR pin26_ISR(void);
void IRAM_ATTR pin25_ISR(void);
void IRAM_ATTR pin14_ISR(void);
void IRAM_ATTR pin27_ISR(void);
void IRAM_ATTR pin13_ISR(void);
void IRAM_ATTR pin19_ISR(void);
void IRAM_ATTR pin18_ISR(void);
void IRAM_ATTR pin17_ISR(void);
void init_ISRs(void);
uint32_t trigger(uint32_t len);

extern uint32_t timings[NUM_SENSORS];
#endif