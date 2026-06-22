#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "overworld.h"

#define DEBUG_PORTRAIT_TILE_BYTES 0x1000
#define DEBUG_PORTRAIT_PAL_BYTES 0x80
#define DEBUG_PORTRAIT_X_TILE 19
#define DEBUG_PORTRAIT_Y_TILE 6

#define DEBUG_MENU_PORTRAIT_ENTRY(id, title) {id, title},

static const struct DebugMenuPortraitEntry sPortraits[] APPEND_RODATA = {
#include "debug_menu_portrait_table.inc"
};

#undef DEBUG_MENU_PORTRAIT_ENTRY

extern u16 gOamBuffer[];

void DebugMenuClearPortraitObjStash(void) {
  CpuFill16(0, gBgVram.cbb4 + 0x2000, DEBUG_PORTRAIT_TILE_BYTES);
  CpuFill16(0, (void *)(gPaletteBuffer + 256 + 0xC0), DEBUG_PORTRAIT_PAL_BYTES);
}

void DebugMenuLoadPortraitIfChanged(u8 *shownId, u8 portraitId) {
  if (portraitId == *shownId)
    return;
  *shownId = portraitId;
  CpuFill16(0, gBgVram.cbb4 + 0x2000, DEBUG_PORTRAIT_TILE_BYTES);
  LoadPortraitGfx(portraitId, EXPRESSION_NEUTRAL);
  LoadObjVRAM();
  LoadPalettes();
}

void DebugMenuApplyPortraitOam(void) {
  struct OamData *oam = (struct OamData *)gOamBuffer;

  sub_804EB04(oam, PORTRAIT_POSITION_RIGHT);
  oam->x = DEBUG_PORTRAIT_X_TILE * 8;
  oam->y = DEBUG_PORTRAIT_Y_TILE * 8;
  oam->paletteNum = 12;
}

void DebugMenuHidePortrait(void) {
  sub_804EB04((struct OamData *)gOamBuffer, PORTRAIT_POSITION_OFF_SCREEN);
  LoadOam();
}

void DebugMenuDrawPortraits(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sPortraits)) {
      DebugMenuFormatTitleRow(buf, sPortraits[index].title);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugPortraitViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u8 shownPortraitId = 0xFF;
  const u16 n = ARRAY_COUNT(sPortraits);

  DebugMenuRedraw(0, 0, DEBUG_VIEW_PORTRAIT);
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
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_PORTRAIT);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_PORTRAIT);
    }

    DebugMenuLoadPortraitIfChanged(&shownPortraitId, sPortraits[cursor].portraitId);
    DebugMenuApplyPortraitOam();
    DebugMenuUpdateCursorSlot(1, cursor - scrollTop, DEBUG_MENU_CURSOR_PAL_SLOT);
    DebugMenuHighlightRow(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  PlayMusic(SFX_CANCEL);
  DebugMenuWaitRelease(B_BUTTON);
  DebugMenuHidePortrait();
  DebugMenuClearPortraitObjStash();
  DebugMenuVBlankNoWin();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  DebugMenuVBlankNoWin();
  REG_WIN0H = DEBUG_WIN0H;
  DebugMenuUpdateCursor(0);
  DebugMenuWaitVBlank();
}
