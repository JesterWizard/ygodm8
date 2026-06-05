#ifndef GUARD_DEBUG_MENU_INTERNAL_H
#define GUARD_DEBUG_MENU_INTERNAL_H

#include "global.h"

#define DEBUG_ROWS 5
#define DEBUG_CHARS 16
#define DEBUG_BG2_SCROLL_TILES_VANILLA (-7)
#define DEBUG_BG2_TEXT_NUDGE_TILES 1
#define DEBUG_BG2_SCROLL_TILES \
  (DEBUG_BG2_SCROLL_TILES_VANILLA + DEBUG_BG2_TEXT_NUDGE_TILES)
#define DEBUG_BG2VOFS_FROM_TILES(scrollTiles) ((u16)(s16)((scrollTiles) * 8))
#define DEBUG_BG2VOFS DEBUG_BG2VOFS_FROM_TILES(DEBUG_BG2_SCROLL_TILES)
#define DEBUG_CURSOR_Y_TILES (0 - DEBUG_BG2_SCROLL_TILES)
#define DEBUG_TEXT_BLOCKS ((DEBUG_CHARS + 1) / 2)
#define DEBUG_TEXT_TILE 0x81
#define DEBUG_TEXT_OFFSET (DEBUG_TEXT_TILE * 32)
#define DEBUG_TEXT_STRIDE (DEBUG_TEXT_BLOCKS * 4 * 32)
#define DEBUG_LINE0_TILE DEBUG_TEXT_TILE
#define DEBUG_LINE_STRIDE (DEBUG_TEXT_STRIDE / 32)
#define DEBUG_ROOT_ITEMS 12
#define DEBUG_WIN0H 0x20D8
#define DEBUG_BG1_ROWS 20
#define DEBUG_BG1_ROW_BYTES 60
#define DEBUG_BG1_VRAM ((void *)0x0600E800)
#define DEBUG_BG2_VRAM ((void *)BG_SCREEN_ADDR(31))
#define THUMB_VBLANK_WIN 0x08005C38
#define THUMB_VBLANK_NOWIN 0x08005C54

#define DEBUG_VIEW_ROOT 0
#define DEBUG_VIEW_MUSIC 1
#define DEBUG_VIEW_PORTRAIT 2
#define DEBUG_VIEW_SPRITE 3
#define DEBUG_VIEW_REACTION 4
#define DEBUG_VIEW_VOICE 5
#define DEBUG_VIEW_MATCH_SETTER 6
#define DEBUG_VIEW_AI_MODE 7
#define DEBUG_VIEW_GRAPHIC 8
#define DEBUG_VIEW_MAP 9
#define DEBUG_VIEW_SCENE 10
#define DEBUG_VIEW_DECK_PRESET 11
#define DEBUG_VIEW_RULESET 12

struct DebugMenuDeckEntry {
  const u16 *cards;
  u8 title[24];
};

#define DEBUG_SPRITE_OAM_SLOT_CURSOR 0
#define DEBUG_SPRITE_OAM_SLOT 1
#define DEBUG_SPRITE_FRAME_DOWN_IDLE 0
/* OBJ slot 0 is overwritten by entity palettes; keep the eye cursor on slot 15. */
#define DEBUG_MENU_CURSOR_PAL_SLOT 15

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

void DebugMenuRedraw(u8 scrollTop, u16 marker, u8 view);
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

#define DEBUG_MENU_TEXT_PAL 15

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
void DebugMenuDrawScenes(u8 scrollTop, u16 confirmedIndex);
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
