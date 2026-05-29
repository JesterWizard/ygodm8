#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"

#define DEBUG_ROWS 3
#define DEBUG_CHARS 16
#define DEBUG_TEXT_BLOCKS ((DEBUG_CHARS + 1) / 2)
#define DEBUG_TEXT_TILE 0x81
#define DEBUG_TEXT_OFFSET (DEBUG_TEXT_TILE * 32)
// Two 0x901 glyphs share a 2x2 tile block.
#define DEBUG_TEXT_STRIDE (DEBUG_TEXT_BLOCKS * 4 * 32)
#define DEBUG_LINE0_TILE DEBUG_TEXT_TILE
#define DEBUG_LINE_STRIDE (DEBUG_TEXT_STRIDE / 32)
#define DEBUG_ROOT_ITEMS 2
#define DEBUG_WIN0H 0x20D8
#define DEBUG_BG1_ROWS 20
#define DEBUG_BG1_ROW_BYTES 60
#define DEBUG_BG1_VRAM ((void *)0x0600E800)
#define THUMB_VBLANK_WIN 0x08005C38
#define THUMB_VBLANK_NOWIN 0x08005C54

struct DebugMenuMusicEntry {
  u16 musicId;
  u8 title[24];
};

#define DEBUG_MENU_MUSIC_ENTRY(id, title) {id, title},

static const struct DebugMenuMusicEntry sTracks[] APPEND_RODATA = {
#include "debug_menu_music_table.inc"
};

#undef DEBUG_MENU_MUSIC_ENTRY

static const u8 sText_Root[] APPEND_RODATA = "$0Music Viewer  ";
static const u8 sText_Blank[] APPEND_RODATA = "$0Coming Soon   ";
static const u8 sText_Clear[] APPEND_RODATA = "$0              ";

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

static void DebugMenuApplyBg2(void) {
  gBG2HOFS = 0xFFB0 + 28;
  gBG2VOFS = 0xFFC8;
  LoadBgOffsets();
}

static void DebugMenuVBlank(void) {
  ((void (*)(void))(THUMB_VBLANK_WIN | 1))();
  DebugMenuApplyBg2();
  REG_WIN0H = DEBUG_WIN0H;
}

static void DebugMenuVBlankNoWin(void) {
  ((void (*)(void))(THUMB_VBLANK_NOWIN | 1))();
  DebugMenuApplyBg2();
}

static void DebugMenuWaitVBlank(void) {
  SetVBlankCallback(DebugMenuVBlank);
  WaitForVBlank();
}

static void DebugMenuSetupTextRows(void) {
  u8 line, block;

  for (line = 0; line < DEBUG_ROWS; line++) {
    u16 base = DEBUG_LINE0_TILE + line * DEBUG_LINE_STRIDE;
    u8 row = line * 2;

    for (block = 0; block < DEBUG_TEXT_BLOCKS; block++) {
      u8 col = block * 2;
      u16 tile = base + block * 4;

      gBgVram.sbb1F[row][col] = 0xF000 | ((tile + 0) & 0x3FF);
      gBgVram.sbb1F[row][col + 1] = 0xF000 | ((tile + 1) & 0x3FF);
      gBgVram.sbb1F[row + 1][col] = 0xF000 | ((tile + 2) & 0x3FF);
      gBgVram.sbb1F[row + 1][col + 1] = 0xF000 | ((tile + 3) & 0x3FF);
    }
  }
}

static void DebugMenuLoadTilemaps(void) {
  u8 i;

  LZ77UnCompWram(gStartMenuCursorTiles, gBgVram.cbb4);
  for (i = 0; i < DEBUG_BG1_ROWS; i++) {
    DmaCopy16(3, gUnk_80798F4[i], gBgVram.sbb1F[i], DEBUG_BG1_ROW_BYTES);
    DmaCopy16(3, gUnk_8079CB4[i], gBgVram.sbb1D[i], DEBUG_BG1_ROW_BYTES);
    DmaCopy16(3, gUnk_807A164[i], gBgVram.sbb1C[i], DEBUG_BG1_ROW_BYTES);
  }
  DebugMenuSetupTextRows();
  CpuCopy16(gStartMenuBgPalette, gPaletteBuffer, 32);
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256, 32);
}

static void DebugMenuUpload(void) {
  LoadCharblock2();
  LoadCharblock3();
  LoadCharblock4();
  LoadPalettes();
  CpuCopy32(gBgVram.sbb1D, DEBUG_BG1_VRAM, DEBUG_BG1_ROWS * DEBUG_BG1_ROW_BYTES);
}

static u16 DebugMenuReadGlyphArg(const u8 **textPtr) {
  const u8 *text = *textPtr;
  u16 glyph;

  if (*text == '\0' || *text == '$') {
    glyph = gUnk_8E00E30[0][0] << 8 | gUnk_8E00E30[0][1];
  } else if (*text <= 127) {
    glyph = gUnk_8E00E30[*text - 32][0] << 8 | gUnk_8E00E30[*text - 32][1];
    text++;
  } else {
    glyph = text[0] << 8 | text[1];
    text += 2;
  }

  *textPtr = text;
  return (glyph >> 8) | (glyph << 8);
}

static void DebugMenuCopyLine(u8 row, const u8 *text) {
  u8 i;
  u8 *dest = (u8 *)gBgVram.sbb18 + DEBUG_TEXT_OFFSET + row * DEBUG_TEXT_STRIDE;

  text = GetCurrentLanguageString(text);
  for (i = 0; i < DEBUG_CHARS; i++)
    sub_8020968(dest + (i / 2 * 4 + (i & 1)) * 32, DebugMenuReadGlyphArg(&text), 0x901);
}

static void DebugMenuFormatTrack(u8 *out, const struct DebugMenuMusicEntry *e, bool8 playing) {
  u8 i, t = 0;

  out[0] = '$';
  out[1] = '0';
  out[2] = playing ? '>' : ' ';
  for (i = 1; i < DEBUG_CHARS; i++)
    out[2 + i] = e->title[t] ? e->title[t++] : ' ';
  out[2 + DEBUG_CHARS] = '\0';
}

static void DebugMenuDrawMusic(u8 scrollTop, u16 playingId) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sTracks)) {
      DebugMenuFormatTrack(buf, &sTracks[index], playingId == sTracks[index].musicId);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, sText_Blank);
    }
  }
}

static void DebugMenuRedraw(u8 scrollTop, u16 playingId, bool8 music) {
  DebugMenuLoadTilemaps();
  if (music)
    DebugMenuDrawMusic(scrollTop, playingId);
  else {
    DebugMenuCopyLine(0, sText_Root);
    DebugMenuCopyLine(1, sText_Blank);
    DebugMenuCopyLine(2, sText_Clear);
  }
  DebugMenuUpload();
}

static void DebugMenuLoadGraphics(void) {
  u8 i;

  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  LoadVRAM();
  DisableDisplay();
  LZ77UnCompWram(gStartMenuBgTiles, gBgVram.cbb0);
  for (i = 0; i < DEBUG_BG1_ROWS; i++)
    DmaCopy16(3, gUnk_8079444[i], gBgVram.sbb1E[i], DEBUG_BG1_ROW_BYTES);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xF0], 32);
  DebugMenuRedraw(0, 0, FALSE);
  SetVBlankCallback(DebugMenuVBlank);
  LoadBgVRAM();
  DebugMenuUpload();
  DebugMenuVBlank();
  REG_WIN0H = DEBUG_WIN0H;
  DebugMenuWaitVBlank();
}

static void DebugMenuUpdateCursor(u8 screenRow) {
  u32 *oam = (u32 *)&gOamBuffer;

  oam[0] = (screenRow << 4) + 56 | ((u32)(0x4040 - 28) << 16);
  oam[1] = 0x800;
}

static void DebugMenuLatchButtons(void) {
  gPressedButtons = ~REG_KEYINPUT;
  gNewButtons = 0;
  gRepeatedOrNewButtons = 0;
  gRepeatedButtonsCounter = 10;
}

static void DebugMenuWaitRelease(u16 mask) {
  SetVBlankCallback(DebugMenuVBlank);
  while (gPressedButtons & mask)
    DebugMenuWaitVBlank();
  DebugMenuLatchButtons();
  gInputRepeatTimer = 0;
}

static u16 DebugMenuButtons(void) {
  return gNewButtons | (gRepeatedOrNewButtons & (DPAD_UP | DPAD_DOWN | DPAD_LEFT | DPAD_RIGHT));
}

static void DebugMusicViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u16 playingId = 0;
  const u16 n = ARRAY_COUNT(sTracks);

  DebugMenuRedraw(0, 0, TRUE);
  DebugMenuUpdateCursor(0);
  LoadOam();
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, playingId, TRUE);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, playingId, TRUE);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      playingId = sTracks[cursor].musicId;
      PlayMusic(playingId);
      DebugMenuRedraw(scrollTop, playingId, TRUE);
      DebugMenuWaitRelease(A_BUTTON);
    }

    DebugMenuUpdateCursor(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  PlayMusic(SFX_CANCEL);
  DebugMenuWaitRelease(B_BUTTON);
  SetVBlankCallback(DebugMenuVBlankNoWin);
  DebugMenuRedraw(0, 0, FALSE);
  DebugMenuVBlankNoWin();
  REG_WIN0H = DEBUG_WIN0H;
  SetVBlankCallback(DebugMenuVBlank);
  DebugMenuWaitVBlank();
}

static void DebugMenuRoot(void) {
  u8 cursor = 0;

  DebugMenuLatchButtons();
  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor--;
    }
    if (buttons & DPAD_DOWN && cursor < DEBUG_ROOT_ITEMS - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor++;
    }
    if (buttons & A_BUTTON) {
      if (cursor == 0) {
        PlayMusic(SFX_SELECT);
        DebugMenuWaitRelease(A_BUTTON);
        DebugMenuLatchButtons();
        DebugMusicViewer();
        DebugMenuLatchButtons();
      } else {
        PlayMusic(SFX_FORBIDDEN);
        DebugMenuWaitRelease(A_BUTTON);
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
  DebugMenuLatchButtons();
  PlayMusic(MUSIC_DECK_ADJUSTMENT_MENU);
  DebugMenuRoot();
  PlayMusic(SFX_CANCEL);
  DebugMenuWaitRelease(B_BUTTON);
  FadeOutMusic(1);
  DisableDisplay();
}
