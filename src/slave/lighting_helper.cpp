#include "lighting_helper.h"

#define NUM_LEDS 70

CRGBArray<NUM_LEDS> _leds;

void handle_action(Action a)
{
    switch (a.fn)
    {
        case LIGHT_FILL:
            _leds.fill_solid(a.value);
            break;
        default:
            P("Unknown function! ("); P(a.fn);
            Pln();
    }

    FastLED.show();
}

void set_leds(CRGBArray<NUM_LEDS> leds)
{
    _leds = leds;
}

void fillWhite(uint8_t val)
{
    _leds.fill_solid(CRGB(val, val, val));
}

CHSV Hue(HSVHue h) { return CHSV(h, 255, 255); }

void examples()
{
    int i = 4;
    EVERY_N_MILLISECONDS(15) {
        // do something
    }

    _leds[i] = CRGB::Red;
    _leds[i] = CHSV(160, random8(), random8(100, 255));
    
    // colors and corrections
    FastLED.setTemperature(Candle);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setCorrection(TypicalPixelString);

    FastLED.show();
}