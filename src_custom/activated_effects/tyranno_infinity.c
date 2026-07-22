#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "removed_from_play.h"
#include "tyranno_infinity.h"

#define TYRANNO_INFINITY_ATK_PER_DINO 1000

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 CountOwnBanishedDinosaurs(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);
  u8 count = 0;
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT || !RemovedFromPlay_IsEnabled())
    return 0;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    u16 id = RemovedFromPlay_GetCardAt(fixedDuelist, i);

    if (GetTypeGroup(id) == TYPE_GROUP_MONSTER
        && Duel_CardHasMonsterType(id, TYPE_DINOSAUR))
      count++;
  }
  return count;
}

u8 TyrannoInfinity_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != TYRANNO_INFINITY)
    return FALSE;

  atk = Duel_StatFromCount(CountOwnBanishedDinosaurs(zone), TYRANNO_INFINITY_ATK_PER_DINO, 0);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateTYRANNO_INFINITY(void)
{
  if (gMonEffect.id != TYRANNO_INFINITY)
    return FALSE;

  /* Continuous ATK via TyrannoInfinity_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateTYRANNO_INFINITYEffect(void)
{
  Duel_ShowEffectTextTyped(TYRANNO_INFINITY, 2);
}
