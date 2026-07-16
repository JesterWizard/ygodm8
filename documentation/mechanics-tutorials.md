# Mechanics Tutorials

---

## Index

- [Introduction](#introduction)
- [Player flow](#player-flow)
- [Adding a tutorial](#adding-a-tutorial)
- [Script format](#script-format)
- [First entry — Boss Cut-Ins](#first-entry--boss-cut-ins)
- [Code locations](#code-locations)
- [TODO](#todo)
- [Limitations & bugs](#limitations--bugs)

## Introduction

**Mechanics tutorials** are guided fixed-board duels launched from the debug menu. They reuse the Timed Duel board layout format (`TimedDuelLayout` + `TD_*` macros) but have **no timer**, **no completion flags**, and **no rewards**.

Narration is a list of textbox lines, each with an optional **dialogue portrait** (`PORTRAIT_YUGI`, `PORTRAIT_JOEY`, …). Soft guidance: set up the board, explain the mechanic, complete when the player performs the key action.

## Player flow

| Step | What happens |
|------|----------------|
| Open debug menu | Overworld, **R** alone (`enable_debug_menu`) |
| **Mechanics** | Root row after Timed Duels — scrollable list |
| **A** on entry | Runs duel; returns to this list when done |
| Duel start | Fixed board applied; draw skipped; summon anims forced on |
| Intro lines | Portrait + textbox per scripted line |
| Complete | e.g. summon target card → outro lines → soft win |
| Exit | No trunk/money rewards; list reappears |

## Adding a tutorial

1. **Layout** — copy `sMechanicsLayout_01` in [`debug_menu_mechanics_layouts.c`](../src_custom/debug/debug_menu_mechanics_layouts.c); add extern in [`debug_menu_mechanics_layouts.h`](../include/debug_menu_mechanics_layouts.h). Use `TD_*` macros; leave `timerSeconds` / `rewardCardId` as `0` / `CARD_NONE`.
2. **Script** — in [`debug_menu_mechanics_scripts.inc`](../src_custom/debug/debug_menu_mechanics_scripts.inc) add title string, text strings (`#0` = newline, `#1` = wait for A), and `MT_LINE` / `MT_END` arrays for intro and outro.
3. **Registry** — one line in [`debug_menu_mechanics_table.inc`](../src_custom/debug/debug_menu_mechanics_table.inc):

   ```c
   MECHANICS_TUTORIAL_ENTRY(sMechanicsLayout_02, DUELIST_TRISTAN_092,
                            sMy_Title, sMy_Intro, sMy_Outro, CARD_NONE)
   ```

4. Rebuild (`make`). Editing the scripts/table `.inc` rebuilds `mechanics_tutorial.o`.

No runtime `switch` on tutorial index — completion is `winOnSummonCardId` on the entry.

## Script format

| Piece | Meaning |
|-------|---------|
| `MT_LINE(PORTRAIT_*, text)` | One textbox; show that portrait first (`PORTRAIT_NONE` = text only) |
| `MT_END` | Terminates an intro/outro list |
| `winOnSummonCardId` | After this card’s summon cut-in: refresh board → outro → `DeclareLoser(opponent)`. Use `CARD_NONE` to disable |

Portrait IDs live in [`overworld.h`](../include/overworld.h) (`PORTRAIT_YUGI`, `PORTRAIT_JOEY`, `PORTRAIT_SETO`, …).

## First entry — Boss Cut-Ins

| Setup | Value |
|-------|--------|
| Player monsters | Mystical Elf ×3 (tribute two for Yubel) |
| Player hand | Yubel |
| Opponent | Kuriboh, 1000 LP |
| Intro | Yugi portrait on both lines |
| Goal | Tribute Summon Yubel → cut-in → Yugi outro → duel ends |

## Code locations

| Feature | Location | Description |
|--------|----------|-------------|
| Entry / line structs | `include/mechanics_tutorial.h` | `MT_LINE` / `MT_END`, entry fields |
| Scripts (text + portraits) | `src_custom/debug/debug_menu_mechanics_scripts.inc` | Author here |
| Registry | `src_custom/debug/debug_menu_mechanics_table.inc` | One line per tutorial |
| Runtime | `src_custom/mechanics_tutorial.c` | Apply board, play lines, win-on-summon |
| Portrait helper | `Duel_ShowPortraitForTextbox` in `src_custom/duel_voice_hooks.c` | Top-left OAM during textbox |
| Layouts | `src_custom/debug/debug_menu_mechanics_layouts.c` | Fixed boards |
| Debug submenu | `src_custom/debug/debug_menu_mechanics.c` | List + launch |
| Intro hook | `PlayerTurnMain__Replacement` | After input maps ready |
| Summon complete | `FinishSummonAnimation` | Outro after cut-in |
| RAM | `asm/ram_map_ewram.s` | Active id + flags |

## TODO

- Optional move hints / soft blockers for wrong plays.
- Non-summon complete conditions (attack, activate spell, etc.) as entry fields.

## Limitations & bugs

- Soft guided only — player can do other legal moves; completion is action-based.
- Summon-complete path only runs when a summon animation actually plays for that card.
- Board apply is duplicated from Timed Duels (extract later if a third consumer appears).
- No persistence / one-shot clear flags.
