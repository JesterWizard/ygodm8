# Custom Card Assets

Put assets for cards with IDs `>= CUSTOM_CARD_START` here.

**Full workflow (big art, manifest, build):** [documentation/adding-custom-cards.md](../../../documentation/adding-custom-cards.md)

**Progress tracker:** [CARD_PROGRESS.md](CARD_PROGRESS.md) — which cards are in the manifest vs art-only. Refresh with `python3 tools/card_art_progress.py`.

## Big art (`512x512/` → `80x80/`)

Preferred: drop Master Duel source art here:

```text
src_custom/assets/cards/512x512/<stem>.png
```

`<stem>` is the manifest `card_const` in lowercase with underscores (for example `ancient_rules.png` for `ANCIENT_RULES`).

On `make`, `tools/batch_80x80.py` writes any missing `80x80/<stem>.png` (bilinear, selective 64-color). Existing `80x80/` files are not overwritten. You can also commit a hand-authored `80x80/<stem>.png` directly.

Then `tools/add_card_art.py` converts each `80x80/` PNG into `build/cards/80x80/*.gbapal` and `<stem>.huff` (`.8bpp` stays in temp files only).

## Mini art (`24x24/`)

Optional source PNGs for hand-authored minis:

```text
src_custom/assets/cards/24x24/<stem>.png
```

`mini.pal` in this folder is the shared palette used when quantizing auto-derived 24×24 tiles.

On `make`, `tools/add_card_art.py` writes `build/cards/24x24/<stem>.lz` for every custom card. If no `24x24/<stem>.png` exists, the mini is derived from the `80x80/<stem>.png` (resize to 24×24, map to `mini.pal`). Intermediate `.8bpp` files are never written into this repo tree.

Regenerate only minis:

```bash
python3 tools/add_card_art.py --generate-minis
```

## Legacy / generated binaries

Older notes referred to hand-placed `*_big_art.bin` files. The current pipeline uses PNG sources plus `gbagfx` output; wire paths through `tools/card_data_manifest.json` (`big_art`, `big_palette`, `mini_art`) and regenerate with `tools/add_card_art.py` on `make`.
