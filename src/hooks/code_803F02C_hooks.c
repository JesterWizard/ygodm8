#include "global.h"
#include "configs/runtime.h"

LYN_REPLACE_CHECK(sub_803FBCC);
unsigned char sub_803FBCC__Replacement(unsigned char a, unsigned char b) {
  if (gRuntimeConfig.disable_element_system == TRUE)
    return 1;
  if (a == ATTRIBUTE_DIVINE)
    return 1;
  if (b == ATTRIBUTE_DIVINE)
    return 1;
  if (a == ATTRIBUTE_SHADOW && b == ATTRIBUTE_LIGHT)
    return 0;
  if (a == ATTRIBUTE_LIGHT && b == ATTRIBUTE_SHADOW)
    return 2;
  return 1;
}
