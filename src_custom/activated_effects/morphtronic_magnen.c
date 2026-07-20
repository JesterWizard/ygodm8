#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMORPHTRONIC_MAGNEN(void)
{
  if (gMonEffect.id != MORPHTRONIC_MAGNEN)
    return FALSE;

  /* ponytail: ATK-position highest-ATK-only attack target + DEF-position
   * redirect-attack need battle/position hooks. Ceiling: not ignition here. */
  return FALSE;
}

void ActivateMORPHTRONIC_MAGNENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_MAGNEN, 2);
}
