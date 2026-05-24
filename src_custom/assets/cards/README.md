# Custom Card Assets

Put assets for cards with IDs `>= CUSTOM_CARD_START` here.

Expected files per card:

- `*_big_art.bin`
  - big card artwork in the same encoded format used by `gCardArts[]`
- `*.gbapal`
  - big card palette
- `*_mini.8bpp`
  - intermediate 8bpp mini-card tile data produced before compression
- `*_mini.lz`
  - LZ77-compressed mini-card tile data
- `mini.pal`
  - shared mini-card palette source used when quantizing 24x24 mini-card PNGs

Wire them in `src_custom/card_asset_hooks.c`.

Use `tools/add_card_art.py` to generate the `INCBIN` declarations from matching
files in `80x80` and `24x24`.

If a custom card has an `80x80/*.png` but no `24x24/*.lz`, the script will
derive the mini card automatically by resizing the 80x80 source to 24x24,
choosing the 16 closest colors from `mini.pal` relative to the 80x80 palette,
and exporting the `.png`, `.8bpp`, and `.lz` files.

To regenerate only mini assets, run:

`python3 tools/add_card_art.py --generate-minis`
