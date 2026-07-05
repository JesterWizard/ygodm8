# Timed Duels

---

## Index

- [Introduction](#introduction)
- [Player flow](#player-flow)
- [Adding a puzzle](#adding-a-puzzle)
- [Layout format](#layout-format)
- [Code locations](#code-locations)
- [TODO](#todo)
- [Limitations & bugs](#limitations--bugs)

## Introduction

**Timed duels** are one-turn puzzle challenges launched from the debug menu. Each entry starts a duel with a fixed board, hands, graveyards, life points, and field. The player must win on that turn; ending the turn without winning counts as a loss.

Completing a puzzle grants **one copy of a rare card** to the trunk. There is **no money** and **no deck-capacity** reward. Each puzzle can be cleared **once per save**; cleared entries appear in **yellow** in the debug menu list.

Completion flags live in **EWRAM** when you win. They are written to flash only when you **save the game** manually (same path as other custom save mirrors in `code_800AC64_hooks.c`). Reloading without saving loses unsaved completions.

Menu labels are auto-generated as **Timed Duel 1**, **Timed Duel 2**, … from list order.

## Player flow

| Step | What happens |
|------|----------------|
| Open debug menu | Overworld, **R** alone (`enable_debug_menu`) |
| **Timed Duels** | Root row 12 — scrollable list |
| **A** on puzzle | Runs duel; returns to this list when done |
| Win this turn | Rare reward card added; completion saved to flash |
| End turn without win | Immediate loss; retry prompt offered |
| Cleared puzzle | Row text drawn in yellow; **A** ignored |

## Adding a puzzle

1. Copy `sTimedDuelLayout_01` in `src_custom/debug/debug_menu_timed_duel_layouts.c` to a new `sTimedDuelLayout_NN` block.
2. Add `extern const struct TimedDuelLayout sTimedDuelLayout_NN;` to `include/debug_menu_timed_duel_layouts.h`.
3. Fill board rows, hands, graveyards, LP, and field using macros from `include/debug_menu_timed_duel_macros.h`.
4. Append one line to `src_custom/debug/debug_menu_timed_duel_table.inc`:

   ```c
   TIMED_DUEL_ENTRY(sTimedDuelLayout_02, DUELIST_TRISTAN_092)
   ```

4. Rebuild (`make`).

## Layout format

`struct TimedDuelLayout` (`include/timed_duel.h`) holds the full duel snapshot:

| Field | Description |
|-------|-------------|
| `board[4][5]` | Field zones — rows are `FixedRow` order (opponent backrow → player backrow) |
| `hands[2][5]` | `[0]` player hand, `[1]` opponent hand |
| `graveyard[2][40]` | Bottom-to-top card stacks per duelist (`CARD_NONE` padded) |
| `playerLp` / `opponentLp` | Starting life points |
| `field` | `FIELD_*` terrain |
| `turnCount` | Board HUD turn number (`0` = random 2..30) |
| `rewardCardId` | Rare card granted on win |

Each zone uses `TimedDuelCardSlot`:

| Member | Meaning |
|--------|---------|
| `cardId` | `CARD_NONE` = empty |
| `faceUp` | Face-up / activated (set traps/spells use `TD_SET`) |
| `defending` | Defense position for monsters |
| `permStage` | Permanent stage boosts (e.g. Exodia Necross) |

Macros (`timed_duel_macros.inc`):

| Macro | Use |
|-------|-----|
| `TD_EMPTY` | Empty zone |
| `TD_ATK(card)` | Face-up attack monster |
| `TD_ATK_STAGE(card, n)` | Face-up attack monster with `permStage` already applied |
| `TD_DEF(card)` | Face-up defense monster |
| `TD_SET(card)` | Face-down set spell/trap |
| `TD_FACEUP(card)` | Face-up backrow |

Example graveyard (player has two cards, opponent empty):

```c
{
  { DARK_MAGICIAN, POT_OF_GREED, CARD_NONE },
  { CARD_NONE },
},
```

## Code locations

| Feature | Location |
|---------|----------|
| Layout struct | `include/timed_duel.h` |
| Slot macros | `include/debug_menu_timed_duel_macros.h` |
| Puzzle layouts | `src_custom/debug/debug_menu_timed_duel_layouts.c` |
| Layout symbols | `include/debug_menu_timed_duel_layouts.h` |
| Puzzle registry | `src_custom/debug/debug_menu_timed_duel_table.inc` |
| Apply logic | `src_custom/timed_duel.c` |
| Menu titles | `TimedDuel_FormatMenuTitle` in `timed_duel.c` |
| Completion persistence | EWRAM on win; flash on manual save via `code_800AC64_hooks.c` |

## TODO

- Per-puzzle custom deck lists.
- Optional win-condition flags beyond “defeat opponent this turn”.

## Limitations & bugs

- Up to **128** puzzles (`TIMED_DUEL_COMPLETION_BYTES`).
- Graveyard stacks need `expand_graveyard` enabled in `configs/runtime.c` for full multi-card GY; otherwise only the top card is applied.
- Opponent does not take a turn.
