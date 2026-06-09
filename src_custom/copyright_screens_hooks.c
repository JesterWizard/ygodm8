#include "global.h"
#include "configs/runtime.h"
#include "constants/opening_screens.h"
#include "duel.h"

typedef void (*VoidFunc)(void);

extern u8 g201EE60;
extern u8 g201EE61;

#include "generated/opening_screen_assets_generated.inc"

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

static inline VoidFunc VanillaCopyrightFn(u32 addr) {
  return (VoidFunc)(addr | 1);
}

/*
 * LynJump overwrites the first 12 bytes at CopyrightScreensMain ($268D8).
 * Calling that address loops back into this replacement; run the vanilla
 * body via its still-intact helper functions instead.
 */
static void VanillaCopyrightScreensMain(void) {
  u8 i;

  CallThumbVoid(0x08026A94);
  SetVBlankCallback(VanillaCopyrightFn(0x08026D74));
  WaitForVBlank();
  for (i = 0; i < 120; i++)
    WaitForVBlank();
  CallThumbVoid(0x08026D04);
  SetVBlankCallback(VanillaCopyrightFn(0x08026E44));
  REG_BLDCNT = 0x3FFF;
  g201EE61 = 16;
  g201EE60 = 0;
  WaitForVBlank();
  while (g201EE61) {
    if (++g201EE60 > 3) {
      if (g201EE61 != 0)
        g201EE61--;
      g201EE60 = 0;
    }
    REG_BLDY = g201EE61;
    WaitForVBlank();
  }
  for (i = 0; i < 120; i++)
    WaitForVBlank();
  g201EE61 = 0;
  g201EE60 = 0;
  while (g201EE61 < 16) {
    if (++g201EE60 > 3) {
      if (g201EE61 < 16)
        g201EE61++;
      g201EE60 = 0;
    }
    REG_BLDY = g201EE61;
    WaitForVBlank();
  }
  CallThumbVoid(0x08026D20);
  SetVBlankCallback(VanillaCopyrightFn(0x08026E94));
  REG_BLDCNT = 0x3FFF;
  g201EE61 = 16;
  g201EE60 = 0;
  WaitForVBlank();
  while (g201EE61) {
    if (++g201EE60 > 3) {
      if (g201EE61 != 0)
        g201EE61--;
      g201EE60 = 0;
    }
    REG_BLDY = g201EE61;
    WaitForVBlank();
  }
  for (i = 0; i < 120; i++)
    WaitForVBlank();
  g201EE61 = 0;
  g201EE60 = 0;
  while (g201EE61 < 16) {
    if (++g201EE60 > 3) {
      if (g201EE61 < 16)
        g201EE61++;
      g201EE60 = 0;
    }
    REG_BLDY = g201EE61;
    WaitForVBlank();
  }
  REG_BLDCNT = 0x3FFF;
  g201EE61 = 16;
  g201EE60 = 0;
  REG_BLDY = g201EE61;
}

static bool8 OpeningScreens_AnyButtonPressed(void) {
  return (~REG_KEYINPUT & ANY_BUTTON) != 0;
}

static bool8 OpeningScreens_WaitForVBlankOrSkip(void) {
  WaitForVBlank();
  return OpeningScreens_AnyButtonPressed();
}

static void OpeningScreens_VBlankInit(void) {
  REG_DISPCNT = DISPCNT_FORCED_BLANK;
  REG_BLDCNT = 0;
  REG_BLDALPHA = 0;
  REG_BLDY = 0;
}

static void OpeningScreens_BuildTilemap(void) {
  u16 x, y, tile;

  for (y = 0; y < OPENING_SCREEN_MAP_HEIGHT; y++) {
    for (x = 0; x < OPENING_SCREEN_MAP_WIDTH; x++) {
      tile = y * OPENING_SCREEN_MAP_WIDTH + x;
      gBgVram.sbb1F[y][x] = tile;
    }
  }
}

static void OpeningScreens_VBlankShowScreen(void) {
  LoadPalettes();
  gBG2VOFS = 0;
  gBG2HOFS = 0;
  LoadBgOffsets();
  REG_BG2CNT = OPENING_SCREEN_BG2CNT;
  REG_DISPCNT = DISPCNT_BG2_ON;
}

static void OpeningScreens_LoadScreenGfx(u8 screenIndex) {
  const struct OpeningScreenAsset *asset;

  if (screenIndex >= OPENING_SCREEN_COUNT)
    return;

  asset = &sOpeningScreenAssets[screenIndex];
  LZ77UnCompWram(asset->tiles, gBgVram.cbb0);
  CpuFill16(0, gPaletteBuffer, OPENING_SCREEN_PALETTE_BYTES);
  CpuCopy16(asset->palette, gPaletteBuffer, OPENING_SCREEN_PALETTE_BYTES);
  OpeningScreens_BuildTilemap();
  LoadVRAM();
  LoadPalettes();
}

static bool8 OpeningScreens_FadeOut(void) {
  g201EE60 = 0;
  while (g201EE61) {
    if (OpeningScreens_AnyButtonPressed())
      return TRUE;
    if (++g201EE60 > OPENING_SCREEN_FADE_STEP_FRAMES) {
      if (g201EE61 != 0)
        g201EE61--;
      g201EE60 = 0;
    }
    REG_BLDY = g201EE61;
    if (OpeningScreens_WaitForVBlankOrSkip())
      return TRUE;
  }
  return FALSE;
}

static bool8 OpeningScreens_FadeIn(void) {
  g201EE61 = 0;
  g201EE60 = 0;
  while (g201EE61 < 16) {
    if (OpeningScreens_AnyButtonPressed())
      return TRUE;
    if (++g201EE60 > OPENING_SCREEN_FADE_STEP_FRAMES) {
      if (g201EE61 < 16)
        g201EE61++;
      g201EE60 = 0;
    }
    REG_BLDY = g201EE61;
    if (OpeningScreens_WaitForVBlankOrSkip())
      return TRUE;
  }
  return FALSE;
}

static bool8 OpeningScreens_Hold(void) {
  u16 i;

  for (i = 0; i < OPENING_SCREEN_HOLD_FRAMES; i++) {
    if (OpeningScreens_WaitForVBlankOrSkip())
      return TRUE;
  }
  return FALSE;
}

static bool8 OpeningScreens_ShowScreen(u8 screenIndex) {
  OpeningScreens_LoadScreenGfx(screenIndex);
  SetVBlankCallback(OpeningScreens_VBlankShowScreen);
  REG_BLDCNT = 0x3FFF;
  WaitForVBlank();

  if (screenIndex != 0) {
    g201EE61 = 16;
    g201EE60 = 0;
    REG_BLDY = g201EE61;
    if (OpeningScreens_FadeOut())
      return TRUE;
  } else {
    g201EE61 = 0;
    g201EE60 = 0;
    REG_BLDY = 0;
  }

  if (OpeningScreens_Hold())
    return TRUE;
  if (OpeningScreens_FadeIn())
    return TRUE;

  return FALSE;
}

static void CustomOpeningScreensMain(void) {
  u8 i;

  OpeningScreens_VBlankInit();
  SetVBlankCallback(OpeningScreens_VBlankInit);
  WaitForVBlank();

  for (i = 0; i < OPENING_SCREEN_COUNT; i++) {
    if (OpeningScreens_ShowScreen(i))
      break;
  }

  REG_BLDCNT = 0x3FFF;
  g201EE61 = 16;
  g201EE60 = 0;
  REG_BLDY = g201EE61;
}

LYN_REPLACE_CHECK(CopyrightScreensMain);
APPEND_TEXT void CopyrightScreensMain__Replacement(void) {
  if (gRuntimeConfig.enable_custom_opening_screens != TRUE) {
    VanillaCopyrightScreensMain();
    return;
  }

  CustomOpeningScreensMain();
  REG_DISPCNT = 0;
}
