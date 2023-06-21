// THIS FILE IS AUTO-GENERATED

#include "sensor_ir.h"
uint32_t timings[NUM_SENSORS] = {0};

void IRAM_ATTR pin34_ISR(void){
	timings[0] = micros();
}

void IRAM_ATTR pin33_ISR(void){
	timings[1] = micros();
}

void init_ISRs(void){
	pinMode(32, OUTPUT);
	pinMode(34, INPUT);
	attachInterrupt(34, pin34_ISR, FALLING);
	pinMode(33, INPUT);
	attachInterrupt(33, pin33_ISR, FALLING);
}

uint32_t trigger(uint32_t len){
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(len);
	digitalWrite(TRIG_PIN, LOW);
	uint32_t trig_time = micros();
	return trig_time;
}