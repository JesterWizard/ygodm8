#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateCYBER_KIRIN(void)
{
  /* ATK-position spell/trap negate, battle-draw, and OPT tribute damage
   * zero need continuous/battle/tribute hooks not wired for permanents. */
  return FALSE;
}

void ActivateCYBER_KIRIN(void)
{
}
