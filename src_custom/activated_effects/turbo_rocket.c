#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTURBO_ROCKET(void)
{
  if (gMonEffect.id != TURBO_ROCKET)
    return FALSE;

  /* ponytail: battle destruction immunity + post-damage burn need battle hooks.
   * Ceiling: not ignition-activatable here; upgrade: battle damage / destroy gate. */
  return FALSE;
}

void ActivateTURBO_ROCKETEffect(void)
{
  Duel_ShowEffectTextTyped(TURBO_ROCKET, 2);
}
