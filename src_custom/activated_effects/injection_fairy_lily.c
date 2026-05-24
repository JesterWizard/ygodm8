#include "global.h"
#include "common-chax.h"

unsigned char CanActivateInjectionFairyLily(void) {
  if (gMonEffect.id != INJECTION_FAIRY_LILY)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 3000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 3000;
}

void ActivateInjectionFairyLilyEffect(void) {
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(3000);
  else
    SetOpponentLifePointsToSubtract(3000);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  for (i = 0; i < 4; i++)
    IncrementPermStage(gTurnZones[gMonEffect.row][gMonEffect.zone]);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = INJECTION_FAIRY_LILY;
    ActivateCardEffectText();
  }
}
