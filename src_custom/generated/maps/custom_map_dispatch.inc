// 0 custom maps

#define CUSTOM_MAP_COUNT 0


// Tileset pointers

static const u8 *const sCustomTilesets[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};


// Ground tilemap pointers

static const u16 *const sCustomGroundTilemaps[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};


// Roof tilemap pointers (NULL = no roof layer)

static const u16 *const sCustomRoofTilemaps[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};


// Palette pointers

static const u16 *const sCustomPalettes[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};


// Collision pointers

static const u16 *const sCustomCollisions[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};


// Music IDs per custom map

static const u16 sCustomMapMusic[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};

// Vanilla → custom map transition patches

#if CUSTOM_MAP_COUNT > 0

static const struct { u16 vanillaLocation; u16 edge; u8 triggerX; u8 triggerYMin; u8 triggerYMax; u16 customMapId; } sCustomMapConnections[] APPEND_RODATA = {
};

#define CUSTOM_MAP_CONNECTION_COUNT 0
#endif

// Custom map dummy MapData entries

#if CUSTOM_MAP_COUNT > 0


static const struct MapData *const sCustomMapData[CUSTOM_MAP_COUNT] APPEND_RODATA = {
};
#endif
