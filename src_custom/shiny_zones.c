#include "global.h"
#include "configs/runtime.h"
#include "shiny_zones.h"
#include "overworld.h"

#include "generated/shiny_zones_generated.inc"

extern void (*g20245AC)(int, u8 *, int);
int sub_80588C4(u8 *, int, int);

static u8 ShinyZones_CheckFlag(u8 flag) {
  if (flag >= SHINY_ZONE_MAX_FLAGS)
    return TRUE;
  return (gShinyZoneFlags[flag >> 3] & (1 << (flag & 7))) != 0;
}

static void ShinyZones_SetFlag(u8 flag) {
  if (flag >= SHINY_ZONE_MAX_FLAGS)
    return;
  gShinyZoneFlags[flag >> 3] |= 1 << (flag & 7);
}

void ShinyZones_ResetFlags(void) {
  u8 i;

  for (i = 0; i < SHINY_ZONE_FLAG_BYTES; i++)
    gShinyZoneFlags[i] = 0;
}

static void ShinyZones_LoadFlagsFromFlash(int address) {
  if (g20245AC == NULL)
    return;
  g20245AC(address, gShinyZoneFlags, SHINY_ZONE_FLAG_BYTES);
}

static void ShinyZones_SaveFlagsToFlash(int address) {
  sub_80588C4(gShinyZoneFlags, address, SHINY_ZONE_FLAG_BYTES);
}

void ShinyZones_LoadFlagsFromFlashPrimary(void) {
  ShinyZones_LoadFlagsFromFlash((int)gShinyZoneFlagsFlashPrimary);
}

void ShinyZones_LoadFlagsFromFlashBackup(void) {
  ShinyZones_LoadFlagsFromFlash((int)gShinyZoneFlagsFlashBackup);
}

void ShinyZones_SaveFlagsToFlashPrimary(void) {
  ShinyZones_SaveFlagsToFlash((int)gShinyZoneFlagsFlashPrimary);
}

void ShinyZones_SaveFlagsToFlashBackup(void) {
  ShinyZones_SaveFlagsToFlash((int)gShinyZoneFlagsFlashBackup);
}

static u8 ShinyZones_Matches(const ShinyZoneEntry *entry, u8 x, u8 y, s8 objectId) {
  s16 dx;
  s16 dy;
  u8 targetX = x;
  u8 targetY = y;

  if (entry->mapId != gOverworld.map.id)
    return FALSE;
  if (entry->state != SHINY_ZONE_ANY_STATE && entry->state != gOverworld.map.state)
    return FALSE;
  if (ShinyZones_CheckFlag(entry->flag) == TRUE)
    return FALSE;

  if (entry->objectId != SHINY_ZONE_NO_OBJECT)
    return objectId == entry->objectId;

  if (entry->coordinateType == SHINY_ZONE_COORD_SCREEN_TILE) {
    targetX = x / 4;
    targetY = y / 4;
  }

  dx = (s16)targetX - (s16)entry->x;
  dy = (s16)targetY - (s16)entry->y;
  return dx >= -1 && dx <= 1 && dy >= -1 && dy <= 1;
}

static const ShinyZoneEntry *ShinyZones_Find(u8 x, u8 y, s8 objectId) {
  unsigned i;

  for (i = 0; i < gShinyZoneEntryCount; i++) {
    if (ShinyZones_Matches(&gShinyZoneEntries[i], x, y, objectId) == TRUE)
      return &gShinyZoneEntries[i];
  }
  return NULL;
}

u8 ShinyZones_TryInteract(u8 x, u8 y, s8 objectId) {
  const ShinyZoneEntry *entry;

  if (gRuntimeConfig.enable_shiny_zones != TRUE)
    return FALSE;

  entry = ShinyZones_Find(x, y, objectId);
  if (entry == NULL)
    return FALSE;

  PlayMusic(SFX_DIALOGUE);
  InitiateScript((struct Script *)entry->script);

  // Shiny-zone scripts can terminate without going through the "press button to close"
  // textbox handler, leaving the overworld textbox/window state visible behind the card view.
  LZ77UnCompWram(g82AD2D0, gVramBuffer + 0xD800);
  sub_805339C();
  REG_WINOUT = 0x3D3E;
  OverworldSetRegDispcnt();
  REG_BLDCNT = 0;

  sub_8053404();
  SetCardInfo(entry->cardId);
  ShowCardDetailView();
  AddCardQtyToTrunk(entry->cardId, 1);
  ShinyZones_SetFlag(entry->flag);
  OverworldLoadGraphics();
  // Returning from the card view, keep the overworld textbox/window disabled.
  LZ77UnCompWram(g82AD2D0, gVramBuffer + 0xD800);
  sub_8053404();
  return TRUE;
}
