#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEAST(void)
{
  if (gMonEffect.id != FUSILIER_DRAGON_THE_DUAL_MODE_BEAST)
    return FALSE;

  /* ponytail: NS without tribute + halved ATK/DEF needs summon tribute gate.
   * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
   * gate outside this file. */
  return FALSE;
}

void ActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEASTEffect(void)
{
  Duel_ShowEffectTextTyped(FUSILIER_DRAGON_THE_DUAL_MODE_BEAST, 2);
}
