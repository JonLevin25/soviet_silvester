#include "lighting_helper.h"
#include "colors.h"


CHSV Hue(HSVHue h) { return CHSV(h, 255, 255); }

void loop_fade_brightness(uint8_t start, uint8_t target, double t)
{
    uint8_t val = lerp8(start, target, t);
    // P("Loop brightness: "); Pln(val);
    FastLED.setBrightness(val);
    FastLED.show();
}

uint8_t lerp8(uint8_t start, uint8_t end, double t)
{
    int16_t iStart = start;
    int16_t iEnd = end;
    return start + t * (iEnd - iStart);
}

struct IncParams {uint8_t idx_start; uint8_t inc; };
IncParams get_inc_params(LedTarget target)
{
    switch (target)
    {
        case TARGET_ALL: return {0, 1};
        case TARGET_EVEN: return { 1, 2 };
        case TARGET_ODD: return { 0, 2 };
        default:
            P("Unknown LedTarget! "); Pln(target);
            return {0, 1};
    }
}

template <typename Color>
void light_fill(LEDS_T leds, LedTarget target, Color color)
{
    if (target == TARGET_ALL)
    {
        leds.fill_solid(color);
        return;
    }

    auto params = get_inc_params(target);
    uint16_t i = params.idx_start;
    while (i < NUM_LEDS) {
        leds[i] = color;
        i += params.inc;
    }
}

template void light_fill<CRGB>(LEDS_T leds, LedTarget target, CRGB color);
template void light_fill<CHSV>(LEDS_T leds, LedTarget target, CHSV color);


// log helpers
const char *GetFn(LightFn fn)
{
    switch (fn)
    {
        case FN_SET_HSV: return "FN_SET_HSV";
        case FN_SET_RGB: return "FN_SET_RGB";
        case FN_SET_BRIGHTNESS: return "FN_SET_BRIGHTNESS";
        case NONE: return "NONE";
        default: return "FN_UNKNOWN";
    }
}

const char *GetTarget(LedTarget target)
{
    switch (target)
    {
        case TARGET_ALL: return "TARGET_ALL";
        case TARGET_EVEN: return "TARGET_EVEN";
        case TARGET_ODD: return "TARGET_ODD";
        default: return "TARGET_UNKNOWN";
    }
}

