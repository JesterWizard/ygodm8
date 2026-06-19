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

## 2026-06-19 — Maju Garzett custom card

**Worked on:** Added Maju Garzett (DARK Fiend L7, passcode 08794435) to manifest/trunk. Effect in `permanent_effects/maju_garzett.c`: on Tribute Summon, ATK becomes sum of original ATK of 2 tributes (pattern from Great Maju Garzett; ATK-only, no doubling). Wired tribute capture, placement finish, board stat overlay, AI 2-tribute path, Soul Exchange, and zone cleanup. `card_in_hand_1 = MAJU_GARZETT`.

**Files:** `tools/card_data_manifest.json`, `include/maju_garzett.h`, `src_custom/permanent_effects/maju_garzett.c`, `asm/ram_map.s`, `src_custom/permanent_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/monster_effect_hooks.c`, `src_custom/ai_tribute_hooks.c`, `src_custom/soul_exchange.c`, `src_custom/duel_helpers.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = MAJU_GARZETT`.

**Open / next:** In-game: Tribute Summon with 2 monsters; confirm ATK = sum of tribute ATK on field overlay and in battle.

---

## 2026-06-19 — Mirror Wall custom card

**Worked on:** Added Mirror Wall (Continuous Trap, passcode 22359980) to manifest/trunk. Effect in `trap_effects/mirror_wall.c`: flips on opponent attack; permanently halves ATK of attacking opponent monsters while face-up (board-cell mask in EWRAM); Standby Phase 2000 LP upkeep or self-destruct via turn effect. Pattern follows Fairy Box + Imperial Order. `card_in_hand_1 = MIRROR_WALL`.

**Files:** `tools/card_data_manifest.json`, `include/mirror_wall.h`, `src_custom/trap_effects/mirror_wall.c`, `asm/ram_map.s`, `src_custom/card_hooks.c`, `src_custom/turn_effect_hooks.c`, `src_custom/duel_activated_backrow.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = MIRROR_WALL`.

**Open / next:** In-game: set MW, let opponent attack; confirm ATK halved in battle and on card overlay; confirm Standby 2000 LP cost or trap destruction; confirm debuff clears when MW leaves field.

---

## 2026-06-19 — Nightmare Wheel → Continuous Spell

**Worked on:** Converted Nightmare Wheel from `TYPE_TRAP`/`TRAP_CARD` to `TYPE_SPELL`/`SPELL_CARD`. Moved effect to `spell_effects/nightmare_wheel.c`; added `GetSpellType` entry; negation via Imperial Order instead of Royal Decree; spell text type (1) for activation.

**Files:** `tools/card_data_manifest.json`, `src_custom/spell_effects/nightmare_wheel.c`, `src_custom/card_hooks.c`, `src_custom/card_effect_tally.md` (removed `trap_effects/nightmare_wheel.c`)

**Outcome:** `make test-cards-build` passes.

---

## 2026-06-19 — Nightmare Wheel custom card

**Worked on:** Added Nightmare Wheel (Continuous Trap, passcode 54704216) to manifest/trunk. Effect in `trap_effects/nightmare_wheel.c`: activate with opponent-monster targeting (`DUEL_CURSOR_NIGHTMARE_WHEEL_TARGET`); target stored on trap zone; blocks attack (`Duel_CanMonsterDeclareAttack`) and position changes; self-destructs when target leaves field; Standby 500 damage to opponent while target remains. Uses `Duel_ShowEffectTextTyped`, `Duel_ActivateContinuousZone`, `Duel_ChangeLp`, `Duel_DestroyZone`. `card_in_hand_1 = NIGHTMARE_WHEEL`.

**Files:** `tools/card_data_manifest.json`, `include/nightmare_wheel.h`, `src_custom/trap_effects/nightmare_wheel.c`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/duel_attack_restrictions.c`, `src_custom/duel_activated_backrow.c`, `src_custom/monster_effect_hooks.c`, `src_custom/turn_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = NIGHTMARE_WHEEL`.

**Open / next:** In-game: set NW, activate targeting opponent monster; confirm lock, Standby burn, and trap destruction when target leaves.

---

## 2026-06-19 — Kaiser Colosseum custom card

**Worked on:** Added Kaiser Colosseum (Continuous Spell, passcode 35059553) to manifest/trunk. Effect in `spell_effects/kaiser_colosseum.c`: while controller has ≥1 monster, opponent cannot place a monster if that would exceed controller's monster count (`Duel_CountMonstersOnFixedRow`); Imperial Order respected; grandfather clause via placement-only check. Hooks in `PlaceMonsterFromId`, `sub_80449D8`, and `CopyCard__Replacement` (AI hand→field path). `GetSpellType` lists KC as activatable continuous spell. `card_in_hand_1 = KAISER_COLOSSEUM`.

**Files:** `tools/card_data_manifest.json`, `include/kaiser_colosseum.h`, `src_custom/spell_effects/kaiser_colosseum.c`, `src_custom/card_hooks.c`, `src_custom/spell_effect_hooks.c`, `src_custom/duel_helpers.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/duel_activated_backrow.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = KAISER_COLOSSEUM`.

**Open / next:** In-game: activate KC with 1 monster; opponent cannot exceed your count. Pre-existing opponent monsters grandfathered.

---

## 2026-06-19 — Ghost Knight of Jackal custom card

**Worked on:** Added Ghost Knight of Jackal (EARTH Beast-Warrior L5 1700/1600, passcode 13386503) to manifest/trunk. Battle effect in `battle_effects/ghost_knight_of_jackal.c`: when Jackal destroys an opponent monster by battle (and survives), special summons that monster from opponent GY to controller's field in face-up Defense Position via `GetGraveCardAndClearGrave` + `Duel_SpecialSummonMonsterId`. Pattern follows Royal Knight trigger + Vampire Baby graveyard steal. `card_in_hand_1 = GHOST_KNIGHT_OF_JACKAL`.

**Files:** `tools/card_data_manifest.json`, `include/ghost_knight_of_jackal.h`, `src_custom/battle_effects/ghost_knight_of_jackal.c`, `asm/ram_map.s`, `src_custom/battle_damage_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_8041C94_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/code_803F02C_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = GHOST_KNIGHT_OF_JACKAL`.

**Open / next:** In-game: Jackal attacks and destroys opponent monster; confirm effect text, opponent monster revives on your field in Defense Position. Confirm no summon if your monster zones are full.

---

## 2026-06-19 — Dark Dust Spirit custom card

**Worked on:** Added Dark Dust Spirit (EARTH Zombie L6 2200/1800, passcode 89111398) to manifest/trunk. Effect in `activated_effects/dark_dust_spirit.c`: cannot Special Summon; on Normal Summon/flip destroys other face-up monsters; End Phase return to hand. Fixed summon effect not firing: Breaker-style `isFaceUp || !isDefending` placement check + `FlipCardFaceUp` before resolve; Zaborg-style permanent-effect hook for tribute summons; flip summon routed like Ryu-Kishin Clown (skip `ActivateMonsterEffect`, use placement hook).

**Files:** `include/constants/monster_effects.h`, `include/dark_dust_spirit.h`, `src_custom/activated_effects/dark_dust_spirit.c`, `src_custom/monster_effect_hooks.c`, `src_custom/permanent_effect_hooks.c`, `src_custom/turn_effect_hooks.c`, `src_custom/duel_helpers.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`

**Worked on:** Dark Dust Spirit destroy-on-summon fix: board wipe now runs before effect text (Cyber Jar / Penguin Soldier order); iterates `gTurnZones` with turn-row graveyard duelists; excludes source by zone pointer; calls `NotifyDynamicEquipFieldChanged`; placement hook sets `gActiveEffect` like Granadora.

**Outcome:** Code updated; run `make test-cards-build` locally to verify link.

**Open / next:** In-game: tribute summon with face-up opponent monsters on field; confirm they are destroyed before activation text; End Phase return still works.

---

## 2026-06-19 — Ryu-Kishin Clown custom card

**Worked on:** Added Ryu-Kishin Clown (DARK Fiend L2 800/500, passcode 42647539) to manifest/trunk. Summon effect in `activated_effects/ryu_kishin_clown.c`: on face-up Normal/Special Summon (placement hook) or Flip Summon (`MONSTER_EFFECT_RYU_KISHIN_CLOWN`), target 1 face-up field monster and toggle battle position via `Duel_NotifyMonsterZoneChanged`; player targeting via `DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET`; AI picks highest-ATK opponent attack-position monster. `card_in_hand_1 = RYU_KISHIN_CLOWN`.

**Files:** `tools/card_data_manifest.json`, `include/constants/monster_effects.h`, `include/ryu_kishin_clown.h`, `src_custom/activated_effects/ryu_kishin_clown.c`, `src_custom/monster_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/duel_helpers.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = RYU_KISHIN_CLOWN`.

**Open / next:** In-game: normal/flip/special summon Clown with a face-up monster on field; confirm position toggle and targeting UI.

---

## 2026-06-19 — World Suppression + AI field spell scoring

**Worked on:** AI terrain field spell — stopped tuning vanilla priority; `AiForceTerrainFieldSpellAction()` in `sub_800EF0C` now hard-picks activate (set Umi on backrow, field not Umi yet) or place (terrain in hand, empty backrow) before normal AI scoring.
**Files:** `src_custom/ai_hooks.c`, `src_custom/ai_spell_hooks.c`, `src_custom/field_spell_effect_hooks.c`, `src_custom/LynJump.event`
**Outcome:** `make test-cards-build` passes. Opponent should set then flip Umi every turn until field is active.

## 2026-06-19 — World Suppression: AI hidden info fix

**Worked on:** AI sim called `IsTrapTriggered` on face-down opponent backrow during spell action validation (`sub_801B35C`/`sub_801B3AC`), so it treated set World Suppression as a known counter and avoided field spells like Umi. Skip unknown face-down inactive backrow traps when `gHideEffectText` (AI simulation).

**Files:** `src_custom/trap_effect_hooks.c`

**Outcome:** `make test-cards-build` passes. AI should play field spells normally vs face-down WS; real activation still chains WS.

---

## 2026-06-19 — World Suppression custom card

**Worked on:** Added World Suppression (Normal Trap, passcode 12253117) to manifest/trunk. Effect in `trap_effects/world_suppression.c`: chains when a Field Spell is activated (vanilla terrain, Burning Land, Seal of Orichalcos); sends trap + triggering spell to GY via `Duel_DestroyZone`/`Duel_ShowTrapResponseText`; sets IWRAM negation flag until end of turn (clears on turn switch). Blocks further field spell resolutions and suppresses Burning Land / Seal ongoing effects. `trapEffect` 33. `card_in_hand_1 = WORLD_SUPPRESSION`.

**Files:** `tools/card_data_manifest.json`, `include/world_suppression.h`, `src_custom/trap_effects/world_suppression.c`, `asm/ram_map.s`, `src_custom/trap_effect_hooks.c`, `src_custom/trap_effects_hooks.c`, `src_custom/spell_effect_hooks.c`, `src_custom/field_spell_effect_hooks.c`, `src_custom/spell_effects/burning_land.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/duel_main_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = WORLD_SUPPRESSION`.

**Open / next:** In-game: set World Suppression, opponent activates Field Spell; confirm trap chains, both go to GY, terrain reverts, no further field spell effects that turn.

---

## 2026-06-19 — Wall of Revealing Light custom card

**Worked on:** Added Wall of Revealing Light (Continuous Trap, passcode 17078030) to manifest/trunk. Effect in `trap_effects/wall_of_revealing_light.c`: auto-flips when opponent declares an attack; pays half controller LP and stores ATK threshold in IWRAM; only opponent monsters with ATK above threshold may attack while face-up (`Duel_CanMonsterDeclareAttack` via attack-restrictions API). Non-selectable when active. `card_in_hand_1 = WALL_OF_REVEALING_LIGHT`.

**Files:** `tools/card_data_manifest.json`, `include/wall_of_revealing_light.h`, `src_custom/trap_effects/wall_of_revealing_light.c`, `asm/ram_map.s`, `include/duel_attack_restrictions.h`, `src_custom/duel_attack_restrictions.c`, `src_custom/trap_effect_hooks.c`, `src_custom/trap_effects_hooks.c`, `src_custom/duel_activated_backrow.c`, `src_custom/code_803F02C_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = WALL_OF_REVEALING_LIGHT`.

**Open / next:** In-game: set Wall face-down, let opponent attack; confirm half LP paid, trap flips, low-ATK attacks blocked and high-ATK attacks proceed. Confirm face-up Wall is not selectable.

---

## 2026-06-19 — Wall of Revealing Light: AI + mini art fixes

**Worked on:** AI no longer pre-blocks attacks vs set Wall (restriction only when face-up); mini art pipeline remaps palette index 0 off opaque pixels (trunk/shop force slot 0 transparent).

**Files:** `src_custom/trap_effects/wall_of_revealing_light.c`, `src_custom/duel_attack_restrictions.c`, `tools/add_card_art.py`, regenerated `build/cards/24x24/wall_of_revealing_light.lz`

**Outcome:** `make test-cards-build` passes.

---

## 2026-06-19 — Vengeful Bog Spirit: LockCard attack block

**Worked on:** Fixed AI never attacking under VBS: `CopyCard` was re-marking every monster copy as "summoned this turn" (now only hand→empty monster zone); AI sim save/restore now includes VBS masks; marks also clear at end of turn.

**Outcome:** `make test-cards-build` passes.

---

## 2026-06-19 — Vengeful Bog Spirit custom card

**Worked on:** Added Vengeful Bog Spirit (Continuous Spell, passcode 95220856) to manifest/trunk. Effect in `spell_effects/vengeful_bog_spirit.c`: while active, monsters summoned or flip-summoned this turn cannot attack (`Duel_CanMonsterDeclareAttack` via per-row IWRAM bit masks; marks clear each turn start). Imperial Order respected; re-activation blocked. `card_in_hand_1 = VENGEFUL_BOG_SPIRIT`.

**Files:** `tools/card_data_manifest.json`, `include/vengeful_bog_spirit.h`, `src_custom/spell_effects/vengeful_bog_spirit.c`, `asm/ram_map.s`, `include/duel_attack_restrictions.h`, `src_custom/duel_attack_restrictions.c`, `src_custom/spell_effect_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/duel_helpers.c`, `src_custom/monster_effect_hooks.c`, `src_custom/card_hooks.c`, `src_custom/duel_activated_backrow.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = VENGEFUL_BOG_SPIRIT`.

**Open / next:** In-game: activate VBS, normal/special summon or flip-summon a monster, confirm attack blocked; next turn confirm attack allowed. Control-change should preserve same-turn mark.

---

## 2026-06-19 — Spirit Caller custom card

**Worked on:** Added Spirit Caller (LIGHT Spellcaster L3 1000/1000 FLIP, passcode 48659020) to manifest/trunk. FLIP effect in `activated_effects/spirit_caller.c`: if controller's graveyard holds a Level 3 or lower Normal Monster and an empty monster zone exists, Special Summon it via `Duel_SpecialSummonFromGrave` (ponytail: single-card graveyard model). `card_in_hand_1 = SPIRIT_CALLER`.

**Files:** `tools/card_data_manifest.json`, `include/spirit_caller.h`, `include/constants/monster_effects.h`, `src_custom/activated_effects/spirit_caller.c`, `src_custom/monster_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = SPIRIT_CALLER`.

**Open / next:** In-game: set Spirit Caller face-down, send a L3-or-lower Normal to GY, flip; confirm special summon. Flip with invalid GY or full field should skip effect.

---

## 2026-06-19 — The Flute of Summoning Dragon custom card

**Worked on:** Added The Flute of Summoning Dragon (Normal Spell, passcode 43973174) to manifest/trunk. Effect in `spell_effects/the_flute_of_summoning_dragon.c`: requires Lord of D on field; Special Summon up to 2 Dragon monsters from hand via `Duel_SpecialSummonFromHand` / `Duel_SpecialSummonFromHandZone`; `CanActivateTheFluteOfSummoningDragon` blocks when requirements unmet. `card_in_hand_1 = THE_FLUTE_OF_SUMMONING_DRAGON`.

**Files:** `tools/card_data_manifest.json`, `include/the_flute_of_summoning_dragon.h`, `src_custom/spell_effects/the_flute_of_summoning_dragon.c`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = THE_FLUTE_OF_SUMMONING_DRAGON`.

**Open / next:** In-game: field Lord of D, hand with 1–2 Dragons, activate Flute; confirm summons and activation block without Lord of D.

---

## 2026-06-19 — Invader of the Throne custom card

**Worked on:** Added Invader of the Throne (EARTH Warrior L4 1350/1700, passcode 03056267) to manifest/trunk. FLIP effect in `activated_effects/invader_of_the_throne.c`: target 1 opponent monster, swap control with this card via zone swap + `Duel_NotifyFixedMonsterRowChanged`; player targeting via `DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET`; AI picks highest-ATK swappable opponent monster. `card_in_hand_1 = INVADER_OF_THE_THRONE`.

**Files:** `tools/card_data_manifest.json`, `include/invader_of_the_throne.h`, `include/constants/monster_effects.h`, `src_custom/activated_effects/invader_of_the_throne.c`, `src_custom/monster_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = INVADER_OF_THE_THRONE`.

**Open / next:** In-game: set Invader face-down, flip with opponent monster on field; confirm control swap and effect text. Skill Drain / control-immune cards should block targeting.

---

## 2026-06-19 — Fire Princess custom card

**Worked on:** Added Fire Princess (FIRE Pyro L4 1300/1500, passcode 64752646) to manifest/trunk. Continuous effect: when controller gains LP (action 7/10), burn opponent 500 via `Duel_ShowEffectTextTyped` + `HandleAtkAndLifePointsAction` (Dark Room defer pattern). Skill Drain blocks. `card_in_hand_1 = FIRE_PRINCESS`.

**Files:** `tools/card_data_manifest.json`, `include/fire_princess.h`, `src_custom/permanent_effects/fire_princess.c`, `asm/ram_map.s`, `src_custom/code_803F02C_hooks.c`, `src_custom/effect_text_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = FIRE_PRINCESS`.

**Open / next:** In-game: summon Fire Princess face-up, activate LP gain spell (e.g. Pot of Greed + Solemn Wishes path or healing spell); confirm 500 burn and effect text.

---

## 2026-06-19 — Bottomless Shifting Sand custom card

**Worked on:** Added Bottomless Shifting Sand (Continuous Trap, passcode 76532077) to manifest/trunk. Turn-start hook: at controller's turn start (opponent's end), flip if set, destroy all face-up monsters tied for highest field ATK (`Duel_GetZoneFinalAtk` + `Duel_DestroyZone`); standby self-destruct when hand ≤ 3 (ponytail: scaled from TCG 4 for 5-card hand cap). `card_in_hand_1 = BOTTOMLESS_SHIFTING_SAND`.

**Files:** `tools/card_data_manifest.json`, `include/bottomless_shifting_sand.h`, `src_custom/trap_effects/bottomless_shifting_sand.c`, `src_custom/turn_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/spell_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = BOTTOMLESS_SHIFTING_SAND`.

**Open / next:** In-game: set trap, pass opponent's turn; confirm highest-ATK destroy and self-destruct at ≤3 hand cards.

---

## 2026-06-19 — Zaborg the Thunder Monarch custom card

**Worked on:** Added Zaborg the Thunder Monarch (LIGHT Thunder L5 2400/1000, passcode 51945556) to manifest/trunk. Tribute Summon trigger in `permanent_effects/zaborg_the_thunder_monarch.c`: player targets 1 field monster (excluding self) via `DUEL_CURSOR_ZABORG_THE_THUNDER_MONARCH_TARGET`; AI picks highest-ATK opponent monster; destroy via `Duel_DestroyZone`. Only fires when `GetPendingTributeSummonCardId()` matches. Fixed Spirit of the Pot of Greed manifest description (2 pages required).

**Files:** `tools/card_data_manifest.json`, `include/zaborg_the_thunder_monarch.h`, `src_custom/permanent_effects/zaborg_the_thunder_monarch.c`, `src_custom/permanent_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = ZABORG_THE_THUNDER_MONARCH`.

**Open / next:** In-game: tribute summon Zaborg with another monster on field; confirm target destroy and effect text. Skill Drain should negate.

---

## 2026-06-19 — Spirit of the Pot of Greed custom card

**Worked on:** Added Spirit of the Pot of Greed (LIGHT Fairy L1 100/100, passcode 04896788) to manifest/trunk. After Pot of Greed resolves, scans both monster rows for face-up Attack Position copies; PoG activator draws 1 per Spirit via `Duel_DrawCards`. Skill Drain blocks; Jar Robber/Maryokutai pre-resolution counters skip the hook.

**Files:** `tools/card_data_manifest.json`, `include/spirit_of_the_pot_of_greed.h`, `src_custom/permanent_effects/spirit_of_the_pot_of_greed.c`, `src_custom/spell_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = SPIRIT_OF_THE_POT_OF_GREED`.

**Open / next:** In-game: normal summon Spirit face-up ATK, activate Pot of Greed; confirm bonus draw and effect text.

---

## 2026-06-19 — Lesser Fiend custom card

**Worked on:** Added Lesser Fiend (DARK Fiend L5 2100/1000, passcode 16475472) to manifest/trunk. Battle trigger: banishes any monster destroyed by battle with Lesser Fiend via `Duel_BanishZone` (D.D. Warrior pattern — apply before GY send clears destroy flag).

**Files:** `tools/card_data_manifest.json`, `include/lesser_fiend.h`, `src_custom/battle_effects/lesser_fiend.c`, `asm/ram_map.s`, `src_custom/battle_damage_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/code_803F02C_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_8041C94_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = LESSER_FIEND`.

**Open / next:** In-game: Lesser Fiend destroys a monster by battle; confirm victim is banished (not in GY) and effect text shows.

---

## 2026-06-19 — Creature Swap custom card

**Worked on:** Added Creature Swap (normal spell, passcode 31036355) to manifest/trunk. Two-step player targeting picks 1 own monster then 1 opponent monster; swaps them in place via zone copy. AI gives away weakest on its board and takes player's highest-ATK monster. Simplified text omits battle-position lock.

**Files:** `tools/card_data_manifest.json`, `include/creature_swap.h`, `src_custom/spell_effects/creature_swap.c`, `asm/ram_map.s`, `src_custom/code_8043EF4_hooks.c`, `src_custom/spell_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = CREATURE_SWAP`.

**Open / next:** In-game: activate with monsters on both sides; confirm swap and AI weakest pick.

---

## 2026-06-19 — Fix Thing in the Crater graveyard trigger

**Worked on:** Effect never fired when Thing was destroyed. Root causes: (1) custom monsters used `GetTypeGroup` for graveyard registration, which could skip custom card IDs on field→GY sends; (2) test hand had Meteor B. Dragon (Dragon) not a Pyro-Type monster. Added `Duel_CardIsMonster`, wired graveyard send hooks, Sangan-style effect text, Pyro filter via `Duel_CardHasMonsterType`. Runtime hand 2 = Flame Manipulator for testing.

**Files:** `include/duel_helpers.h`, `src_custom/duel_helpers.c`, `src_custom/card_passive_hooks.c`, `src_custom/embodiment_of_apophis_hooks.c`, `src_custom/permanent_effects/the_thing_in_the_crater.c`, `configs/runtime.c`

**Outcome:** `make test-cards-build` passes.

**Open / next:** Destroy Thing with Flame Manipulator still in hand; confirm effect text + Pyro special summon prompt.

---

## 2026-06-19 — The Thing in the Crater custom card

**Worked on:** Added The Thing in the Crater (FIRE Pyro L4 1000/1200, passcode 78243409) to manifest/trunk. Graveyard trigger on field destruction: optional Special Summon of 1 Pyro monster from hand via permanent effect hook (Sangan-style field-send + Ancient Rules-style hand summon). Uses `Duel_CardHasMonsterType`, `Duel_SpecialSummonFromHand`/`FromHandZone`.

**Files:** `tools/card_data_manifest.json`, `include/the_thing_in_the_crater.h`, `src_custom/permanent_effects/the_thing_in_the_crater.c`, `src_custom/permanent_effect_hooks.c`, `src_custom/activated_effects/graveyard_draw_on_destroy.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = THE_THING_IN_THE_CRATER`.

**Open / next:** In-game: destroy Thing in the Crater from field with a Pyro in hand, confirm optional summon prompt and AI picks highest-ATK Pyro.

---

## 2026-06-19 — Royal Knight custom card

**Worked on:** Added Royal Knight (LIGHT Fairy L3 1300/800, passcode 68280530) to manifest/trunk. Battle trigger: when it destroys a monster by battle, controller gains LP equal to the destroyed monster's original DEF — modeled on Guardian Angel Joan via `Duel_ChangeLp` + deferred resolve. Fixed truncated activation description text.

**Files:** `tools/card_data_manifest.json`, `include/royal_knight.h`, `src_custom/battle_effects/royal_knight.c`, `src_custom/battle_damage_hooks.c`, `asm/ram_map.s`, `src_custom/code_803F02C_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/code_8041C94_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, generated card includes

**Outcome:** `make test-cards-build` passes. `card_in_hand_1 = ROYAL_KNIGHT`.

**Open / next:** In-game: summon Royal Knight, battle-destroy a monster, confirm LP gain matches defender's DEF and effect text shows.

---

## 2026-06-18 — Fix direct-attack phantom (Kishido anim remap regression)

**Worked on:** Kishido commit added `Duel_RemapMutualDestroyBattleAnim` to all battles; with no GY flags it forced `unk18=8` (monster-vs-monster) on direct attacks (10/15), showing stale defender art (often Kaiser Glider) and 0 damage. Remap and destroy-protection (Kishido, Kaiser Glider) now run only for monster-vs-monster action ids 1/2/3/5. Reverted ineffective stale-data direct-attack band-aids.

**Files:** `src_custom/duel_helpers.c`, `src_custom/battle_effects/kaiser_glider.c`, `tests/host/test_kishido_spirit.py`, reverts in `embodiment_of_apophis_hooks.c`, `code_8043EF4_hooks.c`, `ai_attack_hooks.c`, `include/duel_helpers.h`, `possessed_dark_soul.c`

**Outcome:** `make test-cards-build` passes; host test asserts direct attack anim cases 10/15 are not remapped.

**Open / next:** In-game: opponent direct attack with empty field after prior Kaiser Glider battle — LP damage, no phantom card.

## 2026-06-18 — Direct attack phantom fix after PDS

**Worked on:** Opponent direct attacks left stale player-side `sActionData` / `gUnk2023EA0` from prior battles (phantom defender on battle screen, direct attack blocked). `Duel_ClearStaleDirectAttackDefenderData` runs before `SetAttackActionDirectAttack`; direct-attack empty-row check uses `Duel_InactiveFixedMonsterRowIsEmpty()` on fixed POV; PDS ends with `UpdateAllDuelGfx()`.

**Files:** `src_custom/duel_helpers.c`, `include/duel_helpers.h`, `src_custom/embodiment_of_apophis_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/ai_attack_hooks.c`, `src_custom/activated_effects/possessed_dark_soul.c`, `tests/host/test_possessed_dark_soul.py`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game: PDS tribute + steal, clear your field, let opponent direct attack — no phantom card, LP damage applies.

## 2026-06-18 — Possessed Dark Soul activation + phantom battle fix

**Worked on:** Fixed PDS effect not firing and post-effect battle desync. Self-zone lookup now uses `gFixedZones` (cursor row is fixed POV, not turn POV). Control transfer uses `CopyCard` + `Duel_NotifyMonsterZoneChanged`; relaxed activation to require ≥1 stealable target and ≥1 post-tribute slot (steal as many as fit).

**Files:** `src_custom/activated_effects/possessed_dark_soul.c`, `tests/host/test_possessed_dark_soul.py`

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game retest: face-up PDS vs opponent face-up L3 or lower monsters; confirm field gfx matches battle screen and opponent can direct attack when your row is empty.

## 2026-06-18 — Possessed Dark Soul custom card

**Worked on:** Added Possessed Dark Soul to manifest/trunk (SHADOW Fiend L3 1200/800, passcode 52860176, `MONSTER_EFFECT_POSSESSED_DARK_SOUL`). Ignition effect in `activated_effects/possessed_dark_soul.c`: tribute self, permanently take control of all opponent face-up Level 3 or lower monsters (`Duel_DestroyZone`, `Duel_ShowEffectTextTyped`). `card_in_hand_1 = POSSESSED_DARK_SOUL` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/constants/monster_effects.h`, `include/possessed_dark_soul.h`, `src_custom/activated_effects/possessed_dark_soul.c`, `src_custom/monster_effect_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, `tests/host/test_possessed_dark_soul.py`, generated card includes

**Outcome:** `make test-cards-build` passes; host test passes.

**Open / next:** In-game confirm self-tribute, mass steal of level 3 or lower face-up monsters, and zone-capacity gate when opponent has more targets than post-tribute slots.

## 2026-06-18 — Kishido per-side equal-ATK protection

**Worked on:** Fixed over-protection bug: `ApplyKishidoSpiritEqualAtkProtection` now clears only the protected controller's GY flag (`~1` player / `~2` opponent), matching GBA card text (your-side only). Extended `Duel_RemapMutualDestroyBattleAnim`: force case 2 when both still destroy; case 8 when neither; remap 1/3 only for mutual/attribute equal-ATK cases (2/16/17) so def-position battles stay untouched.

**Files:** `src_custom/duel_helpers.c`, `tests/host/test_kishido_spirit.py`

**Outcome:** `make test-cards-build` passes; host tests assert per-side flags and anim remap.

**Open / next:** In-game verify A–D (especially B: Kishido active, equal ATK vs Jinzo — you survive, enemy to GY, no softlock).

---

**Worked on:** Removed `sub_801B66C` LynJump hook and `Duel_PersistBattleScreenAnimCase` / `Duel_RestoreBattleScreenAnimCase` — stale anim case and bad vanilla tail-call caused post-win and battle-start softlocks. Kept: force `unk18=2` on unprotected mutual destroy, Kishido equal-ATK clears both GY flags, `CanMonsterBeDestroyedByBattle` for Spirit Reaper only.

**Files:** `src_custom/monster_attack_hooks.c`, `src_custom/duel_helpers.c`, `include/duel_helpers.h`, `src_custom/battle_damage_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `src_custom/LynJump.event`, tests

**Outcome:** `make test-cards-build` passes.

## 2026-06-18 — Equal-ATK mutual destroy fix (v2)

**Worked on:** Equal-ATK with no protection: force battle anim case 2 when both monsters still marked for GY; persist/restore anim case through battle screen (`Duel_PersistBattleScreenAnimCase`, hook on `sub_801B66C`). Kishido equal-ATK now clears both GY flags (card text: neither destroyed). Removed Kishido from `CanMonsterBeDestroyedByBattle` (Spirit Reaper only).

**Files:** `src_custom/duel_helpers.c`, `include/duel_helpers.h`, `src_custom/battle_damage_hooks.c`, `src_custom/monster_attack_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/draining_shield_hooks.c`, `src_custom/call_of_the_haunted_hooks.c`, `src_custom/LynJump.event`, tests

**Outcome:** `make test-cards-build` passes.

**Open / next:** In-game retest equal-ATK without Kishido on field; with Kishido active both should survive equal ATK.

## 2026-06-18 — Equal-ATK mutual destroy + battle destroy API

**Worked on:** Fixed equal-ATK battles when no protection applies: both monsters go to GY with vanilla cut+fire (case 2). Consolidated battle indestructibility into `CanMonsterBeDestroyedByBattle`, `Duel_ApplyBattleDestroyProtection`, and `Duel_RemapMutualDestroyBattleAnim` (early return when both sides still marked for destroy). Removed redundant fire-anim skip hook and deleted `battle_effects/kishido_spirit.c` (logic lives in duel_helpers).

**Files:** `src_custom/duel_helpers.c`, `include/duel_helpers.h`, `src_custom/battle_damage_hooks.c`, `src_custom/monster_attack_hooks.c`, `include/kishido_spirit.h`, `src_custom/card_effect_tally.md`, `tests/host/test_kishido_spirit.py`, `tests/host/test_duel_helpers.py`

**Outcome:** `make test-cards-build` and host tests pass.

**Open / next:** In-game verify equal-ATK with/without Kishido; reset `configs/runtime.c` test hand when done.

## 2026-06-18 — Kishido Spirit custom spell

**Worked on:** Added Kishido Spirit to manifest/trunk (continuous spell, passcode 60519422). Activation in `spell_effects/kishido_spirit.c` via `Duel_ActivateContinuousZone` (locks zone, not re-selectable). Battle protection in `battle_effects/kishido_spirit.c`: controller's monsters not destroyed when ATK equals opponent's ATK; respects Imperial Order. `card_in_hand_1 = KISHIDO_SPIRIT` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/kishido_spirit.h`, `src_custom/spell_effects/kishido_spirit.c`, `src_custom/battle_effects/kishido_spirit.c`, `src_custom/spell_effect_hooks.c`, `src_custom/battle_damage_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, `tests/host/test_kishido_spirit.py`, generated card includes

**Outcome:** `make test-cards-build` passes; host test passes. Card ID `0x03CD`.

**Open / next:** In-game confirm equal-ATK battle survival with spell active and locked continuous zone.

---

## 2026-06-18 — Jowls of Dark Demise custom card

**Worked on:** Added Jowls of Dark Demise to manifest/trunk (WATER Fiend L2 200/100, passcode 05257687, `MONSTER_EFFECT_JOWLS_OF_DARK_DEMISE`). FLIP effect in `activated_effects/jowls_of_dark_demise.c`: target 1 opponent monster, take control until End Phase (`willChangeSides`), controlled monster can direct attack (`unkTwo` flag). Player targeting via `DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET`; AI picks highest ATK valid target. `card_in_hand_1 = JOWLS_OF_DARK_DEMISE` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `include/constants/monster_effects.h`, `include/jowls_of_dark_demise.h`, `src_custom/activated_effects/jowls_of_dark_demise.c`, `src_custom/monster_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `src_custom/ai_attack_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, `src_custom/assets/cards/CARD_PROGRESS.md`, `tests/host/test_jowls_of_dark_demise.py`, generated card includes

**Outcome:** `make test-cards-build` passes; host test passes.

**Open / next:** In-game confirm FLIP targeting, End Phase return, and direct attack on stolen monster while opponent still has monsters.

---

## 2026-06-18 — Knight's Title custom spell

**Worked on:** Added Knight's Title to manifest/trunk (`KNIGHTS_TITLE`, passcode 87210505, cost 150). Spell effect in `spell_effects/knights_title.c`: tribute face-up Dark Magician, Special Summon Dark Magician Knight from hand (player pick) / deck / grave (hand > deck > grave). `CanActivateKnightsTitle` blocks activation when requirements unmet. `card_in_hand_1 = KNIGHTS_TITLE` in `configs/runtime.c`.

**Files:** `tools/card_data_manifest.json`, `src_custom/spell_effects/knights_title.c`, `include/knights_title.h`, `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`, `configs/runtime.c`, `src_custom/card_effect_tally.md`, generated card includes

**Outcome:** `make test-cards-build` passes. Card ID `0x03CB`.

**Open / next:** In-game confirm tribute requires face-up DM, hand selection, and grave-only-when-on-top behavior.

---

## 2026-06-18 — Rename Des Scissors to KA-2 Des Scissors

**Worked on:** Renamed card const `DES_SCISSORS` → `KA_2_DES_SCISSORS`, display name "KA-2 Des Scissors", art stem `ka_2_des_scissors.png`. Updated manifest, battle effect hook, CARD_PROGRESS, card_effect_tally; regenerated card data/art.

**Files:** `tools/card_data_manifest.json`, `src_custom/battle_effects/needle_burrower.c`, `src_custom/assets/cards/80x80/ka_2_des_scissors.png`, `src_custom/assets/cards/CARD_PROGRESS.md`, `src_custom/card_effect_tally.md`, generated card includes

**Outcome:** `make test-cards-build` passes. Card ID unchanged at `0x0395`.

**Open / next:** —

---


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
