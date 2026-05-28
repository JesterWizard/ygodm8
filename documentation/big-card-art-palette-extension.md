# Big Card Art Palette Extension

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Authoring Assets](#authoring-assets)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Vanilla big card art on the card detail screen uses **64 colors** (BG palette banks **0–3**) for the artwork. The card frame tint (**BG4**, historically palette bank **4**) and UI text/icons (banks **8–F**) share the same 256-color BG palette RAM. Custom high-color art often needs more than 64 indices; without rearranging banks, extra art colors collide with the card-color bank or with unused foreground banks (**7**, **C**, **D**) that the tilemap still references.

This feature adds a runtime toggle that allows custom cards with **more than 64 colors in their 80×80 art** to use **seven contiguous BG palette banks (0–6)** (**112 colors**), moves the card-color palette to **bank 7**, and keeps UI palettes in **banks 8–F**. Custom cards that only use 64 colors or fewer keep the vanilla bank layout even when the toggle is on.

The change applies only while the **card detail view** is open (trunk/deck “Details”, shiny-zone reward popup, password terminal preview, etc.).

The feature is controlled by `gRuntimeConfig.enable_big_card_art_palette_extension` in `configs/runtime.c`. Per-card extended layout is decided at build time from the source PNG and exposed as `gCardArtUsesExtendedPalette_Hook[]`.

## Plan

### Palette bank layout (toggle ON, card uses >64 art colors)

| BG bank | Role | Source when extension is enabled |
|--------|------|----------------------------------|
| `0`–`6` | Big card art (112 colors) | Card `.gbapal` copied into `gUnk_8E01368` banks 0–6, then into `gPaletteBuffer` via `sub_800B618` |
| `7` | Card color (former BG4) | `gUnk_8E137C4[gCardInfo.color]` via `sub_80267E0` → `gUnk_8E01368 + 0x40`, then copied to `gPaletteBuffer + 7 * 16` after detail setup |
| `8`–`B` | Text / primary UI | `g08097C94` → `gPaletteBuffer[8 * 16]` (unchanged vanilla path in `sub_800B618`) |
| `C`–`D` | Other UI / background | Same `g08097C94` block (unchanged) |
| `E`–`F` | Reserved / vanilla-safe | Not remapped by this feature |

### Palette bank layout (toggle OFF)

Behavior matches vanilla: `PrintCard` fills `gUnk_8E01368` with the standard 64-color art palette plus card color at offset `0x40` (bank 4), and `sub_800B618` copies all 256 halfwords into `gPaletteBuffer` without bank remapping.

### Runtime flow (toggle ON, extended card)

| Stage | Location | Result |
|--------|----------|--------|
| Build-time detection | `count_colors_used_in_big_art` in `tools/add_card_art.py` | Counts distinct non-transparent palette indices in `80x80/<card>.png`; sets `gCardArtUsesExtendedPalette_Hook[id]` when count > 64 |
| Build card gfx | `PrintCard` → `CopyCardArtDataToBuffers__Replacement` | Loads art tiles; copies **224 bytes** (112 colors) only when `CardUsesExtendedBigCardPalette` is true; otherwise **128 bytes** |
| Assemble detail screen | `sub_800B618` | Loads tilemaps/tileset, UI palettes at bank 8+, runs `PrintCard`, copies `gUnk_8E01368` → `gPaletteBuffer` |
| Post-process palettes | `ShowCardDetailView__Replacement` | When `CardUsesExtendedBigCardPalette(gCardInfo.id)`, copies card color from bank **4** → bank **7** in `gPaletteBuffer`; rewrites tilemap palette nibbles **4 → 7** on BG layers `sbb1F`, `sbb1E`, `sbb1D` |
| Display | VBlank `LoadPalettes` | Uploads `gPaletteBuffer` to PLTT |

### Scope

| Screen | Affected when toggle ON? |
|--------|---------------------------|
| Card detail view (`ShowCardDetailView`) | Yes |
| Duel attack zoom / big card overlay (`sub_800B288`) | No |
| Card shop preview | No |

## Authoring Assets

### Big palette file size

Per-card big palettes live at `src_custom/assets/cards/80x80/<card>.gbapal` (or paths listed in `tools/card_data_manifest.json` as `big_palette`). Author the source PNG first; see [adding-custom-cards.md](adding-custom-cards.md#big-card-art) for the 512→80 workflow and Photoshop export settings.

`tools/add_card_art.py` accepts:

| Colors | File size | Use |
|--------|-----------|-----|
| 64 | 128 bytes | Vanilla-compatible custom cards |
| 112 | 224 bytes | Extended art for card detail view (banks 0–6) |

Any other size fails validation at manifest generation time.

### Art tile palette indices

8bpp big art must use palette indices that map to the banks above:

- Art pixels should use indices **0–111** (banks **0–6**).
- Do not rely on bank **4** for art when the extension is enabled; that bank is repurposed for card color at display time (bank **7** on screen).
- If art was authored against old “spare” foreground banks (**7**, **C**, **D**), re-index tiles to **0–6** (or adjust the tilemap) before shipping.

Regenerate bindings after adding or resizing palettes:

```bash
python3 tools/add_card_art.py
make
```

### Runtime toggle

In `configs/runtime.c`:

```c
.enable_big_card_art_palette_extension = TRUE,  /* or FALSE for vanilla layout */
```

Rebuild so `gRuntimeConfig` in ROM matches.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `enable_big_card_art_palette_extension` in `configs/runtime.h` and `configs/runtime.c` | Master switch for extended palette layout |
| Per-card extended flag | `gCardArtUsesExtendedPalette_Hook[]` in `src_custom/generated/card_art_generated.inc` | Build-time: 1 when source PNG uses >64 colors, else 0 |
| Extended palette gate | `CardUsesExtendedBigCardPalette` in `src_custom/card_asset_hooks.c` | Runtime: toggle ON, hook palette present, and per-card flag set |
| Extended palette copy | `CopyCardArtDataToBuffers__Replacement` in `src_custom/card_asset_hooks.c` | Copies 224 bytes only when `CardUsesExtendedBigCardPalette`; 128 bytes otherwise |
| Card color source | `sub_80267E0` in `src/print_card.c` | Still writes card color to `gUnk_8E01368 + 0x40` (logical bank 4 in the staging buffer) |
| Detail screen assembly | `sub_800B618` in `src/card.c` | Vanilla tilemap/tileset setup; copies UI palettes to bank 8+; calls `PrintCard`; uploads `gUnk_8E01368` to `gPaletteBuffer` |
| Bank remap + tilemap fixup | `ShowCardDetailView__Replacement` in `src_custom/code_801EF30_hooks.c` | After `sub_800B618`, moves card color to PLTT bank 7 and patches palette bank nibble 4 → 7 |
| Generated art symbols | `src_custom/generated/card_art_generated.inc` | `INCBIN` big art/palette pointers consumed by `gCardArtPalettes_Hook[]` |
| Palette validation | `validate_big_palette` in `tools/add_card_art.py` | Enforces 64- or 112-color `.gbapal` files during manifest discovery |
| Asset authoring | `documentation/adding-custom-cards.md` | 512→80 big art workflow and 64-color PNG export |
| Asset folder | `src_custom/assets/cards/README.md` | Paths and quick reference for `80x80/` and `24x24/` |

## TODO

- Remap big-art **tile** palette banks in source assets so foreground pieces that used banks **7**, **C**, or **D** are encoded as **0–6** (tooling or documented GIMP/Photoshop workflow).
- Optionally clear or repurpose staging bank **4** in `gPaletteBuffer` after the bank-7 copy to avoid duplicate card-color data.
- Document a reference 112-color `.gbapal` export settings (e.g. gbagfx / Aseprite / GIMP indexed steps).
- Evaluate whether vanilla cards with ROM 64-color palettes benefit from a shared “extension” palette stub when the toggle is ON.

## Limitations & Bugs

- **Card detail only.** Duel big-card popups and other `PrintCard` callers keep the vanilla 64-color + bank-4 layout.
- **Vanilla ROM palettes stay 64 colors.** Extended copy runs only when the toggle is ON, the card has hook art, **and** the source PNG used more than 64 palette indices (excluding index 0).
- **64-color custom cards are unchanged** when the toggle is ON; they keep the vanilla bank layout and 128-byte palette copy.
- **Bank 4 may still exist in `gPaletteBuffer` after remap.** Tilemaps are patched to read bank **7**; bank **4** contents are duplicated, not cleared.
- **Attribute/type icon palettes** in `gUnk_8E01368` (offsets `0x56`, `0x5D`, etc.) are unchanged; they must not overlap banks **0–6** used by extended art.
- **112-color art without tile re-indexing** can still look wrong if tiles reference indices above 111 or old bank nibbles in the uncompressed art stream.
- Toggle **OFF** must preserve prior behavior for regression testing; compare against a build with `.enable_big_card_art_palette_extension = FALSE`.
