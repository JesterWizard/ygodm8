#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateBowganianTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(BOWGANIAN, FALSE, FALSE);
}

void ActivateBowganianTurnEffect(void)
{
  if (Duel_ChangeLp(1 - WhoseTurn(), -600, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(BOWGANIAN, 9);
}
