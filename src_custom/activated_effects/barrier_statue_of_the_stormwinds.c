#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateBARRIER_STATUE_OF_THE_STORMWINDS(void)
{
  if (gMonEffect.id != BARRIER_STATUE_OF_THE_STORMWINDS)
    return FALSE;

  /* WIND-only Special Summon lock via BarrierStatueOfTheStormwinds_BlocksSpecialSummon. */
  return FALSE;
}

void ActivateBARRIER_STATUE_OF_THE_STORMWINDSEffect(void)
{
  Duel_ShowEffectTextTyped(BARRIER_STATUE_OF_THE_STORMWINDS, 2);
}
