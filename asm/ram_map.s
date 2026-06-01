.section .rodata

.include "generated/card_memory_sizes.inc"
.include "generated/voice_memory_sizes.inc"

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

@ Reentrancy guard while Copycat resolves copied stats.
_kernel_malloc gComputingCopycatStats, 1

@ Ultimate Offering extra-summon state for the active duelist's turn.
_kernel_malloc gUltimateOfferingExtraSummonPending, 1
_kernel_malloc gUltimateOfferingExtraSummonUsed, 1

@ Double Summon extra-summon state for the active duelist's turn.
_kernel_malloc gDoubleSummonExtraSummonPending, 1
_kernel_malloc gDoubleSummonExtraSummonUsed, 1

@ Debug Match Setter: selected duelist table index + 1, or 0 for none.
_kernel_malloc gDebugMatchSetterSelection, 1

@ Map Teleport viewer: overworld map id when the viewer opened (0xFF = no pending change).
_kernel_malloc gDebugMenuMapViewerInitialLocation, 1

@ Active while Soul Exchange lets the player tribute opponent monsters this turn.
_kernel_malloc gSoulExchangeActive, 1

@ Counts as one paid tribute when an opponent monster was used for Soul Exchange.
_kernel_malloc gSoulExchangeTributeCredit, 1

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

.macro _kernel_malloc_ewram_array name, size
    .set UsedFreeEwramSpaceTop, UsedFreeEwramSpaceTop - \size
    SET_ARRAY \name, UsedFreeEwramSpaceTop, \size
.endm

@ Persistent randomized-cost seed record lives in the save slot buffer.
_kernel_malloc_ewram sStoredCostSeedRecord, 0x8

@ Bitfield for one-shot delayed duel effects keyed by duelist.
_kernel_malloc_ewram_array gDelayedDuelEffects, 0x2

@ Active while Cost Down reduces monster levels in the active duelist's hand.
_kernel_malloc_ewram gCostDownActive, 1
@ DUEL_PLAYER or DUEL_OPPONENT; set when Cost Down resolves.
_kernel_malloc_ewram gCostDownTargetDuelist, 1

@ Per-board-cell Copycat stats copied on activation (20 cells x 5 bytes).
_kernel_malloc_ewram_array gCopycatBoardStats, 0x64

@ Active Mage Power / United We Stand equip links (5 slots x 16 bytes).
_kernel_malloc_ewram_array gDynamicEquipLinks, 0x50

@ Bitfield for one-shot shiny-zone pickups: 16 bytes, 1 bit per flag.
_kernel_malloc_ewram_array gShinyZoneFlags, 0x10

@ Active custom field spell runtime state.
_kernel_malloc_ewram gActiveCustomFieldSpellId, 1
_kernel_malloc_ewram gActiveFieldSpellZoneRow, 1
_kernel_malloc_ewram gActiveFieldSpellZoneCol, 1
_kernel_malloc_ewram gActiveFieldSpellController, 1

@ Expanded card-shop sorted list, padded to full 7-card rows for every generated card.
_kernel_malloc_ewram_array gCustomShopCardList, CUSTOM_SHOP_CARD_LIST_BYTES

@ Trunk + deck ownership totals for custom card IDs (grows with CUSTOM_CARD_QTY_BYTES).
_kernel_malloc_ewram_array gCustomTotalCardQty, CUSTOM_CARD_QTY_BYTES

@ Custom trunk menu list tail (u16 card IDs) and sort scratch (vanilla + custom entries).
_kernel_malloc_ewram_array gTrunkMenuCustomCards, TRUNK_MENU_CUSTOM_CARD_BYTES
_kernel_malloc_ewram_array gTrunkMenuSortCards, TRUNK_MENU_SORT_LIST_BYTES
@ Cached trunk list size when hide_unowned_trunk_cards is enabled (avoids full scans per scroll).
_kernel_malloc_ewram gTrunkVisibleCardCount, 0x2
_kernel_malloc_ewram gTrunkVisibleStandardCount, 0x2

@ Multiple player decks (decks 2/3 card lists; deck 1 uses vanilla gDeckMenu/save data).
.set PLAYER_DECK_CARD_BYTES, 0x50
_kernel_malloc_ewram_array gPlayerDeck2Cards, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram_array gPlayerDeck3Cards, PLAYER_DECK_CARD_BYTES
@ Legacy-reserved capacity slots. Runtime deck capacity is the single vanilla gDeckCapacity.
_kernel_malloc_ewram gPlayerDeck2Capacity, 0x4
_kernel_malloc_ewram gPlayerDeck3Capacity, 0x4
_kernel_malloc_ewram gActiveDeckIndex, 0x1

@ Debug menu: AI controls both duelists when enabled.
_kernel_malloc_ewram gDebugAiBothSidesMode, 1

@ Scratch for temporarily restoring the active deck while building the vanilla 0x747 blob.
_kernel_malloc_ewram gPlayerDeckSaveStagingAlignPad, 0x1
_kernel_malloc_ewram_array gPlayerDeckSaveStaging, 0x54

@ m4a custom voice clips: DPCM in ROM, decode to PCM in EWRAM at playback.
_kernel_malloc_ewram_array gCustomVoiceWaveBuffer, CUSTOM_VOICE_PCM_BUFFER_BYTES
_kernel_malloc_ewram gCustomVoiceTone, 0xC
_kernel_malloc_ewram gCustomVoiceSongHeader, 0x10
_kernel_malloc_ewram_array gCustomVoicePartTrack, CUSTOM_VOICE_PART_TRACK_BYTES

@ --------------------------------------------------------------------
@ Flash storage (SRAM)
@ --------------------------------------------------------------------

SET_DATA FreeFlashSpaceTop,    0x0E000000
SET_DATA FreeFlashSpaceBottom, 0x0E008000
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

@ Save-sector addresses used by the persistent cost seed.
SET_ARRAY gSaveFlashPrimaryBase, 0x0E000000, 0x1
SET_DATA gCostSeedFlashPrimary, 0x0E000787
SET_DATA gCostSeedFlashBackup,  0x0E004767

@ Save slots stored in flash.
SET_ARRAY gSaveSlotPrimary, 0x0E000040, 0x747
SET_ARRAY gSaveSlotBackup,   0x0E004020, 0x747

@ Custom card count storage mirrored in free flash space.
SET_DATA gCustomCardQtyFlashPrimaryStart, 0x0E000788
SET_DATA gCustomCardQtyFlashBackupStart,  0x0E004768

.set CustomCardQtyFlashPrimaryCursor, gCustomCardQtyFlashPrimaryStart
.set CustomCardQtyFlashBackupCursor,  gCustomCardQtyFlashBackupStart

_kernel_malloc_flash gCustomTrunkCardQty,      CUSTOM_CARD_QTY_BYTES
_kernel_malloc_flash gCustomShopCardQty,       CUSTOM_CARD_QTY_BYTES
_kernel_malloc_flash gCustomPlayerTempCardQty, CUSTOM_CARD_QTY_BYTES
_kernel_malloc_flash gShinyZoneFlags,          0x10
_kernel_malloc_flash gPlayerDeck2Cards,        PLAYER_DECK_CARD_BYTES
_kernel_malloc_flash gPlayerDeck3Cards,        PLAYER_DECK_CARD_BYTES
@ Legacy-reserved capacity slots. Do not read/write; vanilla save owns gDeckCapacity.
_kernel_malloc_flash gPlayerDeck2Capacity,     0x4
_kernel_malloc_flash gPlayerDeck3Capacity,     0x4
_kernel_malloc_flash gActiveDeckIndex,         0x1
_kernel_malloc_flash gPlayerDeckSaveMagic,     0x1
_kernel_malloc_flash gDebugAiBothSidesMode,    0x1
