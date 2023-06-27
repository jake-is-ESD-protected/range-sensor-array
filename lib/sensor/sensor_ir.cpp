// THIS FILE IS AUTO-GENERATED

#include "sensor_ir.h"
uint32_t timings[NUM_SENSORS] = {0};

void IRAM_ATTR pin18_ISR(void){
	timings[0] = micros();
}

void IRAM_ATTR pin19_ISR(void){
	timings[1] = micros();
}

void IRAM_ATTR pin21_ISR(void){
	timings[2] = micros();
}

void IRAM_ATTR pin34_ISR(void){
	timings[3] = micros();
}

void IRAM_ATTR pin35_ISR(void){
	timings[4] = micros();
}

void IRAM_ATTR pin37_ISR(void){
	timings[5] = micros();
}

void IRAM_ATTR pin33_ISR(void){
	timings[6] = micros();
}

void init_ISRs(void){
	pinMode(15, OUTPUT);
	pinMode(18, INPUT);
	attachInterrupt(18, pin18_ISR, FALLING);
	pinMode(19, INPUT);
	attachInterrupt(19, pin19_ISR, FALLING);
	pinMode(21, INPUT);
	attachInterrupt(21, pin21_ISR, FALLING);
	pinMode(34, INPUT);
	attachInterrupt(34, pin34_ISR, FALLING);
	pinMode(35, INPUT);
	attachInterrupt(35, pin35_ISR, FALLING);
	pinMode(37, INPUT);
	attachInterrupt(37, pin37_ISR, FALLING);
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