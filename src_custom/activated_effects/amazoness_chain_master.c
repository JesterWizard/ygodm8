#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

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
      CopyCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)(destZone)), gTurnHands[INACTIVE_DUELIST][i]);
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->isFaceUp = FALSE;
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->isLocked = FALSE;
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->isDefending = FALSE;
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->unkTwo = 0;
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->unkThree = 0;
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->unk4 = 0;
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone)->willChangeSides = FALSE;
      ResetPermStage(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone));
      ResetTempStage(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], destZone));
      ClearZone(gTurnHands[INACTIVE_DUELIST][i]);
      return;
    }

    taken++;
  }
}

void ActivateAmazonessChainMasterEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (CanStealFromOpponentHand())
    TransferRandomOpponentHandCard();

  Duel_ShowEffectTextTyped(AMAZON_CHAIN_MASTER, 2);
}
