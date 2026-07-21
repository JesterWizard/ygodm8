#include "global.h"
#include "debug_deck_swap.h"
#include "player_decks.h"

extern void (*g20245AC)(int, u8 *, int);
int sub_80588C4(u8 *, int, int);

extern u16 gDebugDeckSwapBackupFlashPrimary[40];
extern u16 gDebugDeckSwapBackupFlashBackup[40];
extern u8 gDebugDeckSwapBackupValidFlashPrimary;
extern u8 gDebugDeckSwapBackupValidFlashBackup;

const u16 *DebugMenuDeck_GetCards(u8 index);

static const u16 *DebugDeckSwap_GetPresetCards(u8 presetIndex) {
  return DebugMenuDeck_GetCards(presetIndex);
}

static void DebugDeckSwap_ClearStorage(void) {
  u8 i;

  gDebugDeckSwapBackupValid = FALSE;
  gDebugDeckSwapActivePreset = DEBUG_DECK_SWAP_INACTIVE;
  for (i = 0; i < DECK_SIZE; i++)
    gDebugDeckSwapBackup[i] = CARD_NONE;
}

static void DebugDeckSwap_NormalizeState(void) {
  if (gDebugDeckSwapBackupValid != TRUE)
    gDebugDeckSwapActivePreset = DEBUG_DECK_SWAP_INACTIVE;
}

static void DebugDeckSwap_SaveToFlash(int validAddr, int backupAddr) {
  u8 magic = gDebugDeckSwapBackupValid == TRUE ? DEBUG_DECK_SWAP_SAVE_MAGIC : 0;

  sub_80588C4(&magic, validAddr, 1);
  if (magic == DEBUG_DECK_SWAP_SAVE_MAGIC)
    sub_80588C4((u8 *)gDebugDeckSwapBackup, backupAddr, PLAYER_DECK_CARD_BYTES);
}

static void DebugDeckSwap_LoadFromFlash(int validAddr, int backupAddr) {
  u8 magic = 0;

  if (g20245AC == NULL) {
    DebugDeckSwap_ClearStorage();
    return;
  }

  g20245AC(validAddr, &magic, 1);
  if (magic != DEBUG_DECK_SWAP_SAVE_MAGIC) {
    DebugDeckSwap_ClearStorage();
    return;
  }

  g20245AC(backupAddr, (u8 *)gDebugDeckSwapBackup, PLAYER_DECK_CARD_BYTES);
  gDebugDeckSwapBackupValid = TRUE;
}

void DebugDeckSwap_Reset(void) {
  DebugDeckSwap_ClearStorage();
  DebugDeckSwap_SaveToFlashPrimary();
  DebugDeckSwap_SaveToFlashBackup();
}

u8 DebugDeckSwap_HasBackup(void) {
  return gDebugDeckSwapBackupValid == TRUE;
}

void DebugDeckSwap_ApplyPreset(u8 presetIndex, const u16 *presetCards) {
  DebugDeckSwap_NormalizeState();

  if (gDebugDeckSwapBackupValid != TRUE) {
    PlayerDecks_ReadDeck1(gDebugDeckSwapBackup);
    gDebugDeckSwapBackupValid = TRUE;
  }

  PlayerDecks_ReplaceDeck1(presetCards);
  gDebugDeckSwapActivePreset = presetIndex;
}

void DebugDeckSwap_RestoreOriginal(void) {
  if (gDebugDeckSwapBackupValid != TRUE)
    return;

  PlayerDecks_ReplaceDeck1(gDebugDeckSwapBackup);
  DebugDeckSwap_ClearStorage();
  DebugDeckSwap_SaveToFlashPrimary();
  DebugDeckSwap_SaveToFlashBackup();
}

void DebugDeckSwap_RefreshDeck1IfActive(void) {
  const u16 *presetCards;

  DebugDeckSwap_NormalizeState();
  if (gDebugDeckSwapActivePreset == DEBUG_DECK_SWAP_INACTIVE)
    return;

  presetCards = DebugDeckSwap_GetPresetCards(gDebugDeckSwapActivePreset);
  if (presetCards != NULL)
    PlayerDecks_ReplaceDeck1(presetCards);
}

u8 DebugDeckSwap_GetActivePreset(void) {
  DebugDeckSwap_NormalizeState();
  return gDebugDeckSwapActivePreset;
}

void DebugDeckSwap_LoadFromFlashPrimary(void) {
  DebugDeckSwap_LoadFromFlash((int)&gDebugDeckSwapBackupValidFlashPrimary,
                              (int)gDebugDeckSwapBackupFlashPrimary);
}

void DebugDeckSwap_LoadFromFlashBackup(void) {
  DebugDeckSwap_LoadFromFlash((int)&gDebugDeckSwapBackupValidFlashBackup,
                              (int)gDebugDeckSwapBackupFlashBackup);
}

void DebugDeckSwap_SaveToFlashPrimary(void) {
  DebugDeckSwap_SaveToFlash((int)&gDebugDeckSwapBackupValidFlashPrimary,
                            (int)gDebugDeckSwapBackupFlashPrimary);
}

void DebugDeckSwap_SaveToFlashBackup(void) {
  DebugDeckSwap_SaveToFlash((int)&gDebugDeckSwapBackupValidFlashBackup,
                            (int)gDebugDeckSwapBackupFlashBackup);
}
