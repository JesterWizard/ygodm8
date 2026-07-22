#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

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

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 IsSearchTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == DARK_MAGICIAN)
    return TRUE;

  SetCardInfo(cardId);
  if (gCardInfo.color == RITUAL_CARD)
    return FALSE;

  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static u16 FindSearchTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN) >= 0)
    return DARK_MAGICIAN;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSearchTarget(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 AddSearchTargetToHand(u16 cardId)
{
  s8 handZone;
  s16 deckIndex;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0 || cardId == CARD_NONE)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

static u8 PlaceOneHandCardOnDeckTop(u8 skipHandZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  u8 fixedDuelist = FixedDuelistForActive();

  for (i = 0; i < max; i++) {
    struct DuelCard *slot;
    u16 cardId;

    if (i == skipHandZone)
      continue;

    slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);
    if (slot == NULL || slot->id == CARD_NONE)
      continue;

    cardId = slot->id;
    ClearZone(slot);
    ReturnCardToDeckTop(fixedDuelist, cardId);
    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateILLUSION_OF_CHAOS(void)
{
  if (gMonEffect.id != ILLUSION_OF_CHAOS)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateILLUSION_OF_CHAOSEffect(void)
{
  Duel_ShowEffectTextTyped(ILLUSION_OF_CHAOS, 2);
}

u8 CanActivateIllusionOfChaosFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  if (handZone >= max)
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ILLUSION_OF_CHAOS)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  /* After add, place 1 hand card on top (added card always available). */
  return FindSearchTargetInDeck() != CARD_NONE;
}

u8 TryActivateIllusionOfChaosFromHand(u8 handZone)
{
  u16 searchId;

  if (!CanActivateIllusionOfChaosFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ILLUSION_OF_CHAOS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  searchId = FindSearchTargetInDeck();
  if (searchId == CARD_NONE)
    return FALSE;

  if (!AddSearchTargetToHand(searchId))
    return FALSE;

  /* Place 1 hand card on top (prefer non-self; else the added card). */
  if (!PlaceOneHandCardOnDeckTop(handZone))
    PlaceOneHandCardOnDeckTop(0xFF);

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateIllusionOfChaosFromHand(u8 handZone);
u8 TryActivateIllusionOfChaosFromHand(u8 handZone);
#endif
