#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateSTARDUST_DRAGON(void)
{
  if (gMonEffect.id != STARDUST_DRAGON)
    return FALSE;

  /* Quick Effect tribute-negate-destroy + End Phase GY SS need chain
   * and EP hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateSTARDUST_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(STARDUST_DRAGON, 2);
}
