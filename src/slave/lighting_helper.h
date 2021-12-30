#include <Arduino.h>
#include <FastLED.h>
#include "common.h"

enum LightFn : uint8_t
{
    FN_SET_HSV,
    FN_SET_RGB,
    FN_SET_BRIGHTNESS,
};

enum LedTarget : uint8_t
{
    TARGET_ALL,
    TARGET_EVEN,
    TARGET_ODD,   
};

struct Action
{
    LightFn fn;
    LedTarget target;

    union {
        CHSV hsvColor;
        CRGB rgbColor;
        TProgmemRGBGradientPalette_byte palette;
        uint8_t value;
    };
};

void handle_action(CRGBArray<NUM_LEDS> leds, Action a);
void fillWhite(CRGBArray<NUM_LEDS> leds, uint8_t val);
CHSV Hue(HSVHue h);

const char *GetFn(LightFn fn);
const char *GetTarget(LedTarget target);