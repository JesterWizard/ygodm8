#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateDARK_MAGICIAN_THE_DRAGON_KNIGHT(void)
{
  if (gMonEffect.id != DARK_MAGICIAN_THE_DRAGON_KNIGHT)
    return FALSE;

  /* ponytail: name becomes Dark Magician + S/T protection need permanent/name hooks.
   * Ceiling: not ignition-activatable here; upgrade: permanent overlay. */
  return FALSE;
}

void ActivateDARK_MAGICIAN_THE_DRAGON_KNIGHTEffect(void)
{
  Duel_ShowEffectTextTyped(DARK_MAGICIAN_THE_DRAGON_KNIGHT, 2);
}
