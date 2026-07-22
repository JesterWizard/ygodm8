#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_the_shining.h"
#include "removed_from_play.h"

#define SHINING_ATK_PER_BANISHED_EHERO 300

void ActivatePermanentEffectCardText(u16 cardId);
u8 GetDuelistForZone(struct DuelCard *zone);

static u8 CountBanishedElementalHeroes(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    if (Duel_IsElementalHeroCard(RemovedFromPlay_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

u8 ElementalHeroTheShining_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u32 baseAtk;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_THE_SHINING)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  baseAtk = gCardData_NEW[zone->id].atk;
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id,
                          Duel_StatFromCount(CountBanishedElementalHeroes(fixedDuelist),
                                             SHINING_ATK_PER_BANISHED_EHERO,
                                             baseAtk),
                          gCardInfo.def);
  return TRUE;
}

void ElementalHeroTheShining_OnZoneCleared(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_THE_SHINING)
    return;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return;

  ActivatePermanentEffectCardText(ELEMENTAL_HERO_THE_SHINING);

  /* Return up to 2 banished E-HEROes to hand deferred — no multi-RFP
   * return UI yet. ATK overlay via ElementalHeroTheShining_ApplyDynamicZoneStats. */
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroTheShining_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_THE_SHINING;
  ElementalHeroTheShining_ApplyDynamicZoneStats(&zone);
}
#endif
