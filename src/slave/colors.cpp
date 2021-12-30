#include "colors.h"

DEFINE_GRADIENT_PALETTE( _init_bg_gp ) {
  0, 255,255,255,
  127, 129,221,236,
  255, 255,255,255,
};
CRGBPalette16 _init_bg_palette = _init_bg_gp;

// Gradient palette "white_christmas_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ncdc/tn/white-christmas.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.
DEFINE_GRADIENT_PALETTE( _white_christmas_gp ) {
    0, 117, 97, 49,
   12, 117, 97, 49,
   12,  26,173,106,
   25,  26,173,106,
   25,  10, 77,164,
   63,  10, 77,164,
   63,   0, 21, 85,
  102,   0, 21, 85,
  102,  53, 86,135,
  127,  53, 86,135,
  127,  26, 31, 65,
  153,  26, 31, 65,
  153,  61, 31, 96,
  191,  61, 31, 96,
  191,  82, 97, 85,
  229,  82, 97, 85,
  229, 255,255,255,
  255, 255,255,255};


  TProgmemRGBGradientPalette_byte init_bg_gp() { return _init_bg_gp; }
  CRGBPalette16 init_bg_palette() {return _init_bg_palette; }