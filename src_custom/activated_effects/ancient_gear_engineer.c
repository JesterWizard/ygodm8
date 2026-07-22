#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_ENGINEER(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_ENGINEER)
    return FALSE;

  /* Attack S/T lock live via AncientGear_AttackerBlocksOppSpellTrap.
   * End-of-Damage-Step Set S/T destroy via ApplyAncientGearEngineerBattleEffect.
   * ponytail: opp Trap activation negate on attack needs chain gate. */
  return FALSE;
}

void ActivateANCIENT_GEAR_ENGINEEREffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_ENGINEER, 2);
}
