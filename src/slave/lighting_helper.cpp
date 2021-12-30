#include "lighting_helper.h"
#include "colors.h"

#define LEDS_T CRGBArray<NUM_LEDS>

template <typename Color>
void fill(LEDS_T leds, LedTarget target, Color color);

void handle_action(LEDS_T leds, Action a)
{
    P("Action: "); P(GetFn(a.fn)); P(", Target: "); P(a.target); P(", Value: ");
    
    switch (a.fn)
    {
        case FN_SET_RGB:
            P(a.rgbColor.r); P(' '); P(a.rgbColor.g); P(' '); P(a.rgbColor.b);
            Pln();
            fill<CRGB>(leds, a.target, a.rgbColor);
            break;
        case FN_SET_HSV:
            P(a.hsvColor.h); P(' '); P(a.hsvColor.s); P(' '); P(a.hsvColor.v);
            Pln();
            fill<CHSV>(leds, a.target, a.hsvColor);
            break;
        case FN_SET_BRIGHTNESS:
            Pln(a.value);
            FastLED.setBrightness(a.value);
        default:
            P("Unknown function! ("); P(a.fn);
            Pln();
    }

    FastLED.show();
}

void fillWhite(LEDS_T leds, uint8_t val)
{
    leds.fill_solid(CRGB(val, val, val));
}


CHSV Hue(HSVHue h) { return CHSV(h, 255, 255); }

void examples(LEDS_T leds)
{
    int i = 4;
    EVERY_N_MILLISECONDS(15) {
        // do something
        
    }

    leds[i] = CRGB::Red;
    leds[i] = CHSV(160, random8(), random8(100, 255));
    
    // colors and corrections
    FastLED.setTemperature(Candle);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setCorrection(TypicalPixelString);

    FastLED.show();
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
void fill(LEDS_T leds, LedTarget target, Color color)
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


// log helpers
const char *GetFn(LightFn fn)
{
    switch (fn)
    {
        case FN_SET_HSV: return "FN_SET_HSV";
        case FN_SET_RGB: return "FN_SET_RGB";
        case FN_SET_BRIGHTNESS: return "FN_SET_BRIGHTNESS";
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

