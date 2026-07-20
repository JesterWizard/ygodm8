#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCHAINSAW_INSECT(void)
{
  if (gMonEffect.id != CHAINSAW_INSECT)
    return FALSE;

  /* ponytail: opp draws after Damage Step needs battle end hook.
   * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
   * gate outside this file. */
  return FALSE;
}

void ActivateCHAINSAW_INSECTEffect(void)
{
  Duel_ShowEffectTextTyped(CHAINSAW_INSECT, 2);
}
