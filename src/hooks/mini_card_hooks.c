#include "global.h"
#include "common-chax.h"

extern unsigned char* g8E1168C[]; //attribute mini-icons
extern unsigned char gSharedMem[];
extern unsigned char *g8E17F70[];
extern unsigned char *gUnk_8E17F48[];

static void ComposeMiniCard(void *dest, void *r7, unsigned char *src) {
  unsigned i, j, r8 = 0, ip;
  unsigned char *r4;
  unsigned char *dst = dest;
  unsigned char *src2 = src;
  unsigned char *base = r7;

  for (j = 0; j < 16; j++)
    *dst++ = *src2++;
  for (i = 0; i < 6; i++) {
    for (j = 4; j < 8; j++)
      *dst++ = *src2++;
    r4 = base + i * 8 + r8;
    for (j = 0; j < 4; j++) {
      *dst = *r4;
      dst++;
      src2++;
      r4++;
    }
  }

  ip = 0;
  r8 = 64;
  for (j = 0; j < 16; j++)
    *dst++ = *src2++;
  for (i = 0; i < 6; i++) {
    r4 = base + i * 8 + ip + 4;
    for (j = 4; j < 8; j++) {
      *dst = *r4;
      dst++;
      src2++;
      r4++;
    }
    r4 = base + i * 8 + r8;
    for (j = 0; j < 4; j++) {
      *dst = *r4;
      dst++;
      src2++;
      r4++;
    }
  }

  ip = 64;
  r8 = 128;
  for (j = 0; j < 16; j++)
    *dst++ = *src2++;
  for (i = 0; i < 6; i++) {
    r4 = base + i * 8 + ip + 4;
    for (j = 4; j < 8; j++) {
      *dst = *r4;
      dst++;
      src2++;
      r4++;
    }
    r4 = base + i * 8 + r8;
    for (j = 0; j < 4; j++) {
      *dst = *r4;
      dst++;
      src2++;
      r4++;
    }
  }
}

void sub_80576B4(unsigned char* arg0, unsigned short cardId);

LYN_REPLACE_CHECK(sub_80576B4);
void sub_80576B4__Replacement(unsigned char* arg0, unsigned short cardId) {
  SetCardInfo(cardId);
  if (gRuntimeConfig.disable_element_system == TRUE || gCardInfo.attribute == ATTRIBUTE_NONE)
    return;
  arg0 += 0xC0;
  CpuCopy16(g8E1168C[gCardInfo.attribute], arg0, 64);
}
