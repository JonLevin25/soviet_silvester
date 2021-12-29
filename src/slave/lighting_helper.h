#include <Arduino.h>
#include <FastLED.h>
#include "common.h"

enum LightFn : uint8_t
{
    Fill,
};

void set_leds(CRGBArray<NUM_LEDS> leds);
void fillWhite(uint8_t val);
CHSV Hue(HSVHue h);