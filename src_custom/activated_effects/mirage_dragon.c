#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMIRAGE_DRAGON(void)
{
  if (gMonEffect.id != MIRAGE_DRAGON)
    return FALSE;

  /* ponytail: opp cannot activate Traps in Battle Phase needs trap-activation gate.
   * Ceiling: not ignition-activatable from this file; upgrade: permanent /
   * duel gate outside activated_effects. */
  return FALSE;
}

void ActivateMIRAGE_DRAGONEffect(void)
{
  /* Unreachable while CanActivate returns FALSE. */
  Duel_ShowEffectTextTyped(MIRAGE_DRAGON, 2);
}
