# Custom Background Music (DPCM)

---

## Index

- [Introduction](#introduction)
- [Audio Format](#audio-format)
- [Authoring Workflow](#authoring-workflow)
- [Manifest Schema](#manifest-schema)
- [Playback](#playback)
- [Build Pipeline](#build-pipeline)
- [Debug Menu](#debug-menu)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

This project supports **custom background music** stored as DPCM in main ROM. A JSON manifest drives code generation; `make` resamples source WAV files, compresses them with the same DPCM codec used by custom voices, patches m4a tone/song tables, and links assets into the ROM tail.

Custom tracks use song IDs starting after the custom voice block (default **652**). They play through the main BGM player (`g2025840`) like vanilla overworld music.

## Audio Format

| Property | Value |
|----------|-------|
| In-ROM format | DPCM in m4a `WaveData` (`type` 1) by default; optional signed 8-bit PCM fallback (`type` 0) |
| Playback | BGM player 0 through normal `PlayMusic()` / m4a sequencing |
| Target sample rate | **21024 Hz** (build-time resample; matches vanilla `WaveData.freq` `0x01488000`) |
| Authoring input | **WAV** (16-bit mono or stereo; stereo is downmixed) |
| Pre-build conversion | Resample → optional `gain_db` → peak normalize → optional edge trim → signed 8-bit PCM → DPCM |
| ROM placement | **Main ROM** tail: `.music_pcm_rom` @ `0x08FE3400`, then `.voice_pcm_rom`, then append |
| Long tracks | One `WaveData` + one m4a `TIE`/`EOT` note; loop uses `GOTO` (`0xB2`) |

Registered track sizes are listed in [`src_custom/assets/music/MUSIC.md`](../src_custom/assets/music/MUSIC.md).

## Authoring Workflow

### 1. Prepare source audio

Export or capture a **WAV** (16-bit). Stereo is fine; the build downmixes to mono.

For looping BGM, trim to a clean loop window in Audacity first. The build does **not** auto-detect loop points yet; it loops the full decoded PCM unless you trim the source.

### 2. Place the WAV

```text
src_custom/assets/music/overworld/my_theme.wav
```

### 3. Register in the manifest

Add a row to [`tools/music_manifest.json`](tools/music_manifest.json) (see schema below).

### 4. Build and preview

```bash
make
```

Open the overworld debug menu → **Music Viewer**. Custom rows appear after the vanilla OST list.

## Manifest Schema

File: [`tools/music_manifest.json`](tools/music_manifest.json)

| Field | Required | Description |
|-------|----------|-------------|
| `track_id` | yes | Unique ID; used for generated symbol names |
| `wav` | yes | Path relative to `src_custom/assets/music/` |
| `title` | no | Debug menu label (≤ 23 visible chars) |
| `loop` | no | Loop via m4a `GOTO` (`0xB2`) after the tied note (default **true**) |
| `codec` | no | `dpcm` (default, compressed) or `pcm8` (uncompressed fallback) |
| `gain_db` | no | Per-track loudness boost/cut in dB before peak normalization |
| `trim_silence` | no | Strip leading/trailing near-silence (default **false** for music) |
| `trim_silence_threshold` | no | \|s8\| sample magnitude treated as silence at edges (default **8**) |

Song IDs are allocated sequentially from `song_id_base` (default **0** = auto: `CUSTOM_VOICE_SONG_ID_MAX + 1`). All IDs must stay **below 800** so `PlayMusic()` accepts them.

## Playback

From C code after registering a track:

```c
#include "constants/custom_music_generated.h"

PlayCustomMusic(0);                  // by manifest order index
PlayCustomMusicById(MUSIC_CUSTOM_MY_THEME);  // same as PlayMusic(id) when patched
PlayMusic(MUSIC_CUSTOM_MY_THEME);    // works once song/mode tables are patched
```

`PlayCustomMusicById()` and `PlayMusic()` use `m4aSongNumStartOrChange` (BGM mode **1**). Custom voice clips still use the separate voice player path.

## Build Pipeline

[`tools/generate_music.py`](tools/generate_music.py) runs during `make` when the manifest, generator, voice stamp, or any music WAV changes (`build/.music_generated.stamp`).

| Output | Purpose |
|--------|---------|
| `src_custom/generated/music_assets_generated.s` | DPCM/PCM WaveData + tied-note part tracks + song headers (`.music_pcm_rom`) |
| `src_custom/generated/music_rom_patches.json` | Tone/song-table/mode ROM patch specs |
| `src_custom/generated/debug_menu_music_custom.inc` | Debug menu rows |
| `include/constants/custom_music_generated.h` | Song ID `#define`s |
| `src_custom/assets/music/MUSIC.md` | Source vs in-ROM size inventory |

Pipeline per track:

```text
WAV  →  resample 21024 Hz  →  gain_db  →  peak normalize  →  optional edge trim
  →  signed 8-bit PCM  →  DPCM payload  →  m4a TIE + waits + EOT + optional GOTO
  →  song header + ROM table patches
```

## Debug Menu

The **Music Viewer** lists vanilla OST rows from `debug_menu_music_table.inc` plus generated custom rows. Custom entries use `PlayCustomMusicById()`.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Manifest | `tools/music_manifest.json` | Authoring source of truth |
| Generator | `tools/generate_music.py` | WAV → DPCM/PCM + tied-note codegen |
| Voice helpers | `tools/generate_voices.py` | Shared WAV loading, resampling, DPCM codec, note timing helpers |
| ROM assets | `src_custom/generated/music_assets_generated.s` | Linked `.music_pcm_rom` |
| Playback | `src_custom/custom_music.c` | `PlayCustomMusic`, `PlayCustomMusicById` |
| Song IDs | `include/constants/custom_music_generated.h` | Generated constants |
| ROM patches | `tools/apply_lynjump.py` | Applies `music_rom_patches.json` post-link |
| Debug preview | `src_custom/debug/debug_menu_music.c` | Music Viewer integration |
| Makefile rule | `Makefile` | `MUSIC_*` generator + asset object |
| Linker | `ldscript.ld` | `.music_pcm_rom` before `.voice_pcm_rom` |

## TODO

- [ ] Per-track `loop_start_seconds` / sample-accurate loop points in the manifest.
- [ ] Overworld map / scene hooks to swap vanilla BGM for custom tracks by location.
- [ ] Optional duel BGM override field in duel data or runtime config.

## Limitations & Bugs

- **Song ID ceiling** — IDs must stay below **800** (`PlayMusic` guard). Voice + music share the 601–799 range; keep the combined count under ~148 tracks.
- **ROM budget** — Music and voice DPCM share the tail ROM budget before append; `generate_music.py` sums voice inventory + new music and errors on overflow.
- **DPCM loss** — DPCM is much smaller, but lower fidelity than signed 8-bit PCM. Use `codec: "pcm8"` on a track if you need an uncompressed fallback for comparison.
- **No in-track loop points** — `loop: true` jumps to the start of the part track; trim the WAV for a seamless loop.
- **Timing calibration** — The tied note waits are generated from the existing m4a timing calibration. If a track loops a frame early/late, tune `music_wait_ticks_for_samples()`.
