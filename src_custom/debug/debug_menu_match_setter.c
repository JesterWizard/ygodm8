#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "match_setter.h"
#include "overworld.h"

static const u8 sText_None[] APPEND_RODATA = "(None)";

static void DebugMenuFormatMatchSetterRow(u8 *out, const u8 *title, bool8 selected) {
  DebugMenuFormatListRow(out, title, selected);
}

void DebugMenuDrawMatchSetters(u8 scrollTop, u8 cursor) {
  u8 row, buf[2 + DEBUG_CHARS + 1];
  u8 count = MatchSetter_GetEntryCount();
  u8 totalRows = count + 1;

  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index == 0) {
      DebugMenuFormatMatchSetterRow(buf, sText_None, gDebugMatchSetterSelection == DEBUG_MATCH_SETTER_NONE);
      DebugMenuCopyLine(row, buf);
    } else if (index - 1 < count) {
      const struct MatchSetterEntry *entry = MatchSetter_GetEntry(index - 1);

      DebugMenuFormatMatchSetterRow(buf, entry->title,
                                    gDebugMatchSetterSelection == index);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }

  (void)totalRows;
}

void DebugMatchSetterViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 count = MatchSetter_GetEntryCount();
  const u8 totalRows = count + 1;

  DebugMenuRedraw(0, 0, DEBUG_VIEW_MATCH_SETTER);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_MATCH_SETTER);
    }
    if (buttons & DPAD_DOWN && cursor < totalRows - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_MATCH_SETTER);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      if (cursor == 0)
        gDebugMatchSetterSelection = DEBUG_MATCH_SETTER_NONE;
      else
        gDebugMatchSetterSelection = cursor;
      MatchSetter_RefreshField();
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_MATCH_SETTER);
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
