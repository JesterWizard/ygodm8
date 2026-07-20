#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateDARKBLAZE_DRAGON(void)
{
  if (gMonEffect.id != DARKBLAZE_DRAGON)
    return FALSE;

  /* ponytail: GY SS double stats + battle-destroy burn need SS/battle hooks.
   * Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateDARKBLAZE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(DARKBLAZE_DRAGON, 2);
}
