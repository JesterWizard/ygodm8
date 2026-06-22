#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu_internal.h"
#include "overworld.h"

#define DEBUG_SPRITE_TILE_BYTES 0xE00
#define DEBUG_SPRITE_TILE_OFFSET 0x3400
#define DEBUG_SPRITE_TILE_NUM (DEBUG_SPRITE_TILE_OFFSET / 32)
#define DEBUG_SPRITE_PAL_BYTES 0x20
#define DEBUG_SPRITE_PAL_SLOT 13
#define DEBUG_SPRITE_PAL_OFFSET (DEBUG_SPRITE_PAL_SLOT * 16)
#define DEBUG_SPRITE_X_TILE 22
#define DEBUG_SPRITE_Y_TILE 8
#define DEBUG_MENU_SPRITE_ENTRY(id, title) {id, title},

static const struct DebugMenuSpriteEntry sSprites[] APPEND_RODATA = {
#include "debug_menu_sprite_table.inc"
};

#undef DEBUG_MENU_SPRITE_ENTRY

extern const u8 g82AD20C[];
extern const u16 gOverworldEntityPalettes[];
extern u16 gOamBuffer[];

void sub_80411EC(struct OamData *oam);

void DebugMenuClearSpriteObjStash(void) {
  CpuFill16(0, gBgVram.cbb4 + DEBUG_SPRITE_TILE_OFFSET, DEBUG_SPRITE_TILE_BYTES);
  CpuFill16(0, (void *)(gPaletteBuffer + 256 + DEBUG_SPRITE_PAL_OFFSET),
            DEBUG_SPRITE_PAL_BYTES);
}

void DebugMenuLoadSpriteFrameIfChanged(s16 *shownSpriteId, u8 *shownFrame, s16 spriteId,
                                       u8 frameIndex, bool8 force) {
  u8 palIndex;

  if (!force && spriteId == *shownSpriteId && frameIndex == *shownFrame)
    return;
  *shownSpriteId = spriteId;
  *shownFrame = frameIndex;
  CpuFill16(0, gBgVram.cbb4 + DEBUG_SPRITE_TILE_OFFSET, DEBUG_SPRITE_TILE_BYTES);
  if (spriteId < 0)
    return;
  sub_804F054(spriteId, frameIndex, gBgVram.cbb4 + DEBUG_SPRITE_TILE_OFFSET);
  palIndex = g82AD20C[spriteId];
  CpuCopy16(gOverworldEntityPalettes + palIndex * 16,
            (void *)(gPaletteBuffer + 256 + DEBUG_SPRITE_PAL_OFFSET),
            DEBUG_SPRITE_PAL_BYTES);
  LoadObjVRAM();
  LoadPalettes();
}

static void DebugMenuLoadSpriteIfChanged(s16 *shownId, s16 spriteId, bool8 force) {
  u8 frame = DEBUG_SPRITE_FRAME_DOWN_IDLE;

  DebugMenuLoadSpriteFrameIfChanged(shownId, &frame, spriteId, frame, force);
}

void DebugMenuApplySpriteOam(void) {
  struct OamData *oam = (struct OamData *)&gOamBuffer[DEBUG_SPRITE_OAM_SLOT * 4];

  oam->y = DEBUG_SPRITE_Y_TILE * 8;
  oam->x = DEBUG_SPRITE_X_TILE * 8;
  oam->affineMode = 0;
  oam->objMode = 0;
  oam->mosaic = 0;
  oam->bpp = 0;
  oam->shape = 0;
  oam->size = 2;
  oam->tileNum = DEBUG_SPRITE_TILE_NUM;
  oam->priority = 2;
  oam->paletteNum = DEBUG_SPRITE_PAL_SLOT;
  oam->hflip = 0;
  oam->vflip = 0;
}

void DebugMenuHideSprite(void) {
  sub_80411EC((struct OamData *)&gOamBuffer[DEBUG_SPRITE_OAM_SLOT * 4]);
  LoadOam();
}

void DebugMenuDrawSprites(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sSprites)) {
      DebugMenuFormatTitleRow(buf, sSprites[index].title);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugSpriteViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  s16 shownSpriteId = -2;
  const u16 n = ARRAY_COUNT(sSprites);

  DebugMenuRedraw(0, 0, DEBUG_VIEW_SPRITE);
  DebugMenuHighlightRow(0);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      shownSpriteId = -2;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_SPRITE);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      shownSpriteId = -2;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_SPRITE);
    }

    DebugMenuLoadSpriteIfChanged(&shownSpriteId, sSprites[cursor].spriteId, FALSE);
    DebugMenuApplySpriteOam();
    DebugMenuUpdateCursorSlot(DEBUG_SPRITE_OAM_SLOT_CURSOR, cursor - scrollTop, DEBUG_MENU_CURSOR_PAL_SLOT);
    DebugMenuHighlightRow(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  PlayMusic(SFX_CANCEL);
  DebugMenuWaitRelease(B_BUTTON);
  DebugMenuHideSprite();
  DebugMenuClearSpriteObjStash();
  DebugMenuVBlankNoWin();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  DebugMenuVBlankNoWin();
  REG_WIN0H = DEBUG_WIN0H;
  DebugMenuUpdateCursor(0);
  DebugMenuWaitVBlank();
}
