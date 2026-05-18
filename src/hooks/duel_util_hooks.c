#include "global.h"
#include "common-chax.h"
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


static inline u8 sub_8052268_inline(int y, int x) {
  u8 temp = 0;
  if (y <= 0)
    if (y >= -8)
      temp = 1;
  if (x <= 4)
    if (x >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_8052298_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 8)
    if (x >= 0)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522C0_inline(int y, int x) {
  u8 temp = 0;
  if (y <= 8)
    if (y >= 0)
      temp = 1;
  if (x <= 4)
    if (x >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522E8_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 0)
    if (x >= -8)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

s8 GetObjectIdInFrontOfPlayer(u8 x, u8 y, u8 playerDirection) {
  u8 i, objExists;

  for (i = 1; i < 15; i++) {
    switch (playerDirection) {
      case 0:
        objExists = sub_8052268_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      case 1:
        objExists = sub_8052298_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      case 2:
        objExists = sub_80522C0_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      default:
        objExists = sub_80522E8_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
    }
    if (objExists)
      return i;
  }
  return -1;
}

LYN_REPLACE_CHECK(InitDuelDeck);
void InitDuelDeck__Replacement(unsigned char duelist, u16 duelistId) {
  const u16 *deck;

  if (!duelistId)
    deck = gDeckMenu.cards; // player deck
  else {
    switch (GetTalkingUnitSprite()) {
      case SPRITE_TEA:
        deck = TeaCustomDeck_GetDuelDeck();
        break;
      default:
        deck = gDuelData.duelist.deck;
        break;
    }
  }

  InitCardsForDuelDeck(duelist, (unsigned short *)deck);
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
