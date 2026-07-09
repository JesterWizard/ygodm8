# Summon Popup Animations

## Overview

When a monster with a registered summon animation is placed on the field, the duel board dims, a full-screen sprite animation plays, then the board restores and normal play resumes. This reuses the vanilla overworld GFX effects engine that already drives cut-scene full-art slides.

## How It Works

```
Placement hook (sub_80449D8 / PlaceMonsterFromId)
  └─ TryPlaySummonAnimation(cardId)
       └─ if card has registered graphic:
            ├─ Save duel display (palette, cbb5 tiles, DISPCNT, OAM)
            ├─ Dim BG palette
            ├─ PlayGfxEffectByGraphic(graphicId)
            │    ├─ LZ77 decompress tiles to gSharedMem+0x400
            │    ├─ Copy tiles to gBgVram.cbb5 (interleaved stride)
            │    ├─ Copy 80-color palette to gPaletteBuffer+0x170
            │    ├─ sub_804F2DC commits tiles + palette to hardware
            │    └─ sub_804FE78 / sub_8050114 runs frame sequence
            ├─ Restore duel display
            └─ Resume
```

Two placement hooks intercept every summon path (human normal summon, special summon, flip, set, AI programmatic placement):
- `src_custom/code_8043EF4_hooks.c` → `sub_80449D8__Replacement`
- `src_custom/duel_helpers.c` → `PlaceMonsterFromId()`

## Extracted Reference Art

All registered popup graphics live in `src_custom/assets/popup_animations/` as 240×160 indexed PNGs:

| Card | Graphic | Effect Type |
|------|---------|-------------|
| Blue-Eyes White Dragon | `blue_eyes_white_dragon.png` | 3 (horizontal slide) |
| Red-Eyes B. Dragon | `red_eyes_black_dragon.png` | 3 |
| Harpie Lady Sisters | `harpie_lady_sisters.png` | 4 (vertical slide) |
| Dark Magician | `dark_magician.png` | 4 |
| Jinzo | `jinzo.png` | 3 |
| Master of Dragon Soldier | `master_of_dragon_soldier.png` | 3 |
| Slifer the Sky Dragon | `slifer_the_sky_dragon.png` | 4 |
| Obelisk the Tormentor | `obelisk_the_tormentor.png` | 4 |
| The Winged Dragon of Ra | `the_winged_dragon_of_ra.png` | 4 |
| The Winged Dragon of Ra – Phoenix Mode | `the_winged_dragon_of_ra_phoenix_mode.png` | 4 |

Re-extract from the built ROM:
```bash
python3 tools/extract_popup_animations.py
```

Normalize a PNG so the background color moves to palette index 0 (required for GBA OBJ transparency):
```bash
# Auto-detect background from corners
python3 tools/normalize_popup_png.py src_custom/assets/popup_animations/your_card.png

# Explicit background color (e.g. green screen)
python3 tools/normalize_popup_png.py src_custom/assets/popup_animations/your_card.png --bg 0,255,0
```

## Technical Limits

| Limit | Value |
|-------|-------|
| Screen canvas | 240 x 160 px |
| Sprite color depth | 4 bpp (16 colors per palette bank) |
| Total palette | 80 colors = 5 OBJ palette banks |
| Palette base bank | 7 (copied to `gPaletteBuffer + 0x170`) |
| Transparent index | 0 in every palette bank |
| Max tiles | 448 tiles (14 336 bytes decompressed) |
| Tile compression | GBA LZ77 |
| Tile destination | OBJ charblock 5 (hardware tile base = 512) |
| OAM entry size | 8 bytes per sprite (6 bytes attr0/1/2 + 2 bytes padding) |
| Max sprites per frame | Limited by OAM budget (≈64 sprites minus duel board sprites) |

### Palette Rules

- Palette index 0 is hard-transparent for every bank. Do **not** draw opaque pixels with index 0.
- The 80 palette entries occupy OBJ palette banks 7–11.
- Sprite `attr2` palette bank field must be in the range 7–11 for popup colors.
- The dimming pass darkens BG palette entries 0–255; OBJ palette 256–511 stays full-bright so popup sprites remain vivid.

### Tile Layout (Charblock 5 Reconstruction)

`sub_804FA28` does **not** copy decompressed tiles linearly. It interleaves 512-byte chunks:

```
Loop 1 (16 chunks from src+0x000) -> dest offsets 0x0000, 0x0400, 0x0800, ... 0x3C00
Loop 2 (12 chunks from src+0x2000) -> dest offsets 0x0200, 0x0600, 0x0A00, ... 0x2E00
```

In the reconstructed charblock, hardware tile *N* is at byte offset `N * 32`. The 2-D OBJ tile map uses 32 tiles per row, so a 32x32 sprite (4×4 tiles) occupies tile indices `N`, `N+1`, `N+2`, `N+3` on the first row and `N+32`, `N+33`, `N+34`, `N+35` on the second row.

## Wiring an Existing Graphic to a Card

If the graphic already exists in the ROM (vanilla cut-scene art or previously injected art), wiring it to a card is one line.

**Step 1:** Open `src_custom/summon_animations.c`.

**Step 2:** Add a case to `GetSummonAnimGraphic()`:

```c
static u8 GetSummonAnimGraphic(u16 cardId)
{
    switch (cardId) {
    case BLUE_EYES_WHITE_DRAGON:              return GRAPHIC_BLUE_EYES_WHITE_DRAGON_FULL_ART;
    case JINZO:                               return GRAPHIC_JINZO_FULL_ART;
    case YOUR_NEW_CARD:                       return GRAPHIC_YOUR_NEW_GRAPHIC;
    default:                                  return 0;
    }
}
```

**Step 3:** Ensure the graphic ID is defined in `include/overworld.h`:

```c
enum GraphicId {
    ...
    GRAPHIC_YOUR_NEW_GRAPHIC = 59,
    ...
};
```

**Step 4:** Run the narrowest validation target:

```bash
make test-cards-build
```

That is the entire wiring step. No new C hooks, no event changes, no RAM map edits.

## Creating a Brand-New Graphic

Creating a new full-art popup from scratch is a **ROM data injection** task. The vanilla engine requires three data blobs per graphic:

1. **LZ77-compressed tile data** – 4bpp tiles, max 14 336 bytes uncompressed.
2. **Raw palette data** – 160 bytes (80 RGB555 colors).
3. **Frame animation data** – OAM descriptors + timing metadata.

These are referenced by three pointer tables at fixed ROM addresses:

| Table | Address | Entry Size | Purpose |
|-------|---------|------------|---------|
| `g8FC4440` | `0x08FC4440` | 4 bytes | Tile data pointer |
| `g8FC452C` | `0x08FC452C` | 4 bytes | Palette data pointer |
| `g8FC4618` | `0x08FC4618` | 4 bytes | Frame data pointer |

Plus the effect-type table:

| Table | Address | Entry Size | Purpose |
|-------|---------|------------|---------|
| `g8E0E384` | `0x08E0E384` | 1 byte | Effect type (3=horizontal, 4=vertical, 5=attack, …) |

### Why it is hard

The tables are packed contiguously with no padding:
- Tile table: `0xFC4440` – `0xFC452C` (59 entries)
- Palette table: `0xFC452C` – `0xFC4618` (59 entries)
- Frame table: `0xFC4618` – `0xFC4704` (59 entries)

Appending a 60th entry in place would overwrite the data that follows `0xFC4704`. To add a new graphic safely you must either:

1. **Repoint the entire table block** to a larger free area in ROM, then update `ldscript.ld` symbol addresses and every assembly `.4byte` reference in `overworld_gfx_effects.c`.
2. **Recycle an unused graphic ID** (e.g. `GRAPHIC_UNUSED_33`, `GRAPHIC_UNUSED_35`, `GRAPHIC_UNUSED_51`) and overwrite its three pointers to point at new data injected into an empty ROM region.
3. **Use the debug menu** (`src_custom/debug/debug_menu_graphic_table.inc`) to preview candidate art before committing to a card.

### Suggested workflow for new art

1. Draw the 240×160 reference PNG (see extracted samples for style).
2. Reduce to ≤80 unique non-transparent colors. Index 0 must be pure black `(0,0,0)`.
3. Slice into GBA OBJ sprites (8×8, 16×16, 32×32, 64×64, and rectangular sizes). Keep sprite count low; ~30–60 sprites is typical.
4. Encode tiles to 4bpp, LZ77 compress, and emit palette blob. Tools such as `gbagfx` (from pret projects) or a custom Python pipeline can do this.
5. Build OAM frame data. A type-3 (horizontal slide) frame needs one resting frame with all sprites visible. A type-4 (vertical slide) needs a progressive build-up sequence ending in a hold frame.
6. Inject the three blobs into a free ROM region (use the ROM map / `make memory_report` to find gaps).
7. Overwrite the unused graphic ID's pointers in the three tables to point at your injected blobs.
8. Set the effect type in `g8E0E384` at the same ID index.
9. Add the `GRAPHIC_*` enum to `include/overworld.h`.
10. Wire `cardId → graphicId` in `src_custom/summon_animations.c`.
11. `make test-cards-build` → test in a runtime test hand.

### Effect types

| Type | Function | Visual |
|------|----------|--------|
| 3 | `sub_804FE78` | Horizontal slide in from off-screen |
| 4 | `sub_8050114` | Vertical slide in from off-screen |
| 5 | `sub_805022C` | Monster attack swipe |

Summon popups currently use type 3 or 4. Type 5 is available for attack-declaration popups if desired.

## File Reference

| File | Role |
|------|------|
| `src_custom/summon_animations.c` | Config table, display save/restore, effect playback |
| `include/summon_animations.h` | `TryPlaySummonAnimation()` / `FinishSummonAnimation()` |
| `include/overworld.h` | `enum GraphicId` and effect type constants |
| `src_custom/code_8043EF4_hooks.c` | Human summon path hook |
| `src_custom/duel_helpers.c` | Programmatic / AI summon path hook |
| `src/overworld/overworld_gfx_effects.c` | Vanilla GFX effect renderer (do not edit) |
| `tools/extract_popup_animations.py` | Extract reference PNGs from built ROM |
| `src_custom/assets/popup_animations/` | Extracted 240×160 reference PNGs |
