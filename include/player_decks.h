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
extern u32 gPlayerDeck1Capacity;
extern u32 gPlayerDeck2Capacity;
extern u32 gPlayerDeck3Capacity;
extern u8 gActiveDeckIndex;
extern u8 gPlayerDeckSaveStaging[0x54];

extern u16 gPlayerDeck2CardsFlashPrimary[40];
extern u16 gPlayerDeck2CardsFlashBackup[40];
extern u16 gPlayerDeck3CardsFlashPrimary[40];
extern u16 gPlayerDeck3CardsFlashBackup[40];
extern u32 gPlayerDeck2CapacityFlashPrimary;
extern u32 gPlayerDeck2CapacityFlashBackup;
extern u32 gPlayerDeck3CapacityFlashPrimary;
extern u32 gPlayerDeck3CapacityFlashBackup;
extern u8 gActiveDeckIndexFlashPrimary;
extern u8 gActiveDeckIndexFlashBackup;

u8 PlayerDecks_IsEnabled(void);
u8 PlayerDecks_GetActiveIndex(void);
void PlayerDecks_FlushActive(void);
void PlayerDecks_SetActiveAndLoad(u8 deckIndex);
void PlayerDecks_InitNewGame(void);
void PlayerDecks_OnSaveSlotWrite(void);
void PlayerDecks_OnSaveSlotWriteBackup(void);
void PlayerDecks_OnSaveSlotRead(void);
void PlayerDecks_SavePersistentState(void);
void PlayerDecks_PrepareVanillaSaveBuffer(void);
void PlayerDecks_RestoreAfterVanillaSaveBuffer(void);
u32 PlayerDecks_GetCapacityForIndex(u8 deckIndex);
void PlayerDecks_SetCapacityForIndex(u8 deckIndex, u32 capacity);

#endif
