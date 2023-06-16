pin_list = [4, 22, 23]
trig_pin = 18

with open("./lib/sensor/sensor_ir.h", "w") as f:
    head = "#ifndef _SENSOR_IR_H_\n" + \
           "#define _SENSOR_IR_H_\n" + \
           "#include <Arduino.h>\n" + \
           f"#define NUM_SENSORS {len(pin_list)}\n" + \
           f"#define TRIG_PIN {trig_pin}\n"
    
    tail =  "void init_ISRs(void);\n" + \
            "uint32_t trigger(uint32_t len);\n" + \
            "\nextern uint32_t timings[NUM_SENSORS];\n#endif"

    ir_dump = ""
    for pin in pin_list:
        ir_dump += f"void IRAM_ATTR pin{pin}_ISR(void);\n"

    dump = head + ir_dump + tail
    f.write(dump)

with open("./lib/sensor/sensor_ir.cpp", "w") as f:
    head = '#include "sensor_ir.h"\n' + \
           "uint32_t timings[NUM_SENSORS] = {0};\n\n"
    
    ir_dump = ""
    for i, pin in enumerate(pin_list):
        ir_dump += f"void IRAM_ATTR pin{pin}_ISR(void)" + \
                    "{\n" + \
                   f"\ttimings[{i}] = micros();\n" + \
                    "}\n\n"
    
    init_dump = "void init_ISRs(void){\n"

    for pin in pin_list:
        init_dump += f"\tpinMode({pin}, INPUT);\n"
        init_dump += f"\tattachInterrupt({pin}, pin{pin}_ISR, RISING);\n"
    init_dump += "}\n\n"

    tail = "uint32_t trigger(uint32_t len){\n" + \
           "\tdigitalWrite(TRIG_PIN, HIGH);\n" + \
           "\tuint32_t trig_time = micros();\n" + \
           "\tdelayMicroseconds(len);\n" + \
           "\tdigitalWrite(TRIG_PIN, LOW);\n" + \
           "\treturn trig_time;\n" + \
           "}"


    dump = head + ir_dump + init_dump + tail
    f.write(dump)