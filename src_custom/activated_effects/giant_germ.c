#include "global.h"
#include "common-chax.h"

void ActivateGiantGermEffect(void)
{
  if ((gActiveEffect.turnRow == 6 && WhoseTurn() == DUEL_PLAYER) ||
      (gActiveEffect.turnRow == 7 && WhoseTurn() != DUEL_PLAYER))
    SetOpponentLifePointsToSubtract(500);
  else
    SetPlayerLifePointsToSubtract(500);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (gActiveEffect.turnRow == 6)
    GetGraveCardAndClearGrave(ACTIVE_DUELIST);
  else
    GetGraveCardAndClearGrave(INACTIVE_DUELIST);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = GIANT_GERM;
    ActivateCardEffectText();
  }
}
