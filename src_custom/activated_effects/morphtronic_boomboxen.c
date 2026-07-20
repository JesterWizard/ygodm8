#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMORPHTRONIC_BOOMBOXEN(void)
{
  if (gMonEffect.id != MORPHTRONIC_BOOMBOXEN)
    return FALSE;

  /* ponytail: double attack in ATK + DEF negate-attack need battle/position
   * hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateMORPHTRONIC_BOOMBOXENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_BOOMBOXEN, 2);
}
