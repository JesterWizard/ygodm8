#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateHERALD_OF_THE_ARC_LIGHT(void)
{
  if (gMonEffect.id != HERALD_OF_THE_ARC_LIGHT)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateHERALD_OF_THE_ARC_LIGHTEffect(void)
{
  Duel_ShowEffectTextTyped(HERALD_OF_THE_ARC_LIGHT, 2);
}
