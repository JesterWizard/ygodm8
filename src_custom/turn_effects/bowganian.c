#include "global.h"
#include "common-chax.h"

unsigned char ShouldActivateBowganianTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != BOWGANIAN)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateBowganianTurnEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToSubtract(600);
  else
    SetPlayerLifePointsToSubtract(600);

  HandleAtkAndLifePointsAction();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = BOWGANIAN;
    ActivateCardEffectText();
  }
}
