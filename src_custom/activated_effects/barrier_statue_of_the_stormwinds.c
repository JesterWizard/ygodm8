#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateBARRIER_STATUE_OF_THE_STORMWINDS(void)
{
  if (gMonEffect.id != BARRIER_STATUE_OF_THE_STORMWINDS)
    return FALSE;

  /* ponytail: no SS except WIND needs Special Summon lock gate.
   * Ceiling: not ignition-activatable from this file; upgrade: permanent /
   * duel gate outside activated_effects. */
  return FALSE;
}

void ActivateBARRIER_STATUE_OF_THE_STORMWINDSEffect(void)
{
  /* Unreachable while CanActivate returns FALSE. */
  Duel_ShowEffectTextTyped(BARRIER_STATUE_OF_THE_STORMWINDS, 2);
}
