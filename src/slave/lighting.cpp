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
LightFn lastFn = NONE;

static const size_t len_actions = sizeof(actions) / sizeof(Action);
double get_trigger_t();

unsigned long trig_hit_millis;
uint16_t last_trig = 0;

void test_setup();
void test_loop();

void handle_action(LEDS_T leds, Action a)
{
    P("Action: "); P(GetFn(a.fn)); P(", Target: "); P(a.target); P(", Value: ");
    lastFn = a.fn;

    switch (a.fn)
    {
        case FN_SET_RGB:
            P(a.rgbColor.r); P(' '); P(a.rgbColor.g); P(' '); P(a.rgbColor.b);
            Pln();
            light_fill<CRGB>(leds, a.target, a.rgbColor);
            break;
        case FN_SET_HSV:
            P(a.hsvColor.h); P(' '); P(a.hsvColor.s); P(' '); P(a.hsvColor.v);
            Pln();
            light_fill<CHSV>(leds, a.target, a.hsvColor);
            break;
        case FN_SET_BRIGHTNESS:
            Pln(a.value);
            FastLED.setBrightness(a.value);
            break;
        default:
            P("Unknown function! ("); P(a.fn); P(')');
            Pln();
            return;
    }

    FastLED.show();
}

void handle_action(uint16_t idx)
{
    Action action = actions[idx];
    handle_action(leds, action);
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

    handle_action(idx);
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
    // set idle colors, before and after animations
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

void test_setup()
{
    reset_lighting();
}

void test_loop()
{
    // test iterate over actions (without i2c triggers)
    static uint16_t i = 0;
    if (i < len_actions) {
        EVERY_N_SECONDS(3) {
            handle_action(i++);
        }
    }
}
