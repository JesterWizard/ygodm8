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

1. Big art: a **512×512** source PNG (preferred) or an **80×80** indexed PNG (this doc).
2. A manifest entry with stats, name, password, and effects.
3. A successful `make` run to build ROM assets under `build/cards/`, regenerate includes, and automatic 24x24 mini card art.

See also [custom-card-memory.md](custom-card-memory.md) for save/RAM growth, [card-descriptions.md](card-descriptions.md) for description text, and [big-card-art-palette-extension.md](big-card-art-palette-extension.md) if the PNG uses more than 64 palette colors.

## Plan

| Step | What you do | What the build does |
|------|-------------|---------------------|
| Author big art | Drop a `512x512/<stem>.png` (preferred), or an indexed `80x80/<stem>.png` | `batch_80x80.py` fills missing `80x80/`; `add_card_art.py` runs `gbagfx` → `build/cards/80x80/*.gbapal` and `*.huff` |
| Author mini art (optional) | Add `24x24/<stem>.png`, or omit and let the script derive it | `add_card_art.py` → `build/cards/24x24/<stem>.lz` |
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

**Preferred:** save the source as:

```text
src_custom/assets/cards/512x512/<stem>.png
```

On `make`, `tools/batch_80x80.py` writes any missing `80x80/<stem>.png` (bilinear resize, selective 64-color palette). Existing `80x80/` files are left alone.

**Manual override:** author `80x80/<stem>.png` yourself (Photoshop Save for Web: PNG-8, **64** colors, **Selective**; bilinear downscale to 80×80). Hand-authored files are not overwritten by the batch step.

Example: `ANCIENT_RULES` → `512x512/ancient_rules.png` (or `80x80/ancient_rules.png`).

### 3. Build conversion

You only commit the **PNG**. On `make`, `tools/add_card_art.py` converts each `80x80/<stem>.png` straight into ROM-ready assets under `build/cards/80x80/` (intermediate `.8bpp` tiles are kept in temp files only):

| Generated file | Role |
|----------------|------|
| `build/cards/80x80/<stem>.gbapal` | Big card palette embedded in the ROM |
| `build/cards/80x80/<stem>.huff` | Huff-compressed big art (`big_art` in the manifest) |

Do not hand-edit generated binaries unless you know you are bypassing the normal pipeline.

### 4. More than 64 colors

If the indexed PNG uses **more than 64** non-transparent palette indices, the build enables the extended card-detail palette path (up to **112** colors). That requires a matching 112-entry `.gbapal` and runtime config; see [big-card-art-palette-extension.md](big-card-art-palette-extension.md). For most cards, staying at **64 colors** in Save for Web keeps behavior aligned with vanilla.

## Mini card art

Trunk and shop lists use **24×24** mini art. On `make`, `tools/add_card_art.py` writes ROM-ready `build/cards/24x24/<stem>.lz` files (intermediate `.8bpp` tiles stay in temp files only).

| Approach | Source | Build output |
|----------|--------|--------------|
| Manual | Add `src_custom/assets/cards/24x24/<stem>.png` (16-color indexed; see `mini.pal` in the cards asset folder) | `build/cards/24x24/<stem>.lz` |
| Automatic | Omit the mini PNG; the script derives tiles from the `80x80/<stem>.png` and palette | `build/cards/24x24/<stem>.lz` |

Regenerate only minis:

```bash
python3 tools/add_card_art.py --generate-minis
```

## Manifest and build

1. Append a card entry to `tools/card_data_manifest.json` after the last custom card (or in the custom section). Required fields include `card_const`, `card_name`, combat stats, `password`, and effect IDs.
2. Optional overrides: `big_art`, `big_palette`, `mini_art` (defaults are `build/cards/80x80/<stem>.huff`, `.gbapal`, and `build/cards/24x24/<stem>.lz`).
3. Run `make`. This runs `tools/batch_80x80.py` (missing `80x80/` only), then `tools/add_card_art.py`, and rebuilds generated includes under `src_custom/generated/`.

After adding many custom cards, run `make memory-report` if you need updated save/RAM sizes (see [custom-card-memory.md](custom-card-memory.md)).

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| High-res source drop folder | `src_custom/assets/cards/512x512/` | Commit `<stem>.png` here; `make` fills missing `80x80/` |
| Authoring PNG drop folder | `src_custom/assets/cards/80x80/` | Commit `<stem>.png` here, or let `batch_80x80.py` generate it |
| 512 → 80 downscale | `tools/batch_80x80.py` | Missing `80x80/<stem>.png` only (skips existing) |
| PNG → ROM gfx | `tools/add_card_art.py` | Builds `build/cards/80x80/*.gbapal` and `*.huff`, plus `build/cards/24x24/*.lz` (`.8bpp` in temp only) |
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
