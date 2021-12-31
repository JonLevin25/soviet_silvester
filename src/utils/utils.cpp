#include "utils.h"

void updateMaxError(uint32_t actual, uint32_t expected, int32_t *ptrMaxError) { 
  bool errPositive = actual > expected;
  uint32_t uerror = errPositive
    ? (actual - expected)
    : (expected - actual);
  uint32_t uMaxError = *ptrMaxError > 0
    ? *ptrMaxError
    : -(*ptrMaxError);

  if (uerror < uMaxError) return;

  *ptrMaxError = errPositive
    ? +((int32_t)uerror)
    : -((int32_t)uerror);
}