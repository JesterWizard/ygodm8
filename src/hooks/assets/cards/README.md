# Custom Card Assets

Put assets for cards with IDs `>= CUSTOM_CARD_START` here.

Expected files per card:

- `*_big_art.bin`
  - big card artwork in the same encoded format used by `gCardArts[]`
- `*.gbapal`
  - big card palette
- `*_mini.lz`
  - LZ77-compressed mini-card tile data

Wire them in `src/hooks/card_asset_hooks.c`.
