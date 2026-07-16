#ifndef GUARD_DEBUG_MENU_INTERNAL_H
#define GUARD_DEBUG_MENU_INTERNAL_H

#include "global.h"

/* ========== Root menu ========== */

#define DEBUG_ROWS 15
#define DEBUG_CHARS 16
#define DEBUG_ROOT_ITEMS 16

/* ========== OBJ sidebar overlay ========== */

/* Sidebar art rendered as 50 16×16 OBJ sprites (5 cols × 10 rows).
 * Tile data in cbb4+cbb5 OBJ VRAM at 0x6011000 (2D grid row 4, tile 128).
 * Cursor eye at 0x6010000 (grid row 0, tile 0) — no overlap.
 * OBJ palette bank 12 is used (above entity palettes 0-11). */
#define DEBUG_SIDEBAR_OBJ_PAL_BANK  12
#define DEBUG_SIDEBAR_OBJ_PRIORITY  1     /* priority 1 → BG0 text (prio 0) renders on top */
#define DEBUG_SIDEBAR_SPRITE_SIZE   1     /* 16×16 square: attr1 bits14-15 = 1 (ST_OAM_SIZE_1) */
#define DEBUG_SIDEBAR_SPRITE_SHAPE  0     /* square: attr0 bits14-15 = 0 (ST_OAM_SQUARE) */
#define DEBUG_SIDEBAR_OAM_SLOT_BASE 16    /* 50 sprites: slots 16-65 */
#define DEBUG_SIDEBAR_COLS 10
#define DEBUG_SIDEBAR_ROWS 20
#define DEBUG_SIDEBAR_TILES 200
#define DEBUG_SIDEBAR_OBJ_TILE_BASE 384   /* grid row 12 = cbb4 + 0x3000 = 0x6013000 */
#define DEBUG_SIDEBAR_OBJ_TILE_STRIDE 32  /* 2D mapping stride */

/* Text rendered on BG0 using the overworld font palette (bank 0).
 * Text glyphs stored in cbb1 starting at tile 200+.
 * Text uses palette bank 0, slot 9 (font foreground). */
#define DEBUG_BG0_SBB 19
#define DEBUG_SIDEBAR_COL_START 2    /* text starts at tile column 2 (pixel 16) */
#define DEBUG_BG1_TEXT_TILE_BASE 200
#define DEBUG_BG1_TEXT_ROW       3
#define DEBUG_BG1_TEXT_PAL_BANK  0
#define DEBUG_BG1_TEXT_PAL_INDEX 9

/* Window 0 position (kept for sub-viewers). */
#define DEBUG_WIN0H ((88 << 8) | 0)
#define DEBUG_WIN0V ((160 << 8) | 0)

/* Overworld VBlank (sub_804F1E4). */
#define THUMB_VBLANK_OVERWORLD 0x0804F1E4

/* ========== OAM slot allocation ========== */

#define DEBUG_SPRITE_OAM_SLOT_CURSOR 0
#define DEBUG_SPRITE_OAM_SLOT 1
#define DEBUG_SPRITE_FRAME_DOWN_IDLE 0
#define DEBUG_MENU_CURSOR_PAL_SLOT 15

/* Cursor positioned over the text rows. */
#define DEBUG_CURSOR_Y_TILES 3
#define DEBUG_CURSOR_X        0
#define DEBUG_CURSOR_SIZE     1    /* square 16x16 */

/* Text palette bank used by sub-viewers. */
#define DEBUG_MENU_TEXT_PAL DEBUG_BG1_TEXT_PAL_BANK

/* Highlight bar replaces OBJ cursor — yellow text in BG palette bank 1. */
#define DEBUG_MENU_HIGHLIGHT_PAL_BANK 1

/* ========== View IDs ========== */

#define DEBUG_VIEW_ROOT 0
#define DEBUG_VIEW_MUSIC 1
#define DEBUG_VIEW_PORTRAIT 2
#define DEBUG_VIEW_SPRITE 3
#define DEBUG_VIEW_REACTION 4
#define DEBUG_VIEW_GRAPHIC 5
#define DEBUG_VIEW_VOICE 6
#define DEBUG_VIEW_MATCH_SETTER 7
#define DEBUG_VIEW_AI_MODE 8
#define DEBUG_VIEW_GRAPHIC2 9
#define DEBUG_VIEW_MAP 10
#define DEBUG_VIEW_SCENE 11
#define DEBUG_VIEW_DECK_PRESET 12
#define DEBUG_VIEW_RULESET 13
#define DEBUG_VIEW_TIMED_DUEL     14
#define DEBUG_VIEW_RUNTIME_CONFIG 15
#define DEBUG_VIEW_MECHANICS      16

/* ========== Data entry structs ========== */

struct DebugMenuDeckEntry {
  const u16 *cards;
  u8 title[24];
};

struct DebugMenuMusicEntry {
  u16 musicId;
  u8 title[24];
};

struct DebugMenuVoiceEntry {
  u16 soundId;
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

struct DebugMenuReactionEntry {
  u8 reactionId;
  u8 title[24];
};

struct DebugMenuGraphicEntry {
  u8 graphicId;
  u8 title[24];
};

struct DebugMenuMapEntry {
  u8 locationId;
  u8 title[48];
};

struct DebugMenuSceneEntry {
  u8 mapId;
  u8 state;
  u8 connection;
  u8 title[20];
};

/* ========== Start-menu graphics (ante card viewer; pre-black debug menu) ========== */

#define DEBUG_SM_ROWS 5
#define DEBUG_SM_CHARS 16
#define DEBUG_SM_TEXT_BLOCKS ((DEBUG_SM_CHARS + 1) / 2)
#define DEBUG_SM_TEXT_TILE 0x81
#define DEBUG_SM_TEXT_OFFSET (DEBUG_SM_TEXT_TILE * 32)
#define DEBUG_SM_TEXT_STRIDE (DEBUG_SM_TEXT_BLOCKS * 4 * 32)
#define DEBUG_SM_LINE0_TILE DEBUG_SM_TEXT_TILE
#define DEBUG_SM_LINE_STRIDE (DEBUG_SM_TEXT_STRIDE / 32)
#define DEBUG_SM_WIN0H 0x20D8
#define DEBUG_SM_BG2VOFS 0xFFD4   /* vanilla 0xFFD0 (−60), +12px lifts text rows */
#define DEBUG_SM_CURSOR_Y 40        /* vanilla 56; tracks BG2 scroll above */
#define DEBUG_SM_BG1_ROWS 20
#define DEBUG_SM_ROW_BYTES 60
#define DEBUG_SM_BG1_VRAM ((void *)0x0600E800)
#define DEBUG_SM_BG2_VRAM ((void *)BG_SCREEN_ADDR(31))
#define DEBUG_SM_THUMB_VBLANK_WIN 0x08005C38

/* ========== Function declarations ========== */

void DebugMenuRedraw(u16 scrollTop, u16 marker, u8 view);
void DebugMenuLoadGraphics(void);
void DebugMenuLoadCursorObjTiles(void);
void DebugMenuWaitVBlank(void);
void DebugMenuVBlankNoWin(void);
void DebugMenuLatchButtons(void);
void DebugMenuWaitRelease(u16 mask);
u16 DebugMenuButtons(void);
void DebugMenuUpdateCursor(u8 screenRow);
void DebugMenuUpdateCursorSlot(u8 oamSlot, u8 screenRow, u8 paletteNum);
void DebugMenuLoadReactionObjPalettes(void);
void DebugMenuFormatListRow(u8 *out, const u8 *title, bool8 selected);
void DebugMenuFormatTitleRow(u8 *out, const u8 *title);
void DebugMenuCopyLine(u8 row, const u8 *text);
void DebugMenuRestoreTextPalettes(void);
void DebugMenuSetLinePalette(u8 row, u8 paletteNum);
void DebugMenuHighlightRow(u8 row);

extern const u8 gDebugMenuBlankLine[];
extern const u8 gDebugMenuStartMenuBlankLine[];

void DebugMenuLoadStartMenuGraphics(void);
void DebugMenuCopyLineStartMenu(u8 row, const u8 *text);
void DebugMenuSetLinePaletteStartMenu(u8 row, u8 paletteNum);
void DebugMenuUploadStartMenuText(void);
void DebugMenuUpdateCursorStartMenu(u8 screenRow);

void DebugMenuLoadPortraitIfChanged(u8 *shownId, u8 portraitId);
void DebugMenuApplyPortraitOam(void);
void DebugMenuHidePortrait(void);

void DebugMenuDrawMusic(u8 scrollTop, u16 playingId);
void DebugMenuDrawVoices(u8 scrollTop, u16 playingId);
void DebugMenuDrawPortraits(u8 scrollTop, u8 cursor);
void DebugMenuDrawSprites(u8 scrollTop, u8 cursor);
void DebugMenuDrawRoot(u8 scrollTop, u8 cursor);
void DebugMenuDrawReactions(u8 scrollTop, u8 cursor);
void DebugMenuDrawMatchSetters(u8 scrollTop, u8 cursor);
void DebugMenuDrawGraphics(u8 scrollTop, u16 playingId);
void DebugMenuDrawMaps(u8 scrollTop, u8 confirmedLocationId);
void DebugMenuDrawScenes(u16 scrollTop, u16 confirmedIndex);
void DebugMenuDrawDecks(u8 scrollTop, u8 activePreset);

void DebugMenuLoadSpriteFrameIfChanged(s16 *shownSpriteId, u8 *shownFrame, s16 spriteId,
                                       u8 frameIndex, bool8 force);
void DebugMenuApplySpriteOam(void);
void DebugMenuHideSprite(void);
void DebugMenuClearSpriteObjStash(void);

void DebugMusicViewer(void);
void DebugVoiceViewer(void);
void DebugPortraitViewer(void);
void DebugSpriteViewer(void);
void DebugReactionViewer(void);
void DebugGraphicViewer(void);
void DebugMatchSetterViewer(void);
void DebugMenuDrawAiMode(u8 scrollTop, u8 cursor);
void DebugAiModeViewer(void);
void DebugMenuDrawRuleset(u8 scrollTop, u8 cursor);
void DebugRulesetViewer(void);
void DebugMapViewer(void);
void DebugSceneViewer(void);
void DebugDeckPresetViewer(void);
void DebugMenu_TeardownForDuel(void);
void DebugMenu_ReinitAfterDuel(void);
void DebugMenuDrawTimedDuels(u8 scrollTop, u8 cursor);
void DebugTimedDuelViewer(void);
void DebugMenuDrawRuntimeConfig(u8 scrollTop, u8 cursor);
void DebugRuntimeConfigViewer(void);
void DebugMenuDrawMechanics(u8 scrollTop, u8 cursor);
void DebugMechanicsViewer(void);

#endif // GUARD_DEBUG_MENU_INTERNAL_H
