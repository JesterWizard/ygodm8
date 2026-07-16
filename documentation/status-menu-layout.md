# Status Menu Layout

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Editing the Layout](#editing-the-layout)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The field **Status** screen (opened from the start menu) shows the player name, deck capacity, duelist level, life points, and money. Vanilla hard-codes label positions in the baserom BG tilemap (`gUnk_8088778`) and stat-digit helpers in `asm/status_menu.s`.

This project replaces the whole screen setup in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) via LynJump. Layout constants live at the top of that file so contributors can reposition labels and stat numbers without touching vanilla `src/status_menu.c`.

Player-facing goals:

- Readable two-line labels (**Deck** / **Capacity**, **Duelist** / **Level**, **Life** / **Points**) that fit the panel width.
- Correct stat values and white label text (palette bank 15).
- No ghost tiles when labels are moved away from vanilla map rows.

## Plan

### Screen build order

`StatusMenu__Replacement` runs this sequence:

| Step | Function | Responsibility |
|------|----------|----------------|
| 1 | `PlaceStatusMenuBackground` | Copy baserom tilemap rows into `gBgVram.sbb1F` |
| 2 | `PlaceStatusMenuLabels` | Patch label tile entries (Name, split labels, Money) |
| 3 | `PlaceStatusMenuPlayerName` | Player name slots (fixed asm map indices) |
| 4 | `PlaceStatusMenuAccentTiles` | Decorative accent grids and left icons |
| 5 | `PlaceStatusMenuMoneySuffix` | `"domino"` suffix tiles |
| 6 | `PlaceStatusMenuLabelGfx` | Palettes + `CopyStringTilesToVRAMBuffer` for all label/digit gfx |
| 7 | `PlaceStatusMenuMillenniumTracker` | Seven item icons in a horizontal row (silhouette or color) |
| 8 | Stat draw helpers | Write tall digit glyphs for level, capacity, LP, money |
| 9 | `LoadCharblock3` / `LoadPalettes` | Push VRAM and palette buffers to hardware |

The menu blocks on **B** until exit, then plays the cancel SFX.

### Label types

| Type | Examples | Map placement | Gfx source |
|------|----------|---------------|------------|
| Single-line | Name, Money | One row of consecutive tile indices | Baserom strings (`gUnk_8088C58`, `gUnk_8088DCC`) or fixed `TILE_BASE` |
| Split two-line | Deck Capacity, Duelist Level, Life Points | Word 1 on `row`, word 2 on `row + 1` | Custom `APPEND_RODATA` strings + `sSplitLabels[]` table |
| Tall digits | 65000, 999, 8000, money | Top row + bottom row per digit (`row` and `row + 1`) | Digit glyph table `g8DF811C` |

### Split-label table (`sSplitLabels[]`)

Each entry is a `StatusSplitLabel`:

```c
{ row, col, vanillaRow, vanillaCol, vanillaTiles, word1Tiles, word2Tiles, word2Index, charOffset }
```

| Field | Meaning |
|-------|---------|
| `row`, `col` | Top word map position (BG tilemap row/col in `sbb1F`) |
| `vanillaRow`, `vanillaCol`, `vanillaTiles` | Baserom label slot to clear when moved |
| `word1Tiles` | Horizontal tile count for the first word |
| `word2Tiles` | Horizontal tile count for the second word |
| `word2Index` | Character index in the label string where the second word starts (after the space) |
| `charOffset` | Byte offset in `STATUS_MENU_CHARBUF` where `CopyStringTilesToVRAMBuffer` loads the string |

Tile indices for map entries are `STATUS_LABEL_TILE_BASE(charOffset) + charIndex`, where `STATUS_LABEL_TILE_BASE(x) = x / 32`.

Current defaults:

| Label | Top row / col | Word 1 | Word 2 | `word2Index` | `charOffset` |
|-------|---------------|--------|--------|--------------|--------------|
| Deck Capacity | 1 / 13 | Deck (4) | Capacity (8) | 5 | `0x680` |
| Duelist Level | 6 / 2 | Duelist (7) | Level (5) | 8 | `0x400` |
| Life Points | 6 / 13 | Life (4) | Points (6) | 5 | `0x900` |

Strings must stay in sync with `word1Tiles`, `word2Tiles`, and `word2Index`. Example: `"Deck Capacity"` → indices 0–3 are **Deck**, index 4 is space, indices 5–12 are **Capacity**.

### Stat value layout

Edit the `STATUS_*_VALUE_ROW`, `STATUS_*_VALUE_COL`, and `STATUS_*_VALUE_DIGITS` `#define`s at the top of [`status_menu_hooks.c`](../src_custom/status_menu_hooks.c).

| Stat | Global | Default row / col | Digits |
|------|--------|-------------------|--------|
| Deck capacity | `gDeckCapacity` | 3 / 14 | 5 |
| Duelist level | `gDuelistLevel` | 8 / 3 | 4 |
| Life points | `gLifePointsOutsideDuel` | 8 / 14 | 5 |
| Money | `gMoney` | 17 / 8 | 13 |

LynJump also replaces the four vanilla stat writers (`sub_80079C4`, `sub_8007AB8`, `sub_8007BB0`, `sub_8007CA0`) so values refresh if the vanilla helpers are called again.

### Millennium item progress tracker

Seven **32×32** indexed PNGs in [`src_custom/assets/millenium_items/`](../src_custom/assets/millenium_items/) feed the clear gap between the stats panel and the money bar. Build embeds them via `tools/generate_millennium_item_assets.py` into [`src_custom/generated/millennium_item_assets_generated.inc`](../src_custom/generated/millennium_item_assets_generated.inc).

Icons sit on **row 10**, spaced four tiles apart (no extra middle dim panel — the hieroglyph gap stays visible). That gap is **outside** the status blend windows (`WINOUT` is normally BG3-only), so the VBlank hook re-enables **BG2** there or the icons would stay invisible despite being in the BG2 tilemap.

- Icon tile bases: color `0xA0`, silhouette `0x110` (must stay below tile `0x180` — that offset is the BG3 tilemap `sbb1E` inside charblock 3).
- **Uncollected:** black silhouette tiles (palette bank 14: transparent + black).
- **Collected:** full-color tiles (palette bank 13).

With `gRuntimeConfig.show_all_millennium_items` (debug label **All Millen**), every icon renders collected regardless of flags.

Progress flags in `sMillenniumItems[]`:

| Index | Item | Collected when |
|-------|------|----------------|
| 0 | Puzzle | Not defeated Bandit Keith, or finished game |
| 1 | Ring | Defeated Millennium Guardian 3 |
| 2 | Key | Defeated Millennium Guardian 2 |
| 3 | Scale | Defeated Mimic of Doom |
| 4 | Rod | Defeated Millennium Guardian 5 |
| 5 | Eye | Defeated Millennium Guardian 4 |
| 6 | Necklace | Defeated Millennium Guardian 1 |

To re-export from overworld OBJ sprites:

```bash
python3 tools/export_millennium_item_pngs.py
make all
```

| File | Item |
|------|------|
| `puzzle.png` | Millennium Puzzle |
| `ring.png` | Millennium Ring |
| `key.png` | Millennium Key |
| `scale.png` | Millennium Scale |
| `rod.png` | Millennium Rod |
| `eye.png` | Millennium Eye |
| `necklace.png` | Millennium Necklace |

### Palette and text color

- Full status BG palette: 512 halfwords from `gUnk_8088288`.
- Label text white: bank 15 restored from `gUnk_8079424` at `gPaletteBuffer[0xF0]`.
- Label map entries use palette nibble `0xF000` (`STATUS_LABEL_PALETTE`).

## Editing the Layout

1. Open [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c).
2. For **split labels**, edit the matching row in `sSplitLabels[]` and, if needed, the corresponding `sStatus*Label[]` string and `CopyStringTilesToVRAMBuffer` call in `PlaceStatusMenuLabelGfx`.
3. For **Name** or **Money**, edit the `#define STATUS_*_LABEL_*` block.
4. For **stat numbers**, edit the `STATUS_*_VALUE_*` `#define`s.
5. Rebuild with `make all` and open Status from the field start menu.

**Tips**

- If a moved label leaves ghost text, increase `vanillaTiles` or check that `vanillaRow` / `vanillaCol` match the baserom slot (see `data/data.s` → `gUnk_8088778`).
- Split labels clear the row below the top word before writing; do not place unrelated tiles on `row + 1` under a split label.
- Player name rows use **fixed** asm map indices (`0x7C22`, `0x7C42`, …); only `STATUS_PLAYER_NAME_LINE*_CHARS` are safe to tune without re-deriving indices from `asm/status_menu.s`.
- Accent tiles and the money suffix use **flat** tilemap offsets (`0x7C00 + …`), not `row * 32 + col`. Keep using `StatusMenuWriteMapIndex`.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Layout constants | Top of [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | `#define`s for labels, values, player name char counts |
| Split-label table | `sSplitLabels[]` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Two-line label positions and vanilla clear metadata |
| Label strings | `sStatusDeckCapacityLabel`, etc. in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | `APPEND_RODATA` gfx source strings |
| Main entry | `StatusMenu__Replacement` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Full screen setup, stat draw, input loop |
| Label map patch | `PlaceStatusMenuLabels` / `StatusMenuPlaceSplitLabel` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Writes BG tilemap label entries |
| Label gfx | `PlaceStatusMenuLabelGfx` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Palettes and small/tall font tile uploads |
| Stat digits | `StatusMenuDrawU32Value`, `StatusMenuDrawMoneyValue` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Tall digit rendering via `g8DF811C` |
| Millennium tracker | `PlaceStatusMenuMillenniumTracker`, `sMillenniumItems[]` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Horizontal icon row + event-flag silhouettes / color icons |
| Icon PNG sources | [`src_custom/assets/millenium_items/`](../src_custom/assets/millenium_items/) | 32×32 indexed PNGs |
| Icon build | [`tools/generate_millennium_item_assets.py`](../tools/generate_millennium_item_assets.py) | PNG → `millennium_item_assets_generated.inc` |
| Icon export | [`tools/export_millennium_item_pngs.py`](../tools/export_millennium_item_pngs.py) | Overworld `.4bpp` → PNG (one-time / refresh) |
| Stat LynJumps | `sub_80079C4__Replacement` … `sub_8007CA0__Replacement` in [`src_custom/status_menu_hooks.c`](../src_custom/status_menu_hooks.c) | Per-stat redraw hooks |
| LynJump wiring | [`src_custom/LynJump.event`](../src_custom/LynJump.event) `@ $75DC`, `$79C4`, `$7AB8`, `$7BB0`, `$7CA0` | Redirects vanilla StatusMenu and stat helpers |
| Vanilla asm reference | [`asm/status_menu.s`](../asm/status_menu.s) | Original map-index loops and stat helpers |
| Baserom tilemap | `gUnk_8088778` in [`data/data.s`](../data/data.s) | Baked BG map copied before C overrides |
| Baserom palettes / strings | `gUnk_8088288`, `gUnk_8088C58`, … in [`data/data.s`](../data/data.s) | Assets still loaded by the hook |
| Vanilla C (unchanged) | [`src/status_menu.c`](../src/status_menu.c) | Passthrough; not edited for layout work |

## TODO

- Add a screenshot or annotated map row/col diagram for the default layout.
- Consider moving layout `#define`s into a small header if the hook file grows again.

## Limitations & Bugs

- Background panel art still comes from baserom `gUnk_8088778`; only labels, accents, name slots, and stat digits are repositioned in C.
- Split labels require manual sync between string text, `word1Tiles`, `word2Tiles`, and `word2Index`; there is no compile-time check.
- `sSplitLabels[]` and custom label strings must live in `APPEND_RODATA`; a plain `.rodata` table will fail link with “discarded section `.rodata`”.
- Name label `TILE_BASE` (`0x031`) does not follow `charOffset / 32`; keep baserom-aligned values unless gfx loading changes.
- Money drawing keeps a vanilla quirk: the last digit’s bottom tile may write through `STATUS_MONEY_LAST_DIGIT_BOTTOM_OFFSET` when trailing zeros collapse.
- Long single-line labels can clip or overlap panel edges; prefer the split-label table for two-word titles.
- Layout is compile-time only; there is no in-game editor or `gRuntimeConfig` toggle.
