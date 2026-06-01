#include "global.h"
#include "configs/runtime.h"
#include "debug_deck_swap.h"
#include "player_decks.h"
#include "duel.h"

extern unsigned gDeckCapacity;
extern void InitDeckData(void);
extern u8 GetDeckCardQty(u16 cardId);
extern void (*g20245AC)(int, u8 *, int);
extern u8 *g8E0CD10;
int sub_80588C4(u8 *, int, int);

#define PLAYER_DECK_SAVE_MAGIC 0xD5
/* Byte offset of deck 1 (40 x u16) inside the vanilla 0x747 save blob. */
#define PLAYER_DECK1_SAVE_BUFFER_OFFSET 0x332

#define sDeck1Cards ((u16 *)gPlayerDeckSaveStaging)
#define sSaveRestoreActiveDeck (gPlayerDeckSaveStaging[0x53])

static void NormalizeActiveDeckIndex(void);
static u8 IsCompleteDeck(const u16 *cards);
static u8 DeckHasAnyValidCard(const u16 *cards);

static u16 *GetDeckCardsBacking(u8 deckIndex) {
  switch (deckIndex) {
  case 2:
    return gPlayerDeck2Cards;
  default:
    return gPlayerDeck3Cards;
  }
}

static void CopyDeckCards(u16 *dest, const u16 *src) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++)
    dest[i] = src[i];
}

static void SaveDeck1ToStaging(void) {
  CopyDeckCards(sDeck1Cards, gDeckMenu.cards);
}

static void SyncDeck1ToSaveBuffer(void) {
  CopyDeckCards((u16 *)(g8E0CD10 + PLAYER_DECK1_SAVE_BUFFER_OFFSET), sDeck1Cards);
}

static void SyncDeck1StagingFromSaveSlotMenu(void) {
  CopyDeckCards(sDeck1Cards, gDeckMenu.cards);
}

static u8 DeckHasAnyValidCard(const u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++) {
    if (cards[i] != CARD_NONE && cards[i] < NUM_TOTAL_CARDS)
      return TRUE;
  }

  return FALSE;
}

static void LoadDeck1FromVanillaStorage(void) {
  if (DebugDeckSwap_GetActivePreset() != DEBUG_DECK_SWAP_INACTIVE) {
    DebugDeckSwap_RefreshDeck1IfActive();
    InitDeckData();
    return;
  }

  if (IsCompleteDeck(sDeck1Cards) == TRUE) {
    CopyDeckCards(gDeckMenu.cards, sDeck1Cards);
    return;
  }

  if (DeckHasAnyValidCard(gDeckMenu.cards) == TRUE) {
    SaveDeck1ToStaging();
    return;
  }

  if (DeckHasAnyValidCard(sDeck1Cards) == TRUE)
    CopyDeckCards(gDeckMenu.cards, sDeck1Cards);
}

static void LoadDeckCardsFromBacking(u8 deckIndex) {
  u16 *backing;

  if (deckIndex == PLAYER_DECK_INDEX_MIN) {
    LoadDeck1FromVanillaStorage();
    return;
  }

  backing = GetDeckCardsBacking(deckIndex);

  CopyDeckCards(gDeckMenu.cards, backing);
}

static void SaveDeckCardsToBacking(u8 deckIndex) {
  u16 *backing;

  if (deckIndex == PLAYER_DECK_INDEX_MIN) {
    SaveDeck1ToStaging();
    return;
  }

  backing = GetDeckCardsBacking(deckIndex);

  CopyDeckCards(backing, gDeckMenu.cards);
}

static void ClearDeckCards(u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++)
    cards[i] = CARD_NONE;
}

static u8 IsCompleteDeck(const u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++) {
    if (cards[i] == CARD_NONE || cards[i] >= NUM_TOTAL_CARDS)
      return FALSE;
  }

  return TRUE;
}

static void RequireCompleteActiveDeck(void) {
  NormalizeActiveDeckIndex();

  if (gActiveDeckIndex == PLAYER_DECK_INDEX_MIN)
    return;

  if (IsCompleteDeck(GetDeckCardsBacking(gActiveDeckIndex)) != TRUE)
    gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
}

static void SaveDecksToFlashPrimary(void) {
  u8 magic = PLAYER_DECK_SAVE_MAGIC;

  sub_80588C4((u8 *)gPlayerDeck2Cards, (int)gPlayerDeck2CardsFlashPrimary,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3Cards, (int)gPlayerDeck3CardsFlashPrimary,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4(&gActiveDeckIndex, (int)&gActiveDeckIndexFlashPrimary, 1);
  sub_80588C4(&magic, (int)&gPlayerDeckSaveMagicFlashPrimary, 1);
}

static void SaveDecksToFlashBackup(void) {
  u8 magic = PLAYER_DECK_SAVE_MAGIC;

  sub_80588C4((u8 *)gPlayerDeck2Cards, (int)gPlayerDeck2CardsFlashBackup,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3Cards, (int)gPlayerDeck3CardsFlashBackup,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4(&gActiveDeckIndex, (int)&gActiveDeckIndexFlashBackup, 1);
  sub_80588C4(&magic, (int)&gPlayerDeckSaveMagicFlashBackup, 1);
}

static u8 LoadDecksFromFlashPrimary(void) {
  u8 magic;

  if (g20245AC == NULL)
    return FALSE;

  g20245AC((int)&gPlayerDeckSaveMagicFlashPrimary, &magic, 1);
  if (magic != PLAYER_DECK_SAVE_MAGIC)
    return FALSE;

  g20245AC((int)gPlayerDeck2CardsFlashPrimary, (u8 *)gPlayerDeck2Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3CardsFlashPrimary, (u8 *)gPlayerDeck3Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)&gActiveDeckIndexFlashPrimary, &gActiveDeckIndex, 1);
  return TRUE;
}

static u8 LoadDecksFromFlashBackup(void) {
  u8 magic;

  if (g20245AC == NULL)
    return FALSE;

  g20245AC((int)&gPlayerDeckSaveMagicFlashBackup, &magic, 1);
  if (magic != PLAYER_DECK_SAVE_MAGIC)
    return FALSE;

  g20245AC((int)gPlayerDeck2CardsFlashBackup, (u8 *)gPlayerDeck2Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3CardsFlashBackup, (u8 *)gPlayerDeck3Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)&gActiveDeckIndexFlashBackup, &gActiveDeckIndex, 1);
  return TRUE;
}

static void InitUnsavedExtraDecks(void) {
  ClearDeckCards(gPlayerDeck2Cards);
  ClearDeckCards(gPlayerDeck3Cards);
  gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
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

u8 PlayerDecks_GetTotalDeckCardQty(u16 cardId) {
  u8 qty = 0;
  u8 i;

  if (PlayerDecks_IsEnabled() != TRUE)
    return GetDeckCardQty(cardId);

  NormalizeActiveDeckIndex();

  for (i = 0; i < DECK_SIZE; i++) {
    if ((gActiveDeckIndex == 1 ? gDeckMenu.cards[i] : sDeck1Cards[i]) == cardId)
      qty++;
    if ((gActiveDeckIndex == 2 ? gDeckMenu.cards[i] : gPlayerDeck2Cards[i]) == cardId)
      qty++;
    if ((gActiveDeckIndex == 3 ? gDeckMenu.cards[i] : gPlayerDeck3Cards[i]) == cardId)
      qty++;
  }

  return qty;
}

void PlayerDecks_FlushActive(void) {
  u8 index;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  NormalizeActiveDeckIndex();
  index = gActiveDeckIndex;
  SaveDeckCardsToBacking(index);
}

void PlayerDecks_SetActiveAndLoad(u8 deckIndex) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  if (deckIndex < PLAYER_DECK_INDEX_MIN || deckIndex > PLAYER_DECK_INDEX_MAX)
    deckIndex = PLAYER_DECK_INDEX_MIN;

  NormalizeActiveDeckIndex();
  if (deckIndex != gActiveDeckIndex)
    PlayerDecks_FlushActive();

  gActiveDeckIndex = deckIndex;
  LoadDeckCardsFromBacking(deckIndex);
  InitDeckData();
}

void PlayerDecks_InitNewGame(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
  ClearDeckCards(sDeck1Cards);
  SaveDeck1ToStaging();
  ClearDeckCards(gPlayerDeck2Cards);
  ClearDeckCards(gPlayerDeck3Cards);
}

void PlayerDecks_OnSaveSlotWrite(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  SaveDecksToFlashPrimary();
}

void PlayerDecks_OnSaveSlotWriteBackup(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  SaveDecksToFlashBackup();
}

void PlayerDecks_OnSaveSlotRead(void) {
  u8 deckIndex;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  SyncDeck1StagingFromSaveSlotMenu();

  if (LoadDecksFromFlashPrimary() != TRUE)
    InitUnsavedExtraDecks();

  RequireCompleteActiveDeck();

  deckIndex = gActiveDeckIndex;
  LoadDeckCardsFromBacking(deckIndex);
  InitDeckData();
}

void PlayerDecks_OnSaveSlotReadBackup(void) {
  u8 deckIndex;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  SyncDeck1StagingFromSaveSlotMenu();

  if (LoadDecksFromFlashBackup() != TRUE)
    InitUnsavedExtraDecks();

  RequireCompleteActiveDeck();

  deckIndex = gActiveDeckIndex;
  LoadDeckCardsFromBacking(deckIndex);
  InitDeckData();
}

void PlayerDecks_PrepareVanillaSaveBuffer(void) {
  u8 active;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  PlayerDecks_FlushActive();
  active = gActiveDeckIndex;
  sSaveRestoreActiveDeck = active;

  if (active != PLAYER_DECK_INDEX_MIN) {
    if (IsCompleteDeck(sDeck1Cards) == TRUE)
      CopyDeckCards(gDeckMenu.cards, sDeck1Cards);
    InitDeckData();
  }
}

void PlayerDecks_RestoreAfterVanillaSaveBuffer(void) {
  u8 active;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  active = sSaveRestoreActiveDeck;
  gActiveDeckIndex = active;

  if (active != PLAYER_DECK_INDEX_MIN) {
    LoadDeckCardsFromBacking(active);
    InitDeckData();
  }
}

void PlayerDecks_ReadDeck1(u16 *dest) {
  if (PlayerDecks_IsEnabled() != TRUE) {
    CopyDeckCards(dest, gDeckMenu.cards);
    return;
  }

  NormalizeActiveDeckIndex();

  if (gActiveDeckIndex == PLAYER_DECK_INDEX_MIN) {
    CopyDeckCards(dest, gDeckMenu.cards);
    return;
  }

  PlayerDecks_FlushActive();
  CopyDeckCards(dest, sDeck1Cards);
}

void PlayerDecks_WriteDeck1(const u16 *src) {
  if (PlayerDecks_IsEnabled() != TRUE) {
    CopyDeckCards(gDeckMenu.cards, src);
    InitDeckData();
    SyncDeck1ToSaveBuffer();
    return;
  }

  NormalizeActiveDeckIndex();

  CopyDeckCards(sDeck1Cards, src);

  if (gActiveDeckIndex == PLAYER_DECK_INDEX_MIN) {
    CopyDeckCards(gDeckMenu.cards, src);
    InitDeckData();
  }

  SyncDeck1ToSaveBuffer();
}

void PlayerDecks_ReplaceDeck1(const u16 *src) {
  if (PlayerDecks_IsEnabled() == TRUE)
    gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;

  CopyDeckCards(gDeckMenu.cards, src);

  if (PlayerDecks_IsEnabled() == TRUE)
    CopyDeckCards(sDeck1Cards, src);

  InitDeckData();
  SyncDeck1ToSaveBuffer();
}
