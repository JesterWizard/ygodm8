#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateROAD_SYNCHRON(void)
{
  if (gMonEffect.id != ROAD_SYNCHRON)
    return FALSE;

  /* ponytail: Synchro Level -2 (non-Road Warrior) + battle-hit Level +1 need
   * synchro/battle hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateROAD_SYNCHRONEffect(void)
{
  Duel_ShowEffectTextTyped(ROAD_SYNCHRON, 2);
}
