@ =============================================================================
@ IWRAM free space
@ =============================================================================
@ Range: 0x03001678–0x03007E00 (hot paths, tiny scratch, time-sensitive state)

SET_DATA FreeRamSpaceTop,     0x03001678
SET_DATA FreeRamSpaceBottom,  0x03007E00
SET_DATA UsedFreeRamSpaceTop, FreeRamSpaceBottom

.macro _kernel_malloc name, size
    .set UsedFreeRamSpaceTop, UsedFreeRamSpaceTop - \size
    SET_DATA \name, UsedFreeRamSpaceTop
.endm

@ -- Fixed audio buffers (first bytes of IWRAM free space) ---------------------

@ m4a HQ mixer 16-bit mix buffer (0x580 bytes).
SET_DATA gM4aHqMixBuffer, 0x03001678

@ HQ mixer IWRAM execution buffer (MixerSize bytes, copied from ROM at init).
SET_DATA MixerBuffer, 0x03001BF8

@ -- Card economy & stat scratch -----------------------------------------------

@ Randomized card costs (one u16 per card ID).
_kernel_malloc sRandomizedCardCosts, CARD_COST_TABLE_BYTES

@ Reentrancy guard while Copycat resolves copied stats.
_kernel_malloc gComputingCopycatStats, 1
@ Reentrancy guard while Neos Alius patches display name from SetCardInfo.
_kernel_malloc gApplyingNeosAliusCardInfo, 1
@ ponytail: pad so following IWRAM u16 allocations stay 2-byte aligned.
_kernel_malloc gApplyingNeosAliusCardInfoPad, 1

@ -- Extra Normal Summon -------------------------------------------------------

@ Ultimate Offering extra-summon state for the active duelist's turn.
_kernel_malloc gUltimateOfferingExtraSummonPending, 1
_kernel_malloc gUltimateOfferingExtraSummonUsed, 1

@ Court of Justice hand ignition after a face-up Level 1 Fairy is on field.
_kernel_malloc gCourtOfJusticeIgnitionPending, 1
_kernel_malloc gCourtOfJusticeHandPlacementActive, 1

@ Executor Makyura: owner may activate eligible traps from hand this turn.
_kernel_malloc gExecutorMakyuraActivePlayer, 1
_kernel_malloc gExecutorMakyuraActiveOpponent, 1
_kernel_malloc gExecutorMakyuraPendingPopup, 1

@ Double Summon extra-summon state for the active duelist's turn.
_kernel_malloc gDoubleSummonExtraSummonPending, 1
_kernel_malloc gDoubleSummonExtraSummonUsed, 1

@ -- Duel HUD & debug menus ----------------------------------------------------

@ Duel board HUD turn counter (1-based, incremented at each turn start).
@ ponytail: 2-byte pad — byte flags above leave the bump cursor odd; one pad byte does not flip parity.
_kernel_malloc gDuelBoardTurnCountPad, 2
_kernel_malloc gDuelBoardTurnCount, 2

@ Debug Match Setter: selected duelist table index + 1, or 0 for none.
_kernel_malloc gDebugMatchSetterSelection, 1

@ Map Teleport viewer: overworld map id when the viewer opened (0xFF = no pending change).
_kernel_malloc gDebugMenuMapViewerInitialLocation, 1

@ Scene viewer: reload overworld and run on-enter script after the menu closes (0xFF = none).
_kernel_malloc gDebugMenuPendingSceneActive, 1
_kernel_malloc gDebugMenuPendingSceneMapId, 1
_kernel_malloc gDebugMenuPendingSceneState, 1
_kernel_malloc gDebugMenuPendingSceneConnection, 1

@ -- Tribute summon & Soul Exchange --------------------------------------------

@ Active while Soul Exchange lets the player tribute opponent monsters this turn.
_kernel_malloc gSoulExchangeActive, 1

@ Active while Cybernetic Fusion Support lets fusion spells use hand/field/GY materials.
@ Also keeps gPendingTributeSummonCardId 2-byte aligned (replaces former pad byte).
_kernel_malloc gCyberneticFusionSupportActive, 1

@ Counts as one paid tribute when an opponent monster was used for Soul Exchange.
_kernel_malloc gSoulExchangeTributeCredit, 1

@ Tribute count paid for the most recent monster Normal Summon placement.
_kernel_malloc gPendingSummonTributeCount, 1

@ Card being tribute summoned while the player is paying tributes.
_kernel_malloc gPendingTributeSummonCardId, 2

@ -- Per-card IWRAM flags --------------------------------------------------------

@ Sasuke Samurai #2: blocks inactive-duelist backrow trap activations until end phase.
_kernel_malloc gSasukeSamurai2InactiveBackrowTrapBlock, 1

@ Blast Held by a Tribute: tribute-summon marks per fixed monster row (5 cols each).
_kernel_malloc gTributeSummonedMonsterMaskOpponentRow, 1
_kernel_malloc gTributeSummonedMonsterMaskPlayerRow, 1

@ Vengeful Bog Spirit: same-turn summon marks per fixed monster row (5 cols each).
_kernel_malloc gVengefulBogSpiritSummonedMaskOpponentRow, 1
_kernel_malloc gVengefulBogSpiritSummonedMaskPlayerRow, 1

@ Extra tribute credit from Double Coston's dark-only bonus (not generic).
_kernel_malloc gDoubleCostonDarkBonusPaid, 1

@ Slifer summon penalty waiting for summon placement to finish.
_kernel_malloc gSliferPendingPenaltyActive, 1
_kernel_malloc gSliferPendingPenaltyBoardRow, 1
_kernel_malloc gSliferPendingPenaltyCol, 1

@ Swords of Revealing Light: skip end-of-turn decrement on the activating turn.
_kernel_malloc gSorlSkipDecrementAfterActivation, 1
@ ponytail: keep downstream u16 symbols 2-byte aligned after the extra byte above.
_kernel_malloc gSorlSkipDecrementAfterActivationPad, 1

@ -- Shop, event CG, field restrictions ----------------------------------------

@ Duel win shop drop popup: count plus up to three (cardId, qty) pairs.
_kernel_malloc gDuelShopDropRecord, 0x10

@ Event CG session state (overworld dialogue cutscene graphics).
_kernel_malloc gCgSessionOpen, 1
_kernel_malloc gCgActive, 1
_kernel_malloc gCgFadeSpeed, 1
_kernel_malloc gCgId, 1
@ ponytail: pad so gCgSavedDispcnt lands on an even IWRAM address.
_kernel_malloc gCgSavedDispcntPad, 1
_kernel_malloc gCgSavedDispcnt, 2

@ Active attack-blocking field effects (SORL, Gravity Bind, Level Limit Area B).
_kernel_malloc gDuelAttackRestrictionsActive, 1

@ ponytail: pad so gWallOfRevealingLightAttackThreshold lands on an even IWRAM address.
_kernel_malloc gWallOfRevealingLightAttackThresholdPad, 1
_kernel_malloc gWallOfRevealingLightAttackThreshold, 2

@ World Suppression: field spell effects negated until end of turn.
_kernel_malloc gWorldSuppressionNegatesFieldSpells, 1
