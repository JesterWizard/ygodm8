#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTYRANT_BURST_DRAGON(void)
{
  if (gMonEffect.id != TYRANT_BURST_DRAGON)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * Not field-ignition. */
  return FALSE;
}

void ActivateTYRANT_BURST_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(TYRANT_BURST_DRAGON, 2);
}
