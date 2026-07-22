#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateHORUS_THE_BLACK_FLAME_DRAGON_LV8(void)
{
  if (gMonEffect.id != HORUS_THE_BLACK_FLAME_DRAGON_LV8)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV8Effect(void)
{
  Duel_ShowEffectTextTyped(HORUS_THE_BLACK_FLAME_DRAGON_LV8, 2);
}
