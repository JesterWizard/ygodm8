# Custom Duelist Voice-Overs

---

## Index

- [Introduction](#introduction)
- [Audio Format](#audio-format)
- [Authoring Workflow](#authoring-workflow)
- [Manifest Schema](#manifest-schema)
- [Triggers](#triggers)
- [Build Pipeline](#build-pipeline)
- [Runtime Behavior](#runtime-behavior)
- [Debug Menu](#debug-menu)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

This project supports **custom duelist voice clips** for Yugi, Atem, Kaiba, and Joey. Clips are additive: vanilla voice lines remain unless a custom clip matches the same trigger for that duelist.

Clips are stored as **8-bit mono PCM** in the GBA **m4a Direct Sound** format (same engine path as vanilla duel voicing). A JSON manifest drives code generation; `make` converts source WAV files and wires duel hooks automatically.

## Audio Format

Vanilla duelist VO uses m4a Direct Sound, not MP3/OGG in ROM.

| Property | Value |
|----------|-------|
| In-ROM format | **Signed** 8-bit mono PCM in m4a `WaveData` (`s8`, silence ≈ `0x00`) |
| Target sample rate | **21024 Hz** (resampled at build time; matches vanilla `WaveData.freq` `0x01488000`) |
| Effective bitrate | ~**168 kbps** uncompressed (21024 × 8-bit) |
| Authoring input | **WAV** (mono or stereo; stereo is downmixed) |
| Pre-build conversion | **None** — no `.dmp`, `.lz`, or other compression step; `generate_voices.py` resamples WAV → 8-bit PCM in m4a `WaveData` |
| ROM placement | **Main ROM** (`.voice_pcm_rom` @ `0x08FE3400`) holds WaveData; append ROM holds part tracks; **EWRAM** (`gCustomVoiceBlob`) holds the runtime song header and part track at playback |
| Turn-start target | ≤ **2 s**, ≤ **42 KB** PCM |
| Attack/card target | ≤ **4 s**, ≤ **84 KB** PCM |

Vanilla reference sizes (from baserom analysis; durations assume **21024 Hz** playback):

| Clip type | Size | Duration @ 21024 Hz |
|-----------|------|---------------------|
| Turn start | 14–22 KB | ~0.7–1.1 s |
| Card attack | 40–53 KB | ~2.0–2.5 s |

## Authoring Workflow

### 1. Extract source audio

Demux or capture audio with ffmpeg:

```bash
ffmpeg -i episode.mkv -vn -acodec pcm_s16le -ar 44100 clip_raw.wav
```

### 2. Trim and normalize (Audacity)

1. Open `clip_raw.wav`.
2. Trim leading/trailing silence.
3. **Effect → Normalize** to about **−3 dB** peak (avoids hard clipping in the source WAV).
4. Export as **WAV** (16-bit mono or stereo).

No need to resample manually; the build resamples to **21024 Hz** (vanilla duel VO rate, **not** the m4a engine default of 13379 Hz), scales hot peaks down if needed, and converts to signed 8-bit mono for m4a.

### Optional: SoX preprocessing (FE-style)

Fire Emblem voice guides often preprocess with **SoX** before insertion. That step is optional here but useful for trimming silence and leveling volume before the WAV hits the manifest:

```bash
sox input.mp3 -r 21024 -b 16 -c 1 clip.wav silence 1 0.1 1% -1 0.1 1% norm -3
```

We do **not** use FE's `wav2agb` DPCM step — YGO duel voices go through **m4a Direct Sound** (raw PCM), not FE's compressed sample format.

### 3. Place the WAV

Save under `src_custom/assets/voices/<duelist>/<clip_id>.wav`, for example:

```text
src_custom/assets/voices/kaiba/turn_start_alt.wav
```

### 4. Register in the manifest

Add a row to [`tools/voice_manifest.json`](tools/voice_manifest.json) (see schema below).

### 5. Build and preview

```bash
make
```

Open the overworld debug menu → **Voice Viewer** to preview vanilla and custom clips.

Registered clip sizes are tracked in [`src_custom/assets/voices/VOICES.md`](../src_custom/assets/voices/VOICES.md) (auto-generated on `make`).

## Manifest Schema

File: [`tools/voice_manifest.json`](tools/voice_manifest.json)

| Field | Required | Description |
|-------|----------|-------------|
| `clip_id` | yes | Unique ID; used for generated symbol names |
| `duelist` | yes | `AI_DUELIST_*` from [`include/ai.h`](include/ai.h) |
| `wav` | yes | Path relative to `src_custom/assets/voices/` |
| `trigger` | yes | `turn_start`, `attack_card`, or `opponent_lp_below` |
| `card_id` | attack only | `CARD_*` from [`include/constants/card_ids.h`](include/constants/card_ids.h) |
| `lp_threshold` | LP only | Fire when **opponent** LP drops below this value |
| `title` | no | Debug menu label (≤ 15 visible chars) |
| `priority` | no | Higher wins when multiple clips match (default 0) |
| `replace_vanilla` | no | Reserved for future dual-play behavior (default false) |

Song IDs are allocated sequentially from `song_id_base` (default **601**).

## Triggers

| Trigger | When it fires | Notes |
|---------|---------------|-------|
| `turn_start` | Opponent turn begins | Hooks `TryPlayingMyTurnVoice`; custom match skips vanilla turn voice |
| `attack_card` | AI attacks with a specific card | Hooks `TryAttackVoicing` |
| `opponent_lp_below` | Opponent LP crosses below threshold | Hooks `UpdateLifePointsAfterAction`; **once per turn per clip** |

LP-threshold flags reset on `SwitchTurn`.

## Build Pipeline

[`tools/generate_voices.py`](tools/generate_voices.py) runs during `make` and emits:

| Output | Purpose |
|--------|---------|
| `src_custom/generated/voice_assets_generated.s` | m4a PCM + song blobs (`.append_assets`) |
| `src_custom/generated/voice_triggers_generated.inc` | Runtime trigger + song pointer tables |
| `src_custom/generated/voice_song_headers_generated.inc` | `SongHeader` externs + pointer table for playback |
| `src_custom/generated/voice_rom_patches.json` | Tone/song-table/mode ROM patch specs |
| `src_custom/generated/debug_menu_voice_custom.inc` | Debug menu rows |
| `include/constants/custom_voices_generated.h` | Song ID `#define`s and structs |

Custom clips play via `PlayCustomVoiceClip()`, which copies the part track and builds the song header in EWRAM then calls `m4aSongNumStart()` (not `PlayMusic()` — vanilla `PlayMusic()` rejects song IDs ≥ 800). Build-time ROM patches point the tone table at main-ROM WaveData and the song table at the EWRAM header offset.

## Runtime Behavior

```text
Manifest + WAV  →  generate_voices.py  →  append ROM assets
                                              ↓
Duel hook (turn / attack / LP)  →  lookup sCustomVoiceClips  →  PlayCustomVoiceClip()
                                              ↓
                                    (no match) → vanilla gTurnVoices / gB0AE8 table
```

## Debug Menu

The **Voice Viewer** lists vanilla clips from `debug_menu_voice_table.inc` plus generated custom rows. Custom entries (song ID ≥ 601) use `PlayCustomVoiceClip()` instead of `PlayMusic()`.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Manifest | `tools/voice_manifest.json` | Authoring source of truth |
| Generator | `tools/generate_voices.py` | WAV → m4a + codegen |
| PCM assets | `src_custom/generated/voice_assets_generated.s` | Linked append assets |
| Trigger engine | `src_custom/duel_voice_hooks.c` | Turn, attack, LP hooks + playback |
| Generated tables | `src_custom/generated/voice_triggers_generated.inc` | Clip metadata and song pointers |
| Song IDs | `include/constants/custom_voices_generated.h` | Generated constants |
| LP turn state | `gCustomVoiceLpFiredThisTurn` in `asm/ram_map.s` | Once-per-turn LP flags (64 bytes max) |
| LynJump wiring | `src_custom/LynJump.event` | Patches vanilla duel functions |
| Debug preview | `src_custom/debug/debug_menu_voice.c` | Voice Viewer integration |
| Makefile rule | `Makefile` | `VOICE_*` generator + asset object |

## TODO

- [ ] Add Pegasus / other duelists once `AI_DUELIST_*` IDs are confirmed for them.
- [ ] Optional build-time patch of unused m4a song table slots (currently uses direct `sub_8059D7C` playback).
- [ ] `replace_vanilla` dual-play semantics if both custom and vanilla should overlap.

## Limitations & Bugs

- **No DPCM / wav2agb** — unlike FE8 buildfile voice intros, this project uses vanilla **m4a** raw PCM (`WaveData` + tone/song tables). FE's `wav2agb -c` output is not compatible without replacing the sound engine.
- **Placeholder WAVs** ship for the Kaiba vertical slice; replace with real extracted lines before release.
- **`TryPlayingMyTurnVoice` and `UpdateLifePointsAfterAction` are static** in vanilla source; LynJump patches use computed ROM offsets rather than ELF symbols.
- **LP trigger** only fires on opponent LP **decrease** after battle damage resolution, not on LP gain or heal effects.
- **Custom song IDs** (601+) cannot use `PlayMusic()` directly; always use `PlayCustomVoiceClip()` or the debug menu path.
