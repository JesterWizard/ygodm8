#include "global.h"
#include "common-chax.h"

void ActivateSkullMarkLadyBugEffect(void)
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
    gCardEffectTextData.cardId = SKULL_MARK_LADY_BUG;
    ActivateCardEffectText();
  }
}
