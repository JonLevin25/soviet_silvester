#include <Arduino.h>

#ifndef COMMON_H
#define COMMON_H

#define I2C_ADDR_MASTER 0x66
#define I2C_ADDR_SLAVE 0x55

#define NUM_LEDS 60

// #define P(x) Serial.print(x)
#define P(...) Serial.print(__VA_ARGS__)
#define Pln(x) Serial.println(x)

const size_t MSG_SIZE = 2;
const uint16_t END_VALUE = UINT16_MAX;

#endif