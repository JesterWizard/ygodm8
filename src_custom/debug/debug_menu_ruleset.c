#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "debug_ruleset.h"

static const u8 sText_Default[] APPEND_RODATA = "Default";
static const u8 sText_DuelistKingdom[] APPEND_RODATA = "Duelist Kingdom";

static void DebugMenuFormatRulesetRow(u8 *out, const u8 *title, bool8 selected) {
  DebugMenuFormatListRow(out, title, selected);
}

void DebugMenuDrawRuleset(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  (void)scrollTop;
  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    if (row == 0) {
      DebugMenuFormatRulesetRow(buf, sText_Default,
                                gDebugRuleset == DEBUG_RULESET_DEFAULT);
      DebugMenuCopyLine(row, buf);
    } else if (row == 1) {
      DebugMenuFormatRulesetRow(buf, sText_DuelistKingdom,
                                gDebugRuleset == DEBUG_RULESET_DUELIST_KINGDOM);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugRulesetViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 totalRows = 2;

  DebugMenuRedraw(0, 0, DEBUG_VIEW_RULESET);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_RULESET);
    }
    if (buttons & DPAD_DOWN && cursor < totalRows - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_RULESET);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      DebugRuleset_SetMode(cursor == 0 ? DEBUG_RULESET_DEFAULT : DEBUG_RULESET_DUELIST_KINGDOM);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_RULESET);
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
