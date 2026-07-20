#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGAGAGIGO_THE_RISEN(void)
{
  if (gMonEffect.id != GAGAGIGO_THE_RISEN)
    return FALSE;

  /* ponytail: Gagagigo the Risen has no printed monster effect (Xyz materials only).
   * Ceiling: not ignition-activatable from this file; upgrade: permanent /
   * duel gate outside activated_effects. */
  return FALSE;
}

void ActivateGAGAGIGO_THE_RISENEffect(void)
{
  /* Unreachable while CanActivate returns FALSE. */
  Duel_ShowEffectTextTyped(GAGAGIGO_THE_RISEN, 2);
}
