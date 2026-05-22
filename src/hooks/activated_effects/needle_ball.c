#include "global.h"
#include "common-chax.h"

unsigned char CanActivateNeedleBall(void) {
  if (gMonEffect.id != NEEDLE_BALL)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 2000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 2000;
}

void ActivateNeedleBallEffect(void) {
  if (WhoseTurn() == DUEL_PLAYER) {
    SetPlayerLifePointsToSubtract(2000);
    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    SetOpponentLifePointsToSubtract(1000);
  }
  else {
    SetOpponentLifePointsToSubtract(2000);
    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    SetPlayerLifePointsToSubtract(1000);
  }

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = NEEDLE_BALL;
    ActivateCardEffectText();
  }
}
