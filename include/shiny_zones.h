#ifndef GUARD_SHINY_ZONES_H
#define GUARD_SHINY_ZONES_H

#include "gba/types.h"
#include "overworld.h"

#define SHINY_ZONE_FLAG_BYTES 16
#define SHINY_ZONE_MAX_FLAGS (SHINY_ZONE_FLAG_BYTES * 8)
#define SHINY_ZONE_NO_OBJECT 0xFF
#define SHINY_ZONE_ANY_STATE 0xFF
#define SHINY_ZONE_COORD_OVERWORLD 0
#define SHINY_ZONE_COORD_SCREEN_TILE 1

typedef struct {
  u8 flag;
  u8 mapId;
  u8 state;
  u8 objectId;
  u8 coordinateType;
  u8 x;
  u8 y;
  u16 cardId;
  const struct Script *script;
} ShinyZoneEntry;

extern u8 gShinyZoneFlags[SHINY_ZONE_FLAG_BYTES];
extern u8 gShinyZoneFlagsFlashPrimary[SHINY_ZONE_FLAG_BYTES];
extern u8 gShinyZoneFlagsFlashBackup[SHINY_ZONE_FLAG_BYTES];
extern u8 gShinySparkleAnimTimer;
extern const ShinyZoneEntry gShinyZoneEntries[];
extern const unsigned gShinyZoneEntryCount;

void ShinyZones_ResetFlags(void);
void ShinyZones_LoadFlagsFromFlashPrimary(void);
void ShinyZones_LoadFlagsFromFlashBackup(void);
void ShinyZones_SaveFlagsToFlashPrimary(void);
void ShinyZones_SaveFlagsToFlashBackup(void);
u8 ShinyZones_TryInteract(u8 x, u8 y, s8 objectId);
void ShinyZones_LoadSparkleGfx(void);
void ShinyZones_UpdateSparkles(void);

#endif
