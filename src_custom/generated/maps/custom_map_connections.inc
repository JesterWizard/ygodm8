// Vanilla → custom map transition patches

#if CUSTOM_MAP_COUNT > 0

static const struct { u16 vanillaLocation; u16 edge; u8 triggerX; u8 triggerYMin; u8 triggerYMax; u16 customMapId; } sCustomMapConnections[] APPEND_RODATA = {
};

#define CUSTOM_MAP_CONNECTION_COUNT 0
#endif
