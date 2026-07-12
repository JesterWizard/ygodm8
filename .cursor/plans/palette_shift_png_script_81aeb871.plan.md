---
name: Palette Shift PNG Script
overview: "Create `tools/palette_shift.py` — a script that accepts a folder path, finds all PNGs (non-recursive), and for each palette-based PNG shifts all palette colors down by one index, setting index 0 to #00ff00."
todos:
  - id: create-script
    content: Create tools/palette_shift.py with the palette shift logic
    status: completed
  - id: validate
    content: Run make test or equivalent to validate the script doesn't break anything
    status: completed
isProject: false
---

## Script: `tools/palette_shift.py`

### Behaviour

1. Accept a single positional argument: a folder path.
2. Scan for `*.png` files directly inside that folder (non-recursive, using `pathlib.Path.glob("*.png")`).
3. For each PNG that has a palette (`image.mode == "P"`):
   - Read the palette (list of RGB bytes, 3 per entry).
   - Build a new palette: `new[0] = (0, 255, 0)`, then `new[i] = old[i-1]` for i = 1..N-1. The old last entry (N-1) is discarded.
   - Remap pixel data: every pixel value `v` becomes `v + 1` (old index 0 → new index 1, etc.). Old index N-1 has no replacement — the script will handle this by clamping (pixels at N-1 stay at N-1, or warn).
   - Handle PNG transparency info (`image.info.get("transparency")`): if the old index 0 was transparent, carry the transparency value to new index 1. Set new index 0 as opaque (no transparency).
   - Write the modified palette and pixels back, save with `PNG` format.
4. For non-palette PNGs (RGB/RGBA): skip with a printed note.
5. Print a summary per file (e.g. `path/to/file.png: shifted N colors, remapped M pixels`).

### Edge cases handled

- **File count = 0** — prints "No PNGs found in ..." rather than crashing.
- **Invalid path** — prints an error and exits with code 1.
- **Palette size** — works with any palette size (16, 64, 256 entries).
- **Non-palette PNGs** — skipped gracefully with a message.
- **tRNS chunk** — preserved for the shifted transparency index, cleared for the new index 0.

### Code conventions

- Matches existing tools (`normalize_big_card_png.py`, `normalize_portrait_png.py`): `#!/usr/bin/env python3`, `from __future__ import annotations`, `argparse`, `pathlib`, `if __name__ == "__main__": raise SystemExit(main())`.
- Single-file, no new dependencies — uses only `argparse`, `pathlib`, `sys`, and `PIL` (Pillow, already a project dependency).
- `ponytail:` marker on the discarded-last-index caveat with the upgrade path (extend palette or error).

### Usage

```bash
python tools/palette_shift.py path/to/png_folder
```

### Files touched

- `tools/palette_shift.py` — new file (only creation).
