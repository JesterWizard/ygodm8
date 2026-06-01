#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu_internal.h"
#include "overworld.h"

#define DEBUG_MENU_GRAPHIC_ENTRY(id, title) {id, title},

static const struct DebugMenuGraphicEntry sGraphics[] APPEND_RODATA = {
#include "debug_menu_graphic_table.inc"
};

#undef DEBUG_MENU_GRAPHIC_ENTRY

static void DebugMenuFormatGraphic(u8 *out, const struct DebugMenuGraphicEntry *e,
                                    bool8 playing) {
  DebugMenuFormatListRow(out, e->title, playing);
}

void DebugMenuDrawGraphics(u8 scrollTop, u16 playingId) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sGraphics)) {
      DebugMenuFormatGraphic(buf, &sGraphics[index], playingId == sGraphics[index].graphicId);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

static void DebugMenuPlayOverworldGraphic(u8 graphicId) {
  struct ScriptCtx script;

  script.unk86 = 0;
  DebugMenuVBlankNoWin();
  DisableDisplay();
  sub_8053404();
  OverworldSetRegDispcnt();
  sub_80512E0(&script, graphicId);
  DisableDisplay();
  DebugMenuLoadGraphics();
}

void DebugGraphicViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u16 playingId = 0xFF;
  const u16 n = ARRAY_COUNT(sGraphics);

  DebugMenuRedraw(0, playingId, DEBUG_VIEW_GRAPHIC);
  DebugMenuUpdateCursor(0);
  LoadOam();
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_GRAPHIC);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_GRAPHIC);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      playingId = sGraphics[cursor].graphicId;
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_GRAPHIC);
      DebugMenuWaitRelease(A_BUTTON);
      DebugMenuPlayOverworldGraphic((u8)playingId);
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_GRAPHIC);
      REG_WIN0H = DEBUG_WIN0H;
      DebugMenuUpdateCursor(cursor - scrollTop);
      LoadOam();
      DebugMenuWaitVBlank();
    }

    DebugMenuUpdateCursor(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }

  PlayMusic(SFX_CANCEL);
  DebugMenuWaitRelease(B_BUTTON);
  DebugMenuVBlankNoWin();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  DebugMenuVBlankNoWin();
  REG_WIN0H = DEBUG_WIN0H;
  DebugMenuWaitVBlank();
}
