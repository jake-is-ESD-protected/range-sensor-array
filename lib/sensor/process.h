#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <Arduino.h>

uint32_t get_min(uint32_t* array, uint32_t len);
void sensorLoop(void* p);

#endif