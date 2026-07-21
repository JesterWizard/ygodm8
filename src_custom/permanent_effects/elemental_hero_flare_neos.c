#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ELEMENTAL_HERO_FLARE_NEOS_ATK_PER_ST 400

static u8 CountAllSpellTrapsOnField(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *slot = gFixedZones[row][col];

      if (slot == NULL || slot->id == CARD_NONE)
        continue;
      if (GetTypeGroup(slot->id) == TYPE_GROUP_MONSTER)
        continue;

      count++;
    }
  }

  return count;
}

u8 ElementalHeroFlareNeos_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 baseAtk;
  u32 atk;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_FLARE_NEOS)
    return FALSE;

  baseAtk = gCardData_NEW[zone->id].atk;
  atk = (u32)baseAtk + (u32)CountAllSpellTrapsOnField() * ELEMENTAL_HERO_FLARE_NEOS_ATK_PER_ST;
  Duel_WriteCardInfoStats(zone->id, Duel_ClampStat(atk), gCardData_NEW[zone->id].def);
  return TRUE;
}

unsigned char ShouldActivateELEMENTAL_HERO_FLARE_NEOS(void)
{
  /* End Phase Extra return is live via TryReturnContactFusionsAtEndPhase. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateELEMENTAL_HERO_FLARE_NEOS(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroFlareNeos_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_FLARE_NEOS;
  ElementalHeroFlareNeos_ApplyDynamicZoneStats(&zone);
}
#endif
