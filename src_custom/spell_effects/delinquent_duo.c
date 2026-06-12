#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "delinquent_duo.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);
extern unsigned IsTrapTriggered(void);

#define DELINQUENT_DUO_LP_COST 1000

static u8 CountCardsInOpponentHand(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      count++;

  return count;
}

u8 CanActivateDelinquentDuo(void)
{
  if (CountCardsInOpponentHand() == 0)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= DELINQUENT_DUO_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= DELINQUENT_DUO_LP_COST;
}

static void PayLpCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(DELINQUENT_DUO_LP_COST);
  else
    SetOpponentLifePointsToSubtract(DELINQUENT_DUO_LP_COST);
}

static void DiscardOpponentHandCard(u8 zone)
{
  ClearZoneAndSendMonToGraveyard(gTurnHands[INACTIVE_DUELIST][zone], INACTIVE_DUELIST);
}

static u8 PickRandomOpponentHandZone(void)
{
  u8 i;
  u8 occupied = CountCardsInOpponentHand();
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return 0xFF;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i]->id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return 0xFF;
}

static void ResolveForActivePlayer(void)
{
  s8 chosenZone;
  u8 randomZone;

  chosenZone = SelectExchangeHandCard(gTurnHands[INACTIVE_DUELIST]);

  if (chosenZone < 0)
    return;

  DiscardOpponentHandCard((u8)chosenZone);

  if (CountCardsInOpponentHand() > 0) {
    randomZone = PickRandomOpponentHandZone();
    if (randomZone != 0xFF)
      DiscardOpponentHandCard(randomZone);
  }

  ShowExchangeOpponentHandResult();
}

static void ResolveForInactivePlayer(void)
{
  u8 chosenZone;

  chosenZone = PickRandomOpponentHandZone();
  if (chosenZone == 0xFF)
    return;

  DiscardOpponentHandCard(chosenZone);

  if (CountCardsInOpponentHand() > 0) {
    chosenZone = PickRandomOpponentHandZone();
    if (chosenZone != 0xFF)
      DiscardOpponentHandCard(chosenZone);
  }
}

APPEND_TEXT void EffectDelinquentDuo(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    if (!CanActivateDelinquentDuo())
      return;

    ClearZoneAndSendMonToGraveyard(
        gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    PayLpCost();
    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    if (IsDuelOver() == TRUE)
      return;

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = DELINQUENT_DUO;
      ActivateCardEffectText();
    }

    if (IsDuelOver() == TRUE)
      return;

    if (WhoseTurn() == DUEL_PLAYER)
      ResolveForActivePlayer();
    else
      ResolveForInactivePlayer();
  } else {
    ActivateTrapEffect(DELINQUENT_DUO_LP_COST);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
