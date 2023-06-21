#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <Arduino.h>

#define LOW_MAP 0       // lowest distance value
#define HIGH_MAP 250    // highest distance value (cm)
#define SWITCH_PIN 15   // pin for manual serial/MIDI change (hardware switch)
#define C 343

/* Get smallest number (positive value) in array.
 
* Parameters:
    uint32_t* array: pointer to u-integer array
    uint32_t len: length of array

* Returns:
    uint32_t smallest value in array
*/
uint32_t get_min(uint32_t* array, uint32_t len);

/* Main sensor task (loop)
 
* Parameters:
    void* p: argument pointer (can be loaded from xTaskCreate)

* Notes:
    Does not stop. Initializes MIDI, Serial and the switch pin.
    Sends a rising edge for 1 microsecond and waits for 100
    milliseconds for all return signals to arrive. Calculates smallest
    value from all sensor readings and converts it to CC messages
    or Serial prints
*/
void sensorLoop(void* p);

/* Convert distance to MIDI CC values.
 
* Parameters:
    uint32_t meas: measured distance

* Returns:
    uint8_t corresponding CC value

* Notes:
    Depends on LOW_MAP and HIGH_MAP macros.
*/
uint8_t dist2midi(uint32_t meas);

#endif