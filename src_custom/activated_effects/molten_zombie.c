#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMOLTEN_ZOMBIE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MOLTEN_ZOMBIE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MOLTEN_ZOMBIE)
    return FALSE;

  /* ponytail: printed trigger is SS from GY. Ceiling: once via usage when
   * Activate runs (summon-dispatch or manual). */
  return CanUseMonsterEffect(zone);
}

void ActivateMOLTEN_ZOMBIEEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(MOLTEN_ZOMBIE, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE);
  MarkMonsterEffectUsed(zone);
}
