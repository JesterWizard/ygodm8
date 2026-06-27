# Making a field spell PNG

See the full Implementation Guide at [`documentation/custom-field-spells.md`](/documentation/custom-field-spells.md#graphics-spec).

## Quick spec

| Requirement | Value |
|-------------|-------|
| Source PNG path | `src_custom/assets/field_spells/<stem>/<stem>.png` (preferred) or `<stem>.png` |
| Dimensions | **248 × 304 px** |
| Color mode | **Indexed PNG** (mode `P`) |
| Max colors | **48** |
| Tile budget | ≤ **1024** unique 8×8 tiles (~32 KB) |

`<stem>` is the manifest `card_const` in lowercase with underscores, e.g. `SEAL_OF_ORICHALCOS` → `seal_of_orichalcos`.

## Palette banks

The 48 colors are split into three hardware palette banks (0, 1, 2), 16 colors each. Each 8×8 tile picks one bank — pixels are remapped to the nearest color in that bank at build time. Group related colors in contiguous 16-color blocks for best results.

## Build pipeline

Place the PNG and `make` does the rest:

```
<stem>.png  →  .4bpp  →  .huff  (compressed tiles)
            →  .gbapal          (palette)
            →  .tilemap.c/.bin  (tile index map)
```

Generated files land in `<stem>/` and are gitignored. They are cached under `.cache/field_spells/` so rebuilding is fast.
