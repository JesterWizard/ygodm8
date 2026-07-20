#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCRIMSON_BLADER(void)
{
  if (gMonEffect.id != CRIMSON_BLADER)
    return FALSE;

  /* ponytail: battle destroy → opp cannot NS/SS Lv5+ next turn needs battle
   * destroy + summon-lock hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateCRIMSON_BLADEREffect(void)
{
  Duel_ShowEffectTextTyped(CRIMSON_BLADER, 2);
}
