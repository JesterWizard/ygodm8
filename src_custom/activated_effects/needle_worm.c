#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateNeedleWormEffect(void)
{
  u8 i;

  for (i = 0; i < 5; i++) {
    if (Duel_MillTopDeckCards(INACTIVE_DUELIST, 1, FALSE) != DUEL_ACTION_OK)
      break;
  }

  Duel_ShowEffectTextTyped(NEEDLE_WORM, 2);
}
