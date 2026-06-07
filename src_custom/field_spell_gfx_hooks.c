#include "global.h"
#include "common-chax.h"
#include "custom_field_spell.h"
#include "dynamic_equip.h"

extern unsigned short gBG2HOFS;
extern unsigned short gBG2VOFS;

extern const unsigned char gFieldArenaTiles[];
extern const unsigned char gFieldForestTiles[];
extern const unsigned char gFieldWastelandTiles[];
extern const unsigned char gFieldMountainTiles[];
extern const unsigned char gFieldSogenTiles[];
extern const unsigned char gFieldUmiTiles[];
extern const unsigned char gFieldYamiTiles[];

extern const unsigned short gFieldArenaTilemap[][31];
extern const unsigned short gFieldForestTilemap[][31];
extern const unsigned short gFieldWastelandTilemap[][31];
extern const unsigned short gFieldMountainTilemap[][31];
extern const unsigned short gFieldSogenTilemap[][31];
extern const unsigned short gFieldUmiTilemap[][31];
extern const unsigned short gFieldYamiTilemap[][31];

extern const unsigned short gFieldArenaPalette[];
extern const unsigned short gFieldForestPalette[];
extern const unsigned short gFieldWastelandPalette[];
extern const unsigned short gFieldMountainPalette[];
extern const unsigned short gFieldSogenPalette[];
extern const unsigned short gFieldUmiPalette[];
extern const unsigned short gFieldYamiPalette[];

static const unsigned char *GetVanillaFieldTiles(u8 field)
{
  if (field == FIELD_FOREST)
    return gFieldForestTiles;
  if (field == FIELD_WASTELAND)
    return gFieldWastelandTiles;
  if (field == FIELD_MOUNTAIN)
    return gFieldMountainTiles;
  if (field == FIELD_SOGEN)
    return gFieldSogenTiles;
  if (field == FIELD_UMI)
    return gFieldUmiTiles;
  if (field == FIELD_YAMI)
    return gFieldYamiTiles;
  return gFieldArenaTiles;
}

static const unsigned short (*GetVanillaFieldTilemap(u8 field))[31]
{
  if (field == FIELD_FOREST)
    return gFieldForestTilemap;
  if (field == FIELD_WASTELAND)
    return gFieldWastelandTilemap;
  if (field == FIELD_MOUNTAIN)
    return gFieldMountainTilemap;
  if (field == FIELD_SOGEN)
    return gFieldSogenTilemap;
  if (field == FIELD_UMI)
    return gFieldUmiTilemap;
  if (field == FIELD_YAMI)
    return gFieldYamiTilemap;
  return gFieldArenaTilemap;
}

static const u16 *GetVanillaFieldPalette(u8 field)
{
  if (field >= NUM_VANILLA_FIELDS)
    return gFieldArenaPalette;
  if (field == FIELD_FOREST)
    return gFieldForestPalette;
  if (field == FIELD_WASTELAND)
    return gFieldWastelandPalette;
  if (field == FIELD_MOUNTAIN)
    return gFieldMountainPalette;
  if (field == FIELD_SOGEN)
    return gFieldSogenPalette;
  if (field == FIELD_UMI)
    return gFieldUmiPalette;
  if (field == FIELD_YAMI)
    return gFieldYamiPalette;
  return gFieldArenaPalette;
}

u32 AdjustBackgroundBeforeTurnStart(u8);

#define DUEL_FIELD_TILEMAP_VRAM_OFFSET 0xD800

static const u16 *GetActiveFieldPalette(void)
{
  const u16 *customPalette = GetCustomFieldPalette(gDuel.field);

  if (customPalette != NULL)
    return customPalette;

  return GetVanillaFieldPalette(gDuel.field);
}

static void LoadCustomFieldGfx(u8 field)
{
  const struct CustomFieldGfxAsset *asset = GetCustomFieldGfxAsset(field);
  u8 i;

  if (asset == NULL)
    return;

  HuffUnComp(asset->tiles, gBgVram.cbb0);
  CpuCopy16(asset->palette, gPaletteBuffer, 96);

  for (i = 0; i < 40; i++)
    CpuCopy16(asset->tilemap[i], gBgVram.cbb0 + DUEL_FIELD_TILEMAP_VRAM_OFFSET + i * 64, 64);
}

LYN_REPLACE_CHECK(SetDuelFieldGfx);
void SetDuelFieldGfx__Replacement(u8 field)
{
  u8 i;

  REG_BG2CNT = 0x9B02;

#if NUM_CUSTOM_FIELDS > 0
  if (IsCustomField(field)) {
    LoadCustomFieldGfx(field);
    gBG2HOFS = 4;
    gBG2VOFS = AdjustBackgroundBeforeTurnStart(gDuelCursor.currentY);
    return;
  }
#endif

  if (field >= NUM_VANILLA_FIELDS)
    field = FIELD_ARENA;

  HuffUnComp(GetVanillaFieldTiles(field), gBgVram.cbb0);
  CpuCopy16(GetVanillaFieldPalette(field), gPaletteBuffer, 96);

  {
    const unsigned short (*tilemap)[31] = GetVanillaFieldTilemap(field);

    for (i = 0; i < 40; i++)
      CpuCopy16(tilemap[i], gBgVram.cbb0 + DUEL_FIELD_TILEMAP_VRAM_OFFSET + i * 64, 64);
  }

  gBG2HOFS = 4;
  gBG2VOFS = AdjustBackgroundBeforeTurnStart(gDuelCursor.currentY);
}

void FlushDuelFieldLayerToHardware(void)
{
  CpuCopy16(GetActiveFieldPalette(), (u16 *)PLTT, 96);
  CpuCopy16(
      gBgVram.cbb0 + DUEL_FIELD_TILEMAP_VRAM_OFFSET,
      (void *)(BG_VRAM + DUEL_FIELD_TILEMAP_VRAM_OFFSET),
      0xA00);
  CpuCopy32(gBgVram.cbb0 + 0x8040, (void *)(BG_VRAM + 0x8040), 0x740);
  CpuCopy16(gPaletteBuffer + 0x50, (u16 *)PLTT + 0x50, 0x40);
  CpuCopy32(gBgVram.cbb0 + 0xE800, (void *)(BG_VRAM + 0xE800), 0x480);
}

void sub_8040B4C(void);
void DisplayCardInfoBar(void);
void sub_80577A4(void);
void sub_80408FC(void);
void sub_80411D4(void);
void WaitForVBlank(void);
void LoadPalettes(void);
void SetDuelFieldGfx(u8 field);
void UpdateDuelGfxExceptField(void);
extern u8 gSliferPendingPenaltyActive;
void ResolvePendingSliferSummonPenalty(void);

typedef void (*VoidFunc)(void);

static void CallVanillaSub8040C6C(void)
{
  ((VoidFunc)(0x08040C6C | 1))();
}

static void RunVanillaUpdateDuelGfxExceptField(void)
{
  sub_8040B4C();
  DisplayCardInfoBar();
  CallVanillaSub8040C6C();
  sub_80577A4();
  sub_80408FC();
  WaitForVBlank();
  sub_80411D4();
  REG_WIN1H = 0;
  REG_WIN1V = 0;
  REG_DISPCNT = DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON;
  REG_BLDCNT = 0xD4;
  REG_BLDY = 10;
}

static void RestoreDuelFieldLayerIfNeeded(void)
{
#if NUM_CUSTOM_FIELDS > 0
  if (IsCustomField(gDuel.field)) {
    u16 savedHofs = gBG2HOFS;
    u16 savedVofs = gBG2VOFS;

    SetDuelFieldGfx(gDuel.field);
    gBG2HOFS = savedHofs;
    gBG2VOFS = savedVofs;
    return;
  }
#endif

  if (FieldHasActiveDynamicEquipSpellOnBoard() == TRUE) {
    u16 savedHofs = gBG2HOFS;
    u16 savedVofs = gBG2VOFS;

    SetDuelFieldGfx(gDuel.field);
    gBG2HOFS = savedHofs;
    gBG2VOFS = savedVofs;
  }
}

LYN_REPLACE_CHECK(UpdateDuelGfxExceptField);
void UpdateDuelGfxExceptField__Replacement(void)
{
  RestoreDuelFieldLayerIfNeeded();
  RunVanillaUpdateDuelGfxExceptField();

  if (gSliferPendingPenaltyActive == TRUE)
    ResolvePendingSliferSummonPenalty();
}
