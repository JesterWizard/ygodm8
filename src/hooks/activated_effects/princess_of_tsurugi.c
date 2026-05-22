#include "global.h"
#include "common-chax.h"

void __attribute__((section(".append_text"))) ActivatePrincessOfTsurugiEffect(void)
{
  u8 i;
  u16 damage = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gTurnZones[0][i]->id != CARD_NONE)
      damage += 500;
  }

  if (damage > 0)
  {
    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToSubtract(damage);
    else
      SetPlayerLifePointsToSubtract(damage);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();
  }

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = PRINCESS_OF_TSURUGI;
    ActivateCardEffectText();
  }
}
