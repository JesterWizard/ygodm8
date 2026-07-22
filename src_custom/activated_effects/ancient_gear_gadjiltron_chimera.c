#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_GADJILTRON_CHIMERA(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_GADJILTRON_CHIMERA)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * Not ignition-activatable here. */
  return FALSE;
}

void ActivateANCIENT_GEAR_GADJILTRON_CHIMERAEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_GADJILTRON_CHIMERA, 2);
}
