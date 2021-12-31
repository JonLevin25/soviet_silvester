#include "lighting_helper.h"

#define AHSV(target,val) {FN_SET_HSV, target, {Hue(val)}}
#define ARGB(target,val) {FN_SET_RGB, target, {(CRGB)val}}

Action A(LedTarget target, CRGB rgb)
{
    return Action(FN_SET_RGB, target, rgb);
}

Action A(LedTarget target, CRGB::HTMLColorCode rgb)
{
    return Action(FN_SET_RGB, target, rgb);
}

Action actions[] = {
    AHSV(TARGET_ALL, HUE_RED),               // 0
    AHSV(TARGET_ALL, HUE_RED),               // 1
    AHSV(TARGET_ALL, HUE_RED),           // 2
    AHSV(TARGET_ODD, HUE_YELLOW),            // 3
    ARGB(TARGET_ALL, CRGB::DarkRed),         // 4
    AHSV(TARGET_ALL, HUE_BLUE),             // 5
    ARGB(TARGET_EVEN, CRGB::DarkRed),            // 6
    ARGB(TARGET_EVEN, CRGB::DarkRed),              // 7
    AHSV(TARGET_ODD, HUE_YELLOW),            // 8
    AHSV(TARGET_ALL, HUE_RED),               // 9
    AHSV(TARGET_ODD, HUE_BLUE),             // 10
    AHSV(TARGET_ODD, HUE_BLUE),               // 11
    ARGB(TARGET_EVEN, CRGB::Red),          // 12 // red
    ARGB(TARGET_ODD, CRGB::Salmon),             // 13
    AHSV(TARGET_EVEN, HUE_BLUE),        // 14 // blue
    AHSV(TARGET_ALL, HUE_YELLOW),            // 15
    ARGB(TARGET_EVEN, CRGB::Red),          // 17
    AHSV(TARGET_EVEN, HUE_RED),               // 16
    AHSV(TARGET_ALL, HUE_BLUE),               // 18
    AHSV(TARGET_EVEN, HUE_BLUE),               // 19
    AHSV(TARGET_ODD, HUE_RED),               // 20
    AHSV(TARGET_ALL, HUE_RED),               // 21
    AHSV(TARGET_ALL, HUE_YELLOW),                // 22
};