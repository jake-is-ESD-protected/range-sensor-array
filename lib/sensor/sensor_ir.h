#ifndef _SENSOR_IR_H_
#define _SENSOR_IR_H_
#include <Arduino.h>
#define NUM_SENSORS 3
#define TRIG_PIN 20
void IRAM_ATTR pin1_ISR(void);
void IRAM_ATTR pin2_ISR(void);
void IRAM_ATTR pin3_ISR(void);
void init_ISRs(void);
uint32_t trigger(uint32_t len);

extern uint32_t timings[NUM_SENSORS];
#endif