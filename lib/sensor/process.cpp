#include "sensor_ir.h"
#include "process.h"
#include "MIDI.h"

uint32_t get_min(uint32_t* array, uint32_t len){
    uint32_t min_val = array[0];
    for(uint32_t i = 1; i < len; i++){
        if(min_val > array[i]){
            min_val = array[i];
        }
    }
    return min_val;
}

void sensorLoop(void* p){

    MIDI_CREATE_DEFAULT_INSTANCE();
    MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(115200);
    pinMode(SWITCH_PIN, INPUT);

    while(1){
        uint32_t start = trigger(1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        uint32_t min_dist = get_min(timings, NUM_SENSORS);

        if(digitalRead(SWITCH_PIN)){
            MIDI.sendControlChange(0, dist2midi(min_dist), 1);
        }
        else{
            Serial.print("Distance = ");
            Serial.print(min_dist);
            Serial.println(" cm");
        }
        vTaskDelay(35 / portTICK_PERIOD_MS);
    }
}

uint8_t dist2midi(uint32_t meas){
    uint32_t dist = meas;
    if(dist == 0){
        dist = HIGH_MAP;
    }
    uint32_t cc = map(dist, LOW_MAP, HIGH_MAP, 0, 127);
    if(cc > 127){
        cc = 127;
    }
    if(cc < 0){
        cc = 0;
    }
    return cc;
}
