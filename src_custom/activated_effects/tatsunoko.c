#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTATSUNOKO(void)
{
  if (gMonEffect.id != TATSUNOKO)
    return FALSE;

  /* Hand-as-extra procedure-material and unaffected-by-monster-effects need
   * synchro/summon continuous hooks outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateTATSUNOKOEffect(void)
{
  Duel_ShowEffectTextTyped(TATSUNOKO, 2);
}
