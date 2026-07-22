#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateD_D_WARRIOR(void)
{
  if (gMonEffect.id != D_D_WARRIOR)
    return FALSE;

  /* Ceiling: after damage calc banish both needs battle hook.
   * Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle
   * gate outside this file. */
  return FALSE;
}

void ActivateD_D_WARRIOREffect(void)
{
  Duel_ShowEffectTextTyped(D_D_WARRIOR, 2);
}
