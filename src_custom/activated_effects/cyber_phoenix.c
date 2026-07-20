#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCYBER_PHOENIX(void)
{
  if (gMonEffect.id != CYBER_PHOENIX)
    return FALSE;

  /* ponytail: Attack Position S/T negate + destroy-by-battle draw need continuous
   * and battle hooks. Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateCYBER_PHOENIXEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
}
