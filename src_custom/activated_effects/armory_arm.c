#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateARMORY_ARM(void)
{
  if (gMonEffect.id != ARMORY_ARM)
    return FALSE;

  /* Monster-equipment behavior is intentionally unavailable in this ruleset. */
  return FALSE;
}

void ActivateARMORY_ARMEffect(void)
{
  Duel_ShowEffectTextTyped(ARMORY_ARM, 2);
}
