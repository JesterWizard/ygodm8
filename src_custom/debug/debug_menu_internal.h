#ifndef GUARD_DEBUG_MENU_INTERNAL_H
#define GUARD_DEBUG_MENU_INTERNAL_H

#include "global.h"

/* ========== Root menu ========== */

#define DEBUG_ROWS 15
#define DEBUG_CHARS 8
#define DEBUG_ROOT_ITEMS 13

/* ========== BG1 sidebar overlay ========== */

/* BG1 is unused on the overworld; we use it as a sidebar overlay.
 * cbb1 holds sidebar art tiles (1-200) + text glyph tiles (200+).
 * sbb18 is the BG1 tilemap (sidebar art only).
 * sbb19 is the BG0 tilemap (text only). */
#define DEBUG_BG1_CBB 1
#define DEBUG_BG1_SBB 18
#define DEBUG_BG0_SBB 19

#define DEBUG_SIDEBAR_COLS 10        /* 80 px = 10 tiles */
#define DEBUG_SIDEBAR_COL_START 2    /* screen column 1 (leaves col 0 blank for 16px offset) */
#define DEBUG_SIDEBAR_TILES 200      /* 10*20 tiles */
#define DEBUG_SIDEBAR_PAL_BANK 14

/* Text glyph tiles stored in cbb1 after sidebar art.
 * 5 rows x 10 chars = 50 tiles at tile index 200+. */
#define DEBUG_BG1_TEXT_TILE_BASE 200
#define DEBUG_BG1_TEXT_ROW       3
#define DEBUG_BG1_TEXT_PAL_BANK  15

/* Cursor positioned over the text rows. */
#define DEBUG_CURSOR_Y_TILES 3
#define DEBUG_CURSOR_X        0
#define DEBUG_CURSOR_SIZE     1    /* square 16x16 (matches start menu OAM) */
#define DEBUG_MENU_CURSOR_PAL_SLOT 15

/* Text palette bank used by sub-viewers (reaction viewer, ante viewer). */
#define DEBUG_MENU_TEXT_PAL DEBUG_BG1_TEXT_PAL_BANK

/* Window 0 clips BG1 to columns 0-9.
 * REG_WIN0H = (X2 << 8) | X1  (pixel coordinates)
 * X1=0, X2=80 → 80px = 10 tiles */
#define DEBUG_WIN0H ((88 << 8) | 0)
#define DEBUG_WIN0V ((160 << 8) | 0)

/* Overworld VBlank (sub_804F1E4) — keeps overworld rendering. */
#define THUMB_VBLANK_OVERWORLD 0x0804F1E4

/* ========== OAM slot allocation ========== */

#define DEBUG_SPRITE_OAM_SLOT_CURSOR 0
#define DEBUG_SPRITE_OAM_SLOT 1
#define DEBUG_SPRITE_FRAME_DOWN_IDLE 0
/* OBJ slot 0 is overwritten by entity palettes; keep the eye cursor on slot 15. */
#define DEBUG_MENU_CURSOR_PAL_SLOT 15

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

/* ========== Function declarations ========== */

void DebugMenuRedraw(u16 scrollTop, u16 marker, u8 view);
void DebugMenuLoadGraphics(void);
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

extern const u8 gDebugMenuBlankLine[];

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

#endif // GUARD_DEBUG_MENU_INTERNAL_H
