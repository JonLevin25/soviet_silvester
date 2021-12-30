#include "lighting.h"
#include <FastLED.h>
#include "common.h"
#include "lighting_helper.h"

#define PIN_PIXELS 12

CRGBArray<NUM_LEDS> leds;

Action actions[] = {
    {LIGHT_FILL, Hue(HUE_RED)},
    {LIGHT_FILL, Hue(HUE_GREEN)},
    {LIGHT_FILL, Hue(HUE_RED)},
    {LIGHT_FILL, Hue(HUE_GREEN)},
    {LIGHT_FILL, Hue(HUE_RED)},
    {LIGHT_FILL, Hue(HUE_GREEN)},
};
static const size_t len_actions = sizeof(actions) / sizeof(Action);


void on_light_trigger(uint16_t idx)
{
    P("Trigger: "); P(idx);
    Pln();
    
    if (idx >= len_actions)
    {
        Pln("Index out of range!");
        return;
    }

    handle_action(actions[idx]);
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
    EVERY_N_MILLISECONDS(15) {

    }
}