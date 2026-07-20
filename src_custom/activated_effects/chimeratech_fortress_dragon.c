#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCHIMERATECH_FORTRESS_DRAGON(void)
{
  if (gMonEffect.id != CHIMERATECH_FORTRESS_DRAGON)
    return FALSE;

  /* ponytail: original ATK = 1000 x fusion material count needs fusion/summon
   * stat overlay hook. Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateCHIMERATECH_FORTRESS_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CHIMERATECH_FORTRESS_DRAGON, 2);
}
