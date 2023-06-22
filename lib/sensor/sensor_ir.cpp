// THIS FILE IS AUTO-GENERATED

#include "sensor_ir.h"
uint32_t timings[NUM_SENSORS] = {0};

void IRAM_ATTR pin22_ISR(void){
	timings[0] = micros();
}

void IRAM_ATTR pin23_ISR(void){
	timings[1] = micros();
}

void init_ISRs(void){
	pinMode(18, OUTPUT);
	pinMode(22, INPUT);
	attachInterrupt(22, pin22_ISR, FALLING);
	pinMode(23, INPUT);
	attachInterrupt(23, pin23_ISR, FALLING);
}

uint32_t trigger(uint32_t len){
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(len);
	digitalWrite(TRIG_PIN, LOW);
	uint32_t trig_time = micros();
	return trig_time;
}