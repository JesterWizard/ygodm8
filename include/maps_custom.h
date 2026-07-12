#ifndef GUARD_MAPS_CUSTOM_H
#define GUARD_MAPS_CUSTOM_H

#include "overworld.h"

/* Returns the MapData for a custom map ID, or NULL if not a custom map. */
const struct MapData *GetCustomMapData(u16 mapId);

/* Returns the collision grid for a custom map ID, or NULL. */
const u16 *GetCustomMapCollision(u16 mapId);

/* Returns the LZ77-compressed tileset for a custom map ID. */
const u8 *GetCustomMapTileset(u16 mapId);

/* Returns the ground tilemap for a custom map ID. */
const u16 *GetCustomMapGroundTilemap(u16 mapId);

/* Returns the roof tilemap for a custom map ID, or NULL if no roof. */
const u16 *GetCustomMapRoofTilemap(u16 mapId);

/* Returns the BG palette (240 colors) for a custom map ID. */
const u16 *GetCustomMapPalette(u16 mapId);

/* Returns the music ID for a custom map ID. */
u16 GetCustomMapMusic(u16 mapId);

/* Apply custom map override at end-of-frame (defined in overworld_debug_overlay_hooks.c). */
void ApplyCustomMapOverride(void);

/* Runtime state */
extern bool32 gCustomMapActive;
extern bool32 gCustomMapOverridePending;
extern u16 gCustomMapOverrideId;

#endif /* GUARD_MAPS_CUSTOM_H */
