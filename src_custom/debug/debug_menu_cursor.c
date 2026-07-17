#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "menu_cursor.h"

static const u8 sText_Eye[] APPEND_RODATA = "Eye";
static const u8 sText_Kuriboh[] APPEND_RODATA = "Kuriboh";
static const u8 sText_Puzzle[] APPEND_RODATA = "Puzzle";

static void DebugMenuFormatCursorRow(u8 *out, const u8 *title, bool8 selected) {
  DebugMenuFormatListRow(out, title, selected);
}

static void DebugMenuReloadSelectedCursorGfx(void) {
  MenuCursor_LoadTiles(gBgVram.cbb4);
  MenuCursor_LoadPalette(gPaletteBuffer + 256 + DEBUG_MENU_CURSOR_PAL_SLOT * 16);
  CpuCopy32(gBgVram.cbb4, (void *)0x06010000,
            (32 + 2) * 32); /* tiles 0..33 span for 2D 16x16 */
  LoadPalettes();
}

void DebugMenuDrawCursor(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];
  u8 selected = MenuCursor_GetId();

  (void)scrollTop;
  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    if (row == 0) {
      DebugMenuFormatCursorRow(buf, sText_Eye, selected == MENU_CURSOR_EYE);
      DebugMenuCopyLine(row, buf);
    } else if (row == 1) {
      DebugMenuFormatCursorRow(buf, sText_Kuriboh, selected == MENU_CURSOR_KURIBOH);
      DebugMenuCopyLine(row, buf);
    } else if (row == 2) {
      DebugMenuFormatCursorRow(buf, sText_Puzzle, selected == MENU_CURSOR_PUZZLE);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugCursorViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 totalRows = MENU_CURSOR_COUNT;

  DebugMenuRedraw(0, 0, DEBUG_VIEW_CURSOR);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_CURSOR);
    }
    if (buttons & DPAD_DOWN && cursor < totalRows - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_CURSOR);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      MenuCursor_SetId(cursor);
      DebugMenuReloadSelectedCursorGfx();
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_CURSOR);
      DebugMenuWaitRelease(A_BUTTON);
    }

    DebugMenuUpdateCursor(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  DebugMenuWaitRelease(B_BUTTON);
  DebugMenuVBlankNoWin();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  DebugMenuVBlankNoWin();
  DebugMenuWaitVBlank();
}
