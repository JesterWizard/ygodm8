#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "overworld.h"
#include "maps_custom.h"

#include "src_custom/generated/maps/manifest_connection_overrides.inc"

struct MapState {
  u16 id;
  u16 state;
  u16 flags[8];
  u16 alternativeState;
};

extern const struct MapState gMapStates[];
void sub_804EF84(u16 id, u16 state, u16 connection);

#include "src_custom/generated/maps/custom_map_connections.inc"

extern u8 gDebugSaveAnywhereRestorePending;

static struct DebugSaveAnywhereData *DebugSaveAnywhereData(void) {
  return (struct DebugSaveAnywhereData *)gDebugSaveAnywhereData;
}

/* Replace sub_804EF84 — the final step of any map transition.
 * Intercepts vanilla→custom map connections defined in the manifest.
 * Custom maps use map id 0 (safe dummy) internally to prevent out-of-bounds
 * array accesses; OverworldLoadGraphics__Replacement handles the real
 * custom graphics loading via the sCustomMapOverride* variables. */
LYN_REPLACE_CHECK(sub_804EF84);
void sub_804EF84__Replacement(u16 id, u16 state, u16 connection) {
#if CUSTOM_MAP_CONNECTION_COUNT > 0 && CUSTOM_MAP_COUNT > 0
  unsigned i;
  for (i = 0; i < CUSTOM_MAP_CONNECTION_COUNT; i++) {
    if (sCustomMapConnections[i].vanillaLocation == id) {
      /* Vanilla→custom redirect: store real custom ID for the
       * graphics override, but use safe dummy map (0) for loading. */
      gCustomMapOverridePending = TRUE;
      gCustomMapOverrideId = sCustomMapConnections[i].customMapId;
      gOverworld.map.unk8 = 0;    /* safe dummy */
      gOverworld.map.unkA = 0;
      gOverworld.map.unkC = connection;
      return;
    }
  }
#endif
  if (id >= CUSTOM_MAP_BASE) {
    /* Custom→custom or direct custom transition: set override and redirect
     * to safe dummy map (0) so InitOverworld doesn't read out-of-bounds
     * from gMapCollisions / gMapData. */
    gCustomMapOverridePending = TRUE;
    gCustomMapOverrideId = id;
    gOverworld.map.unk8 = 0;
    gOverworld.map.unkA = 0;
    gOverworld.map.unkC = connection;
    return;
  }
  gCustomMapOverridePending = FALSE;
  gOverworld.map.unk8 = id;
  gOverworld.map.unkA = state;
  gOverworld.map.unkC = connection;
}

LYN_REPLACE_CHECK(sub_80523EC);
void sub_80523EC__Replacement(u16 id, u16 state, u16 connection) {
  int i = -1;
  struct DebugSaveAnywhereData *data;

  /* Check manifest connection overrides before using the ROM-sourced target.
   * This allows the manifest to redirect vanilla edge and script transitions. */
  if (gRuntimeConfig.enable_manifest_map_overrides) {
    u8 override = gManifestConnectionOverrides[gOverworld.map.id][gOverworld.map.unk6];
    if (override != 0xFF) {
      id = override;
    }
  }

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
