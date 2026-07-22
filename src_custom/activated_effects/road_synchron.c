#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateROAD_SYNCHRON(void)
{
  if (gMonEffect.id != ROAD_SYNCHRON)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateROAD_SYNCHRONEffect(void)
{
  Duel_ShowEffectTextTyped(ROAD_SYNCHRON, 2);
}
