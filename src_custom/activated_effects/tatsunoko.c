#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTATSUNOKO(void)
{
  if (gMonEffect.id != TATSUNOKO)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateTATSUNOKOEffect(void)
{
  Duel_ShowEffectTextTyped(TATSUNOKO, 2);
}
