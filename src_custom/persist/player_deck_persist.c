#include "global.h"
#include "player_deck_persist.h"
#include "constants/card_ids.h"

u8 PlayerDeckPersist_IsCompleteDeck(const u16 *cards, u16 numTotalCards) {
  u8 i;

  for (i = 0; i < PLAYER_DECK_PERSIST_CARD_COUNT; i++) {
    if (cards[i] == CARD_NONE || cards[i] >= numTotalCards)
      return FALSE;
  }

  return TRUE;
}

u8 PlayerDeckPersist_MagicIsValid(u8 magic) {
  return magic == PLAYER_DECK_PERSIST_MAGIC;
}
