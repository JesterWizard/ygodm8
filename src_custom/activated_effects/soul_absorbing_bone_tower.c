#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateSOUL_ABSORBING_BONE_TOWER(void)
{
  if (gMonEffect.id != SOUL_ABSORBING_BONE_TOWER)
    return FALSE;

  /* ponytail: attack redirect while another Zombie present + mill 2 on Zombie
   * SS need continuous/SS hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateSOUL_ABSORBING_BONE_TOWEREffect(void)
{
  Duel_ShowEffectTextTyped(SOUL_ABSORBING_BONE_TOWER, 2);
}
