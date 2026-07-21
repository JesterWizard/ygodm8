#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "helios_the_primordial_sun.h"
#include "removed_from_play.h"

#define HELIOS_STAT_PER_BANISHED_MONSTER 100

static u8 CountBanishedMonsters(void)
{
  u8 total = 0;
  u8 d;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (d = 0; d < 2; d++) {
    for (i = 0; i < RemovedFromPlay_GetCount(d); i++) {
      if (GetTypeGroup(RemovedFromPlay_GetCardAt(d, i)) == TYPE_GROUP_MONSTER)
        total++;
    }
  }
  return total;
}

u8 HeliosThePrimordialSun_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != HELIOS_THE_PRIMORDIAL_SUN)
    return FALSE;

  stat = Duel_StatFromCount(CountBanishedMonsters(), HELIOS_STAT_PER_BANISHED_MONSTER, 0);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

unsigned char CanActivateHELIOS_THE_PRIMORDIAL_SUN(void)
{
  if (gMonEffect.id != HELIOS_THE_PRIMORDIAL_SUN)
    return FALSE;

  /* Continuous ATK/DEF via HeliosThePrimordialSun_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateHELIOS_THE_PRIMORDIAL_SUNEffect(void)
{
  Duel_ShowEffectTextTyped(HELIOS_THE_PRIMORDIAL_SUN, 2);
}
