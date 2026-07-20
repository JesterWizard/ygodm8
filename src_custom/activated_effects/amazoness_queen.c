#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateAMAZONESS_QUEEN(void)
{
  if (gMonEffect.id != AMAZONESS_QUEEN)
    return FALSE;

  /* ponytail: Amazoness cannot be destroyed by battle needs battle-destroy protection.
   * Ceiling: not ignition-activatable from this file; upgrade: permanent /
   * duel gate outside activated_effects. */
  return FALSE;
}

void ActivateAMAZONESS_QUEENEffect(void)
{
  /* Unreachable while CanActivate returns FALSE. */
  Duel_ShowEffectTextTyped(AMAZONESS_QUEEN, 2);
}
