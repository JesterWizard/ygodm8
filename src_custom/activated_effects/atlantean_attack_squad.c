#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateATLANTEAN_ATTACK_SQUAD(void)
{
  if (gMonEffect.id != ATLANTEAN_ATTACK_SQUAD)
    return FALSE;

  /* ponytail: continuous +800 ATK while controlling other Fish/SS/Aqua needs
   * permanent overlay. Ceiling: not ignition-activatable here; upgrade:
   * permanent ATK bonus check. */
  return FALSE;
}

void ActivateATLANTEAN_ATTACK_SQUADEffect(void)
{
  Duel_ShowEffectTextTyped(ATLANTEAN_ATTACK_SQUAD, 2);
}
