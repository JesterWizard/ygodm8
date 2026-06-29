#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

#define SHINING_FLARE_WINGMAN_BASE_ATK 2500
#define SHINING_FLARE_WINGMAN_ATK_PER_HERO 300

static u8 CountElementalHeroInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (Duel_IsElementalHeroCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u16 ShiningFlareWingmanCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);

  if (fixedDuelist == 0xFF)
    return SHINING_FLARE_WINGMAN_BASE_ATK;

  return Duel_StatFromCount(
      CountElementalHeroInGraveyard(fixedDuelist),
      SHINING_FLARE_WINGMAN_ATK_PER_HERO,
      SHINING_FLARE_WINGMAN_BASE_ATK);
}

u8 ElementalHeroShiningFlareWingman_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_SHINING_FLARE_WINGMAN)
    return FALSE;

  SetCardInfo(zone->id);
  atk = ShiningFlareWingmanCurrentAtk(zone);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

#if !defined(__GNUC__)
#error Elemental HERO Shining Flare Wingman stat hook self-check requires GCC
#elif __GNUC__
void ElementalHeroShiningFlareWingman_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_SHINING_FLARE_WINGMAN;
  ElementalHeroShiningFlareWingman_ApplyDynamicZoneStats(&zone);
}
#endif
