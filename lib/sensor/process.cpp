#include "sensor_ir.h"

uint32_t get_min(uint32_t* array, uint32_t len){
    uint32_t min_val = array[0];
    for(uint32_t i = 1; i < len; i++){
        if(min_val > array[i]){
            min_val = array[i];
        }
    }
}

void sensorLoop(void* p){
    while(1){
        uint32_t start = trigger(1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        uint32_t min_dist = get_min(timings, NUM_SENSORS);
        // do stuff with values idk
    }
    
}