#include "lighting.h"
#include <FastLED.h>
#include "common.h"
#include "lighting_helper.h"
#include "colors.h"
#include "actions.h"
#include "../triggers.h"

#define PIN_PIXELS 12
// #define LIGHT_TEST

CRGBArray<NUM_LEDS> leds;


static const size_t len_actions = sizeof(actions) / sizeof(Action);
void loop_fade_brightness();

unsigned long trig_hit_millis;
uint16_t last_trig = 0;

double get_trigger_t();

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

    last_trig = idx;
    trig_hit_millis = millis();

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

double get_trigger_t()
{
    if (last_trig == len_triggers - 1) return 1.0;
    double trig_delta_secs = triggers[last_trig+1] - triggers[last_trig];
    unsigned long trig_delta_millis = round(trig_delta_secs * 1E3);

    double millis_since_hit = millis() -  trig_hit_millis;
    double final = millis_since_hit / trig_delta_millis;

    return final;
}