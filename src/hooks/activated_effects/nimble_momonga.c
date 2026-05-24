#include "global.h"
#include "common-chax.h"

void ActivateNimbleMomongaEffect(void)
{
  if ((gActiveEffect.turnRow == 6 && WhoseTurn() == DUEL_PLAYER) ||
      (gActiveEffect.turnRow == 7 && WhoseTurn() != DUEL_PLAYER))
    SetPlayerLifePointsToAdd(1000);
  else
    SetOpponentLifePointsToAdd(1000);

  HandleAtkAndLifePointsAction();

  if (gActiveEffect.turnRow == 6)
    GetGraveCardAndClearGrave(ACTIVE_DUELIST);
  else
    GetGraveCardAndClearGrave(INACTIVE_DUELIST);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = NIMBLE_MOMONGA;
    ActivateCardEffectText();
  }
}
