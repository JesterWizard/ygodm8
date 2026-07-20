#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateAMAZONESS_TRAINEE(void)
{
  if (gMonEffect.id != AMAZONESS_TRAINEE)
    return FALSE;

  /* ponytail: battle shuffle-to-deck-bottom + +200 ATK need battle hooks.
   * Ceiling: not ignition-activatable here; upgrade: battle destroy + stat overlay. */
  return FALSE;
}

void ActivateAMAZONESS_TRAINEEEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_TRAINEE, 2);
}
