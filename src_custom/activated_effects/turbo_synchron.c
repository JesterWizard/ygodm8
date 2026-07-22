#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTURBO_SYNCHRON(void)
{
  if (gMonEffect.id != TURBO_SYNCHRON)
    return FALSE;

  /* Attack-target DEF change + battle-damage SS from hand need battle hooks
   * outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateTURBO_SYNCHRONEffect(void)
{
  Duel_ShowEffectTextTyped(TURBO_SYNCHRON, 2);
}
