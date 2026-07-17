# Card Description Fonts

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Card detail descriptions were locked to the vanilla fixed **8×16** typeface (5 rows × 12/14 columns). Longer effect text needed many pages, and the authored layout pads the first/last rows with leading spaces so glyphs sit inside the blue panel inset.

This feature lets you pick the description typeface at runtime via `RuntimeConfig.card_description_font` (`CARD_DESC_FONT_*` in [`include/constants/card_description_font.h`](../include/constants/card_description_font.h)). Non-vanilla modes recover prose from the large-layout pages, strip inset padding, and reflow for denser reading.

## Plan

### Font modes

| Value | Name | Renderer | Layout |
|------:|------|----------|--------|
| `0` | `CARD_DESC_FONT_VANILLA` | `CopyStringTilesToVRAMBuffer` flag `0x901` | 5 rows × 14 cols (2 tiles tall); authored `^` pages as-is |
| `1` | `CARD_DESC_FONT_SMALL` | Flag `0x001` | 10 rows × 14 cols (1 tile tall); char-wrap reflow |
| `2` | `CARD_DESC_FONT_EMERALD_NARROW` | Emerald `small_narrow` VWF | 5 rows × 16px into the same 140-tile VRAM slot; pixel-wrap, flush-left |

Default in [`configs/runtime.c`](../configs/runtime.c): `CARD_DESC_FONT_EMERALD_NARROW`.

### Switching at runtime

1. Open the debug menu → **Runtime**.
2. Find **Desc Font**.
3. Press **A** to cycle: `Van` → `Sml` → `Emr`.
4. Re-open card detail to see the new font (the detail view reads the config when built).

Build-time default: set `.card_description_font = CARD_DESC_FONT_…` in `gRuntimeConfigRom`.

### Emerald path (flush-left)

1. `RecoverProseFromLargePages` joins authored rows and **drops leading/trailing spaces** on each large-layout row (removes the vanilla inset padding baked into descriptions).
2. `NarrowFontWrapProse` word-wraps by glyph pixel widths into 5 lines × **112px**. Row 0 (continuation pages) and the last row reserve arrow width + 1px so words that would collide with ▲/▼ move to the next line instead.
3. `NarrowFontRenderPage` blits 4bpp glyphs into tiles `148..287`; `NarrowFontApplyDescriptionTilemap` maps screen rows `10..19`.

Glyph source: pret pokeemerald `latin_small_narrow.png`, converted by [`tools/build_narrow_font.py`](../tools/build_narrow_font.py) → [`src_custom/generated/narrow_font_data.inc`](../src_custom/generated/narrow_font_data.inc).

### Adding another font later

1. Add a `CARD_DESC_FONT_*` value and bump `CARD_DESC_FONT_COUNT`.
2. Branch in `DescriptionFontMode` consumers inside [`src_custom/code_801EF30_hooks.c`](../src_custom/code_801EF30_hooks.c).
3. Add a 3-char label in `sDescFontLabels` in the debug runtime config viewer.
4. Document the mode in the table above.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Mode definitions | `CARD_DESC_FONT_*` in [`include/constants/card_description_font.h`](../include/constants/card_description_font.h) | Enum values for `RuntimeConfig.card_description_font` |
| Default | `gRuntimeConfigRom` in [`configs/runtime.c`](../configs/runtime.c) | Build-time default mode |
| Debug cycle | `DebugRuntimeConfigViewer` in [`src_custom/debug/debug_menu_runtime_config.c`](../src_custom/debug/debug_menu_runtime_config.c) | `Desc Font` / `Van`·`Sml`·`Emr` |
| Detail dispatch | `ShowCardDetailView__Replacement` / `CardDetailViewBuildDescription` in [`src_custom/code_801EF30_hooks.c`](../src_custom/code_801EF30_hooks.c) | Chooses vanilla / small / emerald path |
| Emerald VWF | `NarrowFont*` in [`src_custom/narrow_font.c`](../src_custom/narrow_font.c) | Wrap, blit, tilemap |
| Font asset build | [`tools/build_narrow_font.py`](../tools/build_narrow_font.py) | PNG → `narrow_font_data.inc` |
| Reflow scratch | `gDescProseBuf` / `gDescReflowBuf` in [`asm/ram_map_ewram.s`](../asm/ram_map_ewram.s) | EWRAM buffers for recovered prose |

## TODO

- Optional second Emerald face (`latin_narrow` 16px ink denser than `small_narrow`).
- Host golden that asserts flush-left wrap for a fixture description under `CARD_DESC_FONT_EMERALD_NARROW`.

## Limitations & Bugs

- Emerald maps ASCII 32–126 only; other bytes render as `?`.
- Vanilla mode still shows authored leading spaces on inset rows — that is intentional for the original panel layout.
- Changing **Desc Font** mid-detail does not refresh until you leave and re-open the card.
- Report palette contrast issues on custom card frames if Emerald fg/shadow indices clash with bank 15.
