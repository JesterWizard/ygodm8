#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateNEO_SPACIAN_DARK_PANTHER(void)
{
  if (gMonEffect.id != NEO_SPACIAN_DARK_PANTHER)
    return FALSE;

  /* Copy opp monster name/effects needs engine name/effect overlay outside this file.
   * Not field-ignition. */
  return FALSE;
}

void ActivateNEO_SPACIAN_DARK_PANTHEREffect(void)
{
  Duel_ShowEffectTextTyped(NEO_SPACIAN_DARK_PANTHER, 2);
}
