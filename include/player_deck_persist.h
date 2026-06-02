#ifndef GUARD_PLAYER_DECK_PERSIST_H
#define GUARD_PLAYER_DECK_PERSIST_H

#include "gba/types.h"

#define PLAYER_DECK_PERSIST_MAGIC 0xD5
#define PLAYER_DECK_PERSIST_CARD_COUNT 40

u8 PlayerDeckPersist_IsCompleteDeck(const u16 *cards, u16 numTotalCards);
u8 PlayerDeckPersist_MagicIsValid(u8 magic);

#endif
