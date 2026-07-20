#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMORPHTRONIC_BOARDEN(void)
{
  if (gMonEffect.id != MORPHTRONIC_BOARDEN)
    return FALSE;

  /* ponytail: Morphtronic direct attack / battle indestructible continuous need
   * attack and battle hooks. Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateMORPHTRONIC_BOARDENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_BOARDEN, 2);
}
