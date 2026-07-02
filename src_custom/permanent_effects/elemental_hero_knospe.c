#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_knospe.h"

#define ELEMENTAL_HERO_KNOSPE_ATK_GAIN 100
#define ELEMENTAL_HERO_KNOSPE_DEF_LOSS 100

static u8 HasOtherFaceUpElementalHeroOnFixedRow(u8 fixedRow, u16 excludeId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *other = gFixedZones[fixedRow][col];

    if (other != NULL && other->id != CARD_NONE && other->isFaceUp
        && other->id != excludeId && Duel_IsElementalHeroCard(other->id))
      return TRUE;
  }

  return FALSE;
}

static u16 KnospeCurrentAtk(struct DuelCard *zone)
{
  u16 baseAtk = gCardData_NEW[zone->id].atk;

  return Duel_ClampStat((u32)baseAtk + (u8)zone->permStage * ELEMENTAL_HERO_KNOSPE_ATK_GAIN);
}

static u16 KnospeCurrentDef(struct DuelCard *zone)
{
  u32 baseDef = gCardData_NEW[zone->id].def;
  u32 def = baseDef;

  if (baseDef > (u8)zone->permStage * ELEMENTAL_HERO_KNOSPE_DEF_LOSS)
    def = baseDef - (u8)zone->permStage * ELEMENTAL_HERO_KNOSPE_DEF_LOSS;
  else
    def = 0;

  return Duel_ClampStat(def);
}

u8 ElementalHeroKnospe_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_KNOSPE)
    return FALSE;

  Duel_WriteCardInfoStats(zone->id, KnospeCurrentAtk(zone), KnospeCurrentDef(zone));
  return TRUE;
}

u8 ElementalHeroKnospe_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_KNOSPE || !zone->isFaceUp)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  if (HasOtherFaceUpElementalHeroOnFixedRow(fixedRow, ELEMENTAL_HERO_KNOSPE))
    return FALSE;

  return TRUE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroKnospe_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_KNOSPE;
  zone.permStage = 2;
  ElementalHeroKnospe_ApplyDynamicZoneStats(&zone);
}
#endif
