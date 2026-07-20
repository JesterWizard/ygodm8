#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_SPEAR_SOLDIER(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_SPEAR_SOLDIER)
    return FALSE;

  /* ponytail: piercing battle damage needs battle damage gate.
   * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
   * gate outside this file. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_SPEAR_SOLDIEREffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SPEAR_SOLDIER, 2);
}
