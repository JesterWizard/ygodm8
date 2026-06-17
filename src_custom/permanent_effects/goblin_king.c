#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u16 GoblinKingCurrentStat(struct DuelCard *zone)
{
  u8 count = Duel_CountFixedMonstersMatching(Duel_IsFiendZone);

  (void)zone;
  return Duel_StatFromCount(count, 500, 0);
}

u8 GoblinKing_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  stat = GoblinKingCurrentStat(zone);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

#if !defined(__GNUC__)
#error Goblin King stat hook self-check requires GCC
#elif __GNUC__
void GoblinKing_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = GOBLIN_KING;
  GoblinKing_ApplyDynamicZoneStats(&zone);
}
#endif
