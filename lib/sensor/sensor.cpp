#include "sensor.h"
#include "NewPing.h"
#include "MIDI.h"

MIDI_CREATE_DEFAULT_INSTANCE();

// NewPing setup of pins and maximum distance.
NewPing sensor0(TRIG_PINS[0], ECHO_PINS[0], MAX_DISTANCE);
NewPing sensor1(TRIG_PINS[1], ECHO_PINS[1], MAX_DISTANCE);
NewPing sensors[NUM_OF_SENSORS] = {sensor0, sensor1};
int measurements[NUM_OF_SENSORS];

int lastSensorMeasurement = 0;
int transformedSensorValue = 0;

void initSensor(void){
    MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(115200);
    pinMode(SWITCH_PIN, INPUT);
}

void sensorLoop(void* param){
    while(true){

        for (int i = 0; i < NUM_OF_SENSORS; i++)
        {
            measurements[i] = sensors[i].ping_cm();
            if (measurements[i] == 0) {
                measurements[i] = MAX_DISTANCE;
            }
        }
        lastSensorMeasurement = findMin(measurements, NUM_OF_SENSORS);
        

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
            for (int i = 0; i < NUM_OF_SENSORS; i++)
            {
                Serial.print(measurements[i]);
                Serial.print(" \t");
            }
            Serial.print("min: ");
            Serial.print(lastSensorMeasurement);
            Serial.print(" cm \t");
            String bar = "";
            for (int i = 0; i < lastSensorMeasurement / 5; i++)
            {
                bar += "#";
            }
            Serial.println(bar);
        }
        vTaskDelay(35 / portTICK_PERIOD_MS);
    }
}

int findMin(int arr[], int len) {
    int min = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}