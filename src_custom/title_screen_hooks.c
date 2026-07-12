#include "global.h"
#include "configs/runtime.h"
#include "constants/title_screen.h"
#include "duel.h"
#include "text.h"

typedef void (*VoidFunc)(void);

extern u8 gLanguage;
extern unsigned *g8E0CD9C;
extern unsigned char gText_ReplaceSaveData[];
extern unsigned short (*g8E0CDA4)[][30];
extern unsigned *g8E0CDA0;

union {
  u8 a[0x4000];
  u16 b[0x2000];
} extern gVr;

extern struct {
  unsigned short unk0;
  unsigned short unk2;
} *g8E0CDB0;
extern unsigned short g8E0CDB4[];

#include "generated/title_screen_assets_generated.inc"

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

static u16 *TitleScreen_VramWords(void) {
  return (u16 *)&gBgVram;
}

static void TitleScreen_BuildTilemap(void) {
  u16 x, y, tile;

  for (y = 0; y < TITLE_SCREEN_MAP_HEIGHT; y++) {
    for (x = 0; x < TITLE_SCREEN_MAP_WIDTH; x++) {
      tile = y * TITLE_SCREEN_MAP_WIDTH + x;
      gBgVram.sbb1F[y][x] = tile;
    }
  }
}

static void TitleScreen_SetupSaveDialogGfx(void) {
  u32 i;
  u16 *vramWords = TitleScreen_VramWords();

  CopyStringTilesToVRAMBuffer(gVr.a + 0xC000, gText_ReplaceSaveData, 0x4FF);
  for (i = 0; i < 20; i++)
    CpuFill32(0, gVr.a + 0xF000 + i * 64, 60);
  for (i = 0; i < 4; i++) {
    vramWords[0x796E + i] = i + 2;
    vramWords[0x798E + i] = i + 6;
  }
  for (i = 0; i < 13; i++) {
    vramWords[0x78A9 + i] = i + 10;
    vramWords[0x78C9 + i] = i + 23;
    vramWords[0x78E9 + i] = i + 36;
    vramWords[0x7909 + i] = i + 49;
    vramWords[0x7929 + i] = i + 62;
  }
}

static void TitleScreen_LoadCustomPalette(void) {
  CpuCopy16(sTitleScreenPalette, gPaletteBuffer, TITLE_SCREEN_PALETTE_BYTES);
}

static void VanillaCopyBgGfx(void) {
  u32 i;
  u8 *lang = &gLanguage;

  LZ77UnCompWram(g8E0CD9C, gVr.b);
  TitleScreen_SetupSaveDialogGfx();
  switch (*lang) {
    case 1:
      for (i = 0; i < 20; i++)
        CpuCopy32((*g8E0CDA4)[i], gVr.a + 0xF800 + i * 64, 60);
      break;
    case 2:
      for (i = 0; i < 20; i++)
        CpuCopy32((*g8E0CDA4)[i], gVr.a + 0xF800 + i * 64, 60);
      break;
    case 3:
      for (i = 0; i < 20; i++)
        CpuCopy32((*g8E0CDA4)[i], gVr.a + 0xF800 + i * 64, 60);
      break;
    case 4:
      for (i = 0; i < 20; i++)
        CpuCopy32((*g8E0CDA4)[i], gVr.a + 0xF800 + i * 64, 60);
      break;
    default:
      for (i = 0; i < 20; i++)
        CpuCopy32((*g8E0CDA4)[i], gVr.a + 0xF800 + i * 64, 60);
      break;
  }
  CpuCopy32(g8E0CDA0, gPaletteBuffer, TITLE_SCREEN_PALETTE_BYTES);
}

static void CustomCopyBgGfx(void) {
  LZ77UnCompWram(sTitleScreenTiles, gBgVram.cbb0);
  TitleScreen_BuildTilemap();
  TitleScreen_SetupSaveDialogGfx();
  CpuFill16(0, gPaletteBuffer, TITLE_SCREEN_PALETTE_BYTES);
  TitleScreen_LoadCustomPalette();
}

static void VanillaCopyGfxAndInitGfxRegs(void) {
  VanillaCopyBgGfx();
  CallThumbVoid(TITLE_SCREEN_CopySpriteTilesAndPalette);
  CallThumbVoid(TITLE_SCREEN_sub_80357C0);
  SetVBlankCallback((void (*)(void))(TITLE_SCREEN_VBlankCbInitGfxRegs | 1));
  WaitForVBlank();
}

static void CustomCopyGfxAndInitGfxRegs(void) {
  CustomCopyBgGfx();
  CallThumbVoid(TITLE_SCREEN_CopySpriteTilesAndPalette);
  CallThumbVoid(TITLE_SCREEN_sub_80357C0);
  SetVBlankCallback((void (*)(void))(TITLE_SCREEN_VBlankCbInitGfxRegs | 1));
  WaitForVBlank();
}

/* LYN_REPLACE_CHECK(CopyGfxAndInitGfxRegs) */
APPEND_TEXT void CopyGfxAndInitGfxRegs__Replacement(void) {
  if (gRuntimeConfig.enable_custom_title_screen == TRUE)
    CustomCopyGfxAndInitGfxRegs();
  else
    VanillaCopyGfxAndInitGfxRegs();
}

/* LYN_REPLACE_CHECK(VBlankCbTryStartNewGame) */
APPEND_TEXT void VBlankCbTryStartNewGame__Replacement(void) {
  REG_DISPCNT |= DISPCNT_BG0_ON | DISPCNT_WIN0_ON;
  gBLDY = 10;
  LoadBlendingRegs();
}

/* LYN_REPLACE_CHECK(VBlankCbTryStartNewGameEnd) */
APPEND_TEXT void VBlankCbTryStartNewGameEnd__Replacement(void) {
  REG_DISPCNT &= ~(DISPCNT_BG0_ON | DISPCNT_WIN0_ON);
  gBLDY = 0;
  LoadBlendingRegs();
}

static void VanillaSub80357F8(void) {
  if (!g8E0CDB0->unk2) {
    if (g8E0CDB0->unk0 > 29)
      g8E0CDB0->unk0 = 0;
    gBLDALPHA = (g8E0CDB4[g8E0CDB0->unk0] & 0xF) | 0x1000;
    g8E0CDB0->unk2 = 0;
    g8E0CDB0->unk0++;
  } else {
    g8E0CDB0->unk2++;
  }
}

/* Title screen idle frame counter */
extern u16 gTitleScreenIdleFrames;
extern bool8 VideoPlayer_Play(void);

#define IDLE_FRAMES_TO_VIDEO 300  /* ~5 seconds at 60fps */

/* LYN_REPLACE_CHECK(sub_80357F8) */
APPEND_TEXT void sub_80357F8__Replacement(void) {
  VanillaSub80357F8();

  if (gRuntimeConfig.enable_title_screen_video == TRUE) {
    /* EWRAM is not zero-initialised at boot. Clear typical garbage. */
    if (gTitleScreenIdleFrames >= 0xFF00)
      gTitleScreenIdleFrames = 0;

    gTitleScreenIdleFrames++;
    if (gTitleScreenIdleFrames >= IDLE_FRAMES_TO_VIDEO) {
      gTitleScreenIdleFrames = 0;
      VideoPlayer_Play();
    }
  }
}
