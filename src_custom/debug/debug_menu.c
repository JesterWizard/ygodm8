#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"

extern const u16 gOverworldEntityPalettes[];

void DebugMenuClearPortraitObjStash(void);
void DebugMenuClearSpriteObjStash(void);

static const u8 sText_RootMusic[] APPEND_RODATA = "$0Music Viewer  ";
static const u8 sText_RootPortrait[] APPEND_RODATA = "$0Portrait Viewer";
static const u8 sText_RootSprite[] APPEND_RODATA = "$0Sprite Viewer  ";
static const u8 sText_RootReaction[] APPEND_RODATA = "$0Reaction Viewer";
static const u8 *const sRootLabels[] APPEND_RODATA = {
    sText_RootMusic,
    sText_RootPortrait,
    sText_RootSprite,
    sText_RootReaction,
};
const u8 gDebugMenuBlankLine[] APPEND_RODATA = "$0              ";

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

void DebugMenuVBlankNoWin(void) {
  ((void (*)(void))(THUMB_VBLANK_NOWIN | 1))();
  DebugMenuApplyBg2();
}

void DebugMenuWaitVBlank(void) {
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

static void DebugMenuUploadBg(void) {
  LoadCharblock2();
  LoadCharblock3();
  LoadPalettes();
  CpuCopy32(gBgVram.sbb1D, DEBUG_BG1_VRAM, DEBUG_BG1_ROWS * DEBUG_BG1_ROW_BYTES);
}

static void DebugMenuUpload(void) {
  DebugMenuUploadBg();
  LoadCharblock4();
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

void DebugMenuCopyLine(u8 row, const u8 *text) {
  u8 i;
  u8 *dest = (u8 *)gBgVram.sbb18 + DEBUG_TEXT_OFFSET + row * DEBUG_TEXT_STRIDE;

  text = GetCurrentLanguageString(text);
  for (i = 0; i < DEBUG_CHARS; i++)
    sub_8020968(dest + (i / 2 * 4 + (i & 1)) * 32, DebugMenuReadGlyphArg(&text), 0x901);
}

void DebugMenuRestoreTextPalettes(void) {
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xF0], 32);
}

void DebugMenuSetLinePalette(u8 row, u8 paletteNum) {
  u8 block;
  u16 base = DEBUG_LINE0_TILE + row * DEBUG_LINE_STRIDE;
  u8 mapRow = row * 2;
  u16 palMask = (paletteNum & 0xF) << 12;

  for (block = 0; block < DEBUG_TEXT_BLOCKS; block++) {
    u8 col = block * 2;
    u16 tile = base + block * 4;

    gBgVram.sbb1F[mapRow][col] = palMask | ((tile + 0) & 0x3FF);
    gBgVram.sbb1F[mapRow][col + 1] = palMask | ((tile + 1) & 0x3FF);
    gBgVram.sbb1F[mapRow + 1][col] = palMask | ((tile + 2) & 0x3FF);
    gBgVram.sbb1F[mapRow + 1][col + 1] = palMask | ((tile + 3) & 0x3FF);
  }
}

void DebugMenuFormatListRow(u8 *out, const u8 *title, bool8 selected) {
  u8 i, t = 0;

  out[0] = '$';
  out[1] = '0';
  out[2] = selected ? '>' : ' ';
  for (i = 1; i < DEBUG_CHARS; i++)
    out[2 + i] = title[t] ? title[t++] : ' ';
  out[2 + DEBUG_CHARS] = '\0';
}

void DebugMenuFormatTitleRow(u8 *out, const u8 *title) {
  u8 i, t = 0;

  out[0] = '$';
  out[1] = '0';
  for (i = 0; i < DEBUG_CHARS; i++)
    out[2 + i] = title[t] ? title[t++] : ' ';
  out[2 + DEBUG_CHARS] = '\0';
}

void DebugMenuRedraw(u8 scrollTop, u16 marker, u8 view) {
  DebugMenuLoadTilemaps();
  switch (view) {
  case DEBUG_VIEW_MUSIC:
    DebugMenuDrawMusic(scrollTop, marker);
    break;
  case DEBUG_VIEW_PORTRAIT:
    DebugMenuDrawPortraits(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_SPRITE:
    DebugMenuDrawSprites(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_REACTION:
    DebugMenuDrawReactions(scrollTop, (u8)marker);
    break;
  default:
    DebugMenuDrawRoot(scrollTop, (u8)marker);
    break;
  }
  if (view == DEBUG_VIEW_PORTRAIT || view == DEBUG_VIEW_SPRITE ||
      view == DEBUG_VIEW_REACTION)
    DebugMenuUploadBg();
  else
    DebugMenuUpload();
}

void DebugMenuLoadGraphics(void) {
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
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  SetVBlankCallback(DebugMenuVBlank);
  LoadBgVRAM();
  DebugMenuUpload();
  DebugMenuVBlank();
  REG_WIN0H = DEBUG_WIN0H;
  DebugMenuWaitVBlank();
}

void DebugMenuLoadReactionObjPalettes(void) {
  CpuCopy16(gOverworldEntityPalettes, gPaletteBuffer + 256, 0x180);
  CpuCopy16(gStartMenuCursorPalette,
            gPaletteBuffer + 256 + DEBUG_MENU_CURSOR_PAL_SLOT * 16, 32);
  LoadPalettes();
}

void DebugMenuUpdateCursorSlot(u8 oamSlot, u8 screenRow, u8 paletteNum) {
  u32 *oam = (u32 *)&gOamBuffer[oamSlot * 4];

  oam[0] = (screenRow << 4) + 56 | ((u32)(0x4040 - 28) << 16);
  oam[1] = 0x800 | ((paletteNum & 0xF) << 12);
}

void DebugMenuUpdateCursor(u8 screenRow) {
  DebugMenuUpdateCursorSlot(0, screenRow, 0);
}

void DebugMenuLatchButtons(void) {
  gPressedButtons = ~REG_KEYINPUT;
  gNewButtons = 0;
  gRepeatedOrNewButtons = 0;
  gRepeatedButtonsCounter = 10;
}

void DebugMenuWaitRelease(u16 mask) {
  SetVBlankCallback(DebugMenuVBlank);
  while (gPressedButtons & mask)
    DebugMenuWaitVBlank();
  DebugMenuLatchButtons();
  gInputRepeatTimer = 0;
}

u16 DebugMenuButtons(void) {
  return gNewButtons | (gRepeatedOrNewButtons & (DPAD_UP | DPAD_DOWN | DPAD_LEFT | DPAD_RIGHT));
}

void DebugMenuDrawRoot(u8 scrollTop, u8 cursor) {
  u8 row;

  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < DEBUG_ROOT_ITEMS)
      DebugMenuCopyLine(row, sRootLabels[index]);
    else
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
  }
}

static void DebugMenuRoot(void) {
  u8 cursor = 0, scrollTop = 0;

  DebugMenuLatchButtons();
  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
    }
    if (buttons & DPAD_DOWN && cursor < DEBUG_ROOT_ITEMS - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      DebugMenuWaitRelease(A_BUTTON);
      DebugMenuLatchButtons();
      if (cursor == 0)
        DebugMusicViewer();
      else if (cursor == 1)
        DebugPortraitViewer();
      else if (cursor == 2)
        DebugSpriteViewer();
      else
        DebugReactionViewer();
      DebugMenuLatchButtons();
      scrollTop = 0;
      if (cursor >= DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
    }

    DebugMenuUpdateCursor(cursor - scrollTop);
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
  DebugMenuClearPortraitObjStash();
  DebugMenuClearSpriteObjStash();
  FadeOutMusic(1);
  DisableDisplay();
}
