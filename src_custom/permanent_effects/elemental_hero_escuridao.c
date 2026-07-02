#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

#define ESCURIDAO_BASE_ATK 2500
#define ESCURIDAO_ATK_PER_HERO 100

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

static u16 EscuridaoCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);

  if (fixedDuelist == 0xFF)
    return ESCURIDAO_BASE_ATK;

  return Duel_StatFromCount(
      CountElementalHeroInGraveyard(fixedDuelist),
      ESCURIDAO_ATK_PER_HERO,
      ESCURIDAO_BASE_ATK);
}

u8 ElementalHeroEscuridao_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_ESCURIDAO)
    return FALSE;

  atk = EscuridaoCurrentAtk(zone);
  // Reload after CountElementalHeroInGraveyard — Duel_IsElementalHeroCard
  // calls SetCardInfo and leaves gCardInfo on the last GY card checked.
  SetCardInfo(zone->id);
  gCardInfo.atk = atk;
  return TRUE;
}

#if !defined(__GNUC__)
#error Elemental HERO Escuridao stat hook self-check requires GCC
#elif __GNUC__
void ElementalHeroEscuridao_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_ESCURIDAO;
  ElementalHeroEscuridao_ApplyDynamicZoneStats(&zone);
}
#endif
