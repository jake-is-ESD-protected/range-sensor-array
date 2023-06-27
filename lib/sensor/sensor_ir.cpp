// THIS FILE IS AUTO-GENERATED

#include "sensor_ir.h"
uint32_t timings[NUM_SENSORS] = {0};

void IRAM_ATTR pin36_ISR(void){
	timings[0] = micros();
}

void IRAM_ATTR pin34_ISR(void){
	timings[1] = micros();
}

void IRAM_ATTR pin33_ISR(void){
	timings[2] = micros();
}

void IRAM_ATTR pin32_ISR(void){
	timings[3] = micros();
}

void IRAM_ATTR pin26_ISR(void){
	timings[4] = micros();
}

void IRAM_ATTR pin25_ISR(void){
	timings[5] = micros();
}

void IRAM_ATTR pin14_ISR(void){
	timings[6] = micros();
}

void IRAM_ATTR pin27_ISR(void){
	timings[7] = micros();
}

void IRAM_ATTR pin13_ISR(void){
	timings[8] = micros();
}

void IRAM_ATTR pin19_ISR(void){
	timings[9] = micros();
}

void IRAM_ATTR pin18_ISR(void){
	timings[10] = micros();
}

void IRAM_ATTR pin17_ISR(void){
	timings[11] = micros();
}

void init_ISRs(void){
	pinMode(16, OUTPUT);
	pinMode(36, INPUT);
	attachInterrupt(36, pin36_ISR, FALLING);
	pinMode(34, INPUT);
	attachInterrupt(34, pin34_ISR, FALLING);
	pinMode(33, INPUT);
	attachInterrupt(33, pin33_ISR, FALLING);
	pinMode(32, INPUT);
	attachInterrupt(32, pin32_ISR, FALLING);
	pinMode(26, INPUT);
	attachInterrupt(26, pin26_ISR, FALLING);
	pinMode(25, INPUT);
	attachInterrupt(25, pin25_ISR, FALLING);
	pinMode(14, INPUT);
	attachInterrupt(14, pin14_ISR, FALLING);
	pinMode(27, INPUT);
	attachInterrupt(27, pin27_ISR, FALLING);
	pinMode(13, INPUT);
	attachInterrupt(13, pin13_ISR, FALLING);
	pinMode(19, INPUT);
	attachInterrupt(19, pin19_ISR, FALLING);
	pinMode(18, INPUT);
	attachInterrupt(18, pin18_ISR, FALLING);
	pinMode(17, INPUT);
	attachInterrupt(17, pin17_ISR, FALLING);
}

uint32_t trigger(uint32_t len){
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(len);
	digitalWrite(TRIG_PIN, LOW);
	uint32_t trig_time = micros();
	return trig_time;
}