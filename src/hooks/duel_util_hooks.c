#include "global.h"
#include "configs/runtime.h"
#include "custom_decks/custom_decks.h"

extern int NumCardsInDeck(unsigned char);
extern struct DuelDeck gDuelDecks[2];
extern void DeclareLoser(unsigned char);
void InitCardsForDuelDeck(unsigned char, unsigned short *);
void InitDuelDeck(unsigned char, unsigned char);

static void CopyDuelDeckCards(unsigned char duelist, const unsigned short *deck) {
  unsigned i;

  for (i = 0; i < 40; i++)
    gDuelDecks[duelist].cards[i] = deck[i];
}

LYN_REPLACE_CHECK(InitDuelDeck);
void InitDuelDeck__Replacement(unsigned char duelist, unsigned char duelistId) {
  const u16 *deck = NULL;
  const u16 *pendingDeck = NULL;

  if (duelistId == DUEL_PLAYER) {
    deck = gDeckMenu.cards;
  } else if (CustomDecks_IsEnabled() == TRUE) {
    pendingDeck = CustomDecks_GetPendingCardShopDuelDeck();
    deck = pendingDeck;
  }

  if (deck == NULL)
    deck = gDuelData.duelist.deck;

  InitCardsForDuelDeck(duelist, (unsigned short *)deck);

  if (pendingDeck != NULL)
    CustomDecks_ClearPendingCardShopDuel();
}

LYN_REPLACE_CHECK(NumFaceUpMatchingAttributeInRow);
unsigned NumFaceUpMatchingAttributeInRow__Replacement(unsigned char turnRow, unsigned char attribute) {
  u8 i, count = 0;

  if (gRuntimeConfig.disable_element_system == TRUE)
    return 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[turnRow][i]->id == CARD_NONE || !gTurnZones[turnRow][i]->isFaceUp)
      continue;
    SetCardInfo(gTurnZones[turnRow][i]->id);
    if (gCardInfo.attribute == attribute)
      count++;
  }

  return count;
}

LYN_REPLACE_CHECK(TryDrawingCard);
void TryDrawingCard__Replacement(unsigned turn) {
  unsigned char i;
  unsigned short cardDrawn;
  unsigned char turn_u8 = turn;

  if (turn_u8 == DUEL_PLAYER && gDuelDecks[turn_u8].cardsDrawn == 0) {
    u16 cardId = gRuntimeConfig.card_in_hand;
    u16 deckSize = NumCardsInDeck(turn_u8);

    if (cardId != CARD_NONE) {
      for (i = 0; i < deckSize; i++) {
        if (gDuelDecks[turn_u8].cards[i] != cardId)
          continue;

        gDuelDecks[turn_u8].cards[i] = gDuelDecks[turn_u8].cards[0];
        gDuelDecks[turn_u8].cards[0] = cardId;
        break;
      }
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[turn_u8][i].id != CARD_NONE)
      continue;
    if ((unsigned char)NumCardsInDeck(turn_u8) < gDuelDecks[turn_u8].cardsDrawn)
      cardDrawn = CARD_NONE;
    else {
      cardDrawn = gDuelDecks[turn_u8].cards[gDuelDecks[turn_u8].cardsDrawn];
      gDuelDecks[turn_u8].cardsDrawn++;
    }
    if (cardDrawn != CARD_NONE)
      gDuel.hands[turn_u8][i].id = cardDrawn;
    else
      DeclareLoser(turn_u8); // deck out
    break;
  }
}
