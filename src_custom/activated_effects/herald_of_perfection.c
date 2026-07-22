#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateHERALD_OF_PERFECTION(void)
{
  if (gMonEffect.id != HERALD_OF_PERFECTION)
    return FALSE;

  /* Quick negate by sending Fairy from hand needs chain/negation hooks outside.
   * Not field-ignition (either-turn discard Fairy → negate + destroy). */
  return FALSE;
}

void ActivateHERALD_OF_PERFECTIONEffect(void)
{
  Duel_ShowEffectTextTyped(HERALD_OF_PERFECTION, 2);
}
