#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define HEAT_BASE_ATK 1600
#define HEAT_ATK_PER_ELEMENTAL_HERO 200

static const char sElementalHeroArchetypeName[] APPEND_RODATA = "Elemental HERO";

static u8 IsElementalHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sElementalHeroArchetypeName);
}

static u8 IsElementalHeroZone(struct DuelCard *zone)
{
  return zone != NULL && IsElementalHeroMonster(zone->id);
}

static u8 CountElementalHeroOnFixedRow(u8 fixedRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsElementalHeroZone(gFixedZones[fixedRow][col]))
      count++;
  }

  return count;
}

u8 ElementalHeroHeat_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 count;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_HEAT)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  count = CountElementalHeroOnFixedRow(fixedRow);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(
      zone->id,
      Duel_StatFromCount(count, HEAT_ATK_PER_ELEMENTAL_HERO, HEAT_BASE_ATK),
      gCardInfo.def);
  return TRUE;
}

#if !defined(__GNUC__)
#error Elemental HERO Heat stat hook self-check requires GCC
#elif __GNUC__
void ElementalHeroHeat_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_HEAT;
  ElementalHeroHeat_ApplyDynamicZoneStats(&zone);
}
#endif
