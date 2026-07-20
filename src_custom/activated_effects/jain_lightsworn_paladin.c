#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateJAIN_LIGHTSWORN_PALADIN(void)
{
  if (gMonEffect.id != JAIN_LIGHTSWORN_PALADIN)
    return FALSE;

  /* ponytail: Damage Step +300 ATK and End Phase mill 2 need battle/phase hooks.
   * Ceiling: not ignition-activatable here; upgrade: permanent/battle + EP mill. */
  return FALSE;
}

void ActivateJAIN_LIGHTSWORN_PALADINEffect(void)
{
  Duel_ShowEffectTextTyped(JAIN_LIGHTSWORN_PALADIN, 2);
}
