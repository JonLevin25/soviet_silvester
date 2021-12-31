#include "lighting.h"
#include <FastLED.h>
#include "common.h"
#include "lighting_helper.h"
#include "colors.h"
#include "actions.h"

#define PIN_PIXELS 12
#define LIGHT_TEST

CRGBArray<NUM_LEDS> leds;


static const size_t len_actions = sizeof(actions) / sizeof(Action);

void test_setup()
{
    reset_lighting();
}

void test_loop()
{
    static uint16_t i = 0;
    if (i < len_actions) {
        EVERY_N_SECONDS(3) {
            handle_action(leds, actions[i++]);
        }
    }
}

void on_light_trigger(uint16_t idx)
{
    if (idx == END_VALUE)
    {
        Pln("Trigger: END!");
        reset_lighting();
        return;
    }

    P("Trigger: "); P(idx);
    Pln();
    
    if (idx >= len_actions)
    {
        Pln("Index out of range!");
        return;
    }

    handle_action(leds, actions[idx]);
}

void setup_lighting()
{
    FastLED.addLeds<WS2812, PIN_PIXELS, GRB>(leds, NUM_LEDS);

    #ifdef LIGHT_TEST
    test_setup();
    #endif
}

void loop_lighting()
{
    #ifdef LIGHT_TEST
    test_loop();
    #endif
}

void reset_lighting()
{    
    fill_palette(leds, NUM_LEDS, 0, 2, init_bg_palette(), 127, LINEARBLEND);
    light_fill<CRGB>(leds, TARGET_EVEN, CRGB::Green);
    FastLED.show();
}