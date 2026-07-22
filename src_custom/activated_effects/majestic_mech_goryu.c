#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char CanActivateMAJESTIC_MECH_GORYU(void)
{
  if (gMonEffect.id != MAJESTIC_MECH_GORYU)
    return FALSE;

  /* Pierce via ApplySimplePiercersBattleEffect.
   * ponytail: 1-tribute EP self-send need summon/EP hooks.
   * Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateMAJESTIC_MECH_GORYUEffect(void)
{
  Duel_ShowEffectTextTyped(MAJESTIC_MECH_GORYU, 2);
}
