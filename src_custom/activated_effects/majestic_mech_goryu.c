#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMAJESTIC_MECH_GORYU(void)
{
  if (gMonEffect.id != MAJESTIC_MECH_GORYU)
    return FALSE;

  /* ponytail: 1-tribute EP self-send + piercing battle damage need summon/battle
   * hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateMAJESTIC_MECH_GORYUEffect(void)
{
  Duel_ShowEffectTextTyped(MAJESTIC_MECH_GORYU, 2);
}
