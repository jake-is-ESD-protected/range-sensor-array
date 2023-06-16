#include "sensor_ir.h"
uint32_t timings[NUM_SENSORS] = {0};

void IRAM_ATTR pin4_ISR(void){
	timings[0] = micros();
}

void IRAM_ATTR pin22_ISR(void){
	timings[1] = micros();
}

void IRAM_ATTR pin23_ISR(void){
	timings[2] = micros();
}

void init_ISRs(void){
	pinMode(4, INPUT);
	attachInterrupt(4, pin4_ISR, RISING);
	pinMode(22, INPUT);
	attachInterrupt(22, pin22_ISR, RISING);
	pinMode(23, INPUT);
	attachInterrupt(23, pin23_ISR, RISING);
}

uint32_t trigger(uint32_t len){
	digitalWrite(TRIG_PIN, HIGH);
	uint32_t trig_time = micros();
	delayMicroseconds(len);
	digitalWrite(TRIG_PIN, LOW);
	return trig_time;
}