#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"

#define DEBUG_MENU_VISIBLE_ROWS 3
#define DEBUG_MENU_TEXT_TILE_OFFSET 0x5020
#define DEBUG_MENU_TEXT_TILE_STRIDE 0x280
/* 0x901 font uses two tilemap columns per character (vanilla start menu fits 10 in cols 1-20). */
#define DEBUG_MENU_LINE_CHARS 14
#define DEBUG_MENU_TEXT_COL_START 1
#define DEBUG_MENU_CHAR_TILE_STRIDE 4
#define DEBUG_MENU_LINE0_TILE 0x42
#define DEBUG_MENU_LINE_TILE_STRIDE 0x280
/* left=0x20, right=0xD8 -> 184px window (vanilla start menu is 0x38-0xB8 = 128px). */
#define DEBUG_MENU_WIN0H 0x20D8
/* BG2 scroll tweak (added to vanilla start-menu BG2 offsets each VBlank). */
#define DEBUG_MENU_BG2_HOFS_VANILLA 0xFFB0
#define DEBUG_MENU_BG2_VOFS_VANILLA 0xFFC8
#define DEBUG_MENU_BG2_HOFS 28
#define DEBUG_MENU_BG2_VOFS 0
/* OAM cursor: x lives in attr1 (high halfword of oam[0]); oam[1] is tile/priority. */
#define DEBUG_MENU_CURSOR_Y_BASE 56
#define DEBUG_MENU_CURSOR_ATTR1 0x4040 /* x=64 + start-menu size bits */
#define DEBUG_MENU_CURSOR_OAM1 0x800
#define DEBUG_MENU_BG1_TILEMAP_ROWS 20
#define DEBUG_MENU_BG1_TILEMAP_ROW_BYTES 60

#define THUMB_SUB_8005C38 0x08005C38
#define THUMB_SUB_8005C54 0x08005C54

#define DEBUG_MENU_BG1_TILEMAP_VRAM ((void *)0x0600E800)

struct DebugMenuMusicEntry {
  u16 musicId;
  u8 title[24];
};

#define DEBUG_MENU_MUSIC_ENTRY(id, title) {id, title},

static const struct DebugMenuMusicEntry sDebugMenuMusicTracks[] APPEND_RODATA = {
#include "debug_menu_music_table.inc"
};

#undef DEBUG_MENU_MUSIC_ENTRY

enum {
  DEBUG_ROOT_MUSIC_VIEWER = 0,
  DEBUG_ROOT_PLACEHOLDER_1,
  DEBUG_ROOT_PLACEHOLDER_2,
  DEBUG_ROOT_ITEM_COUNT = 3,
};

static const u8 sText_DebugMusicViewer[] APPEND_RODATA = "$0Music Viewer        ";
static const u8 sText_DebugComingSoon1[] APPEND_RODATA = "$0Coming soon 1       ";
static const u8 sText_DebugComingSoon2[] APPEND_RODATA = "$0Coming soon 2       ";

static const u8 *const sDebugRootLabels[DEBUG_ROOT_ITEM_COUNT] APPEND_RODATA = {
  sText_DebugMusicViewer,
  sText_DebugComingSoon1,
  sText_DebugComingSoon2,
};

extern u8 gStartMenuBgTiles[];
extern u8 gStartMenuCursorTiles[];
extern u16 gStartMenuBgPalette[];
extern u16 gStartMenuCursorPalette[];
extern u16 gUnk_8079424[];
extern u16 gUnk_8079444[][30];
extern u16 gUnk_80798F4[][30];
extern u16 gUnk_8079CB4[][30];
extern u16 gUnk_807A164[][30];
extern u16 gOamBuffer[];
extern u16 gNewButtons;
extern u16 gPressedButtons;
extern u16 gRepeatedOrNewButtons;
extern vu8 gRepeatedButtonsCounter;

extern u8 gInputRepeatTimer;

void ClearGraphicsBuffers(void);
void InitButtonMaps(void);

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

static void DebugMenuApplyBg2Offsets(void) {
  gBG2HOFS = DEBUG_MENU_BG2_HOFS_VANILLA + DEBUG_MENU_BG2_HOFS;
  gBG2VOFS = DEBUG_MENU_BG2_VOFS_VANILLA + DEBUG_MENU_BG2_VOFS;
  LoadBgOffsets();
}

static void DebugMenuVBlankCb(void) {
  CallThumbVoid(THUMB_SUB_8005C38);
  DebugMenuApplyBg2Offsets();
  REG_WIN0H = DEBUG_MENU_WIN0H;
}

static void DebugMenuVBlankCbNoWin(void) {
  CallThumbVoid(THUMB_SUB_8005C54);
  DebugMenuApplyBg2Offsets();
}

static void DebugMenuWaitVBlank(void) {
  SetVBlankCallback(DebugMenuVBlankCb);
  WaitForVBlank();
  SetVBlankCallback(DebugMenuVBlankCb);
}

static void DebugMenuSetupTextRowPair(u8 rowTop, u16 lineTileBase) {
  u8 charIndex;

  for (charIndex = 0; charIndex < DEBUG_MENU_LINE_CHARS; charIndex++) {
    u8 col = DEBUG_MENU_TEXT_COL_START + charIndex * 2;
    u16 tile = lineTileBase + charIndex * DEBUG_MENU_CHAR_TILE_STRIDE;

    gBgVram.sbb1D[rowTop][col] = 0xF000 | ((tile + 0) & 0x3FF);
    gBgVram.sbb1D[rowTop][col + 1] = 0xF000 | ((tile + 1) & 0x3FF);
    gBgVram.sbb1D[rowTop + 1][col] = 0xF000 | ((tile + 2) & 0x3FF);
    gBgVram.sbb1D[rowTop + 1][col + 1] = 0xF000 | ((tile + 3) & 0x3FF);
  }
}

static void DebugMenuSetupTextTilemap(void) {
  u8 line;

  for (line = 0; line < DEBUG_MENU_VISIBLE_ROWS; line++) {
    u16 lineTileBase = DEBUG_MENU_LINE0_TILE + line * DEBUG_MENU_LINE_TILE_STRIDE;

    DebugMenuSetupTextRowPair(10 + line * 2, lineTileBase);
  }
}

static void DebugMenuLoadMenuTilemaps(void) {
  u8 i;

  LZ77UnCompWram(gStartMenuCursorTiles, gBgVram.cbb4);
  for (i = 0; i < DEBUG_MENU_BG1_TILEMAP_ROWS; i++) {
    DmaCopy16(3, gUnk_80798F4[i], gBgVram.sbb1F[i], DEBUG_MENU_BG1_TILEMAP_ROW_BYTES);
    DmaCopy16(3, gUnk_8079CB4[i], gBgVram.sbb1D[i], DEBUG_MENU_BG1_TILEMAP_ROW_BYTES);
    DmaCopy16(3, gUnk_807A164[i], gBgVram.sbb1C[i], DEBUG_MENU_BG1_TILEMAP_ROW_BYTES);
  }
  DebugMenuSetupTextTilemap();
  CpuCopy16(gStartMenuBgPalette, gPaletteBuffer, 32);
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256, 32);
}

static void DebugMenuSyncBg1Tilemap(void) {
  CpuCopy32(gBgVram.sbb1D, DEBUG_MENU_BG1_TILEMAP_VRAM,
            DEBUG_MENU_BG1_TILEMAP_ROWS * DEBUG_MENU_BG1_TILEMAP_ROW_BYTES);
}

/* Match start-menu text upload: charblocks 2-4 plus BG1 tilemap sync. */
static void DebugMenuUploadScreen(void) {
  LoadCharblock2();
  LoadCharblock3();
  LoadCharblock4();
  LoadPalettes();
  DebugMenuSyncBg1Tilemap();
}

static void DebugMenuCopyLineToSlot(u8 screenRow, const u8 *text) {
  u32 tileOffset = DEBUG_MENU_TEXT_TILE_OFFSET + screenRow * DEBUG_MENU_TEXT_TILE_STRIDE;

  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[tileOffset], text, 0x901);
}

static void DebugMenuFormatTrackLabel(u8 *out, const struct DebugMenuMusicEntry *entry, bool8 isPlaying) {
  u8 i;
  u8 titleIndex;

  out[0] = '$';
  out[1] = '0';
  titleIndex = 0;
  for (i = 0; i < DEBUG_MENU_LINE_CHARS; i++) {
    if (i == 0)
      out[2 + i] = isPlaying ? '>' : ' ';
    else if (entry->title[titleIndex] != '\0') {
      out[2 + i] = entry->title[titleIndex];
      titleIndex++;
    } else {
      out[2 + i] = ' ';
    }
  }
  out[2 + DEBUG_MENU_LINE_CHARS] = '\0';
}

static void DebugMenuDrawRootLabels(void) {
  u8 i;

  for (i = 0; i < DEBUG_ROOT_ITEM_COUNT; i++)
    DebugMenuCopyLineToSlot(i, sDebugRootLabels[i]);
}

static void DebugMenuDrawMusicScreen(u8 scrollTop, u16 playingId) {
  u8 screenRow;
  u8 lineBuf[2 + DEBUG_MENU_LINE_CHARS + 1];

  for (screenRow = 0; screenRow < DEBUG_MENU_VISIBLE_ROWS; screenRow++) {
    u8 index = scrollTop + screenRow;

    if (index < ARRAY_COUNT(sDebugMenuMusicTracks)) {
      const struct DebugMenuMusicEntry *entry = &sDebugMenuMusicTracks[index];
      bool8 isPlaying = (playingId == entry->musicId);

      DebugMenuFormatTrackLabel(lineBuf, entry, isPlaying);
      DebugMenuCopyLineToSlot(screenRow, lineBuf);
    } else {
      u8 i;

      lineBuf[0] = '$';
      lineBuf[1] = '0';
      for (i = 0; i < DEBUG_MENU_LINE_CHARS; i++)
        lineBuf[2 + i] = ' ';
      lineBuf[2 + DEBUG_MENU_LINE_CHARS] = '\0';
      DebugMenuCopyLineToSlot(screenRow, lineBuf);
    }
  }
}

static void DebugMenuShowRootScreen(void) {
  DebugMenuLoadMenuTilemaps();
  DebugMenuDrawRootLabels();
  DebugMenuUploadScreen();
}

static void DebugMenuShowMusicScreen(u8 scrollTop, u16 playingId) {
  DebugMenuLoadMenuTilemaps();
  DebugMenuDrawMusicScreen(scrollTop, playingId);
  DebugMenuUploadScreen();
}

static void DebugMenuLoadGraphics(void) {
  u8 i;

  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  LoadVRAM();
  DisableDisplay();
  LZ77UnCompWram(gStartMenuBgTiles, gBgVram.cbb0);
  for (i = 0; i < DEBUG_MENU_BG1_TILEMAP_ROWS; i++)
    DmaCopy16(3, gUnk_8079444[i], gBgVram.sbb1E[i], DEBUG_MENU_BG1_TILEMAP_ROW_BYTES);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xF0], 32);
  DebugMenuShowRootScreen();
  SetVBlankCallback(DebugMenuVBlankCb);
  LoadBgVRAM();
  DebugMenuUploadScreen();
  DebugMenuVBlankCb();
  REG_WIN0H = DEBUG_MENU_WIN0H;
  DebugMenuWaitVBlank();
}

static void DebugMenuRefreshFromSubmenu(void) {
  CpuCopy16(gStartMenuBgPalette, gPaletteBuffer, 32);
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256, 32);
  DebugMenuShowRootScreen();
  SetVBlankCallback(DebugMenuVBlankCbNoWin);
  DebugMenuVBlankCbNoWin();
  REG_WIN0H = DEBUG_MENU_WIN0H;
  SetVBlankCallback(DebugMenuVBlankCb);
  DebugMenuWaitVBlank();
}

static void DebugMenuUpdateCursor(u8 screenRow) {
  u32 *oam = (u32 *)&gOamBuffer;
  u16 attr1 = DEBUG_MENU_CURSOR_ATTR1 - DEBUG_MENU_BG2_HOFS;

  oam[0] = (screenRow << 4) + DEBUG_MENU_CURSOR_Y_BASE + DEBUG_MENU_BG2_VOFS | ((u32)attr1 << 16);
  oam[1] = DEBUG_MENU_CURSOR_OAM1;
}

static void DebugMenuLatchButtonState(void) {
  u16 currentInputs = ~REG_KEYINPUT;

  gPressedButtons = currentInputs;
  gNewButtons = 0;
  gRepeatedOrNewButtons = 0;
  gRepeatedButtonsCounter = 10;
}

static void DebugMenuWaitForButtonsRelease(u16 mask) {
  SetVBlankCallback(DebugMenuVBlankCb);

  while (gPressedButtons & mask)
    DebugMenuWaitVBlank();

  DebugMenuLatchButtonState();
  gInputRepeatTimer = 0;
}

static u16 DebugMenuReadMenuButtons(void) {
  u16 buttons = gNewButtons;

  buttons |= gRepeatedOrNewButtons & (DPAD_UP | DPAD_DOWN | DPAD_LEFT | DPAD_RIGHT);
  return buttons;
}

static void DebugMusicViewerMain(void) {
  u8 cursor = 0;
  u8 scrollTop = 0;
  u16 playingId = 0;
  const u16 trackCount = ARRAY_COUNT(sDebugMenuMusicTracks);

  DebugMenuShowMusicScreen(scrollTop, playingId);
  DebugMenuUpdateCursor(0);
  LoadOam();
  DebugMenuWaitVBlank();
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuReadMenuButtons();

    if (buttons & B_BUTTON)
      break;

    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor--;
      if (cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuShowMusicScreen(scrollTop, playingId);
    }
    if (buttons & DPAD_DOWN && cursor < trackCount - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor++;
      if (cursor >= scrollTop + DEBUG_MENU_VISIBLE_ROWS)
        scrollTop = cursor - (DEBUG_MENU_VISIBLE_ROWS - 1);
      DebugMenuShowMusicScreen(scrollTop, playingId);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      playingId = sDebugMenuMusicTracks[cursor].musicId;
      PlayMusic(playingId);
      DebugMenuShowMusicScreen(scrollTop, playingId);
      DebugMenuWaitForButtonsRelease(A_BUTTON);
    }

    DebugMenuUpdateCursor(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  PlayMusic(SFX_CANCEL);
  DebugMenuWaitForButtonsRelease(B_BUTTON);
  DebugMenuRefreshFromSubmenu();
}

static void DebugMenuRootMain(void) {
  u8 cursor = 0;

  DebugMenuLatchButtonState();

  while (1) {
    u16 buttons = DebugMenuReadMenuButtons();

    if (buttons & B_BUTTON)
      break;

    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor--;
    }
    if (buttons & DPAD_DOWN && cursor < DEBUG_ROOT_ITEM_COUNT - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor++;
    }
    if (buttons & A_BUTTON) {
      switch (cursor) {
        case DEBUG_ROOT_MUSIC_VIEWER:
          PlayMusic(SFX_SELECT);
          DebugMenuWaitForButtonsRelease(A_BUTTON);
          DebugMenuLatchButtonState();
          DebugMusicViewerMain();
          DebugMenuLatchButtonState();
          break;
        default:
          PlayMusic(SFX_FORBIDDEN);
          DebugMenuWaitForButtonsRelease(A_BUTTON);
          break;
      }
    }

    DebugMenuUpdateCursor(cursor);
    LoadOam();
    DebugMenuWaitVBlank();
  }
}

void DebugMenuMain(void) {
  InitButtonMaps();
  FadeOutMusic(1);
  DebugMenuLoadGraphics();
  DebugMenuLatchButtonState();
  PlayMusic(MUSIC_DECK_ADJUSTMENT_MENU);
  DebugMenuRootMain();
  PlayMusic(SFX_CANCEL);
  DebugMenuWaitForButtonsRelease(B_BUTTON);
  FadeOutMusic(1);
  DisableDisplay();
}
