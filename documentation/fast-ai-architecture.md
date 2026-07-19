# Fast AI Architecture

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

*Reshef of Destruction* has no rigid Main / Battle / End phases. The opponent may act in flexible order until they pass. That fits a **board-state loop** better than phase-based AI: generate legal actions, score them with vanilla execute-sim, execute the best one, then reevaluate until ending the turn is better than any remaining play.

`fast_ai` does **not** invent free-form heuristic priorities. When enabled it:

1. **Scans the board** and prunes impossible / redundant `gAED58` slabs.
2. **Light-scores attacks** (vanilla face-up after-formula / direct lethal band) without save/execute — including when the opponent has set backrow (trap nuance traded for speed).
3. **Full-sims at most `AI_FAST_FULL_SIM_BUDGET` (16)** non-attack legal lines (high-impact / activates first); skips the budget entirely once a lethal line is already scored.
4. **Preferred empty zone only** for 0-tribute summons and sets (cuts 5× destination templates).
5. **Skips post-batch GFX** and GY tile rebuild after the think.

Priorities still come from vanilla speculative execute. Heuristic top-N scoring stays removed.

[`enable_smarter_ai`](smarter-ai.md) remains a separate post-sim picker concern.

## Plan

### Current turn loop (already Reshef-shaped)

[`AI_Main__Replacement`](../src_custom/ai_main_hooks.c) already implements the board-state loop:

1. Simulate candidate actions (`AiSimulateAllCandidateActions`).
2. Pick one action (`sub_800EF0C__Replacement` → force activates / `AiDecision_PickAction`).
3. Execute it.
4. Run permanent effects / win checks.
5. Repeat until the picker returns pass (end turn).

After a normal summon, `summoningBlocked` makes the next think drop all summon/ritual templates — the main “incremental” saving without stale priorities.

### What `fast_ai` does today

When `fast_ai` is TRUE:

1. [`AiSimScanBoard`](../src_custom/ai_sim_fast.c) fills hand/field flags.
2. [`AiSimQuickReject`](../src_custom/ai_sim_fast.c) skips impossible / redundant entries.
3. Remaining legal candidates run vanilla save → execute → (optional permanent) → restore.
4. A scored line `≥ AI_PRIORITY_LETHAL_MIN` marks lethal; later low-impact categories are skipped.
5. Turn loop skips `GraveyardExpand_RefreshDisplay` and uses `gHideEffectText` for cheap permanent updates after real actions.

When `fast_ai` is FALSE: full table sim with no quick-reject; full GY refresh after each action.

### Reject classes (`AiSimQuickReject`)

| Class | Rule |
|-------|------|
| Empty source | Zone1 empty for summon/set/activate/discard/monster-effect |
| Perm without hand flag | Permanent-card actions when hand has no `unk1E` card |
| WITH_TRAP duplicate | Trap-variant actions when opponent has no set backrow |
| Summoning blocked | All summon/tribute/ritual activates |
| No ritual | Place/activate ritual when no ritual in hand/backrow |
| Tribute count | N-tribute templates when fewer than N monsters on our field |
| No face-up / face-down prey | Face-up/down attack families with no matching enemy |
| Activation blocked | `Duel_IsCardActivationBlocked` |
| Targetless normal spell | `!AiNormalSpellHasActivationTargets` |
| Empty attack/position source | Attack or position-change on empty monster zone |
| Noop position | Already in the requested battle position |
| Empty tribute slots | 1/2/3-tribute actions with empty zone2/3/4 |
| Illegal attack | Cannot declare, empty target, face-up/down mismatch |
| Post-lethal filter | Non-attack / non-high-impact after a lethal priority |
| Empty required zone2 | Non-destination zone2 empty (summon/set destinations still allowed empty) |

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `fast_ai` in [`configs/runtime.h`](../configs/runtime.h) / [`configs/runtime.c`](../configs/runtime.c) | Prune + cheap post-action GFX |
| Debug menu | [`src_custom/debug/debug_menu_runtime_config.c`](../src_custom/debug/debug_menu_runtime_config.c) | In-duel toggle for Fast AI |
| Turn loop | `AI_Main__Replacement` in [`src_custom/ai_main_hooks.c`](../src_custom/ai_main_hooks.c) | Board-state sim → pick → execute → reevaluate |
| Sim loop | `AiSimulateAllCandidateActions` in [`src_custom/ai_hooks.c`](../src_custom/ai_hooks.c) | Vanilla execute-sim; optional prune / lethal / perm skip |
| Quick-reject | `AiSimQuickReject` / `AiSimScanBoard` in [`src_custom/ai_sim_fast.c`](../src_custom/ai_sim_fast.c) | Board-flag prune |
| Action pick | `sub_800EF0C__Replacement` in [`src_custom/ai_hooks.c`](../src_custom/ai_hooks.c) | Force activates, then `AiDecision_PickAction` |
| Save / restore | `sub_800EE24__Replacement` / `sub_800EE94__Replacement` in [`src_custom/ai_simulation_hooks.c`](../src_custom/ai_simulation_hooks.c) | Snapshot duel state around candidate sims |

## TODO

1. Profile remaining sim cost if turns still feel slow with continuous monsters on board.
2. Optional: shallow beam only if vanilla quality gaps appear — do not reintroduce heuristic priority invention.

## Limitations & Bugs

- Light-scoring attacks with set backrow skips WITH_TRAP execute nuance; rare trap-on-attack priority differences may differ from full vanilla sim.
- Force-activate of set normals uses `AiNormalSpellHasActivationTargets` (Spellbinding Circle / Shadow Spell need opponent monsters).
- Quick-reject must treat summon/set **destination** zones (often `zone2`) as allowed-empty; rejecting them caused pass-turn idles (see session logs 2026-06-28).
- Post-lethal filtering keeps attacks and high-impact activates; rare non-attack lethals must already have been scored.
- Skipping permanents when `!AiSimFieldNeedsPermanentRescan()` assumes after-priority does not need continuous ATK recalculation on an empty continuous board.
- `enable_smarter_ai` and `fast_ai` may both be on; smarter AI only reshapes the filled priority table after vanilla scoring.
- Attribute matchups use full vanilla wheel via `sub_803FBCC__Replacement`.

Please report unexpected AI loops, idle passes, or obviously bad lines with the duelist, turn, and board state (and whether `fast_ai` / `enable_smarter_ai` were enabled).
