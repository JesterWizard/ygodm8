# Custom Card Assets

Put assets for cards with IDs `>= CUSTOM_CARD_START` here.

**Full workflow (big art, manifest, build):** [documentation/adding-custom-cards.md](../../../documentation/adding-custom-cards.md)

## Big art (`80x80/`)

Commit one indexed PNG per card:

```text
src_custom/assets/cards/80x80/<stem>.png
```

`<stem>` is the manifest `card_const` in lowercase with underscores (for example `ancient_rules.png` for `ANCIENT_RULES`).

Authoring summary:

1. Start from a **512×512** PNG (prefer [Yugipedia](https://yugipedia.com) **Master Duel** art).
2. Resize to **80×80** at **72 DPI** with a **bilinear** filter.
3. In Photoshop **Save for Web**: **64** colors max, color adaptation **Selective**.
4. Save into this folder.

`make` generates `<stem>.gbapal`, `<stem>.8bpp`, and `<stem>.huff` from the PNG via `graphics.mk`.

## Mini art (`24x24/`)

- `*_mini.lz` — LZ77-compressed mini-card tiles for trunk/shop lists
- `mini.pal` — shared palette used when quantizing 24×24 mini PNGs

If a custom card has an `80x80/*.png` but no `24x24/*.lz`, run:

```bash
python3 tools/add_card_art.py --generate-minis
```

That derives the mini from the 80×80 source (resize to 24×24, map to `mini.pal`).

## Legacy / generated binaries

Older notes referred to hand-placed `*_big_art.bin` files. The current pipeline uses PNG sources plus `gbagfx` output; wire paths through `tools/card_data_manifest.json` (`big_art`, `big_palette`, `mini_art`) and regenerate with `tools/add_card_art.py` on `make`.
