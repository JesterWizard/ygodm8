#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_poison_rose.h"

#define ELEMENTAL_HERO_POISON_ROSE_ATK_GAIN 200
#define ELEMENTAL_HERO_POISON_ROSE_DEF_LOSS 200

static u16 PoisonRoseCurrentAtk(struct DuelCard *zone)
{
  u16 baseAtk = gCardData_NEW[zone->id].atk;

  return Duel_ClampStat((u32)baseAtk + (u8)zone->permStage * ELEMENTAL_HERO_POISON_ROSE_ATK_GAIN);
}

static u16 PoisonRoseCurrentDef(struct DuelCard *zone)
{
  u32 baseDef = gCardData_NEW[zone->id].def;
  u32 def = baseDef;

  if (baseDef > (u8)zone->permStage * ELEMENTAL_HERO_POISON_ROSE_DEF_LOSS)
    def = baseDef - (u8)zone->permStage * ELEMENTAL_HERO_POISON_ROSE_DEF_LOSS;
  else
    def = 0;

  return Duel_ClampStat(def);
}

u8 ElementalHeroPoisonRose_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_POISON_ROSE)
    return FALSE;

  Duel_WriteCardInfoStats(zone->id, PoisonRoseCurrentAtk(zone), PoisonRoseCurrentDef(zone));
  return TRUE;
}

struct DuelCard *ElementalHeroPoisonRose_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id == ELEMENTAL_HERO_POISON_ROSE && zone->isFaceUp)
      return zone;
  }

  return NULL;
}

u8 ElementalHeroPoisonRose_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == ELEMENTAL_HERO_POISON_ROSE)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return ElementalHeroPoisonRose_GetForcedAttackTarget(
      Duel_FixedDuelistForMonsterRow(fixedRow)) == NULL;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroPoisonRose_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_POISON_ROSE;
  zone.permStage = 2;
  ElementalHeroPoisonRose_ApplyDynamicZoneStats(&zone);
}
#endif
