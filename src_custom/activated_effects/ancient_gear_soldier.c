#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_SOLDIER(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_SOLDIER)
    return FALSE;

  /* ponytail: attack → opp cannot activate S/T until end of Damage Step needs
   * battle lock hook. Ceiling: not ignition-activatable here; upgrade: battle
   * phase Spell/Trap activation gate while this card is attacking. */
  return FALSE;
}

void ActivateANCIENT_GEAR_SOLDIEREffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_SOLDIER, 2);
}
