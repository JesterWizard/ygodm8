#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateARMORY_ARM(void)
{
  if (gMonEffect.id != ARMORY_ARM)
    return FALSE;

  /* Ceiling: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs
   * monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE. */
  return FALSE;
}

void ActivateARMORY_ARMEffect(void)
{
  Duel_ShowEffectTextTyped(ARMORY_ARM, 2);
}
