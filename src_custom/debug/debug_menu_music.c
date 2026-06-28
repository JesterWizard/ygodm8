#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "constants/custom_music_generated.h"
#include "debug_menu_internal.h"

#define DEBUG_MENU_MUSIC_ENTRY(id, title) {id, title},

static const struct DebugMenuMusicEntry sTracks[] APPEND_RODATA = {
#include "debug_menu_music_table.inc"
#if CUSTOM_MUSIC_SONG_COUNT > 0
#include "../generated/debug_menu_music_custom.inc"
#endif
};

#undef DEBUG_MENU_MUSIC_ENTRY

static void DebugMenuFormatTrack(u8 *out, const struct DebugMenuMusicEntry *e, bool8 playing) {
  DebugMenuFormatListRow(out, e->title, playing);
}

void DebugMenuDrawMusic(u8 scrollTop, u16 playingId) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sTracks)) {
      DebugMenuFormatTrack(buf, &sTracks[index], playingId == sTracks[index].musicId);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugMusicViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u16 playingId = 0;
  const u16 n = ARRAY_COUNT(sTracks);

  DebugMenuRedraw(0, 0, DEBUG_VIEW_MUSIC);
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
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_MUSIC);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_MUSIC);
    }
    if (buttons & A_BUTTON) {
      u16 musicId;

      PlayMusic(SFX_SELECT);
      musicId = sTracks[cursor].musicId;
      playingId = musicId;
      if (musicId >= CUSTOM_MUSIC_SONG_ID_MIN && musicId <= CUSTOM_MUSIC_SONG_ID_MAX)
        PlayCustomMusicById(musicId);
      else
        PlayMusic(musicId);
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_MUSIC);
      DebugMenuWaitRelease(A_BUTTON);
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
