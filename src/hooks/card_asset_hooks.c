#include "global.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"

extern struct CardInfo gCardInfo;
extern unsigned char gSharedMem[];
extern const unsigned char *gCardArts[];
extern const unsigned short *gCardArtPalettes[];
extern u32 *gUnk_8E17F18[];
extern u32 *gUnk_8E151C8[];
extern u32 *gUnk_8E17E28[][NUM_LANGUAGES];
extern u32 *gUnk_8E14FE8[][NUM_LANGUAGES];
extern u8 *gUnk_8E137C0;
extern u8 *gUnk_8E137C4[];
extern u8 gUnk_8938384[];
extern u8 gUnk_8938598[];
extern u32 gUnk_89385D8[];
extern u32 gUnk_8938618[];
extern u8 gDigitBufferU16[];
extern u8 g2021B50[];
extern u8 g2021B10[];
extern u8 g2021B90[];
extern u16 *gUnk_8E01364;
extern u16 *gUnk_8E01368;
extern u16 *gUnk_8E0136C;
extern u16 gUnk_8936130[][10];
extern unsigned char *gUnk_8E17F48[];

#include "generated/card_art_generated.inc"

static void sub_80565F0(void *dest, void *r7, unsigned char *src) {
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

static void CopyShopCardBorderTiles(unsigned char *dest, unsigned char *r7, unsigned char *src) {
  unsigned i, j, r8 = 0, ip;
  unsigned char *r4;

  for (j = 0; j < 16; j++)
    *dest++ = *src++;
  for (i = 0; i < 6; i++) {
    for (j = 4; j < 8; j++)
      *dest++ = *src++;
    r4 = r7 + i * 8 + r8;
    for (j = 0; j < 4; j++) {
      *dest = *r4;
      dest++;
      src++;
      r4++;
    }
  }

  ip = 0;
  r8 = 64;
  for (j = 0; j < 16; j++)
    *dest++ = *src++;
  for (i = 0; i < 6; i++) {
    r4 = r7 + i * 8 + ip + 4;
    for (j = 4; j < 8; j++) {
      *dest = *r4;
      dest++;
      src++;
      r4++;
    }
    r4 = r7 + i * 8 + r8;
    for (j = 0; j < 4; j++) {
      *dest = *r4;
      dest++;
      src++;
      r4++;
    }
  }
}

void CopyCardArtDataToBuffers(void);
LYN_REPLACE_CHECK(CopyCardArtDataToBuffers);
void CopyCardArtDataToBuffers__Replacement(void) {
  u8 i;
  const unsigned char *bigArt = gCardArts_Hook[gCardInfo.id];
  const unsigned short *bigPalette = gCardArtPalettes_Hook[gCardInfo.id];

  if (!bigArt)
    bigArt = gCardArts[gCardInfo.id];
  if (!bigPalette)
    bigPalette = gCardArtPalettes[gCardInfo.id];

  sub_800E08C((void *)bigArt, gUnk_8E01364 + 32);
  CpuFill16(0, gUnk_8E01364, 64);
  CpuCopy32(bigPalette, gUnk_8E01368, 128);
  *gUnk_8E01368 = 0;
  for (i = 0; i < 10; i++)
    CpuCopy32(gUnk_8936130[i], gUnk_8E0136C + (10 * i + 0x48 + i * 4), 20);
}
