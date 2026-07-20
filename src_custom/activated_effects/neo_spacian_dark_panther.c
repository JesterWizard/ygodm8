#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateNEO_SPACIAN_DARK_PANTHER(void)
{
  if (gMonEffect.id != NEO_SPACIAN_DARK_PANTHER)
    return FALSE;

  /* ponytail: copy opp monster name/effects needs engine name/effect overlay.
   * Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy. */
  return FALSE;
}

void ActivateNEO_SPACIAN_DARK_PANTHEREffect(void)
{
  Duel_ShowEffectTextTyped(NEO_SPACIAN_DARK_PANTHER, 2);
}
