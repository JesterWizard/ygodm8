#include "global.h"
#include "configs/runtime.h"
#include "debug_deck_swap.h"
#include "player_decks.h"
#include "player_deck_persist.h"
#include "duel.h"
#include "constants/card_ids.h"

extern unsigned gDeckCapacity;
extern void InitDeckData(void);
extern u8 GetDeckCardQty(u16 cardId);
extern void (*g20245AC)(int, u8 *, int);
extern u8 *g8E0CD10;
int sub_80588C4(u8 *, int, int);

#define PLAYER_DECK_SAVE_MAGIC PLAYER_DECK_PERSIST_MAGIC
/* Byte offset of deck 1 (40 x u16) inside the vanilla 0x747 save blob. */
#define PLAYER_DECK1_SAVE_BUFFER_OFFSET 0x332

static void NormalizeActiveDeckIndex(void);
static u8 IsCompleteDeck(const u16 *cards);
static void SanitizeDeckCards(u16 *cards);
static u16 *GetDeckCardsBacking(u8 deckIndex);
static void SyncDeck1FromSaveSlotMenu(void);
static void SyncDeck1ToSaveBuffer(void);

static u16 *GetDeckCardsBacking(u8 deckIndex) {
  switch (deckIndex) {
  case 2:
    return gPlayerDeck2Cards;
  case 3:
    return gPlayerDeck3Cards;
  default:
    return gPlayerDeck1Cards;
  }
}

static void CopyDeckCards(u16 *dest, const u16 *src) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++)
    dest[i] = src[i];
}

static void SyncDeck1FromSaveSlotMenu(void) {
  CopyDeckCards(gPlayerDeck1Cards, gDeckMenu.cards);
}

static void SyncDeck1ToSaveBuffer(void) {
  CopyDeckCards((u16 *)(g8E0CD10 + PLAYER_DECK1_SAVE_BUFFER_OFFSET),
                gPlayerDeck1Cards);
}

static void SanitizeDeckCards(u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++) {
    if (cards[i] == CARD_NONE || cards[i] >= NUM_TOTAL_CARDS)
      cards[i] = CARD_NONE;
  }
}

static void LoadDeckCardsFromBacking(u8 deckIndex) {
  if (deckIndex == PLAYER_DECK_INDEX_MIN &&
      DebugDeckSwap_GetActivePreset() != DEBUG_DECK_SWAP_INACTIVE) {
    DebugDeckSwap_RefreshDeck1IfActive();
    InitDeckData();
    return;
  }

  CopyDeckCards(gDeckMenu.cards, GetDeckCardsBacking(deckIndex));
  SanitizeDeckCards(gDeckMenu.cards);
}

static void SaveDeckCardsToBacking(u8 deckIndex) {
  CopyDeckCards(GetDeckCardsBacking(deckIndex), gDeckMenu.cards);
}

static void ClearDeckCards(u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++)
    cards[i] = CARD_NONE;
}

static u8 IsCompleteDeck(const u16 *cards) {
  return PlayerDeckPersist_IsCompleteDeck(cards, NUM_TOTAL_CARDS);
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
  sub_80588C4((u8 *)gPlayerDeck1ExtraDeck, (int)gPlayerDeck1ExtraDeckFlashPrimary,
              EXTRA_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck2ExtraDeck, (int)gPlayerDeck2ExtraDeckFlashPrimary,
              EXTRA_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3ExtraDeck, (int)gPlayerDeck3ExtraDeckFlashPrimary,
              EXTRA_DECK_CARD_BYTES);
  sub_80588C4(&gActiveDeckIndex, (int)&gActiveDeckIndexFlashPrimary, 1);
  sub_80588C4(&magic, (int)&gPlayerDeckSaveMagicFlashPrimary, 1);
}

static void SaveDecksToFlashBackup(void) {
  u8 magic = PLAYER_DECK_SAVE_MAGIC;

  sub_80588C4((u8 *)gPlayerDeck2Cards, (int)gPlayerDeck2CardsFlashBackup,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3Cards, (int)gPlayerDeck3CardsFlashBackup,
              PLAYER_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck1ExtraDeck, (int)gPlayerDeck1ExtraDeckFlashBackup,
              EXTRA_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck2ExtraDeck, (int)gPlayerDeck2ExtraDeckFlashBackup,
              EXTRA_DECK_CARD_BYTES);
  sub_80588C4((u8 *)gPlayerDeck3ExtraDeck, (int)gPlayerDeck3ExtraDeckFlashBackup,
              EXTRA_DECK_CARD_BYTES);
  sub_80588C4(&gActiveDeckIndex, (int)&gActiveDeckIndexFlashBackup, 1);
  sub_80588C4(&magic, (int)&gPlayerDeckSaveMagicFlashBackup, 1);
}

static u8 LoadDecksFromFlashPrimary(void) {
  u8 magic;

  if (g20245AC == NULL)
    return FALSE;

  g20245AC((int)&gPlayerDeckSaveMagicFlashPrimary, &magic, 1);
  if (PlayerDeckPersist_MagicIsValid(magic) != TRUE)
    return FALSE;

  g20245AC((int)gPlayerDeck2CardsFlashPrimary, (u8 *)gPlayerDeck2Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3CardsFlashPrimary, (u8 *)gPlayerDeck3Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck1ExtraDeckFlashPrimary, (u8 *)gPlayerDeck1ExtraDeck,
           EXTRA_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck2ExtraDeckFlashPrimary, (u8 *)gPlayerDeck2ExtraDeck,
           EXTRA_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3ExtraDeckFlashPrimary, (u8 *)gPlayerDeck3ExtraDeck,
           EXTRA_DECK_CARD_BYTES);
  g20245AC((int)&gActiveDeckIndexFlashPrimary, &gActiveDeckIndex, 1);
  return TRUE;
}

static u8 LoadDecksFromFlashBackup(void) {
  u8 magic;

  if (g20245AC == NULL)
    return FALSE;

  g20245AC((int)&gPlayerDeckSaveMagicFlashBackup, &magic, 1);
  if (PlayerDeckPersist_MagicIsValid(magic) != TRUE)
    return FALSE;

  g20245AC((int)gPlayerDeck2CardsFlashBackup, (u8 *)gPlayerDeck2Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3CardsFlashBackup, (u8 *)gPlayerDeck3Cards,
           PLAYER_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck1ExtraDeckFlashBackup, (u8 *)gPlayerDeck1ExtraDeck,
           EXTRA_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck2ExtraDeckFlashBackup, (u8 *)gPlayerDeck2ExtraDeck,
           EXTRA_DECK_CARD_BYTES);
  g20245AC((int)gPlayerDeck3ExtraDeckFlashBackup, (u8 *)gPlayerDeck3ExtraDeck,
           EXTRA_DECK_CARD_BYTES);
  g20245AC((int)&gActiveDeckIndexFlashBackup, &gActiveDeckIndex, 1);
  return TRUE;
}

static void ClearExtraDeck(u16 *deck) {
  u8 i;

  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    deck[i] = CARD_NONE;
}

static void InitUnsavedExtraDecks(void) {
  ClearDeckCards(gPlayerDeck2Cards);
  ClearDeckCards(gPlayerDeck3Cards);
  ClearExtraDeck(gPlayerDeck1ExtraDeck);
  ClearExtraDeck(gPlayerDeck2ExtraDeck);
  ClearExtraDeck(gPlayerDeck3ExtraDeck);
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
    if ((gActiveDeckIndex == 1 ? gDeckMenu.cards[i] : gPlayerDeck1Cards[i]) == cardId)
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
  if (deckIndex != gActiveDeckIndex) {
    PlayerDecks_FlushActive();
    gActiveDeckIndex = deckIndex;
    LoadDeckCardsFromBacking(deckIndex);
  }
  InitDeckData();
}

void PlayerDecks_InitNewGame(void) {
  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  gActiveDeckIndex = PLAYER_DECK_INDEX_MIN;
  SaveDeckCardsToBacking(PLAYER_DECK_INDEX_MIN);
  ClearDeckCards(gPlayerDeck2Cards);
  ClearDeckCards(gPlayerDeck3Cards);
  ClearExtraDeck(gPlayerDeck1ExtraDeck);
  ClearExtraDeck(gPlayerDeck2ExtraDeck);
  ClearExtraDeck(gPlayerDeck3ExtraDeck);
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

  SyncDeck1FromSaveSlotMenu();

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

  SyncDeck1FromSaveSlotMenu();

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
  gPlayerDeckSaveRestoreActiveDeck = active;

  if (active != PLAYER_DECK_INDEX_MIN) {
    CopyDeckCards(gDeckMenu.cards, gPlayerDeck1Cards);
    InitDeckData();
  }
}

void PlayerDecks_RestoreAfterVanillaSaveBuffer(void) {
  u8 active;

  if (PlayerDecks_IsEnabled() != TRUE)
    return;

  active = gPlayerDeckSaveRestoreActiveDeck;
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
  CopyDeckCards(dest, gPlayerDeck1Cards);
}

void PlayerDecks_WriteDeck1(const u16 *src) {
  if (PlayerDecks_IsEnabled() != TRUE) {
    CopyDeckCards(gDeckMenu.cards, src);
    InitDeckData();
    SyncDeck1ToSaveBuffer();
    return;
  }

  NormalizeActiveDeckIndex();

  CopyDeckCards(gPlayerDeck1Cards, src);

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
    CopyDeckCards(gPlayerDeck1Cards, src);

  InitDeckData();
  SyncDeck1ToSaveBuffer();
}
