#include "global.h"
#include "configs/runtime.h"
#include "player_decks.h"
#include "duel.h"

extern unsigned gDeckCapacity;
extern void InitDeckData(void);

extern void (*g20245AC)(int, u8 *, int);
int sub_80588C4(u8 *, int, int);

#define sSaveRestoreDeck1Cards ((u16 *)gPlayerDeckSaveStaging)
#define sSaveRestoreDeck1Capacity (*(u32 *)(gPlayerDeckSaveStaging + 0x50))
#define sSaveRestoreActiveDeck (gPlayerDeckSaveStaging[0x53])

static u32 GetDefaultDeckCapacity(void) {
  if (gRuntimeConfig.max_deck_capacity_at_start == TRUE)
    return 65000;
  return 1600;
}

static u16 *GetDeckCardsBacking(u8 deckIndex) {
  switch (deckIndex) {
  case 1:
    return gPlayerDeck1Cards;
  case 2:
    return gPlayerDeck2Cards;
  default:
    return gPlayerDeck3Cards;
  }
}

static u32 *GetDeckCapacityBacking(u8 deckIndex) {
  switch (deckIndex) {
  case 1:
    return &gPlayerDeck1Capacity;
  case 2:
    return &gPlayerDeck2Capacity;
  default:
    return &gPlayerDeck3Capacity;
  }
}

static void CopyDeckCards(u16 *dest, const u16 *src) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++)
    dest[i] = src[i];
}

static void LoadDeckCardsFromBacking(u8 deckIndex) {
  u16 *backing = GetDeckCardsBacking(deckIndex);

  CopyDeckCards(gDeckMenu.cards, backing);
}

static void SaveDeckCardsToBacking(u8 deckIndex) {
  u16 *backing = GetDeckCardsBacking(deckIndex);

  CopyDeckCards(backing, gDeckMenu.cards);
}

static void SyncActiveCapacityFromWorking(void) {
  u8 index = gActiveDeckIndex;

  if (index < PLAYER_DECK_INDEX_MIN || index > PLAYER_DECK_INDEX_MAX)
    index = PLAYER_DECK_INDEX_MIN;

  *GetDeckCapacityBacking(index) = gDeckCapacity;
}

static void SyncWorkingCapacityFromBacking(u8 deckIndex) {
  if (deckIndex < PLAYER_DECK_INDEX_MIN || deckIndex > PLAYER_DECK_INDEX_MAX)
    deckIndex = PLAYER_DECK_INDEX_MIN;

  gDeckCapacity = *GetDeckCapacityBacking(deckIndex);
}

static void ClearDeckCards(u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++)
    cards[i] = CARD_NONE;
}

static void SaveDeck2And3ToFlashPrimary(void) {
  sub_80588C4((u8 *)gPlayerDeck2Cards, (int)gPlayerDeck2CardsFlashPrimary,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3Cards, (int)gPlayerDeck3CardsFlashPrimary,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)&gPlayerDeck2Capacity, (int)gPlayerDeck2CapacityFlashPrimary, 4);
  sub_80588C4((u8 *)&gPlayerDeck3Capacity, (int)gPlayerDeck3CapacityFlashPrimary, 4);
  sub_80588C4(&gActiveDeckIndex, (int)gActiveDeckIndexFlashPrimary, 1);
}

static void SaveDeck2And3ToFlashBackup(void) {
  sub_80588C4((u8 *)gPlayerDeck2Cards, (int)gPlayerDeck2CardsFlashBackup,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3Cards, (int)gPlayerDeck3CardsFlashBackup,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)&gPlayerDeck2Capacity, (int)gPlayerDeck2CapacityFlashBackup, 4);
  sub_80588C4((u8 *)&gPlayerDeck3Capacity, (int)gPlayerDeck3CapacityFlashBackup, 4);
  sub_80588C4(&gActiveDeckIndex, (int)gActiveDeckIndexFlashBackup, 1);
}

static void LoadDeck2And3FromFlashPrimary(void) {
  if (g20245AC == NULL)
    return;

  g20245AC((int)gPlayerDeck2CardsFlashPrimary, (u8 *)gPlayerDeck2Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3CardsFlashPrimary, (u8 *)gPlayerDeck3Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck2CapacityFlashPrimary, (u8 *)&gPlayerDeck2Capacity, 4);
  g20245AC((int)gPlayerDeck3CapacityFlashPrimary, (u8 *)&gPlayerDeck3Capacity, 4);
  g20245AC((int)gActiveDeckIndexFlashPrimary, &gActiveDeckIndex, 1);
}

static void LoadDeck2And3FromFlashBackup(void) {
  if (g20245AC == NULL)
    return;

  g20245AC((int)gPlayerDeck2CardsFlashBackup, (u8 *)gPlayerDeck2Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3CardsFlashBackup, (u8 *)gPlayerDeck3Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck2CapacityFlashBackup, (u8 *)&gPlayerDeck2Capacity, 4);
  g20245AC((int)gPlayerDeck3CapacityFlashBackup, (u8 *)&gPlayerDeck3Capacity, 4);
  g20245AC((int)gActiveDeckIndexFlashBackup, &gActiveDeckIndex, 1);
}

static void NormalizeActiveDeckIndex(void) {
  if (gActiveDeckIndex < PLAYER_DECK_INDEX_MIN ||
      gActiveDeckIndex > PLAYER_DECK_INDEX_MAX)
    gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
}

u8 PlayerDecks_IsEnabled(void) {
  return gRuntimeConfig.enable_multiple_decks == TRUE;
}

u8 PlayerDecks_GetActiveIndex(void) {
  NormalizeActiveDeckIndex();
  return gActiveDeckIndex;
}

u32 PlayerDecks_GetCapacityForIndex(u8 deckIndex) {
  if (deckIndex < PLAYER_DECK_INDEX_MIN || deckIndex > PLAYER_DECK_INDEX_MAX)
    deckIndex = PLAYER_DECK_INDEX_MIN;

  return *GetDeckCapacityBacking(deckIndex);
}

void PlayerDecks_SetCapacityForIndex(u8 deckIndex, u32 capacity) {
  if (deckIndex < PLAYER_DECK_INDEX_MIN || deckIndex > PLAYER_DECK_INDEX_MAX)
    deckIndex = PLAYER_DECK_INDEX_MIN;

  *GetDeckCapacityBacking(deckIndex) = capacity;
  gDeckCapacity = capacity;
}

void PlayerDecks_FlushActive(void) {
  u8 index;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  NormalizeActiveDeckIndex();
  index = gActiveDeckIndex;
  SaveDeckCardsToBacking(index);
  SyncActiveCapacityFromWorking();
}

void PlayerDecks_SetActiveAndLoad(u8 deckIndex) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  if (deckIndex < PLAYER_DECK_INDEX_MIN || deckIndex > PLAYER_DECK_INDEX_MAX)
    deckIndex = PLAYER_DECK_INDEX_MIN;

  PlayerDecks_FlushActive();
  gActiveDeckIndex = deckIndex;
  LoadDeckCardsFromBacking(deckIndex);
  SyncWorkingCapacityFromBacking(deckIndex);
  InitDeckData();
}

void PlayerDecks_InitNewGame(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
  SaveDeckCardsToBacking(PLAYER_DECK_INDEX_MIN);
  ClearDeckCards(gPlayerDeck2Cards);
  ClearDeckCards(gPlayerDeck3Cards);
}

void PlayerDecks_OnSaveSlotWrite(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  SaveDeck2And3ToFlashPrimary();
}

void PlayerDecks_OnSaveSlotWriteBackup(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  SaveDeck2And3ToFlashBackup();
}

void PlayerDecks_SavePersistentState(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  SaveDeck2And3ToFlashPrimary();
  SaveDeck2And3ToFlashBackup();
}

void PlayerDecks_OnSaveSlotRead(void) {
  u8 deckIndex;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  CopyDeckCards(gPlayerDeck1Cards, gDeckMenu.cards);
  gPlayerDeck1Capacity = gDeckCapacity;

  LoadDeck2And3FromFlashPrimary();

  if (gActiveDeckIndex == 0xFF) {
    ClearDeckCards(gPlayerDeck2Cards);
    ClearDeckCards(gPlayerDeck3Cards);
    gPlayerDeck2Capacity = GetDefaultDeckCapacity();
    gPlayerDeck3Capacity = GetDefaultDeckCapacity();
    gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
  } else {
    NormalizeActiveDeckIndex();
  }

  deckIndex = gActiveDeckIndex;
  if (deckIndex == PLAYER_DECK_INDEX_MIN) {
    gDeckCapacity = gPlayerDeck1Capacity;
  } else {
    LoadDeckCardsFromBacking(deckIndex);
    SyncWorkingCapacityFromBacking(deckIndex);
    InitDeckData();
  }
}

void PlayerDecks_PrepareVanillaSaveBuffer(void) {
  u8 active;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  active = gActiveDeckIndex;
  sSaveRestoreActiveDeck = active;

  CopyDeckCards(sSaveRestoreDeck1Cards, gDeckMenu.cards);
  sSaveRestoreDeck1Capacity = gDeckCapacity;

  if (active != PLAYER_DECK_INDEX_MIN) {
    CopyDeckCards(gDeckMenu.cards, gPlayerDeck1Cards);
    gDeckCapacity = gPlayerDeck1Capacity;
  }
}

void PlayerDecks_RestoreAfterVanillaSaveBuffer(void) {
  u8 active;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  active = sSaveRestoreActiveDeck;
  CopyDeckCards(gPlayerDeck1Cards, gDeckMenu.cards);
  gPlayerDeck1Capacity = gDeckCapacity;

  CopyDeckCards(gDeckMenu.cards, sSaveRestoreDeck1Cards);
  gDeckCapacity = sSaveRestoreDeck1Capacity;
  gActiveDeckIndex = active;

  if (active != PLAYER_DECK_INDEX_MIN) {
    LoadDeckCardsFromBacking(active);
    SyncWorkingCapacityFromBacking(active);
    InitDeckData();
  }
}
