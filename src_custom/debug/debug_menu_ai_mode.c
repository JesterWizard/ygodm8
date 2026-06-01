#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_ai_mode.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"

static const u8 sText_Off[] APPEND_RODATA = "Off";
static const u8 sText_BothSides[] APPEND_RODATA = "AI Both Sides";

static void DebugMenuFormatAiModeRow(u8 *out, const u8 *title, bool8 selected) {
  DebugMenuFormatListRow(out, title, selected);
}

void DebugMenuDrawAiMode(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  (void)scrollTop;
  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    if (row == 0) {
      DebugMenuFormatAiModeRow(buf, sText_Off,
                               gDebugAiBothSidesMode == DEBUG_AI_MODE_OFF);
      DebugMenuCopyLine(row, buf);
    } else if (row == 1) {
      DebugMenuFormatAiModeRow(buf, sText_BothSides,
                               gDebugAiBothSidesMode == DEBUG_AI_MODE_BOTH_SIDES);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugAiModeViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 totalRows = 2;

  DebugMenuRedraw(0, 0, DEBUG_VIEW_AI_MODE);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_AI_MODE);
    }
    if (buttons & DPAD_DOWN && cursor < totalRows - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_AI_MODE);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      DebugAiMode_SetMode(cursor == 0 ? DEBUG_AI_MODE_OFF : DEBUG_AI_MODE_BOTH_SIDES);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_AI_MODE);
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
