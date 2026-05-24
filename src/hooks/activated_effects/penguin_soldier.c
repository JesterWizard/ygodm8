#include "global.h"
#include "common-chax.h"

unsigned char CanActivatePenguinSoldier(void)
{
  u8 enemyRow;
  u8 i;

  if (gMonEffect.id != PENGUIN_SOLDIER)
    return FALSE;

  if (gMonEffect.row != 1 && gMonEffect.row != 2)
    return FALSE;

  if (NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  enemyRow = (gMonEffect.row == 1) ? 2 : 1;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[enemyRow][i]->id != CARD_NONE)
      return TRUE;

  return FALSE;
}

static unsigned char ReturnEnemyMonsterToOpponentHand(u8 enemyRow)
{
  u8 sourceZone;
  u8 destZone;

  if (NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  for (sourceZone = 0; sourceZone < MAX_ZONES_IN_ROW; sourceZone++)
  {
    if (gTurnZones[enemyRow][sourceZone]->id == CARD_NONE)
      continue;

    destZone = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
    CopyCard(gTurnHands[INACTIVE_DUELIST][destZone], gTurnZones[enemyRow][sourceZone]);
    gTurnHands[INACTIVE_DUELIST][destZone]->isFaceUp = FALSE;
    gTurnHands[INACTIVE_DUELIST][destZone]->isLocked = FALSE;
    gTurnHands[INACTIVE_DUELIST][destZone]->isDefending = FALSE;
    gTurnHands[INACTIVE_DUELIST][destZone]->unkTwo = 0;
    gTurnHands[INACTIVE_DUELIST][destZone]->unkThree = 0;
    gTurnHands[INACTIVE_DUELIST][destZone]->unk4 = 0;
    gTurnHands[INACTIVE_DUELIST][destZone]->willChangeSides = FALSE;
    ResetPermStage(gTurnHands[INACTIVE_DUELIST][destZone]);
    ResetTempStage(gTurnHands[INACTIVE_DUELIST][destZone]);
    ClearZone(gTurnZones[enemyRow][sourceZone]);
    return TRUE;
  }

  return FALSE;
}

void ActivatePenguinSoldierEffect(void)
{
  u8 enemyRow = (gMonEffect.row == 1) ? 2 : 1;
  u8 returned = 0;

  while (returned < 2 && ReturnEnemyMonsterToOpponentHand(enemyRow))
    returned++;

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = PENGUIN_SOLDIER;
    ActivateCardEffectText();
  }
}