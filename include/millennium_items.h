#ifndef GUARD_MILLENNIUM_ITEMS_H
#define GUARD_MILLENNIUM_ITEMS_H

#include "gba/types.h"

struct ScriptCtx;

#define MILLENNIUM_ITEM_PUZZLE   0
#define MILLENNIUM_ITEM_RING     1
#define MILLENNIUM_ITEM_KEY      2
#define MILLENNIUM_ITEM_SCALE    3
#define MILLENNIUM_ITEM_ROD      4
#define MILLENNIUM_ITEM_EYE      5
#define MILLENNIUM_ITEM_NECKLACE 6
#define MILLENNIUM_ITEM_COUNT    7

/* Non-zero = acquired. One byte per item. */
extern u8 gMillenniumItemsOwned[MILLENNIUM_ITEM_COUNT];
extern u8 gMillenniumItemsOwnedFlashPrimary[MILLENNIUM_ITEM_COUNT];
extern u8 gMillenniumItemsOwnedFlashBackup[MILLENNIUM_ITEM_COUNT];

u8 MillenniumItems_IsOwned(u8 itemId);
void MillenniumItems_SetOwned(u8 itemId, u8 owned);
void MillenniumItems_ResetOnNewGame(void);
void MillenniumItems_LoadFromFlashPrimary(void);
void MillenniumItems_LoadFromFlashBackup(void);
void MillenniumItems_SaveToFlashPrimary(void);
void MillenniumItems_SaveToFlashBackup(void);
bool8 MillenniumItems_TryConsumeOpcode(struct ScriptCtx *scriptCtx);

#endif
