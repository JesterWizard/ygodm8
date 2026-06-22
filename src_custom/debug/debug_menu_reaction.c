#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu_internal.h"
#include "overworld.h"

#define DEBUG_REACTION_TILE_OFFSET 0x4200
#define DEBUG_REACTION_TILE_NUM (DEBUG_REACTION_TILE_OFFSET / 32)
#define DEBUG_REACTION_X_TILE 25
#define DEBUG_REACTION_Y_TILE 7
#define DEBUG_REACTION_OAM_SLOT 2

#define DEBUG_MENU_REACTION_ENTRY(id, title) {id, title},

static const struct DebugMenuReactionEntry sReactions[] APPEND_RODATA = {
#include "debug_menu_reaction_table.inc"
};

#undef DEBUG_MENU_REACTION_ENTRY

extern const struct {
  int a;
  int b;
} g8105114[][27];
extern u16 g81032A2[];
extern const u8 g82AD2B6[];
extern u16 gOamBuffer[];

void sub_80411EC(struct OamData *oam);

static void DebugMenuLoadReactionGfx(u8 bubbleId) {
  u32 i, j;
  u8 *dest = gBgVram.cbb4 + DEBUG_REACTION_TILE_OFFSET;
  const u8 *src = &ReactionBubbleTiles[g81032A2[bubbleId] * 32];

  CpuFill16(0, dest, 0x800);
  for (i = 0; i < 2; dest += 0x3C0, src += 0x1C0, i++)
    for (j = 0; j < 64; j++)
      *dest++ = *src++;
  LoadObjVRAM();
}

static void DebugMenuHideReactionOam(void) {
  sub_80411EC((struct OamData *)&gOamBuffer[DEBUG_REACTION_OAM_SLOT * 4]);
}

static void DebugMenuApplyReactionOam(u8 bubbleId) {
  struct OamData *oam = (struct OamData *)&gOamBuffer[DEBUG_REACTION_OAM_SLOT * 4];

  if (bubbleId == 0) {
    DebugMenuHideReactionOam();
    return;
  }

  oam->y = DEBUG_REACTION_Y_TILE * 8;
  oam->x = DEBUG_REACTION_X_TILE * 8;
  oam->affineMode = 0;
  oam->objMode = 0;
  oam->mosaic = 0;
  oam->bpp = 0;
  oam->shape = 0;
  oam->size = 1;
  oam->tileNum = DEBUG_REACTION_TILE_NUM;
  oam->priority = 1;
  oam->paletteNum = g82AD2B6[bubbleId];
  oam->hflip = 0;
  oam->vflip = 0;
}

static void DebugMenuClearReactionStash(void) {
  CpuFill16(0, gBgVram.cbb4 + DEBUG_REACTION_TILE_OFFSET, 0x800);
}

static void DebugMenuReactionAnimReset(u8 reactionId, u8 *animFrame, u8 *holdTimer,
                                       u8 *bubbleId) {
  (void)reactionId;
  *animFrame = 0;
  *holdTimer = 0;
  *bubbleId = 0xFF;
}

static u8 DebugMenuReactionAnimStep(u8 listIndex, u8 *animFrame, u8 *holdTimer,
                                    u8 *shownBubbleId) {
  u8 reactionId;
  u8 bubbleId;
  int hold;

  if (listIndex >= ARRAY_COUNT(sReactions))
    return 0;

  reactionId = sReactions[listIndex].reactionId;

  if (*holdTimer != 0) {
    (*holdTimer)--;
    return (u8)g8105114[reactionId][*animFrame].a;
  }

  if (*shownBubbleId != 0xFF) {
    (*animFrame)++;
    if (g8105114[reactionId][*animFrame].a == -1)
      *animFrame = 0;
  }

  bubbleId = (u8)g8105114[reactionId][*animFrame].a;
  hold = g8105114[reactionId][*animFrame].b;
  if (bubbleId != *shownBubbleId) {
    *shownBubbleId = bubbleId;
    if (bubbleId != 0)
      DebugMenuLoadReactionGfx(bubbleId);
  }
  *holdTimer = hold != 0 ? (u8)hold : 1;
  (*holdTimer)--;
  return bubbleId;
}

void DebugMenuDrawReactions(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sReactions)) {
      DebugMenuFormatTitleRow(buf, sReactions[index].title);
      DebugMenuCopyLine(row, buf);
      DebugMenuSetLinePalette(row, DEBUG_MENU_TEXT_PAL);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
      DebugMenuSetLinePalette(row, DEBUG_MENU_TEXT_PAL);
    }
  }
  DebugMenuRestoreTextPalettes();
  DebugMenuLoadReactionObjPalettes();
}

void DebugReactionViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u8 animFrame = 0, holdTimer = 0, shownBubbleId = 0xFF;
  s16 shownSpriteId = -2;
  u8 shownSpriteFrame = 0xFF;
  const u16 n = ARRAY_COUNT(sReactions);

  DebugMenuReactionAnimReset(sReactions[cursor].reactionId, &animFrame, &holdTimer,
                             &shownBubbleId);
  DebugMenuRedraw(0, 0, DEBUG_VIEW_REACTION);
  DebugMenuHighlightRow(0);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();
    u8 bubbleId;

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      shownSpriteId = -2;
      shownSpriteFrame = 0xFF;
      DebugMenuReactionAnimReset(sReactions[cursor].reactionId, &animFrame, &holdTimer,
                                 &shownBubbleId);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_REACTION);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      shownSpriteId = -2;
      shownSpriteFrame = 0xFF;
      DebugMenuReactionAnimReset(sReactions[cursor].reactionId, &animFrame, &holdTimer,
                                 &shownBubbleId);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_REACTION);
    }

    bubbleId = DebugMenuReactionAnimStep(cursor, &animFrame, &holdTimer, &shownBubbleId);
    DebugMenuLoadReactionObjPalettes();
    DebugMenuLoadSpriteFrameIfChanged(&shownSpriteId, &shownSpriteFrame, SPRITE_PLAYER,
                                      DEBUG_SPRITE_FRAME_DOWN_IDLE, FALSE);
    DebugMenuApplySpriteOam();
    DebugMenuApplyReactionOam(bubbleId);
    DebugMenuUpdateCursorSlot(DEBUG_SPRITE_OAM_SLOT_CURSOR, cursor - scrollTop,
                              DEBUG_MENU_CURSOR_PAL_SLOT);
    DebugMenuHighlightRow(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  PlayMusic(SFX_CANCEL);
  DebugMenuWaitRelease(B_BUTTON);
  DebugMenuHideReactionOam();
  DebugMenuHideSprite();
  DebugMenuClearReactionStash();
  DebugMenuClearSpriteObjStash();
  DebugMenuVBlankNoWin();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  DebugMenuVBlankNoWin();
  REG_WIN0H = DEBUG_WIN0H;
  DebugMenuUpdateCursor(0);
  DebugMenuWaitVBlank();
}
