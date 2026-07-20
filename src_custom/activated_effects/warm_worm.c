#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateWARM_WORM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != WARM_WORM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != WARM_WORM)
    return FALSE;

  /* ponytail: printed trigger is when destroyed. Ceiling: once via usage. */
  return CanUseMonsterEffect(zone);
}

void ActivateWARM_WORMEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(WARM_WORM, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  Duel_MillTopDeckCards(INACTIVE_DUELIST, 3, TRUE);
  MarkMonsterEffectUsed(zone);
}
