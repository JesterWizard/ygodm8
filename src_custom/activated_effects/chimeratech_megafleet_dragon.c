#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateCHIMERATECH_MEGAFLEET_DRAGON(void)
{
  if (gMonEffect.id != CHIMERATECH_MEGAFLEET_DRAGON)
    return FALSE;

  /* Fusion ATK overlay via ChimeratechMegafleetDragon_ApplyDynamicZoneStats.
   * Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateCHIMERATECH_MEGAFLEET_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CHIMERATECH_MEGAFLEET_DRAGON, 2);
}
