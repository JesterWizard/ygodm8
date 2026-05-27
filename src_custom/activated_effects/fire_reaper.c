#include "global.h"
#include "common-chax.h"

void ActivateFireReaperEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToSubtract(500);
  else
    SetPlayerLifePointsToSubtract(500);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = FIRE_REAPER;
    ActivateCardEffectText();
  }
}
