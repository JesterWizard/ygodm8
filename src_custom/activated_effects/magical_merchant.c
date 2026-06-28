#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

extern void UpdateDuelGfxExceptField(void);

static u8 OwnerTurnDuelist(void)
{
  if (gMonEffect.row == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (gMonEffect.row == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 OwnerFixedDuelist(void)
{
  u8 turnDuelist = OwnerTurnDuelist();

  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpellOrTrap(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_SPELL || GetTypeGroup(cardId) == TYPE_GROUP_TRAP;
}

static u8 DeckHasSpellOrTrapRemaining(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (IsSpellOrTrap(gDuelDecks[fixedDuelist].cards[i]))
      return TRUE;
  }

  return FALSE;
}

static void SendTopDeckCardToGraveyard(u8 fixedDuelist)
{
  u8 turnDuelist;
  u16 card;

  if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist))
    return;

  card = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];
  gDuelDecks[fixedDuelist].cardsDrawn++;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist]) {
      GraveyardExpand_PushTurn(turnDuelist, card);
      break;
    }
  }
}

unsigned char CanActivateMagicalMerchant(void)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (gMonEffect.id != MAGICAL_MERCHANT)
    return FALSE;

  if (gMonEffect.row != ACTIVE_DUELIST_MONSTER_ROW && gMonEffect.row != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  fixedDuelist = OwnerFixedDuelist();
  turnDuelist = OwnerTurnDuelist();

  if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  if (DeckHasSpellOrTrapRemaining(fixedDuelist)
      && NumEmptyZonesInRow(gTurnHands[turnDuelist]) == 0)
    return FALSE;

  return TRUE;
}

void ActivateMagicalMerchantEffect(void)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 card;

  fixedDuelist = OwnerFixedDuelist();
  turnDuelist = OwnerTurnDuelist();

  Duel_ShowEffectTextTyped(MAGICAL_MERCHANT, 2);

  while (gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist)) {
    card = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];

    if (IsSpellOrTrap(card)) {
      Duel_DrawCards(turnDuelist, 1, FALSE);
      break;
    }

    SendTopDeckCardToGraveyard(fixedDuelist);

    if (IsDuelOver() == TRUE)
      return;
  }

  UpdateDuelGfxExceptField();
}
