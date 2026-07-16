#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "mechanics_tutorial.h"

static void DebugMenuFormatMechanicsRow(u8 *out, u8 index, bool8 selected) {
  u8 title[16];

  (void)selected;
  MechanicsTutorial_FormatMenuTitle(index, title);
  DebugMenuFormatListRow(out, title, selected);
}

void DebugMenuDrawMechanics(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];
  u8 count = MechanicsTutorial_GetCount();

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < count) {
      DebugMenuFormatMechanicsRow(buf, index, index == cursor);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugMechanicsViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 count = MechanicsTutorial_GetCount();

  DebugMenuRedraw(0, 0, DEBUG_VIEW_MECHANICS);
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
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_MECHANICS);
    }
    if (buttons & DPAD_DOWN && cursor < count - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_MECHANICS);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      DebugMenuWaitRelease(A_BUTTON);
      DebugMenu_TeardownForDuel();
      MechanicsTutorial_RunAtIndex(cursor);
      DebugMenu_ReinitAfterDuel();
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_MECHANICS);
      DebugMenuUpdateCursor(cursor - scrollTop);
      LoadOam();
      DebugMenuWaitVBlank();
      continue;
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
