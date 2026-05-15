#include "global.h"
#include "configs/runtime.h"

extern unsigned char* g8E1168C[]; //attribute mini-icons

void sub_80576B4(unsigned char* arg0, unsigned short cardId);

LYN_REPLACE_CHECK(sub_80576B4);
void sub_80576B4__Replacement(unsigned char* arg0, unsigned short cardId) {
  SetCardInfo(cardId);
  if (gRuntimeConfig.disable_element_system == TRUE || gCardInfo.attribute == ATTRIBUTE_NONE)
    return;
  arg0 += 0xC0;
  CpuCopy16(g8E1168C[gCardInfo.attribute], arg0, 64);
}
