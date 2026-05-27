# Custom Portraits

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Dialogue portraits are 64x64 OBJ graphics shown by the event command:

```c
PORTRAIT(portrait_id, expression, position)
```

Custom portraits let event scripts show new face art without editing vanilla portrait data. The current implementation adds `PORTRAIT_PLAYER` and routes it through `DisplayPortrait__Replacement`.

Use a 64x64 indexed PNG with no more than 64 colors. Do not use 128x64 art for dialogue portraits; that size has the same byte count as a 64x64 8bpp image when encoded as 4bpp, but the engine reads portraits as 8bpp OBJ data.

## Plan

The feature has three parts:

1. asset conversion
2. portrait id registration
3. event script usage

### Asset Workflow

Portrait assets live under:

```text
src_custom/assets/portraits/
  player.png
```

The source PNG must be:

| Requirement | Value |
|--------|----------|
| Size | `64x64` |
| Mode | indexed PNG |
| Colors | `1..64` used palette entries |
| Tile format | generated `8bpp` |
| Runtime palette range | OBJ palette indices `0xC0..0xFF` |

During `make`, the player portrait currently builds as:

1. `player.png` -> `player.8bpp`
2. `player.8bpp` -> `player.shifted.8bpp`
3. `player.shifted.8bpp` -> `player.lz`
4. `player.png` -> `player.gbapal`

`tools/offset_portrait_8bpp.py` shifts every tile byte by `0xC0`. This is required because vanilla portrait loading copies the portrait palette to OBJ palette entries `0xC0..0xFF`.

### Adding A New Portrait

To add another custom portrait:

1. Add a PNG under `src_custom/assets/portraits/`, for example `rival.png`.
2. Add matching `8bpp`, `shifted.8bpp`, `lz`, and `gbapal` rules in `Makefile`, following the `player` rules.
3. Add those generated files to the `portrait_hooks` object dependency.
4. Add a portrait id in `enum Portrait` in `include/overworld.h`.
5. Add `INCBIN` declarations in `src_custom/portrait_hooks.c`.
6. Add a branch in `DisplayPortrait__Replacement` that loads the new portrait tiles and palette.

Example hook branch:

```c
if (scriptCtx->portraitId == PORTRAIT_RIVAL) {
  LZ77UnCompWram(sRivalPortraitTiles, gSharedMem);
  CopyTilesToVram(gBgVram.cbb4 + 0x2000, gSharedMem);
  CpuCopy16(sRivalPortraitPalette, gPaletteBuffer + 256 + 0xC0, 128);
}
```

Keep `sub_804EB04` in control of OAM setup. It configures portraits as 64x64 8bpp OBJ sprites and handles left, right, and auto positions.

### Event Usage

Use portraits from event scripts in `events/scripts/`.

Example from `events/scripts/map_09_state_01.c`:

```c
PORTRAIT(PORTRAIT_PLAYER, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "{CARD_1}Perfect\n"
    "Lousy{CARD_2}\n\n"
)
```

Available positions:

| Position | Behavior |
|--------|----------|
| `PORTRAIT_LEFT` | Shows the portrait on the left side |
| `PORTRAIT_RIGHT` | Shows the portrait on the right side |
| `PORTRAIT_AUTO` | Chooses left or right based on player map position |

Use `HIDE_PORTRAIT()` before moving actors or changing scenes when the portrait should leave the screen.

After editing event scripts, run:

```bash
make
```

The build regenerates `src_custom/generated/event_script_replacements.inc`, validates LynJump replacements, and patches `ygodm8.gba`.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Portrait source assets | `src_custom/assets/portraits/` | Holds custom indexed PNG portrait sources |
| Portrait asset rules | `Makefile` | Converts portrait PNGs to shifted compressed tile data and palettes |
| Palette-index shifter | `tools/offset_portrait_8bpp.py` | Moves `0..63` image indices into vanilla portrait OBJ palette range `0xC0..0xFF` |
| Portrait ids | `enum Portrait` in `include/overworld.h` | Defines ids used by event scripts and `DisplayPortrait__Replacement` |
| Runtime loader | `DisplayPortrait__Replacement` in `src_custom/portrait_hooks.c` | Loads custom portrait tile and palette data, then falls back to vanilla portraits |
| Vanilla OAM setup | `sub_804EB04` in `src/overworld/overworld.c` | Configures portrait position, size, priority, tile number, and 8bpp mode |
| Event macro | `PORTRAIT` in `events/scripts/event_macros.h` | Authoring macro parsed by `tools/vanilla_events.py` |
| Current event example | `events/scripts/map_09_state_01.c` | Shows `PORTRAIT_PLAYER` during the intro deck choice |

## TODO

- Replace one-off Makefile portrait rules with wildcard rules once more custom portraits are added.
- Consider adding a custom portrait table so `DisplayPortrait__Replacement` does not need one branch per portrait.
- Document the exact accepted PNG palette workflow for common editors if contributors keep hitting indexed-color issues.

## Limitations & Bugs

- Custom portraits currently support 64 colors because the loader uses palette range `0xC0..0xFF`.
- `expression` is ignored by `PORTRAIT_PLAYER`; each extra expression needs its own asset branch or a custom expression table.
- A 128x64 source image will not display correctly as a dialogue portrait.
- The current custom loader is explicit C code, not data-driven registration.
