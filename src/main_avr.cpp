#include <Arduino.h>
#include <FastLED.h>

#include "utils/utils.h"

#define PIN_PIXELS 15
#define NUM_LEDS 40

int32_t err_fastled = 0;

CRGBArray<NUM_LEDS> leds;

void fill(HSVHue hue)
{
    leds.fill_solid(CHSV(HUE_RED, 255, 255));
}

void setup()
{
    Serial.begin(9600);
    Serial.println("main_avr.cpp");
    FastLED.addLeds<WS2811, PIN_PIXELS>(leds, NUM_LEDS);
    fill(HUE_RED);
}

void loop()
{
    static int i = 0;
    // auto m1 = micros();
    auto x = i % 2 == 0;
    leds.fill_solid(CRGB(x ? 255 : 0 , x ? 0 : 255, 0));
    i++;
    // auto m2 = micros();
    // updateMaxError(m2-m1,0, &err_fastled);
    // Serial.println(m2-m1);
    // Serial.printf("FastLed longest time: %u\n", err_fastled);
}
