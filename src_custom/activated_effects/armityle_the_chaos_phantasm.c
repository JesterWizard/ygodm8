#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateARMITYLE_THE_CHAOS_PHANTASM(void)
{
  if (gMonEffect.id != ARMITYLE_THE_CHAOS_PHANTASM)
    return FALSE;

  /* ponytail: Extra Deck banish-fusion SS + battle indestructible + turn-only
   * +10000 ATK need summon/permanent/battle hooks. Ceiling: not ignition here. */
  return FALSE;
}

void ActivateARMITYLE_THE_CHAOS_PHANTASMEffect(void)
{
  Duel_ShowEffectTextTyped(ARMITYLE_THE_CHAOS_PHANTASM, 2);
}
