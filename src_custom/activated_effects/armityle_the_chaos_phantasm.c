#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateARMITYLE_THE_CHAOS_PHANTASM(void)
{
  if (gMonEffect.id != ARMITYLE_THE_CHAOS_PHANTASM)
    return FALSE;

  /* Pierce + multi-attack via ApplySimplePiercersBattleEffect and
   * TryMarkBuiltInExtraAttackOnPlacement. */
  return FALSE;
}

void ActivateARMITYLE_THE_CHAOS_PHANTASMEffect(void)
{
  Duel_ShowEffectTextTyped(ARMITYLE_THE_CHAOS_PHANTASM, 2);
}
