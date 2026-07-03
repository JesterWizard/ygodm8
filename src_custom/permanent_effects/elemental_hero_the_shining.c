#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_the_shining.h"

void ActivatePermanentEffectCardText(u16 cardId);

void ElementalHeroTheShining_OnZoneCleared(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_THE_SHINING)
    return;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return;

  ActivatePermanentEffectCardText(ELEMENTAL_HERO_THE_SHINING);

  /* ponytail: no banished-zone storage yet — +300 ATK per banished E-HERO and
     return up to 2 banished E-HEROes to hand deferred until banish zone exists. */
}
