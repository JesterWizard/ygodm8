# Custom Card Assets

Put assets for cards with IDs `>= CUSTOM_CARD_START` here.

Expected files per card:

- `*_big_art.bin`
  - big card artwork in the same encoded format used by `gCardArts[]`
- `*.gbapal`
  - big card palette
- `*_mini.4bpp`
  - intermediate 4bpp mini-card tile data produced before compression
- `*_mini.lz`
  - LZ77-compressed mini-card tile data

Wire them in `src_custom/card_asset_hooks.c`.

Use `tools/add_card_art.py` to generate the `INCBIN` declarations from matching
files in `80x80` and `24x24`.

If a custom card has an `80x80/*.png` and `.gbapal` but no `24x24/*.lz`, the
script will derive the mini card automatically by resizing the 80x80 source to
24x24, quantizing it to the card palette, and exporting the `.png`, `.4bpp`,
and `.lz` files.

To regenerate only mini assets, run:

`python3 tools/add_card_art.py --generate-minis`
