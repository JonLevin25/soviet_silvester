#include "lighting_helper.h"

Action actions[] = {
    {FN_SET_HSV, TARGET_ALL, {Hue(HUE_RED)}},
    {FN_SET_BRIGHTNESS, TARGET_ALL, (uint8_t) 127U},
    {FN_SET_BRIGHTNESS, TARGET_ALL, (uint8_t) 255U},
    {FN_SET_HSV, TARGET_EVEN, {Hue(HUE_GREEN)}},
    {FN_SET_HSV, TARGET_EVEN, {Hue(HUE_RED)}},
    {FN_SET_HSV, TARGET_ODD, {Hue(HUE_GREEN)}},
    {FN_SET_HSV, TARGET_ALL, {Hue(HUE_ORANGE)}},
    {FN_SET_HSV, TARGET_EVEN, {Hue(HUE_RED)}},
    {FN_SET_HSV, TARGET_ODD, {Hue(HUE_YELLOW)}},
    {FN_SET_HSV, TARGET_ALL, {Hue(HUE_RED)}},
};