# Session Log

Working history for AI and human contributors. **Read this at the start of every session** before making changes. **Append an entry when you finish meaningful work.**

Format for new entries (newest first):

```markdown
## YYYY-MM-DD — Short title

**Worked on:** …
**Files:** …
**Outcome:** …
**Open / next:** …
```

---

## 2026-06-18 — Dice Jar custom card

**Worked on:** Added Dice Jar to manifest/trunk (LIGHT Rock L3 200/300, passcode 03549275, `MONSTER_EFFECT_DICE_JAR`). FLIP effect in `activated_effects/dice_jar.c`: both players roll d6, lower roll takes winner's roll × 500 (6000 if winner rolled 6), ties reroll. Uses `Duel_ShowEffectTextTyped`, `RandRangeU8`, `Duel_ChangeLp`. `card_in_hand_1 = DICE_JAR` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/constants/monster_effects.h`, `src_custom/activated_effects/dice_jar.c`, `src_custom/monster_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, `tests/host/test_dice_jar.py`

**Outcome:** `make test-cards-build` passes; host test passes.

**Open / next:** In-game confirm FLIP rolls, tie reroll, and 6000 damage on winner's 6.

---

## 2026-06-18 — Gravekeeper's Servant custom card

**Worked on:** Added Gravekeeper's Servant to manifest/trunk (continuous spell, passcode 16762927). Opponent must mill 1 from Deck to declare an attack while controller's face-up copy is active (`TryPayGravekeepersServantAttackCost`, chained via `TryPayAttackFieldCosts` with Toll). Imperial Order aware; empty deck blocks attack. `card_in_hand_1 = GRAVEKEEPERS_SERVANT` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/gravekeepers_servant.h`, `include/toll.h`, `src_custom/spell_effects/gravekeepers_servant.c`, `src_custom/spell_effects/toll.c`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/card_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm opponent cannot attack with empty deck; mills 1 per attack when Servant is active.

---

## 2026-06-18 — Jar Robber custom card

**Worked on:** Added Jar Robber to manifest/trunk (trap, passcode 33784505, `trapEffect` 40). Set on backrow auto-fires when opponent activates Pot of Greed (`TryJarRobberPotOfGreedCounter` in spell activation, before trap window): negates PoG, sends both to GY, draws 1. `card_in_hand_1 = JAR_ROBBER` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/jar_robber.h`, `src_custom/trap_effects/jar_robber.c`, `src_custom/spell_effect_hooks.c`, `src_custom/trap_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm set Jar Robber auto-negates opponent Pot of Greed and draws 1.

---

## 2026-06-18 — Dark Snake Syndrome custom card

**Worked on:** Added Dark Snake Syndrome to manifest/trunk (continuous spell, passcode 47233801). Standby damage via `TryApplyDarkSnakeSyndromeStandbyDamage`: 200 base to both players on controller's Standby, doubling each time (`permStage`). Wired spell activation, turn hooks, and `SPELL_TYPE_NORMAL`. `card_in_hand_1 = DARK_SNAKE_SYNDROME` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/dark_snake_syndrome.h`, `src_custom/spell_effects/dark_snake_syndrome.c`, `src_custom/spell_effect_hooks.c`, `src_custom/turn_effect_hooks.c`, `src_custom/card_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm damage doubles each controller Standby (200 → 400 → 800 …).

---

## 2026-06-18 — Drillago custom card

**Worked on:** Added Drillago to manifest/trunk (`DRILLAGO`, DARK Machine L4 1600/1100, passcode 99050989). Continuous direct-attack passive via `CanDrillagoAttackDirectly` (Black Tyranno pattern): opponent backrow empty, only face-up monsters with 1600+ ATK. Wired into player and AI direct-attack paths. `card_in_hand_1 = DRILLAGO` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/drillago.h`, `src_custom/card_passives/drillago.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/ai_attack_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm direct attack when opponent only has face-up 1600+ ATK monsters; blocked with backrow or sub-1600 ATK monsters.

---


**Worked on:** Effect still failed when Des Kangaroo was destroyed on opponent turn despite attacker ATK < DEF (GBA attribute disadvantage path, unk18=17). Removed live-zone + `FLAG_GRAVEYARD_PLAYER` guards; judge from battle `sActionData` only. Moved `ApplyDesKangarooBattleEffect` before normal graveyard sends so attacker is still marked.

**Files:** `src_custom/battle_effects/des_kangaroo.c`, `src_custom/battle_damage_hooks.c`

**Outcome:** `make test-cards-build` passes.

---

## 2026-06-18 — Des Kangaroo opponent-attack fix

**Worked on:** Opponent AI attacks deferred Des Kangaroo resolve to post-battle animation (`sub_8040EF0`) like Hyper Hammerhead — early resolve in `ai_attack_hooks` cleared pending before animation. Added live zone validation (defender in DEF, attacker zone matches `sActionData`).

**Files:** `src_custom/battle_effects/des_kangaroo.c`, `src_custom/ai_attack_hooks.c`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm 1600 ATK vs 1700 DEF Des Kangaroo shows popup and destroys attacker after battle animation.

---

## 2026-06-18 — Des Kangaroo custom card

**Worked on:** Added Des Kangaroo to manifest/trunk (`DES_KANGAROO`, DARK Beast L4 1500/1700, passcode 78613627). Battle effect: when attacked in Defense Position, if attacker ATK < this card's DEF, destroy the attacker at end of damage step via deferred `Duel_DestroyZone`. `card_in_hand_1 = DES_KANGAROO` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/des_kangaroo.h`, `src_custom/battle_effects/des_kangaroo.c`, `src_custom/battle_damage_hooks.c`, `asm/ram_map.s`, `src_custom/code_803F02C_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_8041C94_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `src_custom/ai_attack_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm attacker destroyed when ATK < 1700 DEF; no effect when ATK ≥ DEF or Des Kangaroo is destroyed.

---

## 2026-06-18 — D.D. Warrior / Breaker effect fixes

**Worked on:** D.D. Warrior only marks/resolves when `sActionData` matches live monster-vs-monster zones. Breaker: spell counter = `permStage` (+500 ATK via normal stage boost); summon `IncrementPermStage`, activation `DecrementPermStage`; dropped RAM counter mask and custom overlay hooks.

**Files:** `src_custom/battle_effects/d_d_warrior.c`, `src_custom/ai_attack_hooks.c`, `src_custom/permanent_effects/breaker_the_magical_warrior.c`, `src_custom/activated_effects/breaker_the_magical_warrior.c`, `src_custom/card_hooks.c`, `src_custom/mini_card_hooks.c`, `src_custom/duel_helpers.c`, `include/breaker_the_magical_warrior.h`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm DD Warrior only on monster battles; Breaker shows 1600 + +300 stamp on summon, activation popup + destroy.

---

## 2026-06-18 — Breaker the Magical Warrior custom card

**Worked on:** Added Breaker the Magical Warrior to manifest/trunk (`BREAKER_THE_MAGICAL_WARRIOR`, DARK Spellcaster L4 1600/1000, passcode 71413901). Normal Summon places 1 Spell Counter (`permStage`, max 1) via placement hook; +300 ATK per counter via dynamic zone stats. Ignition: remove counter, MST-style Spell/Trap targeting, destroy via `Duel_DestroyZone`. `multiple_per_turn`, face-up activation allowed. `card_in_hand_1 = BREAKER_THE_MAGICAL_WARRIOR` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/breaker_the_magical_warrior.h`, `include/constants/monster_effects.h`, `src_custom/permanent_effects/breaker_the_magical_warrior.c`, `src_custom/activated_effects/breaker_the_magical_warrior.c`, `src_custom/monster_effect_hooks.c`, `src_custom/duel_helpers.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm counter on normal summon (not special), 1900 ATK overlay, destroy S/T targeting, Skill Drain negation, and counter persists across turns.

---

## 2026-06-18 — Confiscation custom card

**Worked on:** Added Confiscation to manifest/trunk (`CONFISCATION`, Normal Spell, passcode 17375316). Effect: pay 1000 LP via `Duel_TryResolveSpellThroughTrapsEx`, reveal opponent hand with `SelectExchangeHandCard`, discard chosen card via `Duel_DestroyZone`; AI picks random hand card. `CanActivateConfiscation` blocks activation when opponent hand empty or LP < 1000. `card_in_hand_1 = CONFISCATION` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/confiscation.h`, `src_custom/spell_effects/confiscation.c`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm LP cost, hand reveal UI, discard to GY, and trap-chain behavior.

---

## 2026-06-18 — D.D. Warrior custom card

**Worked on:** Added D.D. Warrior to manifest/trunk (`D_D_WARRIOR`, Effect Monster, passcode 37043180, 1200/1000 L4 Earth Warrior). Battle effect: after damage calculation when battling another monster, banish both via `Duel_BanishZone` (`ClearZone` without graveyard); clears graveyard destruction flags before normal battle cleanup. Deferred resolve wired like Hyper Hammerhead. Art copied from `d.d_warrior.png` → `d_d_warrior.png` for manifest stem. `card_in_hand_1 = D_D_WARRIOR` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `src_custom/assets/cards/80x80/d_d_warrior.png`, `include/d_d_warrior.h`, `src_custom/battle_effects/d_d_warrior.c`, `src_custom/battle_damage_hooks.c`, `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `asm/ram_map.s`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_8041C94_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `documentation/monster-card-effects.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm both monsters banish on win, loss, and mutual-survival battles; opponent-side DD Warrior path.

---

## 2026-06-18 — Blast Held by a Tribute custom card

**Worked on:** Added Blast Held by a Tribute to manifest/trunk (`BLAST_HELD_BY_A_TRIBUTE`, Normal Trap, passcode 89041555, `trapEffect` 31). Attack-triggered trap: when a Tribute Summoned monster declares an attack, destroy all opponent face-up Attack Position monsters (`Duel_DestroyAllMonstersMatching`); if any destroyed, inflict 1000 damage (`Duel_ChangeLp`). Tribute-summon tracking via IWRAM bit masks per monster row (`gTributeSummonedMonsterMaskOpponentRow` / `PlayerRow`), marked on placement/AI tribute and cleared on zone clear; marks transfer on `CopyCard`. `card_in_hand_1 = BLAST_HELD_BY_A_TRIBUTE` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/blast_held_by_a_tribute.h`, `src_custom/trap_effects/blast_held_by_a_tribute.c`, `src_custom/trap_effect_hooks.c`, `src_custom/trap_effects_hooks.c`, `asm/ram_map.s`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/duel_helpers.c`, `src_custom/ai_tribute_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm trap chains on tribute-summoned attacker (fixed AI mark row bug 2026-06-18), mass-destroy + 1000 burn only when at least one monster is destroyed, and tribute mark persists after control change (Brain Control ruling).

---

## 2026-06-18 — Blast Held by a Tribute: AI tribute mark fix

**Worked on:** Trap did not fire when opponent (e.g. Yugi) tribute summoned and attacked — `BlastHeldByATribute_MarkTributeSummonedMonster` passed `ACTIVE_DUELIST` (turn index 0) to `Duel_FixedMonsterRowForDuelist`, which expects `DUEL_PLAYER`/`DUEL_OPPONENT`, so opponent summons were marked on the player row. Fixed by locating the summon on `ACTIVE_DUELIST_MONSTER_ROW` and mapping via `Duel_FindFixedMonsterZone`.

**Files:** `src_custom/trap_effects/blast_held_by_a_tribute.c`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game retest vs Yugi Gaia tribute summon + attack.

---

## 2026-06-18 — Amazoness Tiger custom card

**Worked on:** Added Amazoness Tiger to manifest/trunk (`AMAZONESS_TIGER`, EARTH Beast L4 1100/1500, passcode 10979723). Passive permanent effect: +400 ATK per controller's "Amazoness" monsters (`AmazonessTiger_ApplyDynamicZoneStats` via `sDynamicZoneStats`); only one Tiger per row (`TryAmazonessTigerOnMonsterPlacement` + `AmazonessTiger_EnforceUniquenessOnField`, activation text on duplicate summon); opponent cannot attack other face-up Amazoness while Tiger is up (`AmazonessTiger_CanAttackMonsterZone` in `sAttackZoneChecks`). New helpers: `Duel_CardNameContains`, `Duel_IsAmazonessCard`. `card_in_hand_1 = AMAZONESS_TIGER` in `configs/runtime.c`. Fixed summon uniqueness: normal hand summon copies `isFaceUp=0` even in attack position, so enforcement only ran after battle-screen flip; uniqueness now treats attack-position Tigers as active (`isFaceUp || !isDefending`); face-down set Tigers still exempt until flip.

**Files:** `tools/card_data_manifest.json`, `include/amazoness_tiger.h`, `src_custom/permanent_effects/amazoness_tiger.c`, `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/permanent_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm ATK boost with multiple Amazoness, attack redirect blocks other Amazoness, duplicate Tiger sent to GY on hand summon (activation text + immediate destroy).

---

## 2026-06-18 — Spirit Ryu custom card

**Worked on:** Added Spirit Ryu to manifest/trunk (`SPIRIT_RYU`, WIND Dragon L4 1000/1000, passcode 67957315). Passive battle effect: +1000 ATK when battling a non-Dragon monster (`TryApplySpiritRyuToPendingAction` in `battle_effects/spirit_ryu.c`, wired on all attack paths like Cat's Ear Tribe). No ignition effect (`monsterEffect` 0). `card_in_hand_1 = SPIRIT_RYU` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/spirit_ryu.h`, `src_custom/battle_effects/spirit_ryu.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `src_custom/draining_shield_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm +1000 ATK applies vs non-Dragons only (not direct attacks or Dragon matchups).

---

## 2026-06-18 — Level Limit Area B

**Worked on:** Added Level Limit Area B to manifest/trunk (`LEVEL_LIMIT_AREA_B`, continuous spell, passcode 03136426). Effect forces face-up Lv4+ monsters to Defense Position while active (Imperial Order respected); enforcement on activation, placement, and permanent-effect scan; player monster menu blocks attack-position switch. Wired into unified attack API (`Duel_CanMonsterDeclareAttack` / `gDuelAttackRestrictionsActive`). Fixed AI flipping to attack before declare (`ai_attack_hooks`, turn-start re-enforce). Extended placement hooks to `InitMonsterZone` and `CopyCard__Replacement` for all summon paths. Split `LevelLimitAreaB_EnforceOnSummon` (Lv4+ on placement, including face-down) vs `EnforceOnZone` (face-up only for continuous scan); attack declare blocks all Lv4+ while active. Blocked re-activation via `Duel_ZoneIsNonSelectableActivatedBackrow` + `GetSpellType` normal-spell list. `card_in_hand_1 = LEVEL_LIMIT_AREA_B` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/level_limit_area_b.h`, `src_custom/spell_effects/level_limit_area_b.c`, `src_custom/spell_effect_hooks.c`, `src_custom/permanent_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/monster_effect_hooks.c`, `src_custom/duel_helpers.c`, `include/duel_helpers.h`, `src_custom/duel_attack_restrictions.c`, `include/duel_attack_restrictions.h`, `asm/ram_map.s`, `src_custom/ai_attack_hooks.c`, `src_custom/ai_decision/ai_decision_core.c`, `src_custom/duel_main_hooks.c`, `src_custom/duel_activated_backrow.c`, `include/duel_activated_backrow.h`, `src_custom/card_hooks.c`, `src_custom/LynJump.event`, `configs/runtime.c`, `src_custom/card_effect_tally.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game retest Gemini Elf summon/attack under active LLAB; confirm re-select plays forbidden SFX.

---

## 2026-06-18 — Activated backrow selection API

**Worked on:** Centralized the `HandlePlayerBackrowAction` non-selectable guard list into `Duel_ZoneIsNonSelectableActivatedBackrow()` (Swords of Revealing Light, Chain Energy, Gravity Bind, continuous equips, etc.).

**Files:** `include/duel_activated_backrow.h`, `src_custom/duel_activated_backrow.c`, `src_custom/code_8043EF4_hooks.c`

**Outcome:** `make test-cards-build` passes.

---

## 2026-06-18 — Duel attack restrictions API

**Worked on:** Unified attack-declare checks for Swords of Revealing Light, Gravity Bind, and Level Limit Area B via `gDuelAttackRestrictionsActive` RAM bitfield (`asm/ram_map.s`) and `Duel_CanMonsterDeclareAttack()` in `src_custom/duel_attack_restrictions.c`. Refreshed on field changes and at attack time; player/AI attack paths now call the API instead of per-card checks.

**Files:** `asm/ram_map.s`, `include/duel_attack_restrictions.h`, `src_custom/duel_attack_restrictions.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/permanent_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/ai_decision/ai_decision_core.c`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm SORL/GB/LLAB blocks show forbidden SFX via single API path.

---

## 2026-06-18 — Man-Thro' Tro' custom card

**Worked on:** Added Man-Thro' Tro' to manifest/trunk (`MAN_THRO_TRO`, EARTH Beast-Warrior L4 1000/1000, passcode 43714890). Ignition: tribute 1 Normal Monster (Ojama Trio token form excluded), inflict 800 — Cannon Soldier-style targeting in `activated_effects/man_thro_tro.c`, `multiple_per_turn`. Art from `man-thro-thro.png` copied to `man_thro_tro.png`. `card_in_hand_1 = MAN_THRO_TRO` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/man_thro_tro.h`, `include/constants/monster_effects.h`, `src_custom/activated_effects/man_thro_tro.c`, `src_custom/monster_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, `src_custom/assets/cards/80x80/man_thro_tro.png`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm tribute cursor only accepts Normal Monsters and 800 burn applies.

---

## 2026-06-18 — Servant of Catabolism custom card

**Worked on:** Added Servant of Catabolism to manifest/trunk (`SERVANT_OF_CATABOLISM`, LIGHT Aqua L3 700/500, passcode 02792265). Continuous direct-attack passive via `CanServantOfCatabolismAttackDirectly` (Nightmare Horse pattern) in `card_passives/servant_of_catabolism.c`, wired into player attack path in `code_8043EF4_hooks.c`. `card_in_hand_1 = SERVANT_OF_CATABOLISM` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/servant_of_catabolism.h`, `src_custom/card_passives/servant_of_catabolism.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm direct attack works with opponent monsters on field.

---

## 2026-06-18 — Sasuke Samurai #3 custom card

**Worked on:** Added Sasuke Samurai #3 to manifest/trunk (`SASUKE_SAMURAI_3`, LIGHT Warrior 1000/1000 L3, passcode 77379481). Trigger: when it inflicts battle damage to opponent LP, opponent draws until hand has 7 (`Duel_DrawCardsUntilHandSize` helper; capped at `MAX_ZONES_IN_ROW` 5). Battle effect in `battle_effects/sasuke_samurai_3.c`, deferred resolve like Airknight Parshath. `card_in_hand_1 = SASUKE_SAMURAI_3` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/sasuke_samurai_3.h`, `include/duel_helpers.h`, `src_custom/battle_effects/sasuke_samurai_3.c`, `src_custom/duel_helpers.c`, `src_custom/battle_damage_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_8041C94_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `asm/ram_map.s`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm opponent draws to 5 (hand cap) when Sasuke #3 deals direct battle damage.

---

## 2026-06-18 — Sasuke Samurai #2 custom card (+ trap-block iteration)

**Worked on:** Added Sasuke Samurai #2 to manifest/trunk (`SASUKE_SAMURAI_2`). Ignition: pay 800 LP, once per turn, face-up OK (`lock_after_activation: false`). Until End Phase, opponent backrow traps cannot activate — `gSasukeSamurai2InactiveBackrowTrapBlock` in `asm/ram_map.s`, set at effect start, cleared in `TryActivatingTurnEffects`. Guards: `IsTrapTriggered`, `ActivateTrapEffect`, attack paths (`sub_8044570` / `TryAttackWithMonster`), Apophis on-attack, AI attack traps. Also added `Duel_IsCardActivationBlocked(cardId)` in `duel_helpers` for Imperial Order / Royal Decree / Spell Canceller (separate from Sasuke #2). Card text: opponent traps only (no spell lock). `card_in_hand_1 = SASUKE_SAMURAI_2` in `configs/runtime.c`. Sasuke Samurai (#1) already in trunk with battle effect (`battle_effects/sasuke_samurai.c`).

**Files:** `tools/card_data_manifest.json`, `asm/ram_map.s`, `include/sasuke_samurai_2.h`, `include/constants/monster_effects.h`, `include/duel_helpers.h`, `src_custom/activated_effects/sasuke_samurai_2.c`, `src_custom/duel_helpers.c`, `src_custom/monster_effect_hooks.c`, `src_custom/spell_effect_hooks.c`, `src_custom/trap_effect_hooks.c`, `src_custom/trap_effects_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/embodiment_of_apophis_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/turn_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game confirm Invisible Wire blocked same turn after Sasuke #2 effect.

---

## 2026-06-18 — Ring of Destruction custom card

**Worked on:** Added Ring of Destruction (trap) to manifest/trunk; opponent-turn targeting via Soul Taker-style cursor flow; auto-activates on opponent summon via `Duel_NotifyFixedMonsterRowChanged`, always picking highest-ATK valid face-up target; mirror damage via `duel_helpers`.

**Files:** `tools/card_data_manifest.json`, `src_custom/trap_effects/ring_of_destruction.c`, `include/ring_of_destruction.h`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = RING_OF_DESTRUCTION` for duel testing.

**Open / next:** In-game confirm auto-fire on opponent summon picks highest-ATK valid target; manual activation uses same priority.

---

## 2026-06-17 — Rivalry of Warlords

**Worked on:** Added Rivalry of Warlords (continuous trap) to manifest/trunk; auto-flips when a monster row gains 2+ different Types (face-up or set) while rivalry is set; enforces leftmost monster’s Type per row via `duel_helpers` (`Duel_FixedMonsterRowHasMultipleMonsterTypes`, `Duel_EnforceSingleMonsterTypeOnBothMonsterRows`, `Duel_NotifyMonsterZoneChanged`). Rewrote on fixed rows (`gFixedZones`); fixed player summons (`CopySelectedCardToZone` → `gSelectedCard`, not hand slot). Summon-time flip via placement hooks + `RivalryOfWarlords_CheckAfterFieldChange` at end of permanent-effect scan. Opponent-turn effect text deferred there (AI `sub_8040EF0` was wiping mid-action text); player-turn checks immediately. Trap presentation: viewport scroll, scanner, typed trap text.

**Files:** `tools/card_data_manifest.json`, `src_custom/trap_effects/rivalry_of_warlords.c`, `include/rivalry_of_warlords.h`, `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/permanent_effect_hooks.c`, `src_custom/spell_effect_hooks.c`, `src_custom/card_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = RIVALRY_OF_WARLORDS` for duel testing.

**Open / next:** In-game confirm flip on summon (both sides), effect text on opponent turn, same-Type second monster does not flip, continuous enforcement after activation.

---

## 2026-06-17 — Seven Tools of the Bandit custom card

**Worked on:** Added Seven Tools of the Bandit (counter trap) to manifest/trunk; trap-on-trap negate via `Duel_TryResolveTrapThroughTraps` + discard cost effect body.

**Files:** `tools/card_data_manifest.json`, `src_custom/trap_effects/seven_tools_of_the_bandit.c`, `include/seven_tools_of_the_bandit.h`, `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `src_custom/trap_effect_hooks.c`, `src_custom/trap_effects_hooks.c`, `src_custom/spell_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = SEVEN_TOOLS_OF_THE_BANDIT` for duel testing.

**Open / next:** In-game confirm trap-chain response (set Seven Tools, opponent activates trap, discard 1, origin trap destroyed); empty-hand should not offer activation.

---

## 2026-06-17 — Torpedo Fish custom card

**Worked on:** Added Torpedo Fish (IOC effect monster) to manifest/trunk; Umi-gated spell immunity via card_passives + duel_helpers spell-resolve depth API.

**Files:** `tools/card_data_manifest.json`, `src_custom/card_passives/torpedo_fish.c`, `include/card_passives.h`, `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `src_custom/card_passive_hooks.c`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/spell_effects/book_of_moon.c`, `src_custom/LynJump.event`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = TORPEDO_FISH` for duel testing.

**Open / next:** In-game confirm spell immunity with Umi active (Raigeki, equip, Book of Moon); traps should still affect Torpedo Fish.

---

## 2026-06-17 — Thunder Crash custom card

**Worked on:** Added Thunder Crash (IOC normal spell) to manifest/trunk; destroy-own-monsters + 300 burn per destroyed monster via duel_helpers.

**Files:** `tools/card_data_manifest.json`, `src_custom/spell_effects/thunder_crash.c`, `src_custom/spell_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = THUNDER_CRASH` for duel testing.

**Open / next:** In-game confirm trap response with variable burn; god-card skip matches Raigeki-style helper behavior.

---

## 2026-06-17 — duel_helpers standardization (phase 2)

**Worked on:** Closed open items from repo-wide standardization pass — backrow scans, fixed-zone lookup, forced-attack redirect dispatch, burn-spell migration.

**New APIs:** `Duel_FindFixedZone`, `Duel_FindBackrowCardOnField`, `Duel_IsBackrowCardOnField`, `Duel_GetForcedAttackTarget`, `Duel_MonsterMayBeAttacked`, `Duel_ForcedAttackBlocksDirect`.

**Migrated:** skill_drain, imperial_order, royal_decree (backrow active checks); dynamic_equip (zone coords); tremendous_fire (`Duel_ResolveBurnSpell`); dark_room zone find; attack hooks → generic forced-target dispatch (Raregold table row in `duel_helpers.c`).

**Files:** `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `skill_drain.c`, `imperial_order.c`, `royal_decree.c`, `dynamic_equip.c`, `tremendous_fire.c`, `dark_room_of_nightmare.c`, `raregold_armor.c`, `ai_attack_hooks.c`, `code_8043EF4_hooks.c`, `tests/host/test_duel_helpers.py`.

**Outcome:** `make test-cards-build` and `make test-host` pass.

**Open / next:** Turn-backrow set-card scan for chain activations (imperial order / royal decree loops); `goblin_thief` / `wave_motion_cannon` burn variants; fairy_box backrow scan.

## 2026-06-17 — Repo-wide duel_helpers standardization

**Worked on:** Extended `duel_helpers` with reusable zone/stat/LP/trap APIs and migrated ~60 effect files off duplicated boilerplate.

**New APIs:** `Duel_ActivateContinuousZone`, `Duel_GetZoneFinalAtk`, `Duel_FixedMonsterRowForDuelist` / `Duel_FixedDuelistForMonsterRow`, `Duel_CountMonstersOnTurnRow`, `Duel_IsFixedMonsterRow`, `Duel_IsMonsterZoneTarget`, `Duel_FindBackrowCard`, `Duel_FixedMonsterSlotBit`, `Duel_ZoneIsHandSlot`, `Duel_ChangeLpWithPrefaceText`, `Duel_ResolveBurnSpell`, `Duel_ShowTrapResponseText`, `Duel_DestroyMaskedMonstersInFixedRow`, `Duel_TurnDuelistMatchingWhoseTurn`.

**Migrated:** 41 continuous trap/spell activations; limiter/graceful dice/thousand/triangle EOT masks; turn LP effects; equip spells; burn spells; trap response text; skull invitation/coffin seller; slifer atk check; riryoku/book_of_moon/kaiser_glider row checks.

**Files:** `include/duel_helpers.h`, `src_custom/duel_helpers.c`, bulk `spell_effects/`, `trap_effects/`, `turn_effects/`, `permanent_effects/`, `battle_effects/`.

**Outcome:** `make test-cards-build` and `tests.host.test_duel_helpers` pass.

**Open / next:** Backrow scan helpers for skill drain/imperial order; `Duel_FindFixedZone` (all rows) for dynamic_equip; raregold attack redirect table; more burn spells (tremendous_fire + dark room).

## 2026-06-17 — Card-ID dispatch for dynamic zone stats

**Worked on:**
- Replaced per-card stat/attack APIs (`ApplyGoblinKing*`, `GoblinKing_CanBeAttacked`, etc.) with ID-keyed dispatch in `duel_helpers`
- Central tables in `duel_helpers.c` map `cardId` → zone stat applier / attack gate predicate
- Migrated Goblin King, Gyaku Gire Panda, Great Maju Garzett; deleted `goblin_king.h`

**Files:**
- `include/duel_helpers.h`, `src_custom/duel_helpers.c` — `Duel_TryApplyDynamicZoneStats`, `Duel_TryApplyDynamicStatMod`, `Duel_CanAttackMonsterZone`, helpers
- `src_custom/card_hooks.c`, `code_8043EF4_hooks.c`, `ai_attack_hooks.c` — generic dispatch calls
- `src_custom/permanent_effects/goblin_king.c`, `gyaku_gire_panda.c`, `great_maju_garzett.c`
- `include/great_maju_garzett.h`, `include/gyaku_gire_panda.h`

**Outcome:** `make test-cards-build` passes. New dynamic-stat cards: implement `Card_ApplyDynamicZoneStats`, add one table row + optional attack gate row.

**Open / next:** None for this thread.

## 2026-06-17 — Goblin King stat helpers in duel_helpers

**Worked on:**
- Extracted reusable field-stat / zone-scan APIs from Goblin King into `duel_helpers`
- Refactored `goblin_king.c` to card-specific rules only (Fiend count × 500, attack gate)

**Files:**
- `include/duel_helpers.h` — `Duel_ClampStat`, zone find/count, `Duel_WriteCardInfoStats`, `Duel_ApplyStatModViaZoneApplier`
- `src_custom/duel_helpers.c` — implementations + `Duel_ClampStat` self-check
- `src_custom/permanent_effects/goblin_king.c` — slim card file
- `tests/host/test_duel_helpers.py` — header symbol coverage

**Outcome:**
- `make test-cards-build` and `make test-host` pass
- Gyaku Gire Panda / Great Maju Garzett can adopt `Duel_ApplyStatModViaZoneApplier` next

**Open / next:**
- Migrate other dynamic-stat cards (Gyaku Gire Panda, Great Maju Garzett) to shared helpers

## 2026-06-17 — Repo context docs + Hourglass stat pipeline

**Worked on:**
- Field vs battle ATK/DEF discrepancy (Hourglass of Life and similar stage boosts)
- Split stat pipelines: field uses `ApplyFieldZoneStatsToCardInfo`; battle uses `SetFinalStat` via `SetAttackAction`
- `gSetFinalStatZone` poisoning from field refresh / mismatched zone reads
- Hourglass refactor to `duel_helpers` API
- Created `ARCHITECTURE.md`, this log, and session-context Cursor rule

**Files:**
- `src_custom/card_hooks.c` — `ComputeFinalStage`, `RefreshPendingBattleActionStatsFromZones`, `SetFinalStat` id-match guard, field path clears
- `src_custom/code_803F02C_hooks.c` — `ComputeFinalStage`
- `src_custom/mini_card_hooks.c` — stage stamps via `ComputeFinalStage`
- `src_custom/trap_effects/fairy_box.c` — battle stat resync hook point
- `src_custom/duel_helpers.c` — `Duel_IncrementPermStageOnDuelistMonsters`, `Duel_RefreshMonsterStatOverlays`
- `src_custom/activated_effects/hourglass_of_life.c` — slim API-based effect
- `tests/host/test_mini_card_stats.py`
- `ARCHITECTURE.md`, `SESSION_LOG.md`, `.cursor/rules/session-context.mdc`

**Outcome:**
- Field overlays and battle stats should agree after stage changes when attack goes through `TryApplyFairyBoxToPendingAction`
- Hourglass: boost active duelist row → `Duel_ChangeLp` → refresh overlays → effect text
- `make test-cards-build` and host stat tests pass

**Open / next:**
- In-game confirm Hourglass field + battle ATK match after activate + attack
- Consider migrating other stage-boost effects (Thousand Energy, Triangle Power) to `Duel_RefreshMonsterStatOverlays`
- Broader cleanup: more effects on `duel_helpers` instead of manual LP loops
