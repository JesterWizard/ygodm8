#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCHIMERATECH_FORTRESS_DRAGON(void)
{
  if (gMonEffect.id != CHIMERATECH_FORTRESS_DRAGON)
    return FALSE;

  /* Fusion ATK overlay via ChimeratechFortressDragon_ApplyDynamicZoneStats.
   * Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateCHIMERATECH_FORTRESS_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CHIMERATECH_FORTRESS_DRAGON, 2);
}
