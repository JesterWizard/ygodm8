#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTURBO_SYNCHRON(void)
{
  if (gMonEffect.id != TURBO_SYNCHRON)
    return FALSE;

  /* Attack-target DEF change and post-damage hand summon are omitted. */
  return FALSE;
}

void ActivateTURBO_SYNCHRONEffect(void)
{
  Duel_ShowEffectTextTyped(TURBO_SYNCHRON, 2);
}
