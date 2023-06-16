#include "sensor.h"
#include "NewPing.h"
#include "MIDI.h"

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
MIDI_CREATE_DEFAULT_INSTANCE();

int lastSensorMeasurement = 0;
int transformedSensorValue = 0;

void initSensor(void){
    MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(115200);
    pinMode(SWITCH_PIN, INPUT);
}

void sensorLoop(void* param){
    while(true){
        lastSensorMeasurement = sonar.ping_cm();
        if(digitalRead(SWITCH_PIN))
        {
            if(lastSensorMeasurement == 0)
            {
            lastSensorMeasurement = HIGH_MAP;
            }
            transformedSensorValue = map(lastSensorMeasurement ,LOW_MAP ,HIGH_MAP, 0, 127);
            
            if(transformedSensorValue > 127)
            {
            transformedSensorValue = 127;
            }
            if(transformedSensorValue < 0)
            {
            transformedSensorValue = 0;
            }
            
            MIDI.sendControlChange(0, transformedSensorValue, 1);
        }
        else
        {
            Serial.print("Distance = ");
            Serial.print(lastSensorMeasurement);
            Serial.println(" cm");
        }
        vTaskDelay(35 / portTICK_PERIOD_MS);
    }
}