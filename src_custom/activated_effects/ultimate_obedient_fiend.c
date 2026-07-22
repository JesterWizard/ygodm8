#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateULTIMATE_OBEDIENT_FIEND(void)
{
  if (gMonEffect.id != ULTIMATE_OBEDIENT_FIEND)
    return FALSE;

  /* solo-field + empty-hand attack restriction needs attack gate hook.
   * Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateULTIMATE_OBEDIENT_FIENDEffect(void)
{
  Duel_ShowEffectTextTyped(ULTIMATE_OBEDIENT_FIEND, 2);
}
