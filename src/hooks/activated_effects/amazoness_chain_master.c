#include "global.h"
#include "common-chax.h"

static unsigned char CanStealFromOpponentHand(void)
{
  u8 i;
  u8 occupied = 0;

  if (NumEmptyZonesInRow(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      occupied++;

  return occupied > 0;
}

unsigned char CanActivateAmazonessChainMaster(void)
{
  if (gMonEffect.id != AMAZON_CHAIN_MASTER)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 1000 && CanStealFromOpponentHand();

  return gDuelLifePoints[DUEL_OPPONENT] >= 1000 && CanStealFromOpponentHand();
}

static void TransferRandomOpponentHandCard(void)
{
  u8 i;
  u8 chosen = 0;
  u8 occupied = 0;
  u8 taken = 0;
  u8 destZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      occupied++;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gTurnHands[INACTIVE_DUELIST][i]->id == CARD_NONE)
      continue;

    if (taken == chosen)
    {
      CopyCard(gTurnHands[ACTIVE_DUELIST][destZone], gTurnHands[INACTIVE_DUELIST][i]);
      gTurnHands[ACTIVE_DUELIST][destZone]->isFaceUp = FALSE;
      gTurnHands[ACTIVE_DUELIST][destZone]->isLocked = FALSE;
      gTurnHands[ACTIVE_DUELIST][destZone]->isDefending = FALSE;
      gTurnHands[ACTIVE_DUELIST][destZone]->unkTwo = 0;
      gTurnHands[ACTIVE_DUELIST][destZone]->unkThree = 0;
      gTurnHands[ACTIVE_DUELIST][destZone]->unk4 = 0;
      gTurnHands[ACTIVE_DUELIST][destZone]->willChangeSides = FALSE;
      ResetPermStage(gTurnHands[ACTIVE_DUELIST][destZone]);
      ResetTempStage(gTurnHands[ACTIVE_DUELIST][destZone]);
      ClearZone(gTurnHands[INACTIVE_DUELIST][i]);
      return;
    }

    taken++;
  }
}

void ActivateAmazonessChainMasterEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(1000);
  else
    SetOpponentLifePointsToSubtract(1000);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (CanStealFromOpponentHand())
    TransferRandomOpponentHandCard();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = AMAZON_CHAIN_MASTER;
    ActivateCardEffectText();
  }
}
