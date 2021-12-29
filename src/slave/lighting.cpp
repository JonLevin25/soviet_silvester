#include "lighting.h"
#include <FastLED.h>
#include "common.h"
#include "lighting_helper.h"

#define PIN_PIXELS 12

CRGBArray<NUM_LEDS> leds;

typedef struct {
    LightFn fn;
    CHSV value;
} Action;

Action actions[] = {
    {Fill, Hue(HUE_RED)},
    {Fill, Hue(HUE_GREEN)},
    {Fill, Hue(HUE_RED)},
    {Fill, Hue(HUE_GREEN)},
    {Fill, Hue(HUE_RED)},
    {Fill, Hue(HUE_GREEN)},
};
static const size_t len_actions = sizeof(actions) / sizeof(Action);



void handle_action(uint16_t idx)
{
    Action a = actions[idx];
    switch (a.fn)
    {
        case Fill:
            leds.fill_solid(a.value);
            break;
        default:
            P("Unknown function! ("); P(a.fn);
            Pln();
    }

    FastLED.show();
}

void on_light_trigger(uint16_t idx)
{
    P("Trigger: "); P(idx);
    Pln();
    
    if (idx >= len_actions)
    {
        Pln("Index out of range!");
        return;
    }

    handle_action(idx);
}

void setup_lighting()
{
    FastLED.addLeds<WS2812, PIN_PIXELS, GRB>(leds, NUM_LEDS);
    fillWhite(255U);
    set_leds(leds);
}

void reset_lighting()
{
    fillWhite(255);
}

void loop_lighting()
{

}