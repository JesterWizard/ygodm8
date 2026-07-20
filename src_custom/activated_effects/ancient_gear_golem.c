#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_GOLEM(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_GOLEM)
    return FALSE;

  /* ponytail: attack → opp cannot activate S/T until Damage Step + piercing need
   * battle/attack hooks. Ceiling: not ignition-activatable here; upgrade: battle
   * Spell/Trap lock while attacking + DEF-pierce damage step. */
  return FALSE;
}

void ActivateANCIENT_GEAR_GOLEMEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_GOLEM, 2);
}
