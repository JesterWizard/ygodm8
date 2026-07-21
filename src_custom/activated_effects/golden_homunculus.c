#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "golden_homunculus.h"
#include "removed_from_play.h"

#define GOLDEN_HOMUNCULUS_STAT_PER_BANISHED 300

u8 GetDuelistForZone(struct DuelCard *zone);

u8 GoldenHomunculus_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 banished = 0;
  u16 stat;

  if (zone == NULL || zone->id != GOLDEN_HOMUNCULUS)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  if (RemovedFromPlay_IsEnabled())
    banished = RemovedFromPlay_GetCount(fixedDuelist);

  stat = Duel_StatFromCount(banished, GOLDEN_HOMUNCULUS_STAT_PER_BANISHED, 0);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

unsigned char CanActivateGOLDEN_HOMUNCULUS(void)
{
  if (gMonEffect.id != GOLDEN_HOMUNCULUS)
    return FALSE;

  /* Continuous ATK/DEF via GoldenHomunculus_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateGOLDEN_HOMUNCULUSEffect(void)
{
  Duel_ShowEffectTextTyped(GOLDEN_HOMUNCULUS, 2);
}
