#include "global.h"
#include "common-chax.h"

unsigned char CanActivateCyberStein(void)
{
  if (gMonEffect.id != CYBER_STEIN)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 5000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 5000;
}

void __attribute__((section(".append_text"))) EffectCyberStein(void)
{
  u8 turn = WhoseTurn();

  if (turn == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(5000);
  else
    SetOpponentLifePointsToSubtract(5000);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) > 0)
  {
    u8 emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);

    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->id = BLUE_EYES_ULTIMATE_DRAGON;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->isFaceUp = TRUE;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->isLocked = TRUE;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->isDefending = FALSE;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->permStage = 0;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->tempStage = 0;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->unk4 = 0;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->unkTwo = 0;
    gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]->willChangeSides = 0;
  }

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = CYBER_STEIN;
    ActivateCardEffectText();
  }
}
