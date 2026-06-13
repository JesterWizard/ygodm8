#include "global.h"
#include "common-chax.h"

void ActivateStealthBirdEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToSubtract(1000);
  else
    SetPlayerLifePointsToSubtract(1000);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = STEALTH_BIRD;
    ActivateCardEffectText();
  }
}
