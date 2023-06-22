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
    init_ISRs();

    delay(300);

    while(1){
        uint32_t start = trigger(1);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        uint32_t min_time = get_min(timings, NUM_SENSORS);
        float dist = ((float)(min_time - start-2300) * 0.024);

        // bool sw = digitalRead(SWITCH_PIN);
        bool sw = false;

        if(sw){
            MIDI.sendControlChange(0, dist2midi(dist), 1);
        }
        else{
            Serial.print("Distance = ");
            Serial.print(dist);
            Serial.println(" cm");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
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
