#include "global.h"
#include "configs/runtime.h"
#include "constants/title_screen.h"
#include "duel.h"
#include "game_menu.h"
#include "gfx_reg_buffers.h"
#include "text.h"

extern u8 gLanguage;
extern u16 gNewButtons;
extern unsigned *g8E0CD9C;
extern unsigned char gText_ReplaceSaveData[];
extern unsigned short (*g8E0CDA4)[][30];
extern unsigned *g8E0CDA0;

#define OPTION_NEW_GAME 0

unsigned char sub_800AC64(void);
void sub_800ACE8(unsigned char);
void sub_800ADC4(void);
void sub_800AF68(void);
void sub_800AEC4(void);
void LoadCustomSaveExtrasFromFlashPrimary(void);
extern u8 gLoadCustomSaveExtrasPending;
unsigned char TitleScreenChooseOption(void);
unsigned char TitleScreenNewGameOnly(void);
void sub_80354A8(void);
void TitleScreenMain(void);
void CopySpriteTilesAndPalette(void);
void sub_80357C0(void);
void VBlankCbInitGfxRegs(void);

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

static void RemapDialogFontPixels(void) {
  /* The 1bpp font renderer writes pixel value 0xFF for text.
   * Remap to palette index 0x17 (23) which is pure white (0x7FFF)
   * in the custom title screen palette, avoiding conflict with
   * background pixels that use palette index 255.
   * Scan only the tile area (max 0x2000 bytes = 128 tiles) to
   * avoid corrupting tilemaps at sbb1E/sbb1F (0xF000+). */
  u8 *p = gVr.a + 0xC000;
  u32 i;
  for (i = 0; i < 0x2000; i++) {
    if (p[i] == 0xFF)
      p[i] = 0x17;
  }
}

static void CustomCopyBgGfx(void) {
  /* Cast to u32*: BIOS LZ77 reads the stream as words (needs aligned(4) source). */
  LZ77UnCompWram((const u32 *)sTitleScreenTiles, gBgVram.cbb0);
  TitleScreen_BuildTilemap();
  TitleScreen_SetupSaveDialogGfx();
  RemapDialogFontPixels();
  CpuFill16(0, gPaletteBuffer, TITLE_SCREEN_PALETTE_BYTES);
  TitleScreen_LoadCustomPalette();
}

static void VanillaCopyGfxAndInitGfxRegs(void) {
  VanillaCopyBgGfx();
  CopySpriteTilesAndPalette();
  sub_80357C0();
  SetVBlankCallback(VBlankCbInitGfxRegs);
  WaitForVBlank();
}

static void CustomCopyGfxAndInitGfxRegs(void) {
  CustomCopyBgGfx();
  CopySpriteTilesAndPalette();
  sub_80357C0();
  SetVBlankCallback(VBlankCbInitGfxRegs);
  WaitForVBlank();
}

/* Title screen idle frame counter */
extern u16 gTitleScreenIdleFrames;
extern bool8 VideoPlayer_Play(void);

#define IDLE_FRAMES_TO_VIDEO 300  /* ~5 seconds at 60fps */

/* LYN_REPLACE_CHECK(CopyGfxAndInitGfxRegs) */
APPEND_TEXT void CopyGfxAndInitGfxRegs__Replacement(void) {
  /* EWRAM is not zeroed at boot on every emulator (MyBoy leaves garbage). */
  gTitleScreenIdleFrames = 0;

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

/* LYN_REPLACE_CHECK(sub_80357F8) */
APPEND_TEXT void sub_80357F8__Replacement(void) {
  VanillaSub80357F8();

  if (gRuntimeConfig.enable_title_screen_video != TRUE)
    return;

  /*
   * EWRAM is not zero-initialised at boot. MyBoy (and hardware after some
   * resets) leaves garbage here; any value >= IDLE_FRAMES_TO_VIDEO would
   * start COMET on the first idle tick and crash that emulator. Only clearing
   * >= 0xFF00 was not enough.
   */
  if (gTitleScreenIdleFrames >= IDLE_FRAMES_TO_VIDEO)
    gTitleScreenIdleFrames = 0;

  gTitleScreenIdleFrames++;
  if (gTitleScreenIdleFrames < IDLE_FRAMES_TO_VIDEO)
    return;

  /*
   * Vanilla also calls this once on the New Game / Continue exit path.
   * Do not start COMET on that frame: gNewButtons may still latch the select
   * press after A is released (Continue has no confirm dialog).
   */
  if ((gNewButtons & ANY_BUTTON) != 0 || (~REG_KEYINPUT & ANY_BUTTON) != 0) {
    gTitleScreenIdleFrames = 0;
    return;
  }

  gTitleScreenIdleFrames = 0;
  VideoPlayer_Play();
}

/* No CallThumb into statics — MyBoy dies on that pattern (see NamingScreen). */
LYN_REPLACE_CHECK(TitleScreenMain);
void TitleScreenMain__Replacement(void) {
  unsigned char option;

  if (!sub_800AC64())
    option = TitleScreenNewGameOnly();
  else
    option = TitleScreenChooseOption();

  if (option == OPTION_NEW_GAME) {
    sub_800AF68();
    sub_80354A8();
    return;
  }

  /* Reseat flash stubs before any Continue save op (ACE8 may bx g20245AC). */
  sub_800AEC4();
  sub_800ACE8(sub_800AC64());
  sub_800ADC4();
  sub_80354A8();

  /*
   * Title fade leaves BLDCNT/BLDY hot and VBlank on sub_8035AD8. Blank +
   * clear blend + drop VBlank before Game Menu so MyBoy does not enter
   * sub_8024ECC mid-blend with a stale title VBlank path.
   */
  REG_DISPCNT = DISPCNT_FORCED_BLANK;
  gBLDCNT = 0;
  gBLDY = 0;
  LoadBlendingRegs();
  SetVBlankCallback(NULL);

  GameMenuMain();

  /*
   * Same cleanup before OverworldMain. Extras load is no-op'd for MyBoy
   * Continue bisect — do not set pending until loaders are re-enabled.
   */
  REG_DISPCNT = DISPCNT_FORCED_BLANK;
  gBLDCNT = 0;
  gBLDY = 0;
  LoadBlendingRegs();
  SetVBlankCallback(NULL);
  gLoadCustomSaveExtrasPending = FALSE;
}
