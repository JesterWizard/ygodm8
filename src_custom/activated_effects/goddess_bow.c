#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGODDESS_BOW(void)
{
  if (gMonEffect.id != GODDESS_BOW)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateGODDESS_BOWEffect(void)
{
  Duel_ShowEffectTextTyped(GODDESS_BOW, 2);
}
