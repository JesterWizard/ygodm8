#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGODDESS_BOW(void)
{
  if (gMonEffect.id != GODDESS_BOW)
    return FALSE;

  /* Hermos fusion + equip + battle-phase negate/second attack need
   * fusion/equip/chain hooks outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateGODDESS_BOWEffect(void)
{
  Duel_ShowEffectTextTyped(GODDESS_BOW, 2);
}
