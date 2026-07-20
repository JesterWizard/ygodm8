#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTYRANT_BURST_DRAGON(void)
{
  if (gMonEffect.id != TYRANT_BURST_DRAGON)
    return FALSE;

  /* ponytail: multi-attack + equip-to-monster need battle/equip continuous hooks.
   * Ceiling: not ignition-activatable here; upgrade: permanent battle/equip gate. */
  return FALSE;
}

void ActivateTYRANT_BURST_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(TYRANT_BURST_DRAGON, 2);
}
