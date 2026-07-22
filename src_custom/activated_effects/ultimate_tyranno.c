#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateULTIMATE_TYRANNO(void)
{
  if (gMonEffect.id != ULTIMATE_TYRANNO)
    return FALSE;

  /* multi-attack + Tyranno-only battle phase gate need battle hooks.
   * Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateULTIMATE_TYRANNOEffect(void)
{
  Duel_ShowEffectTextTyped(ULTIMATE_TYRANNO, 2);
}
