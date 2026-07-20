#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivatePROTECTOR_OF_THE_SANCTUARY(void)
{
  if (gMonEffect.id != PROTECTOR_OF_THE_SANCTUARY)
    return FALSE;

  /* ponytail: opp cannot draw except Draw Phase needs draw-gate LynJump.
   * Ceiling: not ignition-activatable from this file; upgrade: permanent /
   * duel gate outside activated_effects. */
  return FALSE;
}

void ActivatePROTECTOR_OF_THE_SANCTUARYEffect(void)
{
  /* Unreachable while CanActivate returns FALSE. */
  Duel_ShowEffectTextTyped(PROTECTOR_OF_THE_SANCTUARY, 2);
}
