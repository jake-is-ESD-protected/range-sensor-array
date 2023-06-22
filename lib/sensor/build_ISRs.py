pin_list = [32, 33, 34]
trig_pin = 27

with open("./lib/sensor/sensor_ir.h", "w") as f:
    head = "// THIS FILE IS AUTO-GENERATED\n\n" + \
           "#ifndef _SENSOR_IR_H_\n" + \
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
    head = "// THIS FILE IS AUTO-GENERATED\n\n" + \
           '#include "sensor_ir.h"\n' + \
           "uint32_t timings[NUM_SENSORS] = {0};\n\n"
    
    ir_dump = ""
    for i, pin in enumerate(pin_list):
        ir_dump += f"void IRAM_ATTR pin{pin}_ISR(void)" + \
                    "{\n" + \
                   f"\ttimings[{i}] = micros();\n" + \
                    "}\n\n"
    
    init_dump = "void init_ISRs(void){\n" + \
                f"\tpinMode({trig_pin}, OUTPUT);\n"

    for pin in pin_list:
        init_dump += f"\tpinMode({pin}, INPUT);\n"
        init_dump += f"\tattachInterrupt({pin}, pin{pin}_ISR, FALLING);\n"
    init_dump += "}\n\n"

    tail = "uint32_t trigger(uint32_t len){\n" + \
           "\tdigitalWrite(TRIG_PIN, HIGH);\n" + \
           "\tdelayMicroseconds(len);\n" + \
           "\tdigitalWrite(TRIG_PIN, LOW);\n" + \
           "\tuint32_t trig_time = micros();\n" + \
           "\treturn trig_time;\n" + \
           "}"


    dump = head + ir_dump + init_dump + tail
    f.write(dump)
