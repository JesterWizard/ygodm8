#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateULTIMATE_TYRANNO(void)
{
  if (gMonEffect.id != ULTIMATE_TYRANNO)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateULTIMATE_TYRANNOEffect(void)
{
  Duel_ShowEffectTextTyped(ULTIMATE_TYRANNO, 2);
}
