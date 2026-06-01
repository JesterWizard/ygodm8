#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "overworld.h"

#define DEBUG_MENU_MAP_ENTRY(id, title) {id, title},

static const struct DebugMenuMapEntry sMaps[] APPEND_RODATA = {
#include "debug_menu_map_table.inc"
};

#undef DEBUG_MENU_MAP_ENTRY

extern struct Overworld gOverworld;

void sub_80523EC(u16 id, u16 state, u16 connection);
void sub_804EEE0(void);

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

extern u8 gDebugMenuMapViewerInitialLocation;

#define DEBUG_MENU_MAP_VIEWER_INACTIVE 0xFF
#define DEBUG_MENU_MAP_NONE 0xFF

static bool8 DebugMenu_SetSavedMapLocation(u8 locationId) {
  if (gOverworld.map.unk8 == locationId)
    return FALSE;

  sub_80523EC(locationId, 0, 0);
  return TRUE;
}

static void DebugMenuFormatMapRow(u8 *out, const struct DebugMenuMapEntry *e, bool8 selected) {
  DebugMenuFormatListRow(out, e->title, selected);
}

void DebugMenuDrawMaps(u8 scrollTop, u8 confirmedLocationId) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < ARRAY_COUNT(sMaps)) {
      DebugMenuFormatMapRow(buf, &sMaps[index],
                            confirmedLocationId != DEBUG_MENU_MAP_NONE &&
                                sMaps[index].locationId == confirmedLocationId);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugMapViewer(void) {
  u8 cursor = 0, scrollTop = 0;
  u8 confirmedLocationId = DEBUG_MENU_MAP_NONE;
  const u16 n = ARRAY_COUNT(sMaps);

  gDebugMenuMapViewerInitialLocation = gOverworld.map.unk8;

  DebugMenuRedraw(0, confirmedLocationId, DEBUG_VIEW_MAP);
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
      DebugMenuRedraw(scrollTop, confirmedLocationId, DEBUG_VIEW_MAP);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, confirmedLocationId, DEBUG_VIEW_MAP);
    }
    if (buttons & A_BUTTON) {
      confirmedLocationId = sMaps[cursor].locationId;
      if (DebugMenu_SetSavedMapLocation(confirmedLocationId))
        PlayMusic(SFX_SELECT);
      DebugMenuRedraw(scrollTop, confirmedLocationId, DEBUG_VIEW_MAP);
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

void DebugMenu_ApplyPendingMapTeleport(void) {
  if (gDebugMenuMapViewerInitialLocation == DEBUG_MENU_MAP_VIEWER_INACTIVE)
    return;
  if (gOverworld.map.unk8 == gDebugMenuMapViewerInitialLocation) {
    gDebugMenuMapViewerInitialLocation = DEBUG_MENU_MAP_VIEWER_INACTIVE;
    return;
  }

  gDebugMenuMapViewerInitialLocation = DEBUG_MENU_MAP_VIEWER_INACTIVE;
  CallThumbVoid(0x0804D640);
  CallThumbVoid(0x0804EFA8);
  sub_804EEE0();
}
