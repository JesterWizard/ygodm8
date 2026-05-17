#include "global.h"
#include "common-chax.h"

extern unsigned char* g8E1168C[]; //attribute mini-icons
extern unsigned char gSharedMem[];
extern unsigned char *g8E17F70[];
extern unsigned char *gUnk_8E17F48[];
extern const unsigned char g89A81DE[];
extern const unsigned char g89A7F1E[][64];
extern const unsigned char g89A875E[][64];
extern const unsigned char g89A849E[][64];
extern u8 gDigitBufferU16[];

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

void sub_80572A8(unsigned char* arg0, struct DuelCard* arg1);
LYN_REPLACE_CHECK(sub_80572A8);
void sub_80572A8__Replacement(unsigned char* arg0, struct DuelCard* arg1) {
  if (gCardInfo.atk == 0xFFFF)
    return;

  gStatMod.card = arg1->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(arg1);
  SetFinalStat(&gStatMod);

  if (gCardInfo.atk / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.atk / 100, DIGIT_FLAG_NONE);

  arg0 += 0x800;
  CpuCopy16(g89A81DE + gDigitBufferU16[3] * 64, arg0, 0x40);
  arg0 += 0x40;
  CpuCopy16(g89A7F1E[gDigitBufferU16[4]], arg0, 0x40);
}

void sub_805733C(unsigned char* arg0, struct DuelCard* arg1);
LYN_REPLACE_CHECK(sub_805733C);
void sub_805733C__Replacement(unsigned char* arg0, struct DuelCard* arg1) {
  if (gCardInfo.atk == 0xFFFF)
    return;

  gStatMod.card = arg1->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(arg1);
  SetFinalStat(&gStatMod);

  if (gCardInfo.def / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.def / 100, DIGIT_FLAG_NONE);

  arg0 += 0x880;
  CpuCopy16(g89A875E[gDigitBufferU16[3]], arg0, 0x40);
  arg0 += 0x40;
  CpuCopy16(g89A849E[gDigitBufferU16[4]], arg0, 0x40);
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
