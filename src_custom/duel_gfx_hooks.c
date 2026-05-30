#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"

extern unsigned short gBG2HOFS;
extern unsigned short gBG2VOFS;

extern const unsigned short gFieldArenaPalette[];
extern const unsigned short gFieldForestPalette[];
extern const unsigned short gFieldWastelandPalette[];
extern const unsigned short gFieldMountainPalette[];
extern const unsigned short gFieldSogenPalette[];
extern const unsigned short gFieldUmiPalette[];
extern const unsigned short gFieldYamiPalette[];

void sub_8040B4C(void);
void DisplayCardInfoBar(void);
void sub_80577A4(void);
void sub_80408FC(void);
void sub_80411D4(void);
void SetDuelFieldGfx(unsigned char field);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);
void LoadPalettes(void);

typedef void (*VoidFunc)(void);

#define DUEL_FIELD_TILEMAP_VRAM_OFFSET 0xD800
#define DUEL_FIELD_TILEMAP_UPLOAD_SIZE 0xA00

static void CallVanillaSub8040C6C(void)
{
  ((VoidFunc)(0x08040C6C | 1))();
}

static const u16 *GetActiveFieldPalette(void)
{
  switch (gDuel.field) {
    case FIELD_FOREST:
      return gFieldForestPalette;
    case FIELD_WASTELAND:
      return gFieldWastelandPalette;
    case FIELD_MOUNTAIN:
      return gFieldMountainPalette;
    case FIELD_SOGEN:
      return gFieldSogenPalette;
    case FIELD_UMI:
      return gFieldUmiPalette;
    case FIELD_YAMI:
      return gFieldYamiPalette;
    default:
      return gFieldArenaPalette;
  }
}

void FlushDuelFieldLayerToHardware(void)
{
  CpuCopy16(GetActiveFieldPalette(), gPaletteBuffer, 96);
  LoadPalettes();
  CpuCopy16(
      gBgVram.cbb0 + DUEL_FIELD_TILEMAP_VRAM_OFFSET,
      (void *)(BG_VRAM + DUEL_FIELD_TILEMAP_VRAM_OFFSET),
      DUEL_FIELD_TILEMAP_UPLOAD_SIZE);
  CpuCopy32(gBgVram.cbb0 + 0x8040, (void *)(BG_VRAM + 0x8040), 0x740);
  CpuCopy16(gPaletteBuffer + 0x50, (u16 *)PLTT + 0x50, 0x40);
  CpuCopy32(gBgVram.cbb0 + 0xE800, (void *)(BG_VRAM + 0xE800), 0x480);
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
}
