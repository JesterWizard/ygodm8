#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "timed_duel.h"

static void DebugMenuFormatTimedDuelRow(u8 *out, u8 index, bool8 selected) {
  u8 title[16];

  (void)selected;
  TimedDuel_FormatMenuTitle(index, title);
  DebugMenuFormatListRow(out, title, selected);
}

void DebugMenuDrawTimedDuels(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];
  u8 count = TimedDuel_GetCount();

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < count) {
      DebugMenuFormatTimedDuelRow(buf, index, index == cursor);
      DebugMenuCopyLine(row, buf);
      if (TimedDuel_IsCompleted(index) == TRUE)
        DebugMenuSetLinePalette(row, DEBUG_MENU_HIGHLIGHT_PAL_BANK);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugTimedDuelViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 count = TimedDuel_GetCount();

  DebugMenuRedraw(0, 0, DEBUG_VIEW_TIMED_DUEL);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (count == 0) {
      DebugMenuUpdateCursor(0);
      LoadOam();
      DebugMenuWaitVBlank();
      continue;
    }
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_TIMED_DUEL);
    }
    if (buttons & DPAD_DOWN && cursor < count - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_TIMED_DUEL);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      if (TimedDuel_IsCompleted(cursor) != TRUE) {
        DebugMenuWaitRelease(A_BUTTON);
        DebugMenu_TeardownForDuel();
        TimedDuel_RunAtIndex(cursor);
        DebugMenu_ReinitAfterDuel();
        DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_TIMED_DUEL);
        DebugMenuUpdateCursor(cursor - scrollTop);
        LoadOam();
        DebugMenuWaitVBlank();
        continue;
      }
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
