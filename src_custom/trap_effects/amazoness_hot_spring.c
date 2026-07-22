#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static void ActivateAMAZONESS_HOT_SPRINGZone(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;
  s8 empty;

  if (Duel_ActivateContinuousTrapPreamble(zone, AMAZONESS_HOT_SPRING)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* Activation adds one Amazoness monster from the deck to the controller's hand.
   * The other printed modes are intentionally omitted by this ruleset. */

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (Duel_IsAmazonessCard(gDuelDecks[fixedDuelist].cards[i])
        && GetTypeGroup(gDuelDecks[fixedDuelist].cards[i]) == TYPE_GROUP_MONSTER) {
      cardId = gDuelDecks[fixedDuelist].cards[i];
      deckIndex = i;
      break;
    }
  }

  if (cardId == CARD_NONE)
    return;

  if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
  UpdateDuelGfxExceptField();
}

void TryActivateAMAZONESS_HOT_SPRINGOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(AMAZONESS_HOT_SPRING,
                                         ActivateAMAZONESS_HOT_SPRINGZone);
}

