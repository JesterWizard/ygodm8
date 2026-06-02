#ifndef GUARD_PLAYER_DECKS_H
#define GUARD_PLAYER_DECKS_H

#include "gba/types.h"

#define PLAYER_DECK_COUNT 3
#define PLAYER_DECK_INDEX_MIN 1
#define PLAYER_DECK_INDEX_MAX 3
#define PLAYER_DECK_CARD_BYTES 0x50

extern u16 gPlayerDeck1Cards[40];
extern u16 gPlayerDeck2Cards[40];
extern u16 gPlayerDeck3Cards[40];
extern u8 gActiveDeckIndex;
extern u8 gPlayerDeckSaveRestoreActiveDeck;

extern u16 gPlayerDeck2CardsFlashPrimary[40];
extern u16 gPlayerDeck2CardsFlashBackup[40];
extern u16 gPlayerDeck3CardsFlashPrimary[40];
extern u16 gPlayerDeck3CardsFlashBackup[40];
extern u8 gActiveDeckIndexFlashPrimary;
extern u8 gActiveDeckIndexFlashBackup;
extern u8 gPlayerDeckSaveMagicFlashPrimary;
extern u8 gPlayerDeckSaveMagicFlashBackup;

u8 PlayerDecks_IsEnabled(void);
u8 PlayerDecks_GetActiveIndex(void);
u8 PlayerDecks_GetTotalDeckCardQty(u16 cardId);
void PlayerDecks_FlushActive(void);
void PlayerDecks_SetActiveAndLoad(u8 deckIndex);
void PlayerDecks_InitNewGame(void);
void PlayerDecks_OnSaveSlotWrite(void);
void PlayerDecks_OnSaveSlotWriteBackup(void);
void PlayerDecks_OnSaveSlotRead(void);
void PlayerDecks_OnSaveSlotReadBackup(void);
void PlayerDecks_PrepareVanillaSaveBuffer(void);
void PlayerDecks_RestoreAfterVanillaSaveBuffer(void);
void PlayerDecks_ReadDeck1(u16 *dest);
void PlayerDecks_WriteDeck1(const u16 *src);
void PlayerDecks_ReplaceDeck1(const u16 *src);

#endif
