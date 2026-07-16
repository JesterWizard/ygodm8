# Custom Title Screen

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Authoring Assets](#authoring-assets)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

After the boot copyright screens, the retail game shows a title screen with background art, animated shimmer, and **NEW GAME** / **CONTINUE** menu labels. This feature lets authors replace the **background art only** with a custom full-screen indexed PNG while keeping vanilla menu sprites, music, selection pulse, and the save-overwrite dialog.

The behavior is controlled by `enable_custom_title_screen` in [`configs/runtime.c`](../configs/runtime.c). When the flag is `FALSE`, vanilla title background loading runs unchanged. When `TRUE`, the ROM loads custom tiles and palette from `title_screen.png`.

This is independent of `enable_custom_opening_screens`, which only affects the pre-title boot splashes.

## Plan

### Title screen flow

| Stage | `enable_custom_title_screen = FALSE` | `enable_custom_title_screen = TRUE` |
|-------|--------------------------------------|-------------------------------------|
| Entry | Vanilla `CopyBgGfx` | `CopyBgGfx__Replacement` |
| BG3 tiles | LZ bundle `g8E0CD9C` | Custom LZ tiles from PNG |
| BG3 tilemap | Vanilla language rows in `sbb1F` | Runtime 30×20 sequential map in `sbb1F` |
| BG0 save dialog | Vanilla charbase-3 tiles + `sbb1E` patches | Same vanilla setup preserved |
| OBJ labels | Vanilla 4bpp NEW GAME / CONTINUE | Unchanged |
| Pulse | Vanilla alpha pulse on menu sprites | Same vanilla blend setup (`gBLDCNT = 0x8D8`) |
| Palette | Vanilla `g8E0CDA0` | Custom palette at load; dialog slots restored only while save prompt is open |

### Asset rules

| Requirement | Value |
|-------------|-------|
| Count | Exactly **1** PNG |
| Size | `240×160` |
| Mode | indexed PNG |
| Colors | up to **256** (8bpp, full palette slots 0–255) |
| Filename | `title_screen.png` |

Build pipeline (only the PNG is committed; tile/palette blobs are embedded into generated includes):

1. Validate PNG (`tools/validate_title_screen.py`)
2. Encode 8bpp tileset + palette (`tools/build_title_screen.py`)
3. Scan vanilla save-dialog tile data for reserved palette indices (`tools/extract_title_screen_palette_reservations.py`)
4. Regenerate `src_custom/generated/title_screen_assets_generated.inc` and `title_screen_palette_reservations_generated.inc`

### Palette safety

The save-overwrite dialog uses BG0 tiles that share the same 256-color BG palette as the title background. The custom palette is loaded unchanged at title screen entry so background art keeps all author colors (including low indices like 0–119). When the save-overwrite prompt opens, `VBlankCbTryStartNewGame__Replacement` temporarily restores dialog-used palette slots from vanilla `g8E0CDA0`; `VBlankCbTryStartNewGameEnd__Replacement` restores the custom palette when the prompt closes.

## Authoring Assets

Drop an indexed PNG into:

```text
src_custom/assets/title_screens/
  title_screen.png
```

Enable the feature in [`configs/runtime.c`](../configs/runtime.c):

```c
.enable_custom_title_screen = TRUE,
```

Rebuild with `make`. A placeholder PNG is generated automatically on first build if the file is missing.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Runtime toggle | `enable_custom_title_screen` in [`configs/runtime.h`](../configs/runtime.h) | Build-time default for custom title background |
| Hook entry | `CopyGfxAndInitGfxRegs__Replacement` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Intercepts title gfx init before sprites/OAM setup |
| Vanilla fallback | `VanillaCopyGfxAndInitGfxRegs` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Replays vanilla bg load, sprites, and darken-blend init via Thumb helpers |
| Custom loader | `CustomCopyGfxAndInitGfxRegs` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | LZ tiles, tilemap, palette, vanilla blend init |
| Save dialog setup | `TitleScreen_SetupSaveDialogGfx` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Shared vanilla BG0 dialog char/tilemap patches |
| Custom palette load | `TitleScreen_LoadCustomPalette` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Loads author palette at title entry |
| Dialog palette merge | `TitleScreen_ApplyDialogPaletteReservations` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Restores dialog indices only during save prompt |
| Save prompt open | `VBlankCbTryStartNewGame__Replacement` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Merges dialog palette + `LoadPalettes()` |
| Save prompt close | `VBlankCbTryStartNewGameEnd__Replacement` in [`src_custom/title_screen_hooks.c`](../src_custom/title_screen_hooks.c) | Restores custom palette + `LoadPalettes()` |
| Asset registration | [`src_custom/generated/title_screen_assets_generated.inc`](../src_custom/generated/title_screen_assets_generated.inc) | Embedded LZ tile and palette arrays |
| Reserved indices | [`src_custom/generated/title_screen_palette_reservations_generated.inc`](../src_custom/generated/title_screen_palette_reservations_generated.inc) | Dialog palette slots restored from vanilla |
| Constants | [`include/constants/title_screen.h`](../include/constants/title_screen.h) | Tile bytes, map size |
| PNG validation | [`tools/validate_title_screen.py`](../tools/validate_title_screen.py) | Size, mode, palette checks |
| Asset encoder | [`tools/build_title_screen.py`](../tools/build_title_screen.py) | 8bpp tileset + LZ |
| Palette reservations | [`tools/extract_title_screen_palette_reservations.py`](../tools/extract_title_screen_palette_reservations.py) | Scans `gText_ReplaceSaveData` in built ROM |
| Asset codegen | [`tools/generate_title_screen_assets.py`](../tools/generate_title_screen_assets.py) | Regenerates INCBIN includes |
| Placeholder PNG | [`tools/generate_title_screen_placeholders.py`](../tools/generate_title_screen_placeholders.py) | Creates default solid-color background |
| Makefile rules | [`graphics.mk`](../graphics.mk), [`Makefile`](../Makefile) | Build and hook object dependencies |
| LynJump | [`src_custom/LynJump.event`](../src_custom/LynJump.event) `@ $35488`, `$357F8`, `$35AE4`, `$35B08` | Routes gfx init, pulse animation, and save-dialog VBlank callbacks |
| Vanilla source | [`src/title_screen.c`](../src/title_screen.c) | Unchanged; hooks use ROM Thumb addresses from [`include/constants/title_screen.h`](../include/constants/title_screen.h) |

## TODO

- Add a debug-menu viewer for previewing the title background without rebooting.
- Document reserved palette index list for artists in a companion table.

## Limitations & Bugs

- Custom art replaces **BG3 background only**; NEW GAME / CONTINUE labels remain vanilla 4bpp OBJ sprites.
- Full-screen 8bpp tilesets use `0x9600` bytes (600 tiles). Decompression targets `gBgVram.cbb0` directly; do not use `gSharedMem` as a staging buffer.
- LZ tile blobs must be **word-aligned** (`APPEND_ASSET` includes `aligned(4)`). BIOS `LZ77UnCompWram` reads ROM as 32-bit words; unaligned sources black-screen + audio static on mGBA/hardware while No$GBA often still boots.
- Tilemaps are built at runtime as a 30×20 sequential grid in `gBgVram.sbb1F`, displayed on BG3 with the vanilla `REG_BG3CNT` setup from `VBlankCbInitGfxRegs`. `LoadVRAM()` must run after `CopyGfxAndInitGfxRegs` so char and screen blocks reach hardware VRAM.
- Language-specific BG3 tilemap rows from `g8E0CDA4` are not applied in custom mode. This does not affect the localized save-overwrite dialog on BG0.
- While the save-overwrite prompt is visible, dialog palette slots temporarily use vanilla colors; background art may tint slightly in overlapping indices during that prompt only.
- Toggle is build-time via `gRuntimeConfig`, not an in-game menu option.
