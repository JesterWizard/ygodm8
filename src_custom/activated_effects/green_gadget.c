#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
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

static u8 DeckHasRedGadget(u8 *outIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == RED_GADGET) {
      *outIndex = i;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateGREEN_GADGET(void)
{
  if (gMonEffect.id != GREEN_GADGET)
    return FALSE;

  /* On-summon add Red Gadget via TryGreenGadgetOnMonsterPlacement. */
  return FALSE;
}

void ActivateGREEN_GADGETEffect(void)
{
  Duel_ShowEffectTextTyped(GREEN_GADGET, 2);
}

void TryGreenGadgetOnMonsterPlacement(struct DuelCard *zone)
{
  u8 deckIndex = 0;
  s8 empty;
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != GREEN_GADGET)
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;

  empty = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (empty < 0 || !DeckHasRedGadget(&deckIndex))
    return;

  Duel_ShowEffectTextTyped(GREEN_GADGET, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[turnDuelist][empty], RED_GADGET);
  UpdateDuelGfxExceptField();
}
