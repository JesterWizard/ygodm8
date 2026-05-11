#include "global.h"
#include "configs/runtime.h"

extern const unsigned char gStarterTrunk[];
extern unsigned char gTrunkCardQty[];
extern unsigned char gTotalCardQty[];
extern unsigned char gUnk_8DFA6A8[];

void InitTrunkData(void);
void TrunkMenuDefaultSort(void);
void ApplyNewSortMode(unsigned char);
void SortCardsAccordingToContext(void);
unsigned char GetDeckCardQty(unsigned short);

LYN_REPLACE_CHECK(InitTrunkCards);
void InitTrunkCards__Replacement(void) {
  u32 id;

  for (id = 0; id < NUM_CARDS; id++) {
    if (gRuntimeConfig.start_with_three_copies_of_every_card == TRUE)
      gTrunkCardQty[id] = 3;
    else if (id >= NUM_VANILLA_CARDS)
      gTrunkCardQty[id] = 0;
    else
      gTrunkCardQty[id] = gStarterTrunk[id];
  }
}

static void InitCustomTrunkCards(void) {
  u32 id;
  u8 deckQty;
  u8 totalQty;

  if (gRuntimeConfig.start_with_three_copies_of_every_card != TRUE)
    return;

  for (id = CUSTOM_CARD_START; id < NUM_CARDS; id++) {
    deckQty = GetDeckCardQty(id);
    totalQty = gTrunkCardQty[id] + deckQty;
    if (totalQty < 3)
      gTrunkCardQty[id] += 3 - totalQty;
  }
}

LYN_REPLACE_CHECK(InitTrunkData);
void InitTrunkData__Replacement(void) {
  u16 cardId;

  InitCustomTrunkCards();

  gTrunkMenu.currentPos = 0;
  gTrunkMenu.displayMode = 1;
  gTrunkMenu.sortMode = CARD_SORT_NUMBER;

  for (cardId = 0; cardId < NUM_CARDS; cardId++)
    gTotalCardQty[cardId] = gTrunkCardQty[cardId] + GetDeckCardQty(cardId);

  for (cardId = 0; cardId < NUM_TRUE_CARDS; cardId++)
    gTrunkMenu.cards[cardId] = cardId + 1;
}

static u8 ShouldPinCustomCard(u16 cardId) {
  return cardId >= CUSTOM_CARD_START && cardId < NUM_CARDS && gTotalCardQty[cardId];
}

static void PinOwnedCustomCardsInTrunk(void) {
  s16 read;
  u16 write = 0;
  u16 cardId;

  for (cardId = CUSTOM_CARD_START; cardId < NUM_CARDS; cardId++) {
    if (!ShouldPinCustomCard(cardId))
      continue;

    for (read = 0; read < NUM_TRUE_CARDS; read++)
      if (gTrunkMenu.cards[read] == cardId)
        break;

    if (read >= NUM_TRUE_CARDS)
      read = NUM_TRUE_CARDS - 1;

    for (; read > write; read--)
      gTrunkMenu.cards[read] = gTrunkMenu.cards[read - 1];

    gTrunkMenu.cards[write++] = cardId;
  }
}

LYN_REPLACE_CHECK(TrunkMenuDefaultSort);
void TrunkMenuDefaultSort__Replacement(void) {
  gCardSortContext.cards = gTrunkMenu.cards;
  gCardSortContext.cardCount = NUM_TRUE_CARDS;
  gCardSortContext.sortMode = gUnk_8DFA6A8[gTrunkMenu.sortMode];
  SortCardsAccordingToContext();
  PinOwnedCustomCardsInTrunk();
}

LYN_REPLACE_CHECK(ApplyNewSortMode);
void ApplyNewSortMode__Replacement(unsigned char val) {
  gCardSortContext.cards = gTrunkMenu.cards;
  gCardSortContext.cardCount = NUM_TRUE_CARDS;
  gCardSortContext.sortMode = gUnk_8DFA6A8[val];
  SortCardsAccordingToContext();
  PinOwnedCustomCardsInTrunk();
  gTrunkMenu.currentPos = 0;
}
