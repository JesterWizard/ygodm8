# Custom Opening Screens

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Authoring Assets](#authoring-assets)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Before the title screen, the retail game shows three boot splashes: **Licensed by Nintendo**, then two **Konami** screens. This feature lets authors replace those three images with custom full-screen art while keeping vanilla fade timing.

The behavior is controlled by `enable_custom_opening_screens` in [`configs/runtime.c`](../configs/runtime.c). When the flag is `FALSE`, vanilla copyright screens run unchanged. When `TRUE`, the ROM shows three custom images from PNG assets.

This is separate from `skip_opening_sequence`, which skips the post-new-game story intro cutscene after naming.

## Plan

### Boot flow

| Stage | `enable_custom_opening_screens = FALSE` | `enable_custom_opening_screens = TRUE` |
|-------|----------------------------------------|----------------------------------------|
| Entry | Vanilla `CopyrightScreensMain` | `CopyrightScreensMain__Replacement` |
| Screens | Nintendo → Konami → Konami | `opening_screen_1` → `opening_screen_2` → `opening_screen_3` |
| Hold | ~120 frames per screen | Same |
| Fade | `REG_BLDY` darken/brighten, step every 3 frames | Same |
| Skip | None | Any button skips remaining screens |
| Exit | `REG_DISPCNT = 0` | Same |

### Asset rules

| Requirement | Value |
|-------------|-------|
| Count | Exactly **3** PNGs |
| Size | `240×160` |
| Mode | indexed PNG |
| Colors | up to **256** (8bpp, full palette slots 0–255) |
| Filenames | `opening_screen_1.png`, `opening_screen_2.png`, `opening_screen_3.png` |

Build pipeline per asset (only PNGs are committed; tile/palette blobs are embedded into the generated include):

1. Validate PNG (`tools/validate_opening_screen.py`)
2. Encode 8bpp tileset + palette (`tools/build_opening_screen.py`, same layout as event CGs)
3. Regenerate `src_custom/generated/opening_screen_assets_generated.inc` with embedded tile/palette arrays

## Authoring Assets

Drop indexed PNGs into:

```text
src_custom/assets/opening_screens/
  opening_screen_1.png
  opening_screen_2.png
  opening_screen_3.png
```

Enable the feature in [`configs/runtime.c`](../configs/runtime.c):

```c
.enable_custom_opening_screens = TRUE,
```

Rebuild with `make`. Placeholder PNGs are generated automatically on first build if the three files are missing.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Runtime toggle | `enable_custom_opening_screens` in [`configs/runtime.h`](../configs/runtime.h) | Build-time default for custom boot splashes |
| Hook entry | `CopyrightScreensMain__Replacement` in [`src_custom/copyright_screens_hooks.c`](../src_custom/copyright_screens_hooks.c) | Delegates to `VanillaCopyrightScreensMain` or custom player |
| Vanilla fallback | `VanillaCopyrightScreensMain` in [`src_custom/copyright_screens_hooks.c`](../src_custom/copyright_screens_hooks.c) | Replays vanilla main-loop logic via intact helper functions (cannot call `$268D8` after LynJump) |
| Custom player | `CustomOpeningScreensMain` in [`src_custom/copyright_screens_hooks.c`](../src_custom/copyright_screens_hooks.c) | Load, fade, hold, skip |
| Asset registration | [`src_custom/generated/opening_screen_assets_generated.inc`](../src_custom/generated/opening_screen_assets_generated.inc) | INCBIN tables generated at build time |
| Constants | [`include/constants/opening_screens.h`](../include/constants/opening_screens.h) | Screen count, hold/fade timing |
| PNG validation | [`tools/validate_opening_screen.py`](../tools/validate_opening_screen.py) | Size, mode, palette checks |
| Asset encoder | [`tools/build_opening_screen.py`](../tools/build_opening_screen.py) | 8bpp tileset + LZ |
| Palette encoder | [`tools/build_opening_palette.py`](../tools/build_opening_palette.py) | Full 256-color `.gbapal` |
| Asset codegen | [`tools/generate_opening_screen_assets.py`](../tools/generate_opening_screen_assets.py) | Regenerates INCBIN include |
| Placeholder PNGs | [`tools/generate_opening_screen_placeholders.py`](../tools/generate_opening_screen_placeholders.py) | Creates default solid-color screens |
| Makefile rules | [`graphics.mk`](../graphics.mk), [`Makefile`](../Makefile) | Build and hook object dependencies |
| LynJump | [`src_custom/LynJump.event`](../src_custom/LynJump.event) `@ $268D8` | Routes boot entry to replacement |

## TODO

- Add a debug-menu viewer for previewing the three screens without rebooting.
- Optional runtime config fields for hold duration and fade speed.

## Limitations & Bugs

- Full-screen 8bpp tilesets use `0x9600` bytes (600 tiles). Decompression targets `gBgVram.cbb0` directly; do not use `gSharedMem` as a staging buffer.
- Tilemaps are built at runtime as a 30×20 sequential grid in `gBgVram.sbb1F`, displayed on BG2 with `REG_BG2CNT = 0x1F82` (same approach as event CGs). `LoadVRAM()` must run after each screen load so char and screen blocks reach hardware VRAM.
- Skip uses raw `REG_KEYINPUT` polling so it works before the normal VBlank input path runs.
- Replacing Nintendo/Konami logos may have legal implications for distributed ROM hacks; authors are responsible for compliance.
- `skip_opening_sequence` remains a separate flag for the post-new-game story cutscene.
