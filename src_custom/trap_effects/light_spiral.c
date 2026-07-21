#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "light_spiral.h"
#include "removed_from_play.h"

static u8 sLightSpiralReentry APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void ActivateLIGHT_SPIRALZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, LIGHT_SPIRAL) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateLIGHT_SPIRALOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(LIGHT_SPIRAL, ActivateLIGHT_SPIRALZone);
}

void TryApplyLightSpiralAfterMill(u8 milledTurnDuelist, u8 count)
{
  u8 fixed;
  u8 oppTurn;
  u8 oppFixed;
  u8 top;
  u16 cardId;

  if (sLightSpiralReentry || count == 0 || IsDuelOver() == TRUE)
    return;

  fixed = FixedDuelistForTurnDuelist(milledTurnDuelist);
  if (Duel_FindBackrowCard(fixed, LIGHT_SPIRAL, TRUE) == NULL)
    return;

  if (!RemovedFromPlay_IsEnabled())
    return;

  oppTurn = milledTurnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  oppFixed = FixedDuelistForTurnDuelist(oppTurn);
  top = gDuelDecks[oppFixed].cardsDrawn;
  if (top >= NumCardsInDeck(oppFixed))
    return;

  cardId = gDuelDecks[oppFixed].cards[top];
  sLightSpiralReentry = TRUE;
  Duel_ShowEffectText(LIGHT_SPIRAL);
  if (Duel_RemoveDeckCardAt(oppTurn, top, FALSE) == DUEL_ACTION_OK)
    RemovedFromPlay_PushFixed(oppFixed, cardId);
  sLightSpiralReentry = FALSE;
}
