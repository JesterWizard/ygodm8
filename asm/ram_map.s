.section .rodata

@ Absolute memory symbols used by the custom code.
@
@ Use:
@ - IWRAM for hot paths, tiny scratch buffers, and time-sensitive state.
@ - EWRAM for larger runtime arrays and state that can tolerate slower access.
@ - Flash/SRAM for persistent save data only.
@
@ The allocator helpers follow the FE8 C Skill System convention:
@ `Top` = low address, `Bottom` = high address.

.macro SET_DATA name, value
    .global \name
    .type \name, object
    .set \name, \value
.endm

.macro SET_ARRAY name, value, size
    SET_DATA \name, \value
    .global \name\()End
    .type \name\()End, object
    .set \name\()End, (\value + \size)
.endm

.macro dat value, name
    SET_DATA \name, \value
.endm

@ --------------------------------------------------------------------
@ IWRAM free space
@ --------------------------------------------------------------------

SET_DATA FreeRamSpaceTop,    0x03001678
SET_DATA FreeRamSpaceBottom, 0x03007E00
SET_DATA UsedFreeRamSpaceTop, FreeRamSpaceBottom

.macro _kernel_malloc name, size
    .set UsedFreeRamSpaceTop, UsedFreeRamSpaceTop - \size
    SET_DATA \name, UsedFreeRamSpaceTop
.endm

@ Randomized card costs live in IWRAM for maximum speed.
_kernel_malloc sRandomizedCardCosts, 0x652

@ --------------------------------------------------------------------
@ EWRAM free space
@ --------------------------------------------------------------------

SET_DATA FreeEwramSpaceTop,    0x02025840
SET_DATA FreeEwramSpaceBottom, 0x02040000
SET_DATA UsedFreeEwramSpaceTop, FreeEwramSpaceBottom

.macro _kernel_malloc_ewram name, size
    .set UsedFreeEwramSpaceTop, UsedFreeEwramSpaceTop - \size
    SET_DATA \name, UsedFreeEwramSpaceTop
.endm

@ --------------------------------------------------------------------
@ Flash storage (SRAM)
@ --------------------------------------------------------------------

SET_DATA FreeFlashSpaceTop,    0x0E000000
SET_DATA FreeFlashSpaceBottom, 0x0E008000
SET_DATA UsedFreeFlashSpaceTop, FreeFlashSpaceBottom

.macro _kernel_malloc_flash name, size
    .set UsedFreeFlashSpaceTop, UsedFreeFlashSpaceTop - \size
    SET_DATA \name, UsedFreeFlashSpaceTop
.endm

@ Save-sector addresses used by the persistent cost seed.
SET_ARRAY gSaveFlashPrimaryBase, 0x0E000000, 0x1
SET_DATA gCostSeedFlashPrimary, 0x0E000787
SET_DATA gCostSeedFlashBackup,  0x0E004767

@ Custom card count storage mirrored in free flash space.
SET_ARRAY gCustomTrunkCardQtyFlashPrimary, 0x0E000788, 0x8
SET_ARRAY gCustomShopCardQtyFlashPrimary, 0x0E000790, 0x8
SET_ARRAY gCustomPlayerTempCardQtyFlashPrimary, 0x0E000798, 0x8
SET_ARRAY gCustomTrunkCardQtyFlashBackup, 0x0E004768, 0x8
SET_ARRAY gCustomShopCardQtyFlashBackup, 0x0E004770, 0x8
SET_ARRAY gCustomPlayerTempCardQtyFlashBackup, 0x0E004778, 0x8

@ Save slots stored in flash.
SET_ARRAY gSaveSlotPrimary, 0x0E000040, 0x747
SET_ARRAY gSaveSlotBackup,   0x0E004020, 0x747

@ Persistent randomized-cost seed record lives in the save slot buffer.
SET_ARRAY sStoredCostSeedRecord, 0x02020E06, 0x8
