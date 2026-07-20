#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateEHREN_LIGHTSWORN_MONK(void)
{
  if (gMonEffect.id != EHREN_LIGHTSWORN_MONK)
    return FALSE;

  /* ponytail: battle shuffle + End Phase mill 3 need battle/phase hooks.
   * Ceiling: not ignition-activatable here; upgrade: battle + EP mill. */
  return FALSE;
}

void ActivateEHREN_LIGHTSWORN_MONKEffect(void)
{
  Duel_ShowEffectTextTyped(EHREN_LIGHTSWORN_MONK, 2);
}
