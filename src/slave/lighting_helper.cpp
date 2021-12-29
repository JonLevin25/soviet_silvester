#include "lighting_helper.h"

#define NUM_LEDS 40

CRGBArray<NUM_LEDS> _leds;

void set_leds(CRGBArray<NUM_LEDS> leds)
{
    _leds = leds;
}

void fillWhite(uint8_t val)
{
    _leds.fill_solid(CRGB(val, val, val));
}

CHSV Hue(HSVHue h) { return CHSV(h, 255, 255); }