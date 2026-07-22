#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTUNINGWARE(void)
{
  if (gMonEffect.id != TUNINGWARE)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateTUNINGWAREEffect(void)
{
  Duel_ShowEffectTextTyped(TUNINGWARE, 2);
}
