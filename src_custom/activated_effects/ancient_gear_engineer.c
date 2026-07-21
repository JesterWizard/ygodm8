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
   * ponytail: trap negate + end-of-Damage-Step destroy need battle/trap hooks. */
  return FALSE;
}

void ActivateANCIENT_GEAR_ENGINEEREffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_ENGINEER, 2);
}
