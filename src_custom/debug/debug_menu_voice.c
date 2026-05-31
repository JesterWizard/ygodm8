#include "global.h"
#include "configs/runtime.h"
#include "constants/custom_voices_generated.h"
#include "debug_menu_internal.h"

#define DEBUG_MENU_VOICE_ENTRY(id, title) {id, title},

static const struct DebugMenuVoiceEntry sVoices[] APPEND_RODATA = {
#include "debug_menu_voice_table.inc"
#if CUSTOM_VOICE_SONG_COUNT > 0
#include "../generated/debug_menu_voice_custom.inc"
#endif
};

#undef DEBUG_MENU_VOICE_ENTRY

static void DebugMenuFormatVoice(u8 *out, const struct DebugMenuVoiceEntry *e, bool8 playing) {
  DebugMenuFormatListRow(out, e->title, playing);
}

void DebugMenuDrawVoices(u8 scrollTop, u16 playingId) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sVoices)) {
      DebugMenuFormatVoice(buf, &sVoices[index], playingId == sVoices[index].soundId);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugVoiceViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u16 playingId = 0;
  const u16 n = ARRAY_COUNT(sVoices);

  DebugMenuRedraw(0, 0, DEBUG_VIEW_VOICE);
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
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_VOICE);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_VOICE);
    }
    if (buttons & A_BUTTON) {
      u16 soundId;

      PlayMusic(SFX_SELECT);
      soundId = sVoices[cursor].soundId;
      playingId = soundId;
      if (soundId >= CUSTOM_VOICE_SONG_ID_MIN && soundId <= CUSTOM_VOICE_SONG_ID_MAX)
        PlayCustomVoiceClip((u8)(soundId - CUSTOM_VOICE_SONG_ID_MIN));
      else
        PlayMusic(soundId);
      DebugMenuRedraw(scrollTop, playingId, DEBUG_VIEW_VOICE);
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
