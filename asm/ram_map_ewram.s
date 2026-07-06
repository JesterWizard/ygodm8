@ =============================================================================
@ EWRAM free space
@ =============================================================================
@ Range: 0x02025840–0x02040000 (larger runtime arrays and duel state)

SET_DATA FreeEwramSpaceTop,     0x02025840
SET_DATA FreeEwramSpaceBottom,  0x02040000
SET_DATA UsedFreeEwramSpaceTop, FreeEwramSpaceBottom

.macro _kernel_malloc_ewram name, size
    .set UsedFreeEwramSpaceTop, UsedFreeEwramSpaceTop - \size
    SET_DATA \name, UsedFreeEwramSpaceTop
.endm

.macro _kernel_malloc_ewram_array name, size
    .set UsedFreeEwramSpaceTop, UsedFreeEwramSpaceTop - \size
    SET_ARRAY \name, UsedFreeEwramSpaceTop, \size
.endm

@ -- Cost seed & delayed effects -----------------------------------------------

@ Persistent randomized-cost seed record lives in the save slot buffer.
_kernel_malloc_ewram sStoredCostSeedRecord, 0x8

@ Bitfield for one-shot delayed duel effects keyed by duelist.
_kernel_malloc_ewram_array gDelayedDuelEffects, 0x2

@ -- Expanded graveyard (two duelists x 40 u16 card IDs = 0xA0 bytes total) ------------
@ See documentation/expanded-graveyard.md

_kernel_malloc_ewram_array gExpandedGraveyard, 0xA0

@ -- Removed from play (two duelists x 40 u16 card IDs = 0xA0 bytes total) -----------
@ See documentation/removed-from-play.md

_kernel_malloc_ewram_array gRemovedFromPlay, 0xA0

@ -- Hand modifiers & board stat overlays --------------------------------------

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

@ Creature Swap pending target zones during activation.
_kernel_malloc_ewram gCreatureSwapPlayerRow, 1
_kernel_malloc_ewram gCreatureSwapPlayerCol, 1
_kernel_malloc_ewram gCreatureSwapOppRow, 1
_kernel_malloc_ewram gCreatureSwapOppCol, 1

@ Riryoku ATK deltas keyed by gDuel.board cell index (20 cells x 2 bytes).
_kernel_malloc_ewram_array gRiryokuAtkDelta, 0x28

@ Power Bond ATK bonus keyed by gDuel.board cell index (20 cells x 2 bytes).
_kernel_malloc_ewram_array gPowerBondAtkBonus, 0x28
@ Power Bond End Phase burn pending for the turn player (2 bytes).
_kernel_malloc_ewram gPowerBondEndPhaseBurn, 2

@ Mirror Wall permanent ATK-halve flags keyed by gDuel.board cell index (20 cells x 1 byte).
_kernel_malloc_ewram_array gMirrorWallHalvedMask, 0x14

@ Gaia fusion effect: permanent target ATK delta keyed by board cell (20 cells x 2 bytes).
_kernel_malloc_ewram_array gElementalHeroGaiaTargetAtkDelta, 0x28
@ Board cell index for Gaia's active ATK boost (0xFFFF = none).
_kernel_malloc_ewram gElementalHeroGaiaBoostCellIndex, 2
@ ATK Gaia gained from its fusion effect while still on field.
_kernel_malloc_ewram gElementalHeroGaiaBoostAmount, 2

@ Big Bang Shot equip markers: 3 slots per duelist (target fixed col+1, 0=inactive).
_kernel_malloc_ewram_array gBigBangShotTargetCol, 6

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

@ -- Custom card inventory (EWRAM; flash mirrors in SRAM below) ----------------
@ CUSTOM_CARD_QTY_BYTES is padded to 200 — bump if cards exceed 200.
@ Keep this block contiguous; do not interleave other symbols between qty arrays.

@ Expanded card-shop sorted list, padded to full 7-card rows for every generated card.
_kernel_malloc_ewram_array gCustomShopCardList, CUSTOM_SHOP_CARD_LIST_BYTES

_kernel_malloc_ewram_array gCustomTrunkCardQty, CUSTOM_CARD_QTY_BYTES
_kernel_malloc_ewram_array gCustomShopCardQty, CUSTOM_CARD_QTY_BYTES
_kernel_malloc_ewram_array gCustomPlayerTempCardQty, CUSTOM_CARD_QTY_BYTES
@ Entropy seed mixed into cost randomization LFSR when randomize_card_costs_at_start.
_kernel_malloc_ewram gCostEntropyState, 0x4

@ Trunk + deck ownership totals for custom card IDs (grows with CUSTOM_CARD_QTY_BYTES).
_kernel_malloc_ewram_array gCustomTotalCardQty, CUSTOM_CARD_QTY_BYTES

@ Card-shop session stock for custom card IDs (mirrors gCustomShopCardQty while shopping).
_kernel_malloc_ewram_array gCustomShopTempCardQty, CUSTOM_CARD_QTY_BYTES

@ -- Trunk menu ----------------------------------------------------------------

@ Custom trunk menu list tail (u16 card IDs) and sort scratch (vanilla + custom entries).
_kernel_malloc_ewram_array gTrunkMenuCustomCards, TRUNK_MENU_CUSTOM_CARD_BYTES
_kernel_malloc_ewram_array gTrunkMenuSortCards, TRUNK_MENU_SORT_LIST_BYTES
@ Cached trunk list size when hide_unowned_trunk_cards is enabled (avoids full scans per scroll).
_kernel_malloc_ewram gTrunkVisibleCardCount, 0x2
_kernel_malloc_ewram gTrunkVisibleStandardCount, 0x2

@ -- Player decks --------------------------------------------------------------

.set PLAYER_DECK_CARD_BYTES, 0x50

@ Multiple player decks (decks 1/2/3 card lists in EWRAM; deck 1 also mirrored in vanilla save).
_kernel_malloc_ewram_array gPlayerDeck1Cards, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram_array gPlayerDeck2Cards, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram_array gPlayerDeck3Cards, PLAYER_DECK_CARD_BYTES
@ Legacy-reserved capacity slots. Runtime deck capacity is the single vanilla gDeckCapacity.
_kernel_malloc_ewram gPlayerDeck2Capacity, 0x4
_kernel_malloc_ewram gPlayerDeck3Capacity, 0x4
_kernel_malloc_ewram gActiveDeckIndex, 0x1

@ -- Debug menu & duel rulesets ------------------------------------------------

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

@ Timed duel puzzles: active id (index + 1), pending menu selection, completion bitfield.
_kernel_malloc_ewram gTimedDuelActiveId, 1
_kernel_malloc_ewram gDebugMenuPendingTimedDuelIndex, 1
_kernel_malloc_ewram_array gTimedDuelCompletionFlags, 0x10

@ Duelist Kingdom: active duelist already attacked this turn.
_kernel_malloc_ewram gDebugRulesetTurnAttackUsed, 1

@ The Dark Door: active duelist already attacked this turn while it is on the field.
_kernel_malloc_ewram gTheDarkDoorTurnAttackUsed, 1

@ TRUE while AiSimulateAllCandidateActions runs; must be EWRAM (not APPEND_DATA/ROM).
_kernel_malloc_ewram gAiSimInBatch, 1
_kernel_malloc_ewram gAiSimInBatchPad, 1

@ AI simulation: saved per-turn attack flags while vanilla AI save/restore runs.
_kernel_malloc_ewram gAiSimSavedDebugRulesetTurnAttackUsed, 1
_kernel_malloc_ewram gAiSimSavedTheDarkDoorTurnAttackUsed, 1
_kernel_malloc_ewram gAiSimSavedVengefulBogSpiritMaskOpponentRow, 1
_kernel_malloc_ewram gAiSimSavedVengefulBogSpiritMaskPlayerRow, 1

@ -- IWRAM bump (mid-EWRAM block; uses _kernel_malloc above) -------------------
@ Smarter AI, overworld, and intro state need IWRAM but sit mid-EWRAM for stable layout.

@ Smarter AI duel-local memory (last action, board knowledge, attack order).
_kernel_malloc gAiDuelMemory, 40

@ Skip one overworld end-frame after a submenu (debug menu, deck viewer, etc.).
_kernel_malloc gSkipOverworldEndFrameAfterSubmenu, 1

@ World-map thought bubble visibility (u8 avoids unaligned IWRAM access).
_kernel_malloc gShowThoughtBubbles, 1

@ -- Debug deck swap & save restore --------------------------------------------

@ Debug deck preset swap: original deck 1 backup in EWRAM (40 x u16) while a preset is active.
_kernel_malloc_ewram_array gDebugDeckSwapBackup, PLAYER_DECK_CARD_BYTES
_kernel_malloc_ewram gDebugDeckSwapActivePreset, 1
@ TRUE when gDebugDeckSwapBackup holds the saved original deck (also mirrored to flash on save).
_kernel_malloc_ewram gDebugDeckSwapBackupValid, 1

@ Active deck index while sub_80351F8 builds the vanilla 0x747 blob.
_kernel_malloc_ewram gPlayerDeckSaveRestoreActiveDeck, 0x1

@ -- Draw-phase skip flags -----------------------------------------------------

@ DUEL_PLAYER/DUEL_OPPONENT whose next draw phase is skipped by Yata Garasu, else 0xFF.
_kernel_malloc_ewram gYataGarasuSkipDrawDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT whose next draw phase is skipped by Time Seal, else 0xFF.
_kernel_malloc_ewram gTimeSealSkipDrawDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT whose draw phases are skipped by Reckless Greed, else 0xFF.
_kernel_malloc_ewram gRecklessGreedSkipDrawDuelist, 1
@ Remaining draw phases to skip for Reckless Greed (0 when inactive).
_kernel_malloc_ewram gRecklessGreedSkipDrawRemaining, 1
@ Nonzero while PerformGuardianTreasureDrawPhaseDraws is drawing (Drop Off gate).
_kernel_malloc_ewram gDrawPhaseNormalDrawActive, 1
@ ponytail: pad keeps even EWRAM alignment for following u16 symbols.
_kernel_malloc_ewram gDrawPhaseNormalDrawActivePad, 1
@ DUEL_PLAYER/DUEL_OPPONENT whose next draw phase is skipped by Fenrir, else 0xFF.
_kernel_malloc_ewram gFenrirSkipDrawDuelist, 1
@ ponytail: pad keeps even EWRAM alignment after Fenrir skip-draw byte.
_kernel_malloc_ewram gFenrirSkipDrawDuelistPad, 1

@ -- Title screen & video player -----------------------------------------------

@ Title screen idle frame counter (u16, counts frames with no button press).
_kernel_malloc_ewram gTitleScreenIdleFrames, 2

@ Set to 1 after the intro video finishes playing. Lives in IWRAM so it survives the
@ COMET blob's bx 0x08000000 cold boot (crt0 / AgbMain don't clear IWRAM). The blob
@ copies code to 0x03000000-0x03001524; our IWRAM pool is at 0x03007xxx, well above
@ the overwritten range.
_kernel_malloc gIntroVideoPlayed, 1

@ Video player state: 1 = playing, 0 = idle.
_kernel_malloc_ewram gVideoPlayerState, 1
@ ponytail: pad keeps gVideoPlayerFrameIndex on an even EWRAM address.
_kernel_malloc_ewram gVideoPlayerStatePad, 1
@ Current frame index being played.
_kernel_malloc_ewram gVideoPlayerFrameIndex, 2

@ -- End-of-turn field spell destruction ---------------------------------------

@ Thousand Energy: fixed monster row + column bitmask for end-of-turn destruction.
_kernel_malloc_ewram gThousandEnergyDestroyMask, 1
_kernel_malloc_ewram gThousandEnergyFixedMonsterRow, 1
@ Limiter Removal: same shape as Thousand Energy.
_kernel_malloc_ewram gLimiterRemovalDestroyMask, 1
_kernel_malloc_ewram gLimiterRemovalFixedMonsterRow, 1
@ Triangle Power: column bitmasks for both monster rows, destroyed at end phase.
_kernel_malloc_ewram gTrianglePowerDestroyMaskPlayer, 1
_kernel_malloc_ewram gTrianglePowerDestroyMaskOpponent, 1
@ ponytail: pad keeps EWRAM layout stable; Heated Heart stats come from dynamic equip link.
_kernel_malloc_ewram gHeatedHeartPad, 2

@ -- Turn flow & AI re-simulation ----------------------------------------------

@ Set when The Unhappy Maiden ends the active duelist's turn during battle.
@ Allocated last so earlier EWRAM symbols (trunk/sort buffers) keep stable addresses.
_kernel_malloc_ewram gForceActiveTurnEnd, 1
@ Set when Call of the Haunted interrupts an AI attack; AI_Main re-simulates actions.
_kernel_malloc_ewram gAiResimulateAfterCallOfTheHaunted, 1
_kernel_malloc_ewram gAiSimSavedResimulateAfterCallOfTheHaunted, 1
@ Nonzero after battle destruction until effect text/turn-end resolve (see the_unhappy_maiden.c).
_kernel_malloc_ewram gPendingUnhappyMaiden, 1

@ -- Battle graveyard deferrals ------------------------------------------------

@ Set when Sangan/Witch is sent to graveyard during battle; cleared after battle UI.
_kernel_malloc_ewram gDeferGraveyardDrawBattleResolve, 1
@ DUEL_PLAYER/DUEL_OPPONENT draw pending after graveyard popup, else PENDING_GRAVEYARD_DRAW_NONE.
_kernel_malloc_ewram gPendingGraveyardDrawFixedDuelist, 1
@ TRUE when the most recent graveyard sentinel write came from a field zone, not hand.
_kernel_malloc_ewram gGraveyardSendWasFromField, 1
@ TRUE when the next field ClearZone came from a return-to-hand copy, not destruction.
_kernel_malloc_ewram gSuppressSkullInvitationDamage, 1
_kernel_malloc_ewram gFamiliarKnightBattleDestroyPending, 1
_kernel_malloc_ewram gElementalHeroFlashBattleDestroyPending, 1
@ ponytail: pad keeps gVampireBabyPendingCardId on an even EWRAM address.
_kernel_malloc_ewram gElementalHeroFlashPendingPad, 1

@ -- Battle destruction triggers (per-card pending state) ------------------------

@ Bitmask: DUEL_PLAYER/DUEL_OPPONENT had Giant Rat destroyed in battle.
_kernel_malloc_ewram gGiantRatBattleDestroyMask, 1
@ DUEL_PLAYER/DUEL_OPPONENT controller for a pending Vampire Baby battle summon, else 0xFF.
_kernel_malloc_ewram gVampireBabyPendingController, 1
@ Fixed duelist whose graveyard holds the destroyed monster for Vampire Baby.
_kernel_malloc_ewram gVampireBabyPendingGraveyardDuelist, 1
@ Card ID of the monster Vampire Baby destroyed in battle.
_kernel_malloc_ewram gVampireBabyPendingCardId, 2
@ TRUE when the next hand ClearZone is a graveyard send, not summon cleanup.
_kernel_malloc_ewram gAbsoluteZeroHandGyClearPending, 1
@ TRUE while hand ClearZone is summon placement cleanup, not a leave.
_kernel_malloc_ewram gAbsoluteZeroHandSummonCleanupPending, 1
@ TRUE while fusion material payment / result summon runs.
_kernel_malloc_ewram gAbsoluteZeroSuppressLeave, 1
@ ponytail: pad keeps gGhostKnightOfJackalPendingController on an even EWRAM address.
_kernel_malloc_ewram gAbsoluteZeroPendingPad, 1
@ DUEL_PLAYER/DUEL_OPPONENT controller for a pending Ghost Knight of Jackal battle summon, else 0xFF.
_kernel_malloc_ewram gGhostKnightOfJackalPendingController, 1
@ Fixed duelist whose graveyard holds the monster Jackal destroyed in battle.
_kernel_malloc_ewram gGhostKnightOfJackalPendingGraveyardDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT hand discard pending for Mefist, else 0xFF.
_kernel_malloc_ewram gPendingMefistDiscardDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT hand discard pending for Reaper on the Nightmare, else 0xFF.
_kernel_malloc_ewram gPendingReaperDiscardDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT hand discard pending for Spirit Reaper, else 0xFF.
_kernel_malloc_ewram gPendingSpiritReaperDiscardDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT LP gain pending for Guardian Angel Joan, else 0xFF.
_kernel_malloc_ewram gPendingGuardianAngelJoanDuelist, 1
@ Original ATK of the monster Joan destroyed in battle.
_kernel_malloc_ewram gPendingGuardianAngelJoanDestroyedAtk, 2
@ DUEL_PLAYER/DUEL_OPPONENT LP gain pending for Royal Knight, else 0xFF.
_kernel_malloc_ewram gPendingRoyalKnightDuelist, 1
@ ponytail: pad keeps gPendingRoyalKnightDestroyedDef on an even EWRAM address.
_kernel_malloc_ewram gPendingRoyalKnightDestroyedDefPad, 1
@ Original DEF of the monster Royal Knight destroyed in battle.
_kernel_malloc_ewram gPendingRoyalKnightDestroyedDef, 2
@ DUEL_PLAYER/DUEL_OPPONENT LP gain pending for Elemental HERO Steam Healer, else 0xFF.
_kernel_malloc_ewram gPendingElementalHeroSteamHealerDuelist, 1
@ ponytail: pad keeps gPendingElementalHeroSteamHealerDestroyedAtk on an even EWRAM address.
_kernel_malloc_ewram gPendingElementalHeroSteamHealerDestroyedAtkPad, 1
@ Original ATK of the monster Steam Healer destroyed in battle.
_kernel_malloc_ewram gPendingElementalHeroSteamHealerDestroyedAtk, 2
@ DUEL_PLAYER/DUEL_OPPONENT burn pending for Elemental HERO Flame Wingman, else 0xFF.
_kernel_malloc_ewram gPendingElementalHeroFlameWingmanDuelist, 1
@ ponytail: pad keeps gPendingElementalHeroFlameWingmanDestroyedAtk on an even EWRAM address.
_kernel_malloc_ewram gPendingElementalHeroFlameWingmanDestroyedAtkPad, 1
@ Original ATK of the monster Flame Wingman destroyed in battle.
_kernel_malloc_ewram gPendingElementalHeroFlameWingmanDestroyedAtk, 2
@ Flame Wingman / Shining Flare Wingman card id for pending battle-burn text.
_kernel_malloc_ewram gPendingElementalHeroFlameWingmanEffectCardId, 2
@ Tempest anchor/protected fixed zones; 0xFF when inactive.
_kernel_malloc_ewram gElementalHeroTempestAnchorRow, 1
_kernel_malloc_ewram gElementalHeroTempestAnchorCol, 1
_kernel_malloc_ewram gElementalHeroTempestProtectedRow, 1
_kernel_malloc_ewram gElementalHeroTempestProtectedCol, 1
@ Tempest activation targeting scratch (pick phase + origin zone).
_kernel_malloc_ewram gElementalHeroTempestPickPhase, 1
_kernel_malloc_ewram gElementalHeroTempestOriginRow, 1
_kernel_malloc_ewram gElementalHeroTempestOriginCol, 1

_kernel_malloc_ewram gElementalHeroWildedgeAttackedMask, 1
_kernel_malloc_ewram gElementalHeroWildedgeEffectActive, 1
_kernel_malloc_ewram gElementalHeroWildedgeAnchorRow, 1
_kernel_malloc_ewram gElementalHeroWildedgeAnchorCol, 1
_kernel_malloc_ewram gElementalHeroNecroshadeUsed, 1
@ Elemental HERO Core: post-battle destroy origin zone (0xFF = none).
_kernel_malloc_ewram gElementalHeroCoreBattledRow, 1
_kernel_malloc_ewram gElementalHeroCoreBattledCol, 1
@ Elemental HERO Ice Edge: post-direct-attack destroy origin zone (0xFF = none).
_kernel_malloc_ewram gElementalHeroIceEdgeBattledRow, 1
_kernel_malloc_ewram gElementalHeroIceEdgeBattledCol, 1
@ Elemental HERO Blazeman: copied stats source + zone (until end of turn).
_kernel_malloc_ewram gElementalHeroBlazemanCopySourceId, 2
_kernel_malloc_ewram gElementalHeroBlazemanCopyRow, 1
_kernel_malloc_ewram gElementalHeroBlazemanCopyCol, 1
@ TRUE when Core was destroyed from field and revive may trigger.
_kernel_malloc_ewram gElementalHeroCoreRevivePending, 1
@ ponytail: pad restores 2-byte alignment after removing a duplicate Core block.
_kernel_malloc_ewram gElementalHeroCorePad, 1
@ The Supremacy Sun: armed + next-standby-ready flags per fixed duelist.
_kernel_malloc_ewram_array gTheSupremacySunArmed, 2
_kernel_malloc_ewram_array gTheSupremacySunStandbyReady, 2
_kernel_malloc_ewram gTheSupremacySunOwnEffectSummon, 1
@ TRUE while resolving Archlord Kristya's own Special Summon effect.
_kernel_malloc_ewram gArchlordKristyaEffectSummon, 1
@ Elemental HERO Sunrise: once-per-turn flags + post-battle destroy origin (0xFF = none).
_kernel_malloc_ewram gElementalHeroSunriseSearchUsed, 1
_kernel_malloc_ewram gElementalHeroSunriseDestroyUsed, 1
_kernel_malloc_ewram gElementalHeroSunriseDestroyRow, 1
_kernel_malloc_ewram gElementalHeroSunriseDestroyCol, 1
@ Per-board-cell Gemini awakened state for Elemental HERO Neos Alius (4 rows x 5 cols).
_kernel_malloc_ewram_array gNeosAliusAwakenedBoard, 0x14
@ TRUE when Lesser Fiend destroyed an opponent's monster by battle and banish is pending.
_kernel_malloc_ewram gPendingLesserFiendBanishRow, 1
_kernel_malloc_ewram gPendingLesserFiendBanishCol, 1
_kernel_malloc_ewram gPendingDarkMagicianOfChaosBanishRow, 1
_kernel_malloc_ewram gPendingDarkMagicianOfChaosBanishCol, 1
@ DUEL_PLAYER/DUEL_OPPONENT draw pending for Airknight Parshath, else 0xFF.
_kernel_malloc_ewram gPendingAirknightParshathDrawDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT draw-until-7 pending for Sasuke Samurai #3, else 0xFF.
_kernel_malloc_ewram gPendingSasukeSamurai3DrawDuelist, 1
@ DUEL_PLAYER/DUEL_OPPONENT controller for a pending Needle Burrower battle hit, else 0xFF.
_kernel_malloc_ewram gPendingNeedleBurrowerController, 1
@ Level of the monster Needle Burrower destroyed in battle (damage = level * 500 at resolve).
_kernel_malloc_ewram gPendingNeedleBurrowerLevel, 1
@ TRUE while Yubel evolution special summons bypass the normal SS lock.
_kernel_malloc_ewram gYubelOwnEffectSummon, 1
@ TRUE when Yubel destroys itself during its End Phase tribute check.
_kernel_malloc_ewram gYubelSelfDestructActive, 1
@ TRUE when face-up Yubel left the monster field (not End Phase self-destruct).
_kernel_malloc_ewram gYubelLeftFieldPending, 1
@ TRUE when face-up Terror Incarnate left the monster field.
_kernel_malloc_ewram gYubelTerrorLeftFieldPending, 1
@ Fixed row/col for Ultimate Nightmare post-battle destroy, else YUBEL_PENDING_DESTROY_NONE.
_kernel_malloc_ewram gPendingYubelUltimateDestroyRow, 1
_kernel_malloc_ewram gPendingYubelUltimateDestroyCol, 1
@ Fixed row/col/owner while Yubel End Phase tribute targeting is active.
_kernel_malloc_ewram gYubelTributeOriginRow, 1
_kernel_malloc_ewram gYubelTributeOriginCol, 1
_kernel_malloc_ewram gYubelTributeOwner, 1
@ TRUE after this turn's Yubel/Terror End Phase chain has been started.
_kernel_malloc_ewram gYubelEndPhaseResolvedThisTurn, 1
@ TRUE when base Yubel reflected attack damage; popup_2 runs after battle anim.
_kernel_malloc_ewram gYubelAttackedReflectPending, 1
@ TRUE when Terror Incarnate reflected attack damage; popup_1 runs after battle anim.
_kernel_malloc_ewram gYubelTerrorAttackedReflectPending, 1
@ Fixed monster row for a pending Hyper Hammerhead bounce, else 0xFF.
_kernel_malloc_ewram gPendingHyperHammerheadRow, 1
@ Fixed monster column for a pending Hyper Hammerhead bounce.
_kernel_malloc_ewram gPendingHyperHammerheadCol, 1
@ Fixed monster row/col for pending D.D. Warrior banish (warrior + battled monster), else 0xFF.
_kernel_malloc_ewram gPendingDDWarriorWarriorRow, 1
_kernel_malloc_ewram gPendingDDWarriorWarriorCol, 1
_kernel_malloc_ewram gPendingDDWarriorOtherRow, 1
_kernel_malloc_ewram gPendingDDWarriorOtherCol, 1
@ Fixed monster row/col for a pending Des Kangaroo attacker destroy, else 0xFF.
_kernel_malloc_ewram gPendingDesKangarooAttackerRow, 1
_kernel_malloc_ewram gPendingDesKangarooAttackerCol, 1
@ DUEL_PLAYER/DUEL_OPPONENT LP gain pending for Absorbing Kid from the Sky, else 0xFF.
_kernel_malloc_ewram gPendingAbsorbingKidFromTheSkyDuelist, 1
@ Level of the monster Absorbing Kid destroyed in battle (heal = level * 300 at resolve).
_kernel_malloc_ewram gPendingAbsorbingKidFromTheSkyLevel, 1
@ Pending Coffin Seller 300LP hits deferred until battle UI closes.
_kernel_malloc_ewram gPendingCoffinSellerDamageToPlayer, 1
_kernel_malloc_ewram gPendingCoffinSellerDamageToOpponent, 1

@ -- Deferred LP triggers (Dark Room, Fire Princess) -----------------------------

@ Dark Room of Nightmare deferred effect-damage trigger.
_kernel_malloc_ewram gSuppressDarkRoomDamage, 1
_kernel_malloc_ewram gPendingDarkRoomTarget, 1
@ Fire Princess deferred LP-gain burn trigger.
_kernel_malloc_ewram gSuppressFirePrincessDamage, 1
_kernel_malloc_ewram gPendingFirePrincessTarget, 1
@ Fire Princess: skip re-trigger until controller LP rises again (player, opponent).
_kernel_malloc_ewram gFirePrincessLpGainHandled, 1
@ ponytail: pad keeps gLastHandledLpGainLp 2-byte aligned in EWRAM.
_kernel_malloc_ewram gLastHandledLpGainLpPad, 1
_kernel_malloc_ewram_array gLastHandledLpGainLp, 2

@ -- Maju Garzett tribute capture ------------------------------------------------

@ Great Maju Garzett tribute capture + per-cell atk/def/active (10 cells, 0x32 total).
_kernel_malloc_ewram_array gGreatMajuGarzettBoardAtk, 0x14
_kernel_malloc_ewram_array gGreatMajuGarzettBoardDef, 0x14
_kernel_malloc_ewram_array gGreatMajuGarzettBoardActive, 0xA
_kernel_malloc_ewram_array gGreatMajuGarzettTributeTotals, 0x4
_kernel_malloc_ewram gGreatMajuGarzettPendingSummon, 1
@ Maju Garzett tribute capture + per-cell atk/active (10 cells, 0x1E total).
_kernel_malloc_ewram gMajuGarzettPreArraysPad, 1
_kernel_malloc_ewram_array gMajuGarzettBoardAtk, 0x14
_kernel_malloc_ewram_array gMajuGarzettBoardActive, 0xA
_kernel_malloc_ewram_array gMajuGarzettTributeAtk, 0x2
_kernel_malloc_ewram gMajuGarzettPendingSummon, 1

@ The Tyrant Neptune tribute capture + per-cell atk/def/active/copy (10 cells).
_kernel_malloc_ewram gTheTyrantNeptunePreArraysPad, 1
_kernel_malloc_ewram_array gTheTyrantNeptuneBoardAtk, 0x14
_kernel_malloc_ewram_array gTheTyrantNeptuneBoardDef, 0x14
_kernel_malloc_ewram_array gTheTyrantNeptuneBoardActive, 0xA
_kernel_malloc_ewram_array gTheTyrantNeptuneCopiedCardId, 0x14
_kernel_malloc_ewram_array gTheTyrantNeptuneTributeTotals, 0x4
_kernel_malloc_ewram_array gTheTyrantNeptuneTributeIds, 0x6
_kernel_malloc_ewram gTheTyrantNeptuneTributeCount, 1
_kernel_malloc_ewram gTheTyrantNeptunePendingSummon, 1
@ Keep following Ring-of-Destruction byte + u16 pair halfword-aligned.
_kernel_malloc_ewram gTheTyrantNeptunePostPad, 1

@ Chimeratech Overdragon: per-cell material count + attacks used this turn (10 cells each).
_kernel_malloc_ewram_array gChimeratechOverdragonMaterialCount, 0xA
_kernel_malloc_ewram_array gChimeratechOverdragonAttacksUsed, 0xA

@ The Grand Jupiter: absorbed monsters in controller backrow (10 slots: opp 0-4, player 5-9).
_kernel_malloc_ewram_array gGrandJupiterEquipActive, 0xA
_kernel_malloc_ewram_array gGrandJupiterEquipOriginalAtk, 0x14
_kernel_malloc_ewram_array gGrandJupiterEquipJupiterRow, 0xA
_kernel_malloc_ewram_array gGrandJupiterEquipJupiterCol, 0xA

@ Future Fusion: material count for pending summons (fixed backrow: opp 0-4, player 5-9).
@ ponytail: cannot use tempStage — permanent effects zero it before the delayed summon.
_kernel_malloc_ewram_array gFutureFusionMaterialCount, 0xA

@ -- Misc duel UI state ----------------------------------------------------------

@ Ring of Destruction: opponent monster row changed this action; fire after permanent scan.
_kernel_malloc_ewram gRingOfDestructionPending, 1
@ Debug menu: saved BG0CNT to restore overworld BG0 on exit (no flash storage needed).
_kernel_malloc_ewram gSavedDebugMenuBg0Cnt, 2
@ Card ID whose GY effect is negated by Harpie Lady 2, else CARD_NONE.
_kernel_malloc_ewram gHarpieLady2NegatedCardId, 2
@ Per-column turns remaining for Harpie Lady 3 attack lock (player row, opponent row).
_kernel_malloc_ewram gHarpieLady3RestrictTurns, 0xA
_kernel_malloc_ewram gHarpieLady3LastProcessedTurn, 1
@ PickZone targeting callbacks for Duel_BeginPickZone (4 function pointers = 16 bytes).
_kernel_malloc_ewram gPickZoneState, 0x10
@ ponytail: pad keeps gTheBigSaturnGyDamagePending on an even EWRAM address.
_kernel_malloc_ewram gTheBigSaturnGyDamagePendingPad, 1
@ ATK snapshot for The Big Saturn graveyard damage when destroyed by opponent effect.
_kernel_malloc_ewram gTheBigSaturnGyDamagePending, 2
@ Permanent-effect GY scan row (6 or 7) for pending Big Saturn damage.
_kernel_malloc_ewram gTheBigSaturnGyDamageTurnRow, 1
@ Field destroy (not hand) when pending was armed.
_kernel_malloc_ewram gTheBigSaturnGyDamageFromField, 1

@ -- Ameba control-switch burn (deferred until field gfx refresh) ----------------

@ Number of queued Ameba control-switch triggers (0..2).
_kernel_malloc_ewram gAmebaPendingCount, 1
@ DUEL_PLAYER/DUEL_OPPONENT damage target for each queued trigger.
_kernel_malloc_ewram gAmebaPendingDamageTarget0, 1
_kernel_malloc_ewram gAmebaPendingDamageTarget1, 1
@ Re-entry guard for flush during UpdateDuelGfxExceptField.
_kernel_malloc_ewram gAmebaFlushing, 1
@ AI sim snapshots (see ai_simulation_hooks.c).
_kernel_malloc_ewram gAiSimSavedAmebaPendingCount, 1
_kernel_malloc_ewram gAiSimSavedAmebaPendingDamageTarget0, 1
_kernel_malloc_ewram gAiSimSavedAmebaPendingDamageTarget1, 1
