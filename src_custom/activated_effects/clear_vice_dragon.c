#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCLEAR_VICE_DRAGON(void)
{
  if (gMonEffect.id != CLEAR_VICE_DRAGON)
    return FALSE;

  /* ponytail: Clear World immunity + battle ATK double + discard-to-save need
   * continuous/battle/destruction hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateCLEAR_VICE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CLEAR_VICE_DRAGON, 2);
}
