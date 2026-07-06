#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "delinquent_duo.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define DELINQUENT_DUO_LP_COST 1000

u8 CanActivateDelinquentDuo(void)
{
  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= DELINQUENT_DUO_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= DELINQUENT_DUO_LP_COST;
}

static void ResolveForActivePlayer(void)
{
  s8 chosenZone;
  s8 randomZone;

  chosenZone = SelectExchangeHandCard(gTurnHands[INACTIVE_DUELIST]);

  if (chosenZone < 0)
    return;

  Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][chosenZone], INACTIVE_DUELIST, FALSE);

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0) {
    randomZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);
    if (randomZone >= 0)
      Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][randomZone], INACTIVE_DUELIST, FALSE);
  }

  ShowExchangeOpponentHandResult();
}

static void ResolveForInactivePlayer(void)
{
  s8 chosenZone;

  chosenZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);
  if (chosenZone < 0)
    return;

  Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][chosenZone], INACTIVE_DUELIST, FALSE);

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0) {
    chosenZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);
    if (chosenZone >= 0)
      Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][chosenZone], INACTIVE_DUELIST, FALSE);
  }
}

static void DelinquentDuo_ResolveBody(void)
{
  if (!CanActivateDelinquentDuo())
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -DELINQUENT_DUO_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_ShowEffectText(DELINQUENT_DUO);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    ResolveForActivePlayer();
  else
    ResolveForInactivePlayer();
}

APPEND_TEXT void EffectDelinquentDuo(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(DELINQUENT_DUO, DELINQUENT_DUO_LP_COST,
                                         DelinquentDuo_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
