# Adding Custom Cards

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Big card art](#big-card-art)
- [Mini card art](#mini-card-art)
- [Manifest and build](#manifest-and-build)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Custom cards are defined in `tools/card_data_manifest.json` and backed by art under `src_custom/assets/cards/`. Card IDs and generated lookup tables come from the manifest order; anything after `SORCERER_OF_DARK_MAGIC` in the manifest is treated as a custom card.

A new card needs at least:

1. An **80×80** indexed PNG for trunk/card-detail **big** art (this doc).
2. A manifest entry with stats, name, password, and effects.
3. A successful `make` run to regenerate `.huff`, `.gbapal`, generated includes, and automatic 24x24 mini card art.

See also [custom-card-memory.md](custom-card-memory.md) for save/RAM growth, [card-descriptions.md](card-descriptions.md) for description text, and [big-card-art-palette-extension.md](big-card-art-palette-extension.md) if the PNG uses more than 64 palette colors.

## Plan

| Step | What you do | What the build does |
|------|-------------|---------------------|
| Author big art | Save an indexed `80x80/<stem>.png` (see below) | `graphics.mk` runs `gbagfx` → `.8bpp`, `.gbapal`, `.huff` |
| Author mini art (optional) | Add `24x24/<stem>.png`, or omit and let the script derive it | LZ mini tiles from PNG or from big art |
| Manifest | Append a card object to `tools/card_data_manifest.json` | `tools/add_card_art.py` regenerates IDs, data, names, art includes |
| Verify | `make` | Links custom art into the ROM |

The `<stem>` must match the manifest `card_const` in lowercase with underscores (for example `ANCIENT_RULES` → `ancient_rules.png`).

## Big card art

Big art is the artwork shown on the **card detail** screen and drives the palette used for that card. The game expects **80×80** pixels at runtime; contributors prepare a high-resolution source, downscale it, then export a **64-color indexed PNG** so in-game colors stay close to the source.

### 1. Source image

| Requirement | Value |
|-------------|-------|
| Preferred source size | **512×512** PNG |
| Recommended source | [Yugipedia](https://yugipedia.com) **Master Duel** card scans/art for the card you are adding |
| Format | PNG (truecolor is fine before the export step below) |

Use the highest-quality Master Duel asset available on Yugipedia so fine detail survives the downscale.

### 2. Downscale to 80×80

In an image editor (Photoshop, GIMP, etc.):

| Setting | Value |
|---------|-------|
| Output size | **80×80** pixels |
| Resolution | **72 DPI** (document resolution; pixel dimensions matter for the game) |
| Resampling / interpolation | **Bilinear** |

Do not use nearest-neighbor for this step; bilinear keeps gradients smoother before the 64-color quantize.

### 3. Export indexed PNG (Photoshop)

In **Photoshop**, use **File → Export → Save for Web** (legacy name: *Save for Web*):

| Setting | Value |
|---------|-------|
| File format | PNG-8 (indexed) |
| Colors | **64** (maximum) |
| Color reduction / adaptation | **Selective** |

**Selective** adaptation keeps the exported palette as close as possible to the downscaled truecolor image, which matters because the build copies palette indices from this PNG into the in-game card detail view.

Save the file as:

```text
src_custom/assets/cards/80x80/<stem>.png
```

Example: `ANCIENT_RULES` → `src_custom/assets/cards/80x80/ancient_rules.png`.

Other editors can produce equivalent indexed PNGs if they honor the same **80×80**, **≤64 colors**, and a selective/perceptual quantize; the project workflow above is what contributors have validated against in-game.

### 4. Build conversion

You only commit the **PNG**. On `make`, `graphics.mk` generates sibling files from it:

| Generated file | Role |
|----------------|------|
| `<stem>.gbapal` | Big card palette embedded in the ROM |
| `<stem>.8bpp` | Uncompressed 8bpp tiles |
| `<stem>.huff` | Huff-compressed big art (`big_art` in the manifest) |

Do not hand-edit `.huff` / `.gbapal` unless you know you are bypassing the normal pipeline.

### 5. More than 64 colors

If the indexed PNG uses **more than 64** non-transparent palette indices, the build enables the extended card-detail palette path (up to **112** colors). That requires a matching 112-entry `.gbapal` and runtime config; see [big-card-art-palette-extension.md](big-card-art-palette-extension.md). For most cards, staying at **64 colors** in Save for Web keeps behavior aligned with vanilla.

## Mini card art

Trunk and shop lists use **24×24** mini art.

| Approach | Path |
|----------|------|
| Manual | Add `src_custom/assets/cards/24x24/<stem>.png` (16-color indexed; see `mini.pal` in the cards asset folder) |
| Automatic | Omit the mini PNG; `python3 tools/add_card_art.py` can derive mini tiles from the 80×80 PNG and palette |

Regenerate only minis:

```bash
python3 tools/add_card_art.py --generate-minis
```

## Manifest and build

1. Append a card entry to `tools/card_data_manifest.json` after the last custom card (or in the custom section). Required fields include `card_const`, `card_name`, combat stats, `password`, and effect IDs.
2. Optional overrides: `big_art`, `big_palette`, `mini_art` (defaults are `src_custom/assets/cards/80x80/<stem>.huff`, `.gbapal`, and `24x24/<stem>.lz`).
3. Run `make`. This runs `tools/add_card_art.py` and rebuilds generated includes under `src_custom/generated/`.

After adding many custom cards, run `make memory-report` if you need updated save/RAM sizes (see [custom-card-memory.md](custom-card-memory.md)).

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Authoring PNG drop folder | `src_custom/assets/cards/80x80/` | Commit `<stem>.png` here |
| PNG → ROM gfx rules | `graphics.mk` | `gbagfx` rules for `.8bpp`, `.gbapal`, `.huff` |
| Manifest source | `tools/card_data_manifest.json` | Card order, stats, optional asset paths |
| Art / data generator | `tools/add_card_art.py` | Regenerates IDs, `card_art_generated.inc`, mini derivation |
| Generated art tables | `src_custom/generated/card_art_generated.inc` | `INCBIN` big art and palette pointers |
| Asset folder readme | `src_custom/assets/cards/README.md` | Short pointer to this doc |
| Extended palette behavior | `documentation/big-card-art-palette-extension.md` | >64-color big art on card detail |

## TODO

- Document a validated GIMP/Krita Save-for-Web equivalent to the Photoshop 64-color / Selective steps.
- Add a manifest JSON schema snippet for a minimal new custom card entry.

## Limitations & Bugs

- **Manifest order is the card ID.** Reordering or removing entries shifts IDs and breaks saves; treat that as a breaking change.
- **Filename stem must match `card_const`.** A mismatch leaves the card without hook art at runtime.
- **Save for Web settings matter.** Nearest-neighbor downscale or a loose quantize (for example Perceptual with too few colors) can look noticeably worse in the card detail view than Selective @ 64 colors.
- **Big art only applies to custom cards** wired through the manifest and generated hooks; vanilla ROM cards keep their original art paths.
