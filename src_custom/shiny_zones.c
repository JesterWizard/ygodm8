#include "global.h"
#include "configs/runtime.h"
#include "shiny_zones.h"
#include "overworld.h"

#include "generated/shiny_zones_generated.inc"

extern void (*g20245AC)(int, u8 *, int);
extern struct OamData gOamBuffer[];
int sub_80588C4(u8 *, int, int);

/* Upper OBJ VRAM (tiles >= 0x200) survives the per-frame cbb4→0x06010000 copy.
 * Palette must stay in 0–11: dialogue portraits are 8bpp and own OBJ banks 12–15.
 * Priority 2 matches overworld sprites (above ground BG); priority 3 is under the map.
 * OAM: borrow shadow slots (112+i) for Y-sort index i when that entity has no shadow
 * (spriteId == -1 or !hasShadow). Those indices are above body sprites (97–111), so
 * characters draw on top; active shadows stay untouched. */
#define SHINY_SPARKLE_TILE_BASE 0x3FB
#define SHINY_SPARKLE_PALETTE_NUM 10
#define SHINY_SPARKLE_SHADOW_OAM_BASE 112
#define SHINY_SPARKLE_MAX 8
#define SHINY_SPARKLE_FRAME_COUNT 4
#define SHINY_SPARKLE_LOOP_FRAMES 60
#define SHINY_SPARKLE_PRIORITY 2

static const u8 sShinySparkleTiles[] APPEND_ASSET = INCBIN_U8("src_custom/assets/animations/sheet_sparkle.4bpp");
static const u16 sShinySparklePalette[] APPEND_ASSET = INCBIN_U16("src_custom/assets/animations/sheet_sparkle.gbapal");

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

void ShinyZones_LoadSparkleGfx(void) {
  CpuFastCopy(sShinySparkleTiles, (void *)(0x06010000 + SHINY_SPARKLE_TILE_BASE * 32),
              SHINY_SPARKLE_FRAME_COUNT * 32);
  CpuCopy16(sShinySparklePalette, gPaletteBuffer + 0x100 + SHINY_SPARKLE_PALETTE_NUM * 16, 0x20);
  CpuCopy16(sShinySparklePalette, (void *)(OBJ_PLTT + SHINY_SPARKLE_PALETTE_NUM * 0x20), 0x20);
}

/* Shadow OAM is 112+i for Y-sort slot i → entity unk21C[i]. Empty / no-shadow
 * entities leave that OAM off-screen; reuse it so sparkles sit behind bodies. */
static u8 ShinyZones_CollectFreeShadowOam(u8 *outIndices, u8 maxOut) {
  u8 i;
  u8 n = 0;

  for (i = 0; i < 15 && n < maxOut; i++) {
    s16 entityId = gOverworld.unk21C[i];
    struct Object *obj;

    if (entityId < 0 || entityId >= 15)
      continue;
    obj = &gOverworld.objects[entityId];
    if (obj->spriteId != -1 && obj->hasShadow)
      continue;
    outIndices[n++] = SHINY_SPARKLE_SHADOW_OAM_BASE + i;
  }
  return n;
}

static u8 ShinyZones_TryGetSparkleScreenPos(const ShinyZoneEntry *entry, int *outX, int *outY) {
  int sx;
  int sy;

  if (entry->objectId != SHINY_ZONE_NO_OBJECT) {
    u8 objId = entry->objectId;

    if (objId >= 15 || gOverworld.objects[objId].spriteId == -1)
      return FALSE;
    sy = gOverworld.objects[objId].y * 2 - gOverworld.objects[objId].unk8 + gOverworld.unk24C;
    sx = gOverworld.objects[objId].x * 2 + gOverworld.unk24E;
  } else if (entry->coordinateType == SHINY_ZONE_COORD_SCREEN_TILE) {
    sx = entry->x * 8 + gOverworld.unk24E;
    sy = entry->y * 8 + gOverworld.unk24C;
  } else {
    sx = entry->x * 2 + gOverworld.unk24E;
    sy = entry->y * 2 + gOverworld.unk24C;
  }

  if (sy < 0 || sy > 159 || sx < 0 || sx > 239)
    return FALSE;

  *outX = sx;
  *outY = sy;
  return TRUE;
}

void ShinyZones_UpdateSparkles(void) {
  u16 *oam = (u16 *)gOamBuffer;
  unsigned i;
  u8 slot = 0;
  u8 frame;
  u16 attr2;
  u8 freeOam[SHINY_SPARKLE_MAX];
  u8 freeCount;

  if (gRuntimeConfig.enable_shiny_zones != TRUE)
    return;

  freeCount = ShinyZones_CollectFreeShadowOam(freeOam, SHINY_SPARKLE_MAX);
  if (freeCount == 0)
    return;

  ShinyZones_LoadSparkleGfx();

  gShinySparkleAnimTimer++;
  if (gShinySparkleAnimTimer >= SHINY_SPARKLE_LOOP_FRAMES)
    gShinySparkleAnimTimer = 0;
  frame = gShinySparkleAnimTimer / (SHINY_SPARKLE_LOOP_FRAMES / SHINY_SPARKLE_FRAME_COUNT);
  attr2 = (SHINY_SPARKLE_TILE_BASE + frame)
        | (SHINY_SPARKLE_PRIORITY << 10)
        | (SHINY_SPARKLE_PALETTE_NUM << 12);

  for (i = 0; i < gShinyZoneEntryCount && slot < freeCount; i++) {
    const ShinyZoneEntry *entry = &gShinyZoneEntries[i];
    int sx;
    int sy;
    u16 idx;

    if (entry->mapId != gOverworld.map.id)
      continue;
    if (entry->state != SHINY_ZONE_ANY_STATE && entry->state != gOverworld.map.state)
      continue;
    if (ShinyZones_CheckFlag(entry->flag) == TRUE)
      continue;
    if (ShinyZones_TryGetSparkleScreenPos(entry, &sx, &sy) != TRUE)
      continue;

    idx = freeOam[slot] * 4;
    oam[idx] = (u8)sy;
    oam[idx + 1] = (u16)sx;
    oam[idx + 2] = attr2;
    oam[idx + 3] = 0;
    slot++;
  }
}
