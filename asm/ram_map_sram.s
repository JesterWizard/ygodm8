@ =============================================================================
@ Flash storage (SRAM)
@ =============================================================================
@ Range: 0x0E000000–0x0E008000 (persistent save data; lower 32 KiB only)

SET_DATA FreeFlashSpaceTop,     0x0E000000
SET_DATA FreeFlashSpaceBottom,  0x0E008000
SET_DATA UsedFreeFlashSpaceTop, FreeFlashSpaceBottom

.macro _kernel_malloc_flash_free name, size
    .set UsedFreeFlashSpaceTop, UsedFreeFlashSpaceTop - \size
    SET_DATA \name, UsedFreeFlashSpaceTop
.endm

.macro _kernel_malloc_flash name, size
    SET_ARRAY \name\()FlashPrimary, CustomCardQtyFlashPrimaryCursor, \size
    .set CustomCardQtyFlashPrimaryCursor, CustomCardQtyFlashPrimaryCursor + \size
    SET_ARRAY \name\()FlashBackup, CustomCardQtyFlashBackupCursor, \size
    .set CustomCardQtyFlashBackupCursor, CustomCardQtyFlashBackupCursor + \size
.endm

@ -- Fixed save slots -----------------------------------------------------------

@ Save-sector addresses used by the persistent cost seed.
SET_ARRAY gSaveFlashPrimaryBase, 0x0E000000, 0x1
SET_DATA  gCostSeedFlashPrimary, 0x0E000787
SET_DATA  gCostSeedFlashBackup,  0x0E004767

@ Save slots stored in flash.
SET_ARRAY gSaveSlotPrimary, 0x0E000040, 0x747
SET_ARRAY gSaveSlotBackup,  0x0E004020, 0x747

@ -- Mirrored custom data (primary/backup cursors) ------------------------------
@ CUSTOM_CARD_QTY_BYTES is even-aligned (floor 0x200) in tools/add_card_art.py
@ (render_card_memory_sizes_asm) so that adding new cards does not shift the flash
@ save layout. Bump the minimum if custom cards exceed 200.

SET_DATA gCustomCardQtyFlashPrimaryStart, 0x0E000788
SET_DATA gCustomCardQtyFlashBackupStart,  0x0E004768

.set CustomCardQtyFlashPrimaryCursor, gCustomCardQtyFlashPrimaryStart
.set CustomCardQtyFlashBackupCursor,  gCustomCardQtyFlashBackupStart

@ Custom card count storage mirrored in free flash space.
_kernel_malloc_flash gCustomTrunkCardQty,       CUSTOM_CARD_QTY_BYTES
_kernel_malloc_flash gCustomShopCardQty,        CUSTOM_CARD_QTY_BYTES
_kernel_malloc_flash gCustomPlayerTempCardQty,  CUSTOM_CARD_QTY_BYTES
_kernel_malloc_flash gShinyZoneFlags,             0x10
_kernel_malloc_flash gPlayerDeck2Cards,         PLAYER_DECK_CARD_BYTES
_kernel_malloc_flash gPlayerDeck3Cards,         PLAYER_DECK_CARD_BYTES
@ Extra decks (15 u16 per deck = 30 bytes) — persisted for all 3 decks.
_kernel_malloc_flash gPlayerDeck1ExtraDeck,     EXTRA_DECK_CARD_BYTES
_kernel_malloc_flash gPlayerDeck2ExtraDeck,     EXTRA_DECK_CARD_BYTES
_kernel_malloc_flash gPlayerDeck3ExtraDeck,     EXTRA_DECK_CARD_BYTES
@ Legacy-reserved capacity slots. Do not read/write; vanilla save owns gDeckCapacity.
_kernel_malloc_flash gPlayerDeck2Capacity,      0x4
_kernel_malloc_flash gPlayerDeck3Capacity,      0x4
_kernel_malloc_flash gActiveDeckIndex,          0x1
_kernel_malloc_flash gPlayerDeckSaveMagic,      0x1
_kernel_malloc_flash gDebugAiBothSidesMode,     0x1
_kernel_malloc_flash gMenuCursorId,             0x1
_kernel_malloc_flash gDebugRuleset,             0x1
_kernel_malloc_flash gDebugDeckSwapBackup,      PLAYER_DECK_CARD_BYTES
_kernel_malloc_flash gDebugDeckSwapBackupValid, 0x1
_kernel_malloc_flash gDebugSaveAnywhereData,     0xC
_kernel_malloc_flash gTimedDuelCompletionFlags, 0x10
_kernel_malloc_flash gMillenniumItemsOwned,     7
