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

Bank 0 stays reserved for the dialogue font. Map layers and overworld sprites are hidden while the CG is active.

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
| Colors | up to **224 distinct colors** packed into hardware slots `32..32+n-1` |
| Textbox UI | hardware slots `16..31` left untouched (vanilla dialogue frame palette) |
| Runtime palette | slots `0..15` font, `16..31` textbox, `32..32+n-1` CG art; slots `32+n..255` cleared each apply |

Build pipeline per asset (intermediate binaries live under `build/cgs/`; only PNGs are committed):

1. `name.png` → raw 8bpp tiles in a temp file (600 tiles, `gbagfx` validates tile count)
2. temp 8bpp → palette-offset temp file (`tools/offset_cg_8bpp.py`; author indices pack into hardware slots `32..32+n-1`)
3. temp shifted 8bpp → `build/cgs/name.lz` (GBA BIOS LZ77, ~20 KB for a full screen)
4. `name.png` → `build/cgs/name.gbapal` (`tools/build_cg_palette.py`; only packed slots written; `32+n..255` stay zero)
5. `tools/generate_cg_assets.py` reads those build artifacts and **embeds** LZ + palette bytes into `src_custom/generated/event_cg_assets_generated.inc` as aligned C arrays (same approach as opening screens)

Decompressed tile data is **38,400 bytes** (`0x9600`, 600 tiles × 64 bytes).

### Runtime graphics

CG display must work on **cycle-accurate hardware and mGBA**, not just permissive emulators. The load path follows these rules:

| Step | Function | What it does |
|------|----------|--------------|
| Decompress | `EventCg_DecompressCgTiles` | `LZ77UnCompWram((const u32 *)tiles, gBgVram.cbb0)` — BIOS output lands in EWRAM staging across `cbb0` + `cbb1` + part of `cbb2` |
| Upload | `EventCg_SyncBg2Vram` | Re-decompresses from ROM, then `CpuCopy16` staging → hardware char VRAM (`BG_CHAR_ADDR(0)`, `0x9600` bytes) and tilemap → `BG_SCREEN_ADDR(31)` |
| BG2 setup | `EventCg_ApplyCgBgRegs` | `REG_BG2CNT` with `BGCNT_256COLOR`, char base 0, screen base 31; re-applied after textbox work |
| Textbox | `EventCg_LoadTextboxBg` / `EventCg_PushTextboxVram` | Loads vanilla textbox tiles into `gVramBuffer + 0xD800` and pushes textbox screen blocks — **after** CG char data is staged |

**Why re-decompress and direct VRAM upload each sync**

- `gVramBuffer` and `gBgVram` alias at `0x02000400`. While a CG session runs, textbox decompression and glyph rendering constantly rewrite parts of that shared EWRAM buffer. Uploading CG tiles once via `LoadVRAM()` and assuming staging stays valid produces stripe corruption on real hardware.
- `EventCg_SyncBg2Vram` runs on load, each script frame end, and after text-wait — mirroring the refresh pattern needed to keep BG2 char VRAM stable while the textbox is active.

**Why LZ sources are embedded aligned arrays**

- GBA BIOS `LZ77UnCompWram` reads the compressed stream as 32-bit words. Sources in `.append_assets` that are packed via `INCBIN` can land at odd ROM addresses; unaligned reads return rotated garbage on hardware/mGBA and produce “tile soup”.
- `generate_cg_assets.py` embeds each `.lz` blob as `const u8 …[] APPEND_ASSET __attribute__((aligned(4))) = { … }`, matching opening-screen asset registration. Cast the pointer to `(const u32 *)` when calling `LZ77UnCompWram`.

**Why not `gSharedMem`**

- `gSharedMem` is only ~17 KB (`0x4314`). A full-screen CG `.lz` is ~20 KB. Copying compressed data there before decompress **overflows** adjacent EWRAM and crashes (invalid jump addresses on mGBA). Decompress directly into `gBgVram.cbb0` instead.

**Tilemap**

- Built at runtime as a 30×20 sequential grid in `gBgVram.sbb1F`. Columns 30–31 are padded with the last column tile so the 32-wide screen block is fully defined.

## Authoring Assets

Drop a **240×160 indexed PNG** into `src_custom/assets/cgs/`. Filename becomes the enum id:

| File | Enum id | Script usage |
|------|---------|--------------|
| `meeting_yugi.png` | `CG_MEETING_YUGI` | `DISPLAY_CG(CG_MEETING_YUGI)` |
| `test_1.png` | `CG_TEST_1` | `DISPLAY_CG(CG_TEST_1)` |

On `make`, the build automatically:

1. Validates PNGs (`tools/validate_cg.py`)
2. Builds `build/cgs/*.lz` and `build/cgs/*.gbapal` for each PNG (`tools/build_cg.py`)
3. Regenerates `include/constants/event_cg_generated.h` and `src_custom/generated/event_cg_assets_generated.inc` (embedded tile/palette arrays + lookup table)

No manual edits to `cg_hooks.c`, Makefile rules, or enum registration are required.

## Event Script Usage

```c
DISPLAY_CG(CG_TEST_1, 8)
TEXT("Hello world")
HIDE_CG(8)
DUEL(DUELIST_JOEY)
```

```c
DISPLAY_CG(CG_TEST_1, 4)
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
| Asset registration | `src_custom/generated/event_cg_assets_generated.inc` | Auto-generated **embedded** LZ/palette arrays (`aligned(4)` tiles) + `EventCg_GetAssetFromTable` |
| Asset load / fade / restore | `src_custom/cg_hooks.c` | Decompress, per-frame VRAM sync, palette, tilemap, session state |
| LZ decompress | `EventCg_DecompressCgTiles` in `src_custom/cg_hooks.c` | `LZ77UnCompWram` into `gBgVram.cbb0` |
| VRAM sync | `EventCg_SyncBg2Vram` in `src_custom/cg_hooks.c` | Re-decompress + `CpuCopy16` char/tilemap blocks to hardware VRAM |
| BG2 re-apply | `EventCg_ApplyCgBgRegs` in `src_custom/cg_hooks.c` | Restores `BGCNT_256COLOR` and scroll after textbox uploads |
| Asset scan + codegen | `tools/generate_cg_assets.py` | Builds intermediates, embeds bytes into generated include |
| Tile/palette encode | `tools/build_cg.py`, `tools/offset_cg_8bpp.py`, `tools/build_cg_palette.py` | PNG → shifted 8bpp → `.lz` + `.gbapal` |
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

- Runtime keeps slots `32..32+n-1` on the CG asset palette; slots `32+n..255` are zeroed in `gPaletteBuffer` and uploaded each apply (`CpuFill16`/`CpuCopy16` sizes are in bytes — the full 224-entry CG region is 448 bytes).
- All overworld OBJ entries are hidden during an active CG (including the player at OAM slot 0); `PORTRAIT` is not shown until after `HIDE_CG()`.
- CG tiles use ~38 KB of BG char VRAM (`cbb0` + `cbb1` + part of `cbb2`). Decompression targets `gBgVram.cbb0` directly — **do not** use `gSharedMem` (~17 KB) as a staging buffer for compressed or decompressed CG data.
- Do **not** register CG tile blobs with plain `INCBIN` in `.append_assets` without 4-byte alignment; use the generated embedded arrays from `generate_cg_assets.py`.
- Do **not** rely on a one-shot `LoadVRAM()` for CG char data during an active textbox session; use `EventCg_SyncBg2Vram` instead.
- Session-ending opcode list is maintained manually in `EventCg_ClassifyOpcode()`; new vanilla opcodes may need explicit classification.
- Replacing a CG with another `DISPLAY_CG` fades out the previous image but does not run a full map restore between them.
