#include "global.h"
#include "configs/runtime.h"
#include "debug_menu_internal.h"
#include "menu_cursor.h"
#include "text.h"

/* ponytail: start-menu BG path from dc805e25 (f687d912^), before debug black BG. */

extern u8 gStartMenuBgTiles[];
extern u16 gStartMenuBgPalette[];
extern u16 gUnk_8079424[];
extern u16 gUnk_8079444[][30];
extern u16 gUnk_80798F4[][30];
extern u16 gUnk_8079CB4[][30];
extern u16 gUnk_807A164[][30];
extern const u8 *gUnk_8E00E30[];

extern u16 gOamBuffer[];

const u8 gDebugMenuStartMenuBlankLine[] APPEND_RODATA = "$0              ";

void ClearGraphicsBuffers(void);
void LoadBgVRAM(void);
void LoadCharblock2(void);
void LoadCharblock3(void);
void LoadCharblock4(void);
void LoadPalettes(void);
void LoadBgOffsets(void);
void LoadOam(void);
void LoadVRAM(void);
void DisableDisplay(void);
void SetVBlankCallback(void (*)(void));

static void DebugMenuApplyStartMenuBg2(void) {
  gBG2HOFS = 0xFFB0 + 28;
  gBG2VOFS = DEBUG_SM_BG2VOFS;
  LoadBgOffsets();
}

static void DebugMenuStartMenuVBlank(void) {
  ((void (*)(void))(DEBUG_SM_THUMB_VBLANK_WIN | 1))();
  DebugMenuApplyStartMenuBg2();
  REG_WIN0H = DEBUG_SM_WIN0H;
}

static void DebugMenuSetupStartMenuTextRows(void) {
  u8 line, block;

  for (line = 0; line < DEBUG_SM_ROWS; line++) {
    u16 base = DEBUG_SM_LINE0_TILE + line * DEBUG_SM_LINE_STRIDE;
    u8 row = line * 2;

    for (block = 0; block < DEBUG_SM_TEXT_BLOCKS; block++) {
      u8 col = block * 2;
      u16 tile = base + block * 4;

      gBgVram.sbb1F[row][col] = 0xF000 | ((tile + 0) & 0x3FF);
      gBgVram.sbb1F[row][col + 1] = 0xF000 | ((tile + 1) & 0x3FF);
      gBgVram.sbb1F[row + 1][col] = 0xF000 | ((tile + 2) & 0x3FF);
      gBgVram.sbb1F[row + 1][col + 1] = 0xF000 | ((tile + 3) & 0x3FF);
    }
  }
}

static void DebugMenuLoadStartMenuTilemaps(void) {
  u8 i;

  MenuCursor_LoadTiles(gBgVram.cbb4);
  for (i = 0; i < DEBUG_SM_BG1_ROWS; i++) {
    DmaCopy16(3, gUnk_80798F4[i], gBgVram.sbb1F[i], DEBUG_SM_ROW_BYTES);
    DmaCopy16(3, gUnk_8079CB4[i], gBgVram.sbb1D[i], DEBUG_SM_ROW_BYTES);
    DmaCopy16(3, gUnk_807A164[i], gBgVram.sbb1C[i], DEBUG_SM_ROW_BYTES);
  }
  DebugMenuSetupStartMenuTextRows();
  CpuCopy16(gStartMenuBgPalette, gPaletteBuffer, 32);
  MenuCursor_LoadPalette(gPaletteBuffer + 256);
}

static void DebugMenuUploadStartMenuBg(void) {
  LoadCharblock2();
  LoadCharblock3();
  LoadPalettes();
  CpuCopy32(gBgVram.sbb1D, DEBUG_SM_BG1_VRAM, DEBUG_SM_BG1_ROWS * DEBUG_SM_ROW_BYTES);
  CpuCopy32(gBgVram.sbb1F, DEBUG_SM_BG2_VRAM, DEBUG_SM_BG1_ROWS * DEBUG_SM_ROW_BYTES);
}

static void DebugMenuUploadStartMenu(void) {
  DebugMenuUploadStartMenuBg();
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

void DebugMenuCopyLineStartMenu(u8 row, const u8 *text) {
  u8 i;
  u8 *dest = (u8 *)gBgVram.sbb18 + DEBUG_SM_TEXT_OFFSET + row * DEBUG_SM_TEXT_STRIDE;

  text = GetCurrentLanguageString(text);
  for (i = 0; i < DEBUG_SM_CHARS; i++)
    sub_8020968(dest + (i / 2 * 4 + (i & 1)) * 32, DebugMenuReadGlyphArg(&text), 0x901);
}

void DebugMenuSetLinePaletteStartMenu(u8 row, u8 paletteNum) {
  u8 block;
  u16 base = DEBUG_SM_LINE0_TILE + row * DEBUG_SM_LINE_STRIDE;
  u8 mapRow = row * 2;
  u16 palMask = (paletteNum & 0xF) << 12;

  for (block = 0; block < DEBUG_SM_TEXT_BLOCKS; block++) {
    u8 col = block * 2;
    u16 tile = base + block * 4;

    gBgVram.sbb1F[mapRow][col] = palMask | ((tile + 0) & 0x3FF);
    gBgVram.sbb1F[mapRow][col + 1] = palMask | ((tile + 1) & 0x3FF);
    gBgVram.sbb1F[mapRow + 1][col] = palMask | ((tile + 2) & 0x3FF);
    gBgVram.sbb1F[mapRow + 1][col + 1] = palMask | ((tile + 3) & 0x3FF);
  }
}

void DebugMenuUploadStartMenuText(void) {
  LoadCharblock3();
  CpuCopy32(gBgVram.sbb1F, DEBUG_SM_BG2_VRAM, DEBUG_SM_BG1_ROWS * DEBUG_SM_ROW_BYTES);
}

void DebugMenuUpdateCursorStartMenu(u8 screenRow) {
  u32 *oam = (u32 *)&gOamBuffer[0];

  oam[0] = (screenRow << 4) + DEBUG_SM_CURSOR_Y | ((u32)(0x4040 - 28) << 16);
  oam[1] = 0x800;
}

void DebugMenuLoadStartMenuGraphics(void) {
  u8 i;

  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  LoadVRAM();
  DisableDisplay();
  LZ77UnCompWram(gStartMenuBgTiles, gBgVram.cbb0);
  for (i = 0; i < DEBUG_SM_BG1_ROWS; i++)
    DmaCopy16(3, gUnk_8079444[i], gBgVram.sbb1E[i], DEBUG_SM_ROW_BYTES);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xF0], 32);
  DebugMenuLoadStartMenuTilemaps();
  SetVBlankCallback(DebugMenuStartMenuVBlank);
  LoadBgVRAM();
  DebugMenuUploadStartMenu();
  DebugMenuStartMenuVBlank();
  REG_WIN0H = DEBUG_SM_WIN0H;
  SetVBlankCallback(DebugMenuStartMenuVBlank);
  WaitForVBlank();
}
