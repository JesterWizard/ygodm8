# Mechanics Tutorials

---

## Index

- [Introduction](#introduction)
- [Player flow](#player-flow)
- [Adding a tutorial](#adding-a-tutorial)
- [First entry — Boss Cut-Ins](#first-entry--boss-cut-ins)
- [Code locations](#code-locations)
- [TODO](#todo)
- [Limitations & bugs](#limitations--bugs)

## Introduction

**Mechanics tutorials** are guided fixed-board duels launched from the debug menu. They reuse the Timed Duel board layout format (`TimedDuelLayout` + `TD_*` macros) but have **no timer**, **no completion flags**, and **no rewards**. Narration uses vanilla duel textboxes (`sub_8041C94` with `#0` newlines and `#1` wait-for-input).

The goal is soft guidance: set up the board, explain the mechanic, tell the player what to do, and complete when they perform the key action.

## Player flow

| Step | What happens |
|------|----------------|
| Open debug menu | Overworld, **R** alone (`enable_debug_menu`) |
| **Mechanics** | Root row after Timed Duels — scrollable list |
| **A** on entry | Runs duel; returns to this list when done |
| Duel start | Fixed board applied; draw skipped; summon anims forced on |
| Intro text | Character-prefixed lines explain the mechanic and the move to make |
| Complete | Tutorial-specific (e.g. summon Yubel) → outro text → soft win |
| Exit | No trunk/money rewards; list reappears |

## Adding a tutorial

1. Copy `sMechanicsLayout_01` in `src_custom/debug/debug_menu_mechanics_layouts.c` to a new `sMechanicsLayout_NN` block.
2. Add `extern const struct TimedDuelLayout sMechanicsLayout_NN;` to `include/debug_menu_mechanics_layouts.h`.
3. Fill board / hands / LP using macros from `include/debug_menu_timed_duel_macros.h` (`timerSeconds` / `rewardCardId` unused — set `0` / `CARD_NONE`).
4. Add a title string in `mechanics_tutorial.c` and append one line to `src_custom/debug/debug_menu_mechanics_table.inc`:

   ```c
   MECHANICS_TUTORIAL_ENTRY(sMechanicsLayout_02, DUELIST_TRISTAN_092, sTitle_MyMechanic)
   ```

5. Extend the `switch` in `MechanicsTutorial_TryShowIntro` / `MechanicsTutorial_OnSummonAnimFinished` (or other complete hook) for the new index.
6. Rebuild (`make`). The Makefile rebuilds `mechanics_tutorial.o` when the table `.inc` or layouts header changes.

## First entry — Boss Cut-Ins

| Setup | Value |
|-------|--------|
| Player monsters | Mystical Elf ×3 (tribute two for Yubel) |
| Player hand | Yubel |
| Opponent | Kuriboh, 1000 LP |
| Goal | Tribute Summon Yubel → custom cut-in plays → outro → duel ends |

## Code locations

| Feature | Location | Description |
|--------|----------|-------------|
| API / entry struct | `include/mechanics_tutorial.h` | Active id, apply, skip-draw, intro/summon hooks |
| Runtime | `MechanicsTutorial_*` in `src_custom/mechanics_tutorial.c` | Table, apply, narration, complete |
| Layouts | `src_custom/debug/debug_menu_mechanics_layouts.c` | Fixed boards |
| Registry | `src_custom/debug/debug_menu_mechanics_table.inc` | Entry list |
| Debug submenu | `DebugMechanicsViewer` in `src_custom/debug/debug_menu_mechanics.c` | List + launch |
| Root menu | `src_custom/debug/debug_menu.c` | `"Mechanics"` row |
| InitBoard apply | `InitBoard__Replacement` in `src_custom/code_803F02C_hooks.c` | Seeds board |
| Intro | `PlayerTurnMain__Replacement` | After input maps ready |
| Skip draw | `duel_main_hooks.c` | Same pattern as Timed Duels |
| Summon complete | `FinishSummonAnimation` in `src_custom/summon_animations.c` | Outro after cut-in (rebuilds board gfx first) |
| Win/loss exit | `HandleWin__Replacement` / `HandleLoss__Replacement` | No rewards |
| RAM | `gMechanicsTutorial*` in `asm/ram_map_ewram.s` | Active id + flags |

## TODO

- Per-entry callback table instead of index `switch` once a few tutorials exist.
- Optional move hints / soft blockers for wrong plays.
- Named speaker portraits (reuse duel voice portrait path).

## Limitations & bugs

- Soft guided only — player can do other legal moves; completion is action-based.
- Summon-complete path only runs when a summon animation actually plays for that card.
- Board apply is duplicated from Timed Duels (extract later if a third consumer appears).
- No persistence / one-shot clear flags.
