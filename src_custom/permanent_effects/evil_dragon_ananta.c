#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

#define EVIL_DRAGON_ANANTA_STAT_PER_REPTILE 600

static u8 CountReptileInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);

  for (i = 0; i < gyCount; i++) {
    if (Duel_CardHasMonsterType(GraveyardExpand_GetCardAt(fixedDuelist, i), TYPE_REPTILE))
      count++;
  }

  return count;
}

static u16 AnantaCurrentStat(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);

  if (fixedDuelist == 0xFF)
    return 0;

  return Duel_StatFromCount(
      CountReptileInGraveyard(fixedDuelist),
      EVIL_DRAGON_ANANTA_STAT_PER_REPTILE,
      0);
}

u8 EvilDragonAnanta_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != EVIL_DRAGON_ANANTA)
    return FALSE;

  stat = AnantaCurrentStat(zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

unsigned char ShouldActivateEVIL_DRAGON_ANANTA(void)
{
  /* ponytail: End Phase destroy 1 card needs turn_effect hook — ApplyDynamicZoneStats only. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_DRAGON_ANANTA(void)
{
}

#if !defined(__GNUC__)
#error Evil Dragon Ananta stat hook self-check requires GCC
#elif __GNUC__
void EvilDragonAnanta_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = EVIL_DRAGON_ANANTA;
  EvilDragonAnanta_ApplyDynamicZoneStats(&zone);
}
#endif
