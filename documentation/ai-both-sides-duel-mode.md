# AI Both Sides Duel Mode

---

## Index

- [Introduction](#introduction)
- [Debug Menu Access](#debug-menu-access)
- [Duel Behavior](#duel-behavior)
- [Auto-Advance Text](#auto-advance-text)
- [Persistence](#persistence)
- [Bug Fixes](#bug-fixes)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

**AI Both Sides** is a debug-menu option that lets the vanilla duel AI control **both** duelists. It is useful for stress-testing card effects, watching full duels without input, and reproducing AI attack paths on the player’s side of the board.

With the option **Off** (default), behavior matches vanilla: you play your turns; the AI plays opponent turns only.

With **AI Both Sides** enabled:

- Your turn runs `AI_Main()` instead of `PlayerTurnMain()`.
- Opponent turns still run `AI_Main()` as in vanilla.
- Duel textboxes (turn banners, effect activations, win/loss lines) advance without waiting for **A** / **B** / **R**.
- The setting is saved to SRAM and restored on load.

See also [debug-menu.md](debug-menu.md) for how to open the overworld debug menu.

## Debug Menu Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_debug_menu` in `configs/runtime.c` (default **on**) |
| Overworld input | Press **B** on the field to open the debug menu |
| Root row | **AI Mode** (last item in the seven-row root list) |

### AI Mode submenu

| Row | Label | **A** behavior |
|-----|-------|----------------|
| 0 | Off | Disables both-sides AI; writes flash immediately |
| 1 | AI Both Sides | Enables both-sides AI; writes flash immediately |

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor |
| **A** | Apply highlighted mode (saved to primary + backup flash) |
| **B** | Return to root menu |

Implementation: `DebugAiModeViewer` in `src_custom/debug/debug_menu_ai_mode.c`.

## Duel Behavior

### Turn routing

Vanilla `DuelMain` in `src/duel/duel_main.c` already calls `AI_Main()` on opponent turns. The custom hook replaces only the **player** turn entry point:

| Turn | Vanilla | With AI Both Sides |
|------|---------|------------------|
| Player | `PlayerTurnMain()` | `AI_Main()` via `PlayerTurnMain__Replacement` |
| Opponent | `AI_Main()` | `AI_Main()` (unchanged) |

`PlayerTurnMain__Replacement` still runs end-of-turn cleanup after the AI finishes: `DestroyKarateManAtEndOfTurn`, `ResolveDelayedDuelEffectsAtTurnEnd`, and `UpdateDuelGfxExceptField`.

Manual duel controls (cursor, **A**/**B**, debug **SELECT**/**START** instant-loss shortcuts in `ProcessInput__Replacement`) are **not** used on player turns while both-sides mode is on, because the normal player input loop is skipped.

### AI attack execution

The AI schedules attacks through `sAI_Command` and vanilla helpers `sub_800E58C`–`sub_800E6B8`. Those functions call `SetAttackAction` / `SetAttackActionDirectAttack`, then `HandleAtkAndLifePointsAction`, then `CheckGraveyardAndLoserFlags`.

Custom replacements live in `src_custom/ai_attack_hooks.c` (see [Bug Fixes](#bug-fixes) for why they exist).

## Auto-Advance Text

While **AI Both Sides** is active, `WaitForTextboxAdvanceInput__Replacement` in `src_custom/code_8041C94_hooks.c` immediately advances any textbox that would normally wait for **A**, **B**, or **R**.

That covers:

- Turn banners (`DUEL_TEXT_PLAYER_TURN`, opponent turn strings)
- Monster, spell, and trap activation text (`sub_8041C94`, `sub_8041CCC`, effect handlers in `effect_text_hooks.c`)
- Post-duel lines (victory, capacity increase, card obtained, and similar)

There is no separate per-message flag anymore; the check is `DebugAiMode_IsBothSides()`.

## Persistence

| Symbol | RAM | Role |
|--------|-----|------|
| `gDebugAiBothSidesMode` | EWRAM (`asm/ram_map.s`) | Runtime value: `DEBUG_AI_MODE_OFF` (0) or `DEBUG_AI_MODE_BOTH_SIDES` (1) |
| `gDebugAiBothSidesModeFlashPrimary` | Flash mirror | Saved with primary save |
| `gDebugAiBothSidesModeFlashBackup` | Flash mirror | Saved with backup save |

| Event | Handler |
|-------|---------|
| Toggle in debug menu | `DebugAiMode_SetMode` → `DebugAiMode_SaveToFlashPrimary/Backup` |
| Save slot write | `code_800AC64_hooks.c` |
| Save slot read | `code_800AC64_hooks.c` → `DebugAiMode_LoadFromFlashPrimary/Backup` |
| New game | `DebugAiMode_Reset` |

API header: `include/debug_ai_mode.h`. Core logic: `src_custom/debug_ai_mode.c`.

## Bug Fixes

Short summaries of issues found while building this feature and how they were addressed.

### 1. AI direct attack used the wrong board column

**Symptom:** When the AI attacked on the **player** turn (both-sides mode), attack art could vanish and the opponent’s LP jumped to 0 regardless of the monster’s actual ATK.

**Cause:** Vanilla AI attack helpers (`sub_800E58C`, `sub_800E5E4`, `sub_800E63C`, `sub_800E6B8` in `src/duel/ai.c`) pass `4 - col2` into `SetAttackActionDirectAttack` / `SetAttackAction`. That mirror matches **opponent** `gFixedZones[1]` layout (`board[1][4-i]`). On the player side, `gFixedZones[2]` is **not** mirrored (`board[2][i]`). The wrong column could read an empty zone or the wrong card, producing bogus damage and broken battle GFX.

**Fix:** LynJump replacements in `src_custom/ai_attack_hooks.c` resolve the correct fixed column with `AiFixedColForZone(zone, fixedRow)` by finding which `gFixedZones[fixedRow][i]` pointer matches the attacker/defender `DuelCard*`. Direct and monster attacks call `TryApplyFairyBoxToPendingAction`, `HandleAtkAndLifePointsAction`, and `CheckGraveyardAndLoserFlags` like vanilla. Empty attackers (`CARD_NONE`) are skipped.

### 2. Turn text still waited for a button press

**Symptom:** With both-sides AI on, “YOUR TURN” (and opponent turn text) still required **A**/**B**/**R**.

**Cause:** Only vanilla `DisplayDuelText` paths were considered initially.

**Fix (evolved):** First version used a temporary IWRAM flag around player/opponent turn strings. Final version auto-advances **all** duel textboxes via `WaitForTextboxAdvanceInput__Replacement` when `DebugAiMode_IsBothSides()` is true (see [Auto-Advance Text](#auto-advance-text)).

### 3. No deck capacity or win rewards after winning

**Symptom:** After a duel that visibly ended with the opponent at 0 LP, the player did not receive deck capacity, money, or trunk rewards.

**Cause:** `DuelEnd` in `src/duel/duel_main.c` sets `gDuelData.winner` from `gDuelistStatus[DUEL_OPPONENT] == DUELIST_STATUS_DEFEAT` only. Some AI attack paths updated `gDuelLifePoints` to 0 without calling `DeclareLoser(DUEL_OPPONENT)`, so `HandleOutcome` ran `HandleLoss` instead of `HandleWin` even though the board showed a win.

**Fix:** `HandleOutcome__Replacement` in `src_custom/code_801EF30_hooks.c` runs `ReconcileDuelDefeatStatus()` before winner selection: if LP is 0 or the duelist decked out but defeat status was never set, it calls `DeclareLoser` for that duelist. Then it applies the same winner logic as vanilla `DuelEnd` and calls `HandleWin` or `HandleLoss`.

**Note:** If `max_deck_capacity_at_start` is **true** in `configs/runtime.c`, capacity may already be 65000, so the capacity **number** will not increase even when `IncreaseDeckCapacity` runs correctly. Other rewards (money, cards, victory text) should still apply.

### 4. Build / RAM placement (implementation note)

Early prototypes stored a separate “auto-advance turn text” flag in a linker section that was discarded. The symbol was moved into `asm/ram_map.s` (IWRAM). That flag was later removed in favor of checking `DebugAiMode_IsBothSides()` directly in `WaitForTextboxAdvanceInput`, which simplified the design and covered all effect text.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Mode constants / API | `include/debug_ai_mode.h` | `DEBUG_AI_MODE_*`, `DebugAiMode_IsBothSides`, save/load/reset |
| Runtime + flash I/O | `src_custom/debug_ai_mode.c` | EWRAM value, normalize, persist to flash mirrors |
| Debug UI | `DebugAiModeViewer`, `DebugMenuDrawAiMode` in `src_custom/debug/debug_menu_ai_mode.c` | Submenu Off / AI Both Sides |
| Root wiring | `debug_menu.c`, `debug_menu_internal.h` | `DEBUG_VIEW_AI_MODE`, root label **AI Mode** |
| Player turn hook | `PlayerTurnMain__Replacement` in `src_custom/code_803F02C_hooks.c` | Calls `AI_Main()` when both sides enabled |
| AI attack hooks | `src_custom/ai_attack_hooks.c` | `sub_800E58C`–`sub_800E6B8` replacements, column fix |
| LynJump (attacks) | `src_custom/LynJump.event` | POINs for four AI attack helpers |
| Text auto-advance | `WaitForTextboxAdvanceInput__Replacement` in `src_custom/code_8041C94_hooks.c` | Skips wait when both sides on |
| Win / outcome | `HandleOutcome__Replacement`, `ReconcileDuelDefeatStatus` in `src_custom/code_801EF30_hooks.c` | Defeat reconciliation + `HandleWin`/`HandleLoss` |
| LynJump (outcome) | `src_custom/LynJump.event` @ `$1FF70` | `HandleOutcome__Replacement` |
| Save integration | `src_custom/code_800AC64_hooks.c` | Load/save/reset with game SRAM |
| RAM map | `asm/ram_map.s` | `gDebugAiBothSidesMode` (EWRAM), flash mirrors |
| Vanilla AI loop | `AI_Main` in `src/duel/ai.c` | Unchanged; used for both duelists when enabled |
| Vanilla duel flow | `DuelMain`, `DuelEnd` in `src/duel/duel_main.c` | Turn loop and outcome entry |

## TODO

- Optional runtime-config toggle to enable both-sides AI without the debug menu (for CI or automated soak tests).
- Speed control (frame skip or faster text) while watching AI-only duels.
- Log or on-screen overlay of AI command indices for debugging bad plays.

## Limitations & Bugs

- **No human player input** on your turn while both-sides mode is on; use **Off** to play normally.
- AI quality and rules knowledge are still vanilla AI; this mode does not improve AI strategy.
- Auto-advance text removes time to read effect copy during AI duels; pause is not implemented.
- Debug duel shortcuts on **SELECT** / **START** in `ProcessInput__Replacement` only apply when the manual player turn loop runs (both-sides **Off**).
- Opponent-turn `AI_Main` simulation still saves/restores duel state (`sub_800EE24` / `sub_800EE94` in `ai.c`); rare desyncs should be reported with a save state and repro steps.
- At max deck capacity (`max_deck_capacity_at_start`), capacity rewards are applied in code but the displayed cap may not change.

If you see incorrect LP, missing rewards, or stuck text with **AI Both Sides** enabled, note the duelist, last card played, and whether the duel ended by LP, deck out, or effect win (Exodia, Destiny Board, etc.).
