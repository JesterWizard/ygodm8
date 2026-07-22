#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEAST(void)
{
  if (gMonEffect.id != FUSILIER_DRAGON_THE_DUAL_MODE_BEAST)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEASTEffect(void)
{
  Duel_ShowEffectTextTyped(FUSILIER_DRAGON_THE_DUAL_MODE_BEAST, 2);
}
