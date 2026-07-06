#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define DANCING_FAIRY_STANDBY_HEAL 1000

unsigned char ShouldActivateDancingFairyTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(DANCING_FAIRY, TRUE, FALSE);
}

void ActivateDancingFairyTurnEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), DANCING_FAIRY_STANDBY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(DANCING_FAIRY, 9);
}
