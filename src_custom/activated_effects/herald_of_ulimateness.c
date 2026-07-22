#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateHERALD_OF_ULIMATENESS(void)
{
  if (gMonEffect.id != HERALD_OF_ULIMATENESS)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateHERALD_OF_ULIMATENESSEffect(void)
{
  Duel_ShowEffectTextTyped(HERALD_OF_ULIMATENESS, 2);
}
