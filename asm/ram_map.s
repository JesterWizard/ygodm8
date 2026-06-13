.section .rodata

.include "generated/card_memory_sizes.inc"

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

@ m4a HQ mixer 16-bit mix buffer (0x580 bytes). First byte of IWRAM free space.
SET_DATA gM4aHqMixBuffer, 0x03001678

@ HQ mixer IWRAM execution buffer (MixerSize bytes, copied from ROM at init).
SET_DATA MixerBuffer, 0x03001BF8

@ Randomized card costs live in IWRAM for maximum speed (one u16 per card ID).
_kernel_malloc sRandomizedCardCosts, CARD_COST_TABLE_BYTES

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

@ Scene viewer: reload overworld and run on-enter script after the menu closes (0xFF = none).
_kernel_malloc gDebugMenuPendingSceneActive, 1
_kernel_malloc gDebugMenuPendingSceneMapId, 1
_kernel_malloc gDebugMenuPendingSceneState, 1
_kernel_malloc gDebugMenuPendingSceneConnection, 1

@ Active while Soul Exchange lets the player tribute opponent monsters this turn.
_kernel_malloc gSoulExchangeActive, 1

@ Counts as one paid tribute when an opponent monster was used for Soul Exchange.
_kernel_malloc gSoulExchangeTributeCredit, 1

@ Tribute count paid for the most recent monster Normal Summon placement.
_kernel_malloc gPendingSummonTributeCount, 1

@ Slifer summon penalty waiting for summon placement to finish.
_kernel_malloc gSliferPendingPenaltyActive, 1
_kernel_malloc gSliferPendingPenaltyBoardRow, 1
_kernel_malloc gSliferPendingPenaltyCol, 1

@ Duel win shop drop popup: count plus up to three (cardId, qty) pairs.
_kernel_malloc gDuelShopDropRecord, 0x10

@ Event CG session state (overworld dialogue cutscene graphics).
_kernel_malloc gCgSessionOpen, 1
_kernel_malloc gCgActive, 1
_kernel_malloc gCgFadeSpeed, 1
_kernel_malloc gCgId, 1
_kernel_malloc gCgSavedDispcnt, 2

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

@ Riryoku pending target zones during two-step activation.
_kernel_malloc_ewram gRiryokuSourceRow, 1
_kernel_malloc_ewram gRiryokuSourceCol, 1
_kernel_malloc_ewram gRiryokuRecipientRow, 1
_kernel_malloc_ewram gRiryokuRecipientCol, 1

@ Riryoku ATK deltas keyed by gDuel.board cell index (20 cells x 2 bytes).
_kernel_malloc_ewram_array gRiryokuAtkDelta, 0x28

@ Zone used by the most recent GetFinalStage call before SetFinalStat.
_kernel_malloc_ewram gSetFinalStatZone, 4

@ Embodiment of Apophis trap/monster zone pairs (5 slots x 5 bytes).
_kernel_malloc_ewram_array gApophisLinks, 0x19
@ Re-entrancy guard while clearing linked Apophis zones.
_kernel_malloc_ewram gApophisClearingPartner, 1

@ Bitfield for one-shot shiny-zone pickups: 16 bytes, 1 bit per flag.
_kernel_malloc_ewram_array gShinyZoneFlags, 0x10

@ Active custom field spell runtime state.
_kernel_malloc_ewram gActiveCustomFieldSpellId, 1
_kernel_malloc_ewram gActiveFieldSpellZoneRow, 1
_kernel_malloc_ewram gActiveFieldSpellZoneCol, 1
_kernel_malloc_ewram gActiveFieldSpellController, 1

@ Expanded card-shop sorted list, padded to full 7-card rows for every generated card.
_kernel_malloc_ewram_array gCustomShopCardList, CUSTOM_SHOP_CARD_LIST_BYTES

@ Custom trunk/shop/player-temp card quantities (EWRAM; flash mirrors below in SRAM).
@ CUSTOM_CARD_QTY_BYTES is padded to 200 — bump if cards exceed 200.
_kernel_malloc_ewram_array gCustomTrunkCardQty, CUSTOM_CARD_QTY_BYTES
_kernel_malloc_ewram_array gCustomShopCardQty, CUSTOM_CARD_QTY_BYTES
_kernel_malloc_ewram_array gCustomPlayerTempCardQty, CUSTOM_CARD_QTY_BYTES
@ Entropy seed mixed into cost randomization LFSR when randomize_card_costs_at_start.
_kernel_malloc_ewram gCostEntropyState, 0x4

@ Trunk + deck ownership totals for custom card IDs (grows with CUSTOM_CARD_QTY_BYTES).
_kernel_malloc_ewram_array gCustomTotalCardQty, CUSTOM_CARD_QTY_BYTES

@ Card-shop session stock for custom card IDs (mirrors gCustomShopCardQty while shopping).
_kernel_malloc_ewram_array gCustomShopTempCardQty, CUSTOM_CARD_QTY_BYTES

@ Custom trunk menu list tail (u16 card IDs) and sort scratch (vanilla + custom entries).
_kernel_malloc_ewram_array gTrunkMenuCustomCards, TRUNK_MENU_CUSTOM_CARD_BYTES
_kernel_malloc_ewram_array gTrunkMenuSortCards, TRUNK_MENU_SORT_LIST_BYTES
@ Cached trunk list size when hide_unowned_trunk_cards is enabled (avoids full scans per scroll).
_kernel_malloc_ewram gTrunkVisibleCardCount, 0x2
_kernel_malloc_ewram gTrunkVisibleStandardCount, 0x2

@ Multiple player decks (decks 1/2/3 card lists in EWRAM; deck 1 also mirrored in vanilla save).
.set PLAYER_DECK_CARD_BYTES, 0x50
_kernel_malloc_ewram_array gPlayerDeck1Cards, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram_array gPlayerDeck2Cards, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram_array gPlayerDeck3Cards, PLAYER_DECK_CARD_BYTES
@ Legacy-reserved capacity slots. Runtime deck capacity is the single vanilla gDeckCapacity.
_kernel_malloc_ewram gPlayerDeck2Capacity, 0x4
_kernel_malloc_ewram gPlayerDeck3Capacity, 0x4
_kernel_malloc_ewram gActiveDeckIndex, 0x1

@ Debug menu: AI controls both duelists when enabled.
_kernel_malloc_ewram gDebugAiBothSidesMode, 1
_kernel_malloc_ewram gDebugSaveAnywhereData, 0xC
_kernel_malloc_ewram gDebugMenuPendingSaveAnywhere, 0x1
_kernel_malloc_ewram gDebugSaveAnywherePendingCapture, 0x1
_kernel_malloc_ewram gDebugSaveAnywhereRestorePending, 0x1
_kernel_malloc_ewram gDebugSaveAnywhereApplyCoordsPending, 0x1
_kernel_malloc_ewram gDebugSaveAnywhereOpenDialogPending, 0x1
_kernel_malloc_ewram gDebugSaveAnywhereOpenDialogReady, 0x1

@ Debug menu: active duel ruleset (default / Duelist Kingdom).
_kernel_malloc_ewram gDebugRuleset, 1

@ Duelist Kingdom: active duelist already attacked this turn.
_kernel_malloc_ewram gDebugRulesetTurnAttackUsed, 1

@ The Dark Door: active duelist already attacked this turn while it is on the field.
_kernel_malloc_ewram gTheDarkDoorTurnAttackUsed, 1

@ AI simulation: saved per-turn attack flags while vanilla AI save/restore runs.
_kernel_malloc_ewram gAiSimSavedDebugRulesetTurnAttackUsed, 1
_kernel_malloc_ewram gAiSimSavedTheDarkDoorTurnAttackUsed, 1

@ Smarter AI duel-local memory (last action, board knowledge, attack order).
_kernel_malloc gAiDuelMemory, 40

@ Skip one overworld end-frame after a submenu (debug menu, deck viewer, etc.).
_kernel_malloc gSkipOverworldEndFrameAfterSubmenu, 1

@ World-map thought bubble visibility (u8 avoids unaligned IWRAM access).
_kernel_malloc gShowThoughtBubbles, 1

@ Debug deck preset swap: original deck 1 backup in EWRAM (40 x u16) while a preset is active.
_kernel_malloc_ewram_array gDebugDeckSwapBackup, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram gDebugDeckSwapActivePreset, 1
@ TRUE when gDebugDeckSwapBackup holds the saved original deck (also mirrored to flash on save).
_kernel_malloc_ewram gDebugDeckSwapBackupValid, 1

@ Active deck index while sub_80351F8 builds the vanilla 0x747 blob.
_kernel_malloc_ewram gPlayerDeckSaveRestoreActiveDeck, 0x1

@ DUEL_PLAYER/DUEL_OPPONENT whose next draw phase is skipped by Yata Garasu, else 0xFF.
_kernel_malloc_ewram gYataGarasuSkipDrawDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT whose next draw phase is skipped by Time Seal, else 0xFF.
_kernel_malloc_ewram gTimeSealSkipDrawDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT whose draw phases are skipped by Reckless Greed, else 0xFF.
_kernel_malloc_ewram gRecklessGreedSkipDrawDuelist, 1
@ Remaining draw phases to skip for Reckless Greed (0 when inactive).
_kernel_malloc_ewram gRecklessGreedSkipDrawRemaining, 1
@ Thousand Energy: fixed monster row + column bitmask for end-of-turn destruction.
_kernel_malloc_ewram gThousandEnergyDestroyMask, 1
_kernel_malloc_ewram gThousandEnergyFixedMonsterRow, 1
@ Limiter Removal: same shape as Thousand Energy.
_kernel_malloc_ewram gLimiterRemovalDestroyMask, 1
_kernel_malloc_ewram gLimiterRemovalFixedMonsterRow, 1
@ Set when The Unhappy Maiden ends the active duelist's turn during battle.
@ Allocated last so earlier EWRAM symbols (trunk/sort buffers) keep stable addresses.
_kernel_malloc_ewram gForceActiveTurnEnd, 1
@ Nonzero after battle destruction until effect text/turn-end resolve (see the_unhappy_maiden.c).
_kernel_malloc_ewram gPendingUnhappyMaiden, 1
@ Set when Sangan/Witch is sent to graveyard during battle; cleared after battle UI.
_kernel_malloc_ewram gDeferGraveyardDrawBattleResolve, 1
@ DUEL_PLAYER/DUEL_OPPONENT draw pending after graveyard popup, else PENDING_GRAVEYARD_DRAW_NONE.
_kernel_malloc_ewram gPendingGraveyardDrawFixedDuelist, 1
@ TRUE when the most recent graveyard sentinel write came from a field zone, not hand.
_kernel_malloc_ewram gGraveyardSendWasFromField, 1
@ TRUE when the next field ClearZone came from a return-to-hand copy, not destruction.
_kernel_malloc_ewram gSuppressSkullInvitationDamage, 1
_kernel_malloc_ewram gFamiliarKnightBattleDestroyPending, 1
@ DUEL_PLAYER/DUEL_OPPONENT controller for a pending Vampire Baby battle summon, else 0xFF.
_kernel_malloc_ewram gVampireBabyPendingController, 1
@ Fixed duelist whose graveyard holds the destroyed monster for Vampire Baby.
_kernel_malloc_ewram gVampireBabyPendingGraveyardDuelist, 1
@ Card ID of the monster Vampire Baby destroyed in battle.
_kernel_malloc_ewram gVampireBabyPendingCardId, 2
@ DUEL_PLAYER/DUEL_OPPONENT hand discard pending for Mefist, else 0xFF.
_kernel_malloc_ewram gPendingMefistDiscardDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT LP gain pending for Guardian Angel Joan, else 0xFF.
_kernel_malloc_ewram gPendingGuardianAngelJoanDuelist, 1
@ ponytail: pad so the u16 below lands on an even EWRAM address (ARM7 misreads odd halfwords).
_kernel_malloc_ewram gPendingGuardianAngelJoanPad, 1
@ Original ATK of the monster Joan destroyed in battle.
_kernel_malloc_ewram gPendingGuardianAngelJoanDestroyedAtk, 2
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
@ CUSTOM_CARD_QTY_BYTES is padded to 200 (0xC8) in tools/add_card_art.py
@ (render_card_memory_sizes_asm) so that adding new cards does not shift
@ the flash save layout.  Bump the minimum if custom cards exceed 200.
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
_kernel_malloc_flash gDebugRuleset,             0x1
_kernel_malloc_flash gDebugDeckSwapBackup,     PLAYER_DECK_CARD_BYTES
_kernel_malloc_flash gDebugDeckSwapBackupValid, 0x1
_kernel_malloc_flash gDebugSaveAnywhereData,    0xC
