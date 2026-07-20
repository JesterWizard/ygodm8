#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMORPHTRONIC_VIDEON(void)
{
  if (gMonEffect.id != MORPHTRONIC_VIDEON)
    return FALSE;

  /* ponytail: position-based ATK/DEF per Equip needs continuous stat overlay.
   * Ceiling: not ignition-activatable here; upgrade: permanent position/equip gate. */
  return FALSE;
}

void ActivateMORPHTRONIC_VIDEONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_VIDEON, 2);
}
