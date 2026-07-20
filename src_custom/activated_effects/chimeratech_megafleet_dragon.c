#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCHIMERATECH_MEGAFLEET_DRAGON(void)
{
  if (gMonEffect.id != CHIMERATECH_MEGAFLEET_DRAGON)
    return FALSE;

  /* ponytail: original ATK = 1200 x fusion material count needs fusion/summon
   * stat overlay hook. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateCHIMERATECH_MEGAFLEET_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CHIMERATECH_MEGAFLEET_DRAGON, 2);
}
