#include "sensor_ir.h"
uint32_t timings[NUM_SENSORS] = {0};

void IRAM_ATTR pin1_ISR(void){
	timings[0] = micros();
}

void IRAM_ATTR pin2_ISR(void){
	timings[1] = micros();
}

void IRAM_ATTR pin3_ISR(void){
	timings[2] = micros();
}

void init_ISRs(void){
	pinMode(1, INPUT);
	attachInterrupt(1, pin1_ISR, RISING);
	pinMode(2, INPUT);
	attachInterrupt(2, pin2_ISR, RISING);
	pinMode(3, INPUT);
	attachInterrupt(3, pin3_ISR, RISING);
}

uint32_t trigger(uint32_t len){
	digitalWrite(TRIG_PIN, HIGH);
	uint32_t trig_time = micros();
	delayMicroseconds(len);
	digitalWrite(TRIG_PIN, LOW);
	return trig_time;
}