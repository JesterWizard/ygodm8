#include "global.h"
#include "millennium_items.h"
#include "overworld.h"

extern void (*g20245AC)(int, u8 *, int);
int sub_80588C4(u8 *, int, int);

u8 MillenniumItems_IsOwned(u8 itemId) {
  if (itemId >= MILLENNIUM_ITEM_COUNT)
    return FALSE;
  return gMillenniumItemsOwned[itemId] != 0;
}

void MillenniumItems_SetOwned(u8 itemId, u8 owned) {
  if (itemId >= MILLENNIUM_ITEM_COUNT)
    return;
  gMillenniumItemsOwned[itemId] = owned ? 1 : 0;
}

void MillenniumItems_ResetOnNewGame(void) {
  u8 i;

  for (i = 0; i < MILLENNIUM_ITEM_COUNT; i++)
    gMillenniumItemsOwned[i] = 0;
}

static void MillenniumItems_LoadFromFlash(int address) {
  if (g20245AC == NULL)
    return;
  g20245AC(address, gMillenniumItemsOwned, MILLENNIUM_ITEM_COUNT);
}

void MillenniumItems_LoadFromFlashPrimary(void) {
  MillenniumItems_LoadFromFlash((int)&gMillenniumItemsOwnedFlashPrimary);
}

void MillenniumItems_LoadFromFlashBackup(void) {
  MillenniumItems_LoadFromFlash((int)&gMillenniumItemsOwnedFlashBackup);
}

void MillenniumItems_SaveToFlashPrimary(void) {
  sub_80588C4(gMillenniumItemsOwned, (int)&gMillenniumItemsOwnedFlashPrimary,
              MILLENNIUM_ITEM_COUNT);
}

void MillenniumItems_SaveToFlashBackup(void) {
  sub_80588C4(gMillenniumItemsOwned, (int)&gMillenniumItemsOwnedFlashBackup,
              MILLENNIUM_ITEM_COUNT);
}

bool8 MillenniumItems_TryConsumeOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  /* SET_MILLENNIUM_ITEM(id) / CLEAR: 0x7C 'B' id value */
  if (script[pointer] != 0x7C || script[pointer + 1] != 'B')
    return FALSE;

  MillenniumItems_SetOwned(script[pointer + 2], script[pointer + 3]);
  scriptCtx->pointer += 4;
  return TRUE;
}
