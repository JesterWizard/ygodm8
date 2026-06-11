#include "global.h"
#include "common-chax.h"

unsigned char ShouldActivateCureMermaidTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != CURE_MERMAID)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateCureMermaidTurnEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToAdd(800);
  else
    SetOpponentLifePointsToAdd(800);

  HandleAtkAndLifePointsAction();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = CURE_MERMAID;
    ActivateCardEffectText();
  }
}
