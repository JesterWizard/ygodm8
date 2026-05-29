#ifndef GUARD_DEBUG_MENU_INTERNAL_H
#define GUARD_DEBUG_MENU_INTERNAL_H

#include "global.h"

#define DEBUG_ROWS 3
#define DEBUG_CHARS 16
#define DEBUG_TEXT_BLOCKS ((DEBUG_CHARS + 1) / 2)
#define DEBUG_TEXT_TILE 0x81
#define DEBUG_TEXT_OFFSET (DEBUG_TEXT_TILE * 32)
#define DEBUG_TEXT_STRIDE (DEBUG_TEXT_BLOCKS * 4 * 32)
#define DEBUG_LINE0_TILE DEBUG_TEXT_TILE
#define DEBUG_LINE_STRIDE (DEBUG_TEXT_STRIDE / 32)
#define DEBUG_ROOT_ITEMS 3
#define DEBUG_WIN0H 0x20D8
#define DEBUG_BG1_ROWS 20
#define DEBUG_BG1_ROW_BYTES 60
#define DEBUG_BG1_VRAM ((void *)0x0600E800)
#define THUMB_VBLANK_WIN 0x08005C38
#define THUMB_VBLANK_NOWIN 0x08005C54

#define DEBUG_VIEW_ROOT 0
#define DEBUG_VIEW_MUSIC 1
#define DEBUG_VIEW_PORTRAIT 2
#define DEBUG_VIEW_SPRITE 3

struct DebugMenuMusicEntry {
  u16 musicId;
  u8 title[24];
};

struct DebugMenuPortraitEntry {
  u8 portraitId;
  u8 title[24];
};

struct DebugMenuSpriteEntry {
  s16 spriteId;
  u8 title[24];
};

void DebugMenuRedraw(u8 scrollTop, u16 marker, u8 view);
void DebugMenuLoadGraphics(void);
void DebugMenuWaitVBlank(void);
void DebugMenuVBlankNoWin(void);
void DebugMenuLatchButtons(void);
void DebugMenuWaitRelease(u16 mask);
u16 DebugMenuButtons(void);
void DebugMenuUpdateCursor(u8 screenRow);
void DebugMenuUpdateCursorSlot(u8 oamSlot, u8 screenRow);
void DebugMenuFormatListRow(u8 *out, const u8 *title, bool8 selected);
void DebugMenuFormatTitleRow(u8 *out, const u8 *title);
void DebugMenuCopyLine(u8 row, const u8 *text);
void DebugMenuSetLinePalette(u8 row, u8 paletteNum);

extern const u8 gDebugMenuBlankLine[];

void DebugMenuDrawMusic(u8 scrollTop, u16 playingId);
void DebugMenuDrawPortraits(u8 scrollTop, u8 cursor);
void DebugMenuDrawSprites(u8 scrollTop, u8 cursor);

void DebugMusicViewer(void);
void DebugPortraitViewer(void);
void DebugSpriteViewer(void);

#endif // GUARD_DEBUG_MENU_INTERNAL_H
