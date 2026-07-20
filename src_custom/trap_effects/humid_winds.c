#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static const u8 sHumidPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

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

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaName);
}

static void SearchAroma(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 empty;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (IsAromaMonster(gDuelDecks[fixedDuelist].cards[i])) {
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
  (void)sHumidPickLabels;
}

static void ActivateHUMID_WINDSZone(struct DuelCard *zone)
{
  u16 myLp;
  u16 oppLp;

  if (Duel_ActivateContinuousTrapPreamble(zone, HUMID_WINDS) == DUEL_ACTION_DUEL_OVER)
    return;

  /* On flip: try pay 1000 → search Aroma (one-shot stand-in for OPT ignition). */
  myLp = gDuelLifePoints[FixedDuelistForTurnDuelist(INACTIVE_DUELIST)];
  if (myLp > 1000) {
    Duel_ChangeLp(INACTIVE_DUELIST, -1000, FALSE);
    SearchAroma();
  }

  myLp = gDuelLifePoints[FixedDuelistForTurnDuelist(INACTIVE_DUELIST)];
  oppLp = gDuelLifePoints[FixedDuelistForTurnDuelist(ACTIVE_DUELIST)];
  if (myLp < oppLp)
    Duel_ChangeLp(INACTIVE_DUELIST, 500, TRUE);

  UpdateDuelGfxExceptField();

  /* ponytail: each effect OPT as face-up ignition needs Main Phase hooks +
   * turn reset. Ceiling: one search+heal path on activate flip. */
}

void TryActivateHUMID_WINDSOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(HUMID_WINDS, ActivateHUMID_WINDSZone);
}
