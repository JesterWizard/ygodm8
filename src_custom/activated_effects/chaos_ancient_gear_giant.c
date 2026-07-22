#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCHAOS_ANCIENT_GEAR_GIANT(void)
{
  if (gMonEffect.id != CHAOS_ANCIENT_GEAR_GIANT)
    return FALSE;

  /* Attack S/T lock via AncientGear_AttackerBlocksOppSpellTrap; pierce via
   * ApplySimplePiercersBattleEffect; multi-attack via TryMarkBuiltInExtraAttackOnPlacement.
   * Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateCHAOS_ANCIENT_GEAR_GIANTEffect(void)
{
  Duel_ShowEffectTextTyped(CHAOS_ANCIENT_GEAR_GIANT, 2);
}
