#include "global.h"
#include "configs/runtime.h"

extern unsigned gDeckCapacity;
extern unsigned gDuelistLevel;
void CalculateCurrentDeckCost(void);
void AddCardToDeck(unsigned short);
unsigned char IsPlayerDeckFull(void);

static u8 GetRuntimeDeckLimit(void) {
  u8 limit = gRuntimeConfig.max_deck_cards;

  if (limit == 0 || limit > DECK_SIZE)
    return DECK_SIZE;
  return limit;
}

LYN_REPLACE_CHECK(InitDeckCapacity);
void InitDeckCapacity__Replacement(void) {
  gDeckCapacity = 1600;

  if (gRuntimeConfig.max_deck_capacity_at_start == TRUE)
    gDeckCapacity = 65000;
}

LYN_REPLACE_CHECK(InitDuelistLevel);
void InitDuelistLevel__Replacement(void) {
  gDuelistLevel = 72;

  if (gRuntimeConfig.max_duelist_level_at_start == TRUE)
    gDuelistLevel = 999;
}

LYN_REPLACE_CHECK(AddCardToDeck);
void AddCardToDeck__Replacement(unsigned short cardId) {
  unsigned limit = GetRuntimeDeckLimit();

  if (gDeckMenu.cardCount >= limit)
    return;

  gDeckMenu.cards[gDeckMenu.cardCount] = cardId;
  gDeckMenu.cardCount++;
  CalculateCurrentDeckCost();
}

LYN_REPLACE_CHECK(IsPlayerDeckFull);
unsigned char IsPlayerDeckFull__Replacement(void) {
  return gDeckMenu.cardCount >= GetRuntimeDeckLimit();
}
