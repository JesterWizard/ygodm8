#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTATSUNOKO(void)
{
  if (gMonEffect.id != TATSUNOKO)
    return FALSE;

  /* ponytail: hand-as-Synchro-material and unaffected-by-monster-effects need
   * synchro/summon continuous hooks. Ceiling: not field-ignition here. */
  return FALSE;
}

void ActivateTATSUNOKOEffect(void)
{
  Duel_ShowEffectTextTyped(TATSUNOKO, 2);
}
