#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

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
  struct DuelCard *zone;
  u8 idx;

  if (gMonEffect.id != GREEN_GADGET)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GREEN_GADGET)
    return FALSE;

  /* Ceiling: once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return DeckHasRedGadget(&idx);
}

void ActivateGREEN_GADGETEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 deckIndex = 0;
  s8 empty;

  Duel_ShowEffectTextTyped(GREEN_GADGET, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0 || !DeckHasRedGadget(&deckIndex))
    return;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], RED_GADGET);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
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
