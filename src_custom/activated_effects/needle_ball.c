#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char CanActivateNeedleBall(void) {
  if (gMonEffect.id != NEEDLE_BALL)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 2000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 2000;
}

void ActivateNeedleBallEffect(void) {
  u8 opponent = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (Duel_ChangeLp(WhoseTurn(), -2000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(opponent, -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(NEEDLE_BALL, 2);
}
