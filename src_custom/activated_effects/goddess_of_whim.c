#include "global.h"
#include "common-chax.h"

void ActivateGoddessOfWhimEffect(void)
{
  u8 turn = WhoseTurn();

  if (turn == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(500);
  else
    SetOpponentLifePointsToSubtract(500);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  TryDrawingCard(turn);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = GODDESS_OF_WHIM;
    ActivateCardEffectText();
  }
}
