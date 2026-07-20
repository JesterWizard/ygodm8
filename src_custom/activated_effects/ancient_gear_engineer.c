#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_ENGINEER(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_ENGINEER)
    return FALSE;

  /* ponytail: trap negate + attack lock + end-of-Damage-Step destroy need
   * battle/trap hooks. Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateANCIENT_GEAR_ENGINEEREffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_ENGINEER, 2);
}
