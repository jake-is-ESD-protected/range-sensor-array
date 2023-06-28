#include "sensor_ir.h"
#include "process.h"
#include "MIDI.h"
#include <list>

uint32_t get_min(uint32_t *array, uint32_t len)
{
    uint32_t min_val = array[0];
    for (uint32_t i = 1; i < len; i++)
    {
        if (min_val > array[i])
        {
            min_val = array[i];
        }
    }
    return min_val;
}

float timeToDist(uint32_t startTime, uint32_t endTime)
{
    return ((float)(endTime - startTime - 2300) * 0.022);
}

void sensorLoop(void *p)
{

    MIDI_CREATE_DEFAULT_INSTANCE();
    MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(115200);
    // pinMode(SWITCH_PIN, INPUT);
    init_ISRs();

    uint32_t detections = 0;
#ifdef INTRUSION_DETECTION_VIA_LIST
    std::list<float> distHist{};
    for (uint8_t i = 0; i < INTRUSION_HISTORY_LENGTH; i++)
    {
        distHist.push_back((float)10000);   // arbitrary high number that is greater than the INTRUSION_DISTANCE
    }
#endif

    delay(300);

    while (1)
    {
        uint32_t start = trigger(1);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        uint32_t min_time = get_min(timings, NUM_SENSORS);
        float dist = timeToDist(start, min_time);

#ifndef INTRUSION_DETECTION_VIA_LIST
        if (dist < INTRUSION_DISTANCE)
        {
            detections++;
        }
        else
        {
            detections = 0;
        }
#endif
#ifdef INTRUSION_DETECTION_VIA_LIST
        distHist.pop_front();
        distHist.push_back(dist);

        detections = 0;
        for (auto const &d : distHist)
        {
            // Serial.println(d);
            if (d < INTRUSION_DISTANCE)
            {
                detections++;
            }
        }
#endif

        // bool sw = digitalRead(SWITCH_PIN);
        bool sw = false;

        if (sw)
        {
            // MIDI.sendControlChange(0, dist2midi(dist), 1);
            uint8_t midiVal = detections >= INTRUSION_INTERVAL ? 127 : 0;  // binary version
            MIDI.sendControlChange(0, midiVal, 1);
        }
        else
        {

            for (int i = 0; i < NUM_SENSORS; i++)
            {
                Serial.print(timeToDist(start, timings[i]));
                Serial.print(" \t");
            }
            Serial.print("min: ");
            Serial.print(dist);
            Serial.println(" cm \t");

            if (detections >= INTRUSION_INTERVAL)
            {
                Serial.println("ALARM!");
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

uint8_t dist2midi(uint32_t meas)
{
    uint32_t dist = meas;
    if (dist == 0)
    {
        dist = HIGH_MAP;
    }
    uint32_t cc = map(dist, LOW_MAP, HIGH_MAP, 0, 127);
    if (cc > 127)
    {
        cc = 127;
    }
    if (cc < 0)
    {
        cc = 0;
    }
    return cc;
}
