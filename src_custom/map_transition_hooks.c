#include "global.h"
#include "common-chax.h"
#include "debug_save_anywhere.h"
#include "overworld.h"

struct MapState {
  u16 id;
  u16 state;
  u16 flags[8];
  u16 alternativeState;
};

extern const struct MapState gMapStates[];
void sub_804EF84(u16 id, u16 state, u16 connection);
extern u8 gDebugSaveAnywhereRestorePending;

static struct DebugSaveAnywhereData *DebugSaveAnywhereData(void) {
  return (struct DebugSaveAnywhereData *)gDebugSaveAnywhereData;
}

LYN_REPLACE_CHECK(sub_80523EC);
void sub_80523EC__Replacement(u16 id, u16 state, u16 connection) {
  int i = -1;
  struct DebugSaveAnywhereData *data;

  if (gDebugSaveAnywhereRestorePending == TRUE) {
    data = DebugSaveAnywhereData();
    if (data->magic == DEBUG_SAVE_ANYWHERE_MAGIC) {
      id = data->mapId;
      state = data->mapState;
      connection = data->mapConnection;
    }
    gDebugSaveAnywhereRestorePending = FALSE;
  }

  while (gMapStates[++i].id != 0xFFFF) {
    if (gMapStates[i].id == id && gMapStates[i].state == state) {
      int j;
      bool32 keepState = FALSE;

      for (j = 0; j < 8; j++) {
        if (gMapStates[i].flags[j] != 0xFFFF && !CheckFlag(gMapStates[i].flags[j]))
          keepState = TRUE;
      }
      if (!keepState)
        state = gMapStates[i].alternativeState;
    }
  }

  sub_804EF84(id, state, connection);
}
