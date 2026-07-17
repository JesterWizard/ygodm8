#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateAllDuelGfx(void);

static u8 CanActivateExchange(void)
{
  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  if (NumEmptyZonesInRow(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return TRUE;
}

static void RevealHandCards(u8 duelist)
{
  u8 i;
  u8 fixedDuelist;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[duelist][i]->id != CARD_NONE)
      gTurnHands[duelist][i]->isFaceUp = TRUE;
  }

  if (!IsSixCardHandEnabled())
    return;

  fixedDuelist = SixCardHand_FixedDuelistForHandRow(gTurnHands[duelist]);
  if (fixedDuelist != 0xFF && gHandExtraSlots[fixedDuelist].id != CARD_NONE)
    gHandExtraSlots[fixedDuelist].isFaceUp = TRUE;
}

static void TransferHandCard(u8 srcDuelist, u8 srcZone, u8 dstDuelist, u8 dstZone, u8 faceUp)
{
  struct DuelCard *dst = SixCardHand_ZoneAtHandRow(gTurnHands[dstDuelist], dstZone);
  struct DuelCard *src = SixCardHand_ZoneAtHandRow(gTurnHands[srcDuelist], srcZone);

  CopyCard(dst, src);
  dst->isFaceUp = faceUp;
  dst->isLocked = FALSE;
  dst->isDefending = FALSE;
  dst->unkTwo = 0;
  dst->unkThree = 0;
  dst->unk4 = 0;
  dst->willChangeSides = FALSE;
  ResetPermStage(dst);
  ResetTempStage(dst);
  ClearZone(src);
}

static u8 PickRandomHandZone(struct DuelCard **handRow)
{
  u8 i;
  u8 occupied = Duel_CountCardsInHand(handRow);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return 0xFF;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return 0xFF;
}

static void ResolveExchangeForActivePlayer(void)
{
  s8 takenZone;
  u8 givenZone;
  u8 receiveZone;

  RevealHandCards(INACTIVE_DUELIST);
  takenZone = SelectExchangeHandCard(gTurnHands[INACTIVE_DUELIST]);

  if (takenZone < 0)
    return;

  givenZone = PickRandomHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (givenZone == 0xFF)
    return;

  receiveZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  TransferHandCard(INACTIVE_DUELIST, takenZone, ACTIVE_DUELIST, receiveZone, FALSE);
  TransferHandCard(ACTIVE_DUELIST, givenZone, INACTIVE_DUELIST, takenZone, TRUE);

  RevealHandCards(INACTIVE_DUELIST);
  ShowExchangeOpponentHandResult();
}

static void ResolveExchangeForInactivePlayer(void)
{
  u8 takenZone;
  u8 givenZone;
  u8 receiveZone;

  takenZone = PickRandomHandZone(gTurnHands[INACTIVE_DUELIST]);
  if (takenZone == 0xFF)
    return;

  givenZone = PickRandomHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (givenZone == 0xFF)
    return;

  receiveZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  TransferHandCard(INACTIVE_DUELIST, takenZone, ACTIVE_DUELIST, receiveZone, FALSE);
  TransferHandCard(ACTIVE_DUELIST, givenZone, INACTIVE_DUELIST, takenZone, TRUE);

  UpdateAllDuelGfx();
}

APPEND_TEXT void EffectExchange(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (!CanActivateExchange())
    return;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = EXCHANGE;
    gCardEffectTextData.cardId2 = 0;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    ResolveExchangeForActivePlayer();
  else
    ResolveExchangeForInactivePlayer();
}
