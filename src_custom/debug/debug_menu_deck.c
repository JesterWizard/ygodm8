#include "global.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "debug_deck_swap.h"
#include "debug_menu_internal.h"

const u16 sDirectDamage_Deck[] APPEND_RODATA = {
    LEOGUN, LEOGUN, LEOGUN, LEOGUN, LEOGUN, LEOGUN, LEOGUN, LEOGUN,
    UMI, UMI, UMI, UMI, UMI, UMI, UMI, UMI,
    THE_INEXPERIENCED_SPY, THE_INEXPERIENCED_SPY, THE_INEXPERIENCED_SPY, THE_INEXPERIENCED_SPY,
    THE_INEXPERIENCED_SPY, THE_INEXPERIENCED_SPY, THE_INEXPERIENCED_SPY, THE_INEXPERIENCED_SPY,
    MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN,
    BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON,
    BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON,
};

const u16 sRAPhoenixMode_Deck[] APPEND_RODATA = {
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE, 
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
    THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE,
};

#define DEBUG_MENU_DECK_ROW_ORIGINAL 0
#define DEBUG_MENU_DECK_ROW_DIRECT_DAMAGE 1
#define DEBUG_MENU_DECK_ROW_RA 2

#define DEBUG_MENU_DECK_RESTORE_ENTRY(title) {NULL, title},
#define DEBUG_MENU_DECK_ENTRY(deckSym, title) {deckSym, title},

static const struct DebugMenuDeckEntry sDecks[] APPEND_RODATA = {
#include "debug_menu_deck_table.inc"
};

#undef DEBUG_MENU_DECK_RESTORE_ENTRY
#undef DEBUG_MENU_DECK_ENTRY

static bool8 DebugMenuIsDeckRowActive(u8 index, u8 activePreset) {
  if (index == DEBUG_MENU_DECK_ROW_ORIGINAL)
    return activePreset == DEBUG_DECK_SWAP_INACTIVE;
  return activePreset == index;
}

static void DebugMenuFormatDeckRow(u8 *out, const struct DebugMenuDeckEntry *e, bool8 active) {
  DebugMenuFormatListRow(out, e->title, active);
}

void DebugMenuDrawDecks(u8 scrollTop, u8 activePreset) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sDecks)) {
      DebugMenuFormatDeckRow(buf, &sDecks[index], DebugMenuIsDeckRowActive(index, activePreset));
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugDeckPresetViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  const u8 n = ARRAY_COUNT(sDecks);
  DebugMenuRedraw(0, DebugDeckSwap_GetActivePreset(), DEBUG_VIEW_DECK_PRESET);
  DebugMenuWaitVBlank();

  while (1) {
    u16 buttons = DebugMenuButtons();
    u8 activePreset = DebugDeckSwap_GetActivePreset();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, activePreset, DEBUG_VIEW_DECK_PRESET);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, activePreset, DEBUG_VIEW_DECK_PRESET);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      if (cursor == DEBUG_MENU_DECK_ROW_ORIGINAL) {
        DebugDeckSwap_RestoreOriginal();
      } else if (cursor == DEBUG_MENU_DECK_ROW_DIRECT_DAMAGE) {
        DebugDeckSwap_ApplyPreset(cursor, sDirectDamage_Deck);
      } else if (cursor == DEBUG_MENU_DECK_ROW_RA) {
        DebugDeckSwap_ApplyPreset(cursor, sRAPhoenixMode_Deck);
      }
      activePreset = DebugDeckSwap_GetActivePreset();
      DebugMenuRedraw(scrollTop, activePreset, DEBUG_VIEW_DECK_PRESET);
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
