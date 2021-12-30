#include <Arduino.h>
#include <FastLED.h>
#include "common.h"

enum LightFn : uint8_t
{
    LIGHT_FILL,
    BRIGHTNESS,
};

typedef struct {
    LightFn fn;
    CHSV value;
} Action;


void handle_action(Action action);
void set_leds(CRGBArray<NUM_LEDS> leds);
void fillWhite(uint8_t val);
CHSV Hue(HSVHue h);