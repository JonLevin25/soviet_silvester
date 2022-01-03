#include <Arduino.h>
#include <Wire.h>
#include "common.h"
#include "utils/utils.h"
#include "utils/i2c_helper.h"
#include "slave/lighting.h"

void onData(uint16_t value);

void setup()
{
    Serial.begin(9600);
    Serial.println("main_slave.cpp");
    
    pinMode(SDA, INPUT_PULLUP);
    pinMode(SCL, INPUT_PULLUP);

    wire_setup(false, I2C_ADDR_SLAVE);
    wire_registerCallback(onData);

    setup_lighting();
}

void onData(uint16_t value)
{
    P("Received Data: "); P(value);
    Pln();
    if (value == END_VALUE)
    {
        reset_lighting();
    }
    else
    {
        on_light_trigger(value);
    }
}

void loop()
{
    loop_lighting();
}
