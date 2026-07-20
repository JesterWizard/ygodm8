#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMORPHTRONIC_RADION(void)
{
  if (gMonEffect.id != MORPHTRONIC_RADION)
    return FALSE;

  /* ponytail: position-based Morphtronic ATK/DEF boost needs continuous stat overlay.
   * Ceiling: not ignition-activatable here; upgrade: permanent position gate. */
  return FALSE;
}

void ActivateMORPHTRONIC_RADIONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_RADION, 2);
}
