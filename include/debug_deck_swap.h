#ifndef GUARD_DEBUG_DECK_SWAP_H
#define GUARD_DEBUG_DECK_SWAP_H

#include "gba/types.h"

#define DEBUG_DECK_SWAP_INACTIVE 0xFF
#define DEBUG_DECK_SWAP_SAVE_MAGIC 0xD6

extern u16 gDebugDeckSwapBackup[40];
extern u16 gDebugDeckSwapExtraBackup[15];
extern u8 gDebugDeckSwapActivePreset;
extern u8 gDebugDeckSwapBackupValid;

u8 DebugDeckSwap_GetActivePreset(void);
u8 DebugDeckSwap_HasBackup(void);
void DebugDeckSwap_ApplyPreset(u8 presetIndex, const u16 *presetCards, const u16 *presetExtra);
void DebugDeckSwap_RefreshDeck1IfActive(void);
void DebugDeckSwap_RestoreOriginal(void);
void DebugDeckSwap_Reset(void);
void DebugDeckSwap_LoadFromFlashPrimary(void);
void DebugDeckSwap_LoadFromFlashBackup(void);
void DebugDeckSwap_SaveToFlashPrimary(void);
void DebugDeckSwap_SaveToFlashBackup(void);

#endif
