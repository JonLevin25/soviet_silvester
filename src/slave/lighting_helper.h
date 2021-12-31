#include <Arduino.h>
#include <FastLED.h>
#include "common.h"

#define LEDS_T CRGBArray<NUM_LEDS>

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
    Action(LightFn fn, LedTarget target, uint8_t val) : fn(fn), target(target), value(val) {}
    Action(LightFn fn, LedTarget target, CHSV hsv) : fn(fn), target(target), hsvColor(hsv) {}
    Action(LightFn fn, LedTarget target, CRGB rgb) : fn(fn), target(target), rgbColor(rgb) {}
    // Action(LightFn fn, LedTarget target, TProgmemRGBGradientPalette_byte palette) : fn(fn), target(target), palette(palette) {}

    LightFn fn;
    LedTarget target;

    union {
        CHSV hsvColor;
        uint8_t value;
        CRGB rgbColor;
        TProgmemRGBGradientPalette_byte palette;
    };
};

template <typename Color>
void light_fill(LEDS_T leds, LedTarget target, Color color);



void handle_action(LEDS_T leds, Action a);
void fillWhite(LEDS_T leds, uint8_t val);
CHSV Hue(HSVHue h);

const char *GetFn(LightFn fn);
const char *GetTarget(LedTarget target);