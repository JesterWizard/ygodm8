# Event CG Framework

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Authoring Assets](#authoring-assets)
- [Event Script Usage](#event-script-usage)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Event CGs are full-screen overworld dialogue backgrounds: a **240×160 indexed image** with up to **240 BG colors** (palette banks 1–15), shown during event scripts with the **vanilla textbox** on top. Authors trigger a CG with `DISPLAY_CG(id)`, run dialogue and compatible commands, then call **`HIDE_CG()`** to fade out and restore the map.

Bank 0 stays reserved for the dialogue font. Map layers and overworld entity sprites are hidden while the CG is active; engine `PORTRAIT` sprites still work.

## Plan

### Session flow

| Stage | Behavior |
|-------|----------|
| `DISPLAY_CG(id)` | Fade out map, fade in CG on BG2 |
| Session body | Text, portraits, reactions, delays, another `DISPLAY_CG`, etc. |
| `HIDE_CG()` | Fade out CG and restore overworld graphics |
| Session-ending opcode | If CG still active (`DUEL`, `WARP`, `END`, …), auto fade out + restore |

Fade-in completes **before** the next opcode runs. `HIDE_CG()` is blocking.

### Asset rules

| Requirement | Value |
|-------------|-------|
| Size | `240×160` |
| Mode | indexed PNG |
| Colors | up to **224 author indices** (`0..223` → hardware slots `32..255`) |
| Textbox UI | hardware slots `16..31` left untouched (vanilla dialogue frame palette) |
| Runtime palette | slots `0..15` font, `16..31` textbox, `32..255` CG art |

Build pipeline per asset (only `.lz` and `.gbapal` are kept on disk):

1. `name.png` → optimized pixel indices (`tools/cg_optimize.py`, removes warm dither speckles from open background zones)
2. optimized pixels → raw 8bpp tiles in a temp file (600 tiles, `gbagfx` validates tile count)
3. temp 8bpp → palette-offset temp file (`tools/offset_cg_8bpp.py`, author index `N` → hardware slot `32 + N`)
4. temp shifted 8bpp → `name.lz`
5. `name.png` → `name.gbapal` (`tools/build_cg_palette.py`, BGR555-quantized colors)

## Authoring Assets

Drop a **240×160 indexed PNG** into `src_custom/assets/cgs/`. Filename becomes the enum id:

| File | Enum id | Script usage |
|------|---------|--------------|
| `meeting_yugi.png` | `CG_MEETING_YUGI` | `DISPLAY_CG(CG_MEETING_YUGI)` |
| `test_placeholder.png` | `CG_TEST_PLACEHOLDER` | `DISPLAY_CG(CG_TEST_PLACEHOLDER)` |

On `make`, the build automatically:

1. Validates PNGs (`tools/validate_cg.py`)
2. Builds `.lz` and `.gbapal` for each PNG
3. Regenerates `include/constants/event_cg_generated.h` and `src_custom/generated/event_cg_assets_generated.inc`

No manual edits to `cg_hooks.c`, Makefile rules, or enum registration are required.

Regenerate the sample placeholder PNG:

```bash
python3 tools/generate_test_cg_png.py
```

## Event Script Usage

```c
DISPLAY_CG(CG_TEST_PLACEHOLDER, 8)
TEXT("Hello world")
HIDE_CG(8)
DUEL(DUELIST_JOEY)
```

```c
DISPLAY_CG(CG_TEST_PLACEHOLDER, 4)
TEXT("I remember...")
PAGE_BREAK()
TEXT("That day changed everything.")
HIDE_CG(4)
WARP(LOCATION_DOMINO, 0, 0, 0)
```

Macro definitions:

```c
#define DISPLAY_CG(cg_id, fade_speed) RAW(0x7C, '9', cg_id, fade_speed)
#define HIDE_CG(fade_speed)            RAW(0x7C, 'A', fade_speed)
```

Bytecode: `[0x7C, '9', id, speed]` and `[0x7C, 'A', speed]`. Speed is frames per blend step (same scale as `FADE_SCREEN`; `0` means default `8`).

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| CG ids | `enum EventCg` in `include/constants/event_cg_generated.h` | Auto-generated from PNG filenames |
| Asset registration | `src_custom/generated/event_cg_assets_generated.inc` | Auto-generated INCBIN + lookup tables |
| Asset load / fade / restore | `src_custom/cg_hooks.c` | VRAM, palette, tilemap, session state |
| Asset scan + codegen | `tools/generate_cg_assets.py` | Scans `src_custom/assets/cgs/*.png` |
| Makefile graphics rules | `graphics.mk` | Pattern rules for all CG PNGs |
| Script VM hook | `sub_80526D0__Replacement` in `src_custom/script_cg_hooks.c` | Opcode dispatch, text-wait close |
| Event entry | `InitiateScript__Replacement` in `src_custom/event_system_hooks.c` | Runs CG-aware script loop; force-close on exit |
| Portrait text window | `DisplayPortrait__Replacement` in `src_custom/portrait_hooks.c` | CG-aware WIN1 setup |
| Session RAM | `gCgSessionOpen`, … in `asm/ram_map.s` | IWRAM session flags |
| Macro | `DISPLAY_CG`, `HIDE_CG` in `events/scripts/event_macros.h` | Authoring API |
| Bytecode | `tools/vanilla_events.py` | Emits `0x7C '9'` / `0x7C 'A'` |
| Validation | `tools/validate_cg.py` | PNG / palette checks |
| LynJump | `src_custom/LynJump.event` `@ $526D0` | Routes vanilla script loop to replacement |

## TODO

- Add a debug-menu CG viewer (similar to portrait/graphic debug menus).
- Optional fade speed argument on `DISPLAY_CG`.

## Limitations & Bugs

- Author palette index `N` maps to hardware slot `32 + N` (slots `0..31` stay reserved for font and textbox UI).
- CG tiles use ~38 KB of BG char VRAM (`cbb0` + `cbb1` + part of `cbb2`); decompression targets `gBgVram.cbb0` directly — do not use `gSharedMem` (~17 KB).
- Session-ending opcode list is maintained manually in `EventCg_ClassifyOpcode()`; new vanilla opcodes may need explicit classification.
- Replacing a CG with another `DISPLAY_CG` fades out the previous image but does not run a full map restore between them.
