# Duel B Menu Surrender

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

During a duel, pressing **B** opens the B menu overlay with options such as Details, Turn End, and Discard. Vanilla only exposes three choices. This feature adds a fourth option, **Surrender**, which forfeits the duel immediately.

When enabled, the menu uses a **2×2 grid** of labels and the vanilla Millennium Eye cursor. The feature is controlled by `gRuntimeConfig.enable_surrender_in_duel_b_menu` in `configs/runtime.c` (default **on**). When disabled, `BMenuMain__Replacement` falls back to the vanilla three-option loop unchanged.

## Plan

### Player-facing layout

Labels are drawn in a fixed grid. Cursor positions (eye sprite) stay at vanilla tile offsets; text columns are offset to the right of each cursor.

| | Left (col 5) | Right (col 17) |
|---|---|---|
| **Rows 1–2** | Details | Discard |
| **Rows 3–4** | Turn End | Surrender |

Cursor highlight cells (unchanged from vanilla, plus a fourth slot for Surrender):

| Option | Tilemap row | Cursor col |
|--------|-------------|------------|
| Details | 1 | 2 |
| Turn End | 3 | 2 |
| Discard | 1 | 14 |
| Surrender | 3 | 14 |

### D-pad navigation

| From | Up | Down | Left | Right |
|------|----|------|------|-------|
| Details | Details | Turn End | Details | Discard |
| Turn End | Details | Turn End | Turn End | Surrender |
| Discard | Discard | Surrender | Details | Discard |
| Surrender | Discard | Surrender | Turn End | Surrender |

### A-button actions

| Option | Result |
|--------|--------|
| Details | Show card details for the field cursor target (same as vanilla) |
| Turn End | Set `gIsPlayerTurnOver = 1` and exit the menu |
| Discard | Send the field cursor monster to the graveyard when valid (same as vanilla) |
| Surrender | Call `DeclareLoser(DUEL_PLAYER)` and exit the menu |

### Label drawing model

Vanilla `InitBMenu` copies a baked tilemap template (`g80F13D0`) that already contains label glyphs in the wrong places for a four-option layout. The custom path **does not** rely on template text cells. Instead:

1. Copy the template (frame, deck/LP stat blocks, graveyard names).
2. On each refresh, **clear** all label bands and any remaining label tiles (index ≥ 88).
3. Load a **four-string** localized label blob into CHR at `gBgVram.cbb0 + 0x8B00`.
4. Draw all four entries from `sBMenuOptionLabels` via direct tilemap writes.
5. Re-apply the eye cursor highlight for the current selection.
6. Flush with `sub_8041014()`.

`DuelBMenu_RefreshOverlay(highlightedOption)` runs on init and after every D-pad move so label redraw does not erase the cursor.

### CHR tile bases (four-string layout)

The extended string is four 10-character fields (40 chars total):

```
Details   Turn end  Discard   Surrender 
```

With font flag `0x901`, each 10-character block occupies **20 CHR tiles** in VRAM. Tile bases for drawing must use **20-tile spacing**, not the vanilla three-option spacing:

| Option | Tile top | Tile bottom | Notes |
|--------|----------|-------------|-------|
| Details | 88 | 90 | Same as vanilla |
| Turn End | 108 | 110 | Was 128 in vanilla 3-option layout |
| Discard | 128 | 130 | Was 148 in vanilla 3-option layout |
| Surrender | 148 | 150 | New fourth block |

Each draw uses `g8DF811C[i]` for `i = 0 .. width-1` within the selected block. Do **not** add a per-option character offset on top of the tile base; the base already selects the string section.

Localized strings live in `sText_BMenuLabelsExtended` in `src_custom/duel_b_menu_hooks.c` and mirror the vanilla `{ENG}` / `{FRE}` / … pattern.

### Enable / disable flow

```
BMenuMain__Replacement
├── enable_surrender_in_duel_b_menu == TRUE  → BMenuMainWithSurrender → DuelBMenu_* API
└── FALSE                                    → BMenuMainVanilla       → vanilla InitBMenu loop
```

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `enable_surrender_in_duel_b_menu` in `configs/runtime.h` and `configs/runtime.c` | Enables the four-option menu and Surrender action |
| Public API | `include/duel_b_menu.h` | `B_MENU_*` enum and `DuelBMenu_*` entry points |
| Menu init / labels / cursor | `src_custom/duel_b_menu_hooks.c` | Template init, table-driven label draw, highlight, surrender handler |
| Label table | `sBMenuOptionLabels` in `src_custom/duel_b_menu_hooks.c` | Column, row, width, and CHR tile bases per option |
| Extended label text | `sText_BMenuLabelsExtended` in `src_custom/duel_b_menu_hooks.c` | Four-field localized menu strings |
| Main loop hook | `BMenuMain__Replacement`, `BMenuMainWithSurrender` in `src_custom/duel_opponent_hand_scroll_hooks.c` | D-pad navigation, A/B handling, calls into `DuelBMenu_*` |
| LynJump wiring | `POIN BMenuMain__Replacement` in `src_custom/LynJump.event` | Replaces vanilla `BMenuMain` at `$080421CC` |
| Vanilla reference | `InitBMenu`, `BMenuMain`, `sub_80428EC` in `src/duel/code_80421CC.c` | Original three-option layout and cursor helper |
| Host validator | `tools/validate_duel_b_menu.py` | Checks layout constants and simulates clear/draw against ROM template |
| Host tests | `tests/host/test_duel_b_menu.py` | Unit tests for validator and layout constants |
| GFX flush | `sub_8041014` in `src/duel/duel_textbox.c` | Copies B-menu tilemap/CHR from EWRAM buffer to BG VRAM |

## TODO

- Add a screenshot or short clip to this doc once the layout is stable across languages.
- Confirm Japanese label spacing in `sText_BMenuLabelsExtended` if JP menu text looks cramped.

## Limitations & Bugs

- Surrender always declares **the player** (`DUEL_PLAYER`) the loser. There is no “offer draw” or AI surrender path.
- When the runtime flag is off, behavior matches vanilla exactly; no Surrender string is loaded.
- Label placement assumes the vanilla B-menu template (`g80F13D0`) is unchanged in ROM. If the template tilemap changes, update `GOLDEN_TEMPLATE_SURRENDER_CELLS` in `tools/validate_duel_b_menu.py`.
- CHR tile bases **must** stay on 20-tile boundaries for the four-string blob. Reverting to vanilla 88/128/148 spacing will mislabel options (Discard shown as Turn End, etc.).
- Right-column labels use col **17**, not col 14 (cursor col). Col 14 overlaps the tail of the Details string when col 5 + width 10 is used.
- Rows **14–16** of the template still contain baked Discard bands; the clear pass wipes these so they do not appear below the 2×2 grid.
