#include "colors.h"

DEFINE_GRADIENT_PALETTE( _init_bg_gp ) {
  0, 255,255,255,
  127, 129,221,236,
  255, 255,255,255,
};
CRGBPalette16 _init_bg_palette = _init_bg_gp;


TProgmemRGBGradientPalette_byte init_bg_gp() { return _init_bg_gp; }
CRGBPalette16 init_bg_palette() {return _init_bg_palette; }