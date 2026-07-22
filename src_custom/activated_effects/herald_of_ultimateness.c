#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateHERALD_OF_ULTIMATENESS(void)
{
  if (gMonEffect.id != HERALD_OF_ULTIMATENESS)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * Not field-ignition (either-turn discard Fairy → negate + destroy). */
  return FALSE;
}

void ActivateHERALD_OF_ULTIMATENESSEffect(void)
{
  Duel_ShowEffectTextTyped(HERALD_OF_ULTIMATENESS, 2);
}
