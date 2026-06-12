#include "global.h"
#include "configs/runtime.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "event_system.h"
#include "overworld.h"

#define DEBUG_MENU_SCENE_ENTRY(mapId, state, connection, title) \
  {mapId, state, connection, title},

static const struct DebugMenuSceneEntry sScenes[] APPEND_RODATA = {
#include "debug_menu_scene_table.inc"
};

#undef DEBUG_MENU_SCENE_ENTRY

extern struct Overworld gOverworld;

void sub_80523EC(u16 id, u16 state, u16 connection);
void sub_804EEE0(void);

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

#define DEBUG_MENU_SCENE_NONE 0xFFFF
#define DEBUG_MENU_SCENE_INACTIVE 0xFF

extern u8 gDebugMenuPendingSceneActive;
extern u8 gDebugMenuPendingSceneMapId;
extern u8 gDebugMenuPendingSceneState;
extern u8 gDebugMenuPendingSceneConnection;

static void DebugMenu_SetPendingScene(const struct DebugMenuSceneEntry *e) {
  sub_80523EC(e->mapId, e->state, e->connection);
  gDebugMenuPendingSceneMapId = e->mapId;
  gDebugMenuPendingSceneState = e->state;
  gDebugMenuPendingSceneConnection = e->connection;
  gDebugMenuPendingSceneActive = TRUE;
}

static void DebugMenuFormatSceneRow(u8 *out, const struct DebugMenuSceneEntry *e, bool8 selected) {
  DebugMenuFormatListRow(out, e->title, selected);
}

void DebugMenuDrawScenes(u16 scrollTop, u16 confirmedIndex) {
  u8 row, buf[2 + DEBUG_CHARS + 1];

  for (row = 0; row < DEBUG_ROWS; row++) {
    u16 index = scrollTop + row;

    if (index < ARRAY_COUNT(sScenes)) {
      DebugMenuFormatSceneRow(buf, &sScenes[index],
                              confirmedIndex != DEBUG_MENU_SCENE_NONE && index == confirmedIndex);
      DebugMenuCopyLine(row, buf);
    } else {
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
    }
  }
}

void DebugSceneViewer(void) {
  u16 cursor = 0, scrollTop = 0;
  u16 confirmedSceneIndex = DEBUG_MENU_SCENE_NONE;
  const u16 n = ARRAY_COUNT(sScenes);

  DebugMenuRedraw(0, confirmedSceneIndex, DEBUG_VIEW_SCENE);
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
      DebugMenuRedraw(scrollTop, confirmedSceneIndex, DEBUG_VIEW_SCENE);
    }
    if (buttons & DPAD_DOWN && cursor < n - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, confirmedSceneIndex, DEBUG_VIEW_SCENE);
    }
    if (buttons & DPAD_LEFT && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (cursor >= 5)
        cursor -= 5;
      else
        cursor = 0;
      if (cursor < scrollTop)
        scrollTop = cursor;
      DebugMenuRedraw(scrollTop, confirmedSceneIndex, DEBUG_VIEW_SCENE);
    }
    if (buttons & DPAD_RIGHT && cursor < n - 1) {
      u16 newCursor;

      PlayMusic(SFX_MOVE_CURSOR);
      newCursor = cursor + 5;
      if (newCursor >= n)
        cursor = n - 1;
      else
        cursor = newCursor;
      if (cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, confirmedSceneIndex, DEBUG_VIEW_SCENE);
    }
    if (buttons & A_BUTTON) {
      confirmedSceneIndex = cursor;
      DebugMenu_SetPendingScene(&sScenes[cursor]);
      PlayMusic(SFX_SELECT);
      DebugMenuRedraw(scrollTop, confirmedSceneIndex, DEBUG_VIEW_SCENE);
      DebugMenuWaitRelease(A_BUTTON);
    }

    DebugMenuUpdateCursor((u8)(cursor - scrollTop));
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

void DebugMenu_ApplyPendingScene(void) {
  struct Script *script;

  if (gDebugMenuPendingSceneActive != TRUE)
    return;

  gDebugMenuPendingSceneActive = DEBUG_MENU_SCENE_INACTIVE;

  CallThumbVoid(0x0804D640);
  CallThumbVoid(0x0804EFA8);
  sub_804EEE0();

  script = gOverworld.unk1F4[gOverworld.map.unk4];
  if (script != NULL)
    InitiateScript(script);
}
