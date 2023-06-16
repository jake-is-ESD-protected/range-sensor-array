#ifndef _UI_SERVER_H_
#define _UI_SERVER_H_

#include <Arduino.h>

void getSensorReadings();
void initWiFi();
String processor(const String& var);
void initServer();
void serverLoop(void* param);

#endif