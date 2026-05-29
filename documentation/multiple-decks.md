# Multiple player decks

## Index

- [Introduction](#introduction)
- [Runtime config](#runtime-config)
- [Code locations](#code-locations)
- [Save layout](#save-layout)

## Introduction

When `enable_multiple_decks` is `TRUE`, the field start menu lists **Deck 1**, **Deck 2**, and **Deck 3** instead of a single **Deck** row. Each deck stores 40 card IDs (80 bytes) and its own remaining deck-capacity value. Opening a deck editor sets that deck as the **active** deck used for duels and for B-to-exit validation on the start menu.

## Runtime config

| Field | Default in `configs/runtime.c` |
|-------|--------------------------------|
| `enable_multiple_decks` | `TRUE` (set `FALSE` for vanilla single-deck UI) |

## Code locations

| Piece | Location |
|-------|----------|
| Core logic | `src_custom/player_decks/player_decks.c`, `include/player_decks.h` |
| EWRAM / flash symbols | `asm/ram_map.s` |
| Start menu UI | `src_custom/start_menu_hooks.c` |
| Capacity / duelist level | `src_custom/deck_menu_hooks.c` |
| Save slot read/write | `src_custom/code_800AC64_hooks.c`, `src_custom/card_hooks.c` (`sub_803519C`, `sub_80351F8`) |
| LynJump | `src_custom/LynJump.event` |

## Save layout

- **Deck 1** cards and capacity remain in the vanilla `0x747` save blob via `g80D2D00` (through `gDeckMenu` / `gDeckCapacity` while building that blob).
- **Deck 2 / 3** cards, their capacities, and **active deck index** use mirrored flash pairs allocated after custom card qty in `asm/ram_map.s`.
- Before `sub_80351F8` writes the save buffer, deck 1 is copied into `gDeckMenu` so the vanilla layout still sees deck 1 even if another deck was active.

On first load after enabling the feature, flash `gActiveDeckIndex == 0xFF` initializes empty deck 2/3 and default capacities.
