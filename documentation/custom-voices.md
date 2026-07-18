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

This project supports **custom duelist voice clips** for story and AI duelists. Clips are additive: vanilla voice lines remain unless a custom clip matches the same trigger for that duelist.

Clips are stored as **wav2agb-compatible DPCM** in m4a `WaveData` blobs (same engine family as vanilla duel voicing). A JSON manifest drives code generation; `make` converts source WAV files and wires duel hooks automatically.

## Audio Format

Vanilla duelist VO uses m4a Direct Sound, not MP3/OGG in ROM.

| Property | Value |
|----------|-------|
| In-ROM format | **DPCM** in m4a `WaveData` (`type` 1; wav2agb mono layout) |
| Playback | ITCM decoder expands DPCM → signed 8-bit PCM in **EWRAM**, then m4a Direct Sound |
| Target sample rate | **21024 Hz** (resampled at build time; matches vanilla `WaveData.freq` `0x01488000`) |
| Effective ROM bitrate | ~**84 kbps** DPCM (~50% of raw 8-bit PCM at 21024 Hz) |
| Authoring input | **WAV** (16-bit mono or stereo; stereo is downmixed) |
| Pre-build conversion | Resample → peak normalize → **edge silence trim** → 8-bit PCM → DPCM encode |
| ROM placement | **Main ROM** (`.voice_pcm_rom` @ `0x08FE3400`, grows until append) holds WaveData + part tracks + song headers; appended code follows at `__append_start`; **EWRAM** (`gCustomVoiceBlob`) holds the runtime song header, part track, and decode buffer at playback |
| Turn-start target | ≤ **2 s** authored; vanilla reference ~0.7–1.1 s |
| Attack/card target | ≤ **4 s** authored; vanilla reference ~2.0–2.5 s |

Vanilla reference sizes (from baserom analysis; durations assume **21024 Hz** playback, **uncompressed** PCM in ROM):

| Clip type | Size (vanilla PCM) | Duration @ 21024 Hz |
|-----------|-------------------|---------------------|
| Turn start | 14–22 KB | ~0.7–1.1 s |
| Card attack | 40–53 KB | ~2.0–2.5 s |

Custom clips at the same rate typically land around **half** those byte counts in ROM thanks to DPCM. See [`src_custom/assets/voices/VOICES.md`](../src_custom/assets/voices/VOICES.md) for per-clip source vs in-ROM sizes.

## Authoring Workflow

### 1. Extract source audio

Demux or capture audio with ffmpeg:

```bash
ffmpeg -i episode.mkv -vn -acodec pcm_s16le -ar 44100 clip_raw.wav
```

### 2. Trim and normalize (Audacity)

1. Open `clip_raw.wav`.
2. Trim leading/trailing silence (the build also trims near-silence at edges; manual trim still helps).
3. **Effect → Normalize** to about **−3 dB** peak (avoids hard clipping in the source WAV).
4. Export as **WAV** (16-bit mono or stereo).

No need to resample manually; the build resamples to **21024 Hz** (vanilla duel VO rate, **not** the m4a engine default of 13379 Hz), applies optional `gain_db`, peak-normalizes, trims edge silence, and encodes DPCM.

### Optional: SoX preprocessing

Fire Emblem voice guides often preprocess with **SoX** before insertion. That step is optional here but useful for trimming silence and leveling volume before the WAV hits the manifest:

```bash
sox input.mp3 -r 21024 -b 16 -c 1 clip.wav silence 1 0.1 1% -1 0.1 1% norm -3
```

The build uses the same **wav2agb DPCM layout** as FE's `wav2agb -c` output, but encodes in-tree via [`tools/generate_voices.py`](tools/generate_voices.py) and plays through the **m4a** tone/song path (not FE's sound driver).

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

Registered clip sizes are tracked in [`src_custom/assets/voices/VOICES.md`](../src_custom/assets/voices/VOICES.md) (regenerated with the voice pipeline when inputs change).

## Manifest Schema

File: [`tools/voice_manifest.json`](tools/voice_manifest.json)

| Field | Required | Description |
|-------|----------|-------------|
| `clip_id` | yes | Unique ID; used for generated symbol names |
| `duelist` | yes | `AI_DUELIST_*` from [`include/ai.h`](include/ai.h) and/or `DUELIST_*` from [`include/overworld.h`](include/overworld.h) (JSON array allowed) |
| `wav` | yes | Path relative to `src_custom/assets/voices/` |
| `trigger` | yes | `turn_start`, `attack_card`, or `opponent_lp_below` |
| `card_id` | attack only | `CARD_*` from [`include/constants/card_ids.h`](include/constants/card_ids.h) |
| `lp_threshold` | LP only | Use this clip for **turn_start** while **opponent** LP is strictly below this value |
| `title` | no | Debug menu label (≤ 15 visible chars) |
| `turn_text` | no | Replaces the opponent-turn duel textbox line (e.g. vanilla “It's my turn.”). Only on `turn_start` / `opponent_lp_below`; uses the same LP rule as the voice clip. Plain ASCII; `\n` becomes a line break. All in-game languages show the same text; the textbox waits for A/B/R before the turn continues. |
| `gain_db` | no | Per-clip loudness boost/cut in dB before peak normalization |
| `trim_silence` | no | Strip leading/trailing near-silence before DPCM (default **true**; manifest-level default supported) |
| `trim_silence_threshold` | no | \|s8\| sample magnitude treated as silence at edges (default **8**) |
| `priority` | no | Higher wins when multiple clips match (default 0) |
| `replace_vanilla` | no | Reserved for future dual-play behavior (default false) |

Song IDs are allocated sequentially from `song_id_base` (default **601**).

## Triggers

| Trigger | When it fires | Notes |
|---------|---------------|-------|
| `turn_start` | Opponent turn begins | Hooks `OpponentTurnTextAndVoice` (voice + optional `turn_text`) |
| `attack_card` | AI attacks with a specific card | Hooks `TryAttackVoicing` |
| `opponent_lp_below` | Alternate **turn_start** while opponent LP is below `lp_threshold` | Same hook; swaps voice and `turn_text` when low on LP |

## Build Pipeline

[`tools/generate_voices.py`](tools/generate_voices.py) runs during `make` when the manifest, generator, headers, or any voice WAV changes (tracked via `build/.voice_generated.stamp`). Per-clip DPCM payloads are cached under `.cache/voice_dpcm/` (kept by `make clean-build`; removed by `make clean-cache` or full `make clean`). It emits:

| Output | Purpose |
|--------|---------|
| `src_custom/generated/voice_assets_generated.s` | DPCM WaveData + part tracks + song headers (`.voice_pcm_rom`) |
| `src_custom/generated/voice_triggers_generated.inc` | Runtime trigger + song pointer tables |
| `src_custom/generated/voice_turn_text_generated.inc` | Optional `turn_text` string blobs |
| `src_custom/generated/voice_song_headers_generated.inc` | `SongHeader` externs + pointer table for playback |
| `src_custom/generated/voice_rom_patches.json` | Tone/song-table/mode ROM patch specs |
| `src_custom/generated/debug_menu_voice_custom.inc` | Debug menu rows |
| `include/constants/custom_voices_generated.h` | Song ID `#define`s and structs |
| `src_custom/assets/voices/VOICES.md` | Source vs in-ROM size inventory |

Pipeline per clip:

```text
WAV  →  resample 21024 Hz  →  gain_db  →  peak normalize  →  edge silence trim
  →  DPCM encode (wav2agb layout)  →  m4a WaveData + part track + song header
```

Custom clips play via `PlayCustomVoiceClip()`, which copies the part track, decodes DPCM into EWRAM, builds the song header, then calls `m4aSongNumStart()` (not `PlayMusic()` — vanilla `PlayMusic()` rejects song IDs ≥ 800). Build-time ROM patches point the tone table at main-ROM WaveData and the song table at the EWRAM header offset.

## Runtime Behavior

```text
Manifest + WAV  →  generate_voices.py  →  DPCM in .voice_pcm_rom
                                              ↓
Duel hook (turn / attack / LP)  →  lookup sCustomVoiceClips  →  PlayCustomVoiceClip()
                                              ↓
                         DPCM decode (ITCM) → EWRAM PCM → m4a Direct Sound
                                              ↓
                                    (no match) → vanilla gTurnVoices / gB0AE8 table
```

When `gRuntimeConfig.show_duel_voice_portraits` is TRUE (default) and a **turn-start** voice plays, the opponent's dialogue portrait is shown at the **top-left** for the duration of the turn textbox. Mini-card / cursor OAM is hidden while it is up (portrait tiles share OBJ VRAM with board cards). Attack voicing is audio-only and does not show a portrait yet. Toggle via debug menu → Runtime Config → **Voice Port**.

While a **custom** opponent voice clip plays, duel BGM is ducked to `duel_voice_bgm_volume_percent` (default **70**). Volume restores when the voice player goes idle (checked on each duel graphics refresh). Set the percent to **100** to disable. Vanilla turn/attack lines that take over the music player are unchanged.

## Debug Menu

The **Voice Viewer** lists vanilla clips from `debug_menu_voice_table.inc` plus generated custom rows. Custom entries (song ID ≥ 601) use `PlayCustomVoiceClip()` instead of `PlayMusic()`.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Manifest | `tools/voice_manifest.json` | Authoring source of truth |
| Generator | `tools/generate_voices.py` | WAV → DPCM + codegen |
| DPCM decode | `src_custom/voice_dpcm_itcm.s` | ITCM hook for m4a PCM read |
| ROM assets | `src_custom/generated/voice_assets_generated.s` | Linked `.voice_pcm_rom` |
| Trigger engine | `src_custom/duel_voice_hooks.c` | Turn, attack, LP hooks + playback + optional voice portrait + BGM duck |
| Opponent→portrait | `src_custom/duel_voice_portrait_table.inc` | `DUELIST_*` → `PORTRAIT_*` lookup |
| Generated tables | `src_custom/generated/voice_triggers_generated.inc` | Clip metadata and song pointers |
| Song IDs | `include/constants/custom_voices_generated.h` | Generated constants |
| LynJump wiring | `src_custom/LynJump.event` | Patches vanilla duel functions |
| Debug preview | `src_custom/debug/debug_menu_voice.c` | Voice Viewer integration |
| BGM duck config | `duel_voice_bgm_volume_percent` in `configs/runtime.c` | Percent of normal BGM volume during custom VO (100 = off) |
| BGM duck restore | `UpdateDuelBgmVoiceDuck` via `sub_80411D4__Replacement` | Restores full volume when voice player 3 is idle |
| Makefile rule | `Makefile` | `VOICE_*` generator + asset object |

## TODO

- [ ] Add Pegasus / other duelists once `AI_DUELIST_*` IDs are confirmed for them.
- [ ] Optional build-time patch of unused m4a song table slots (currently uses direct `sub_8059D7C` playback).
- [ ] `replace_vanilla` dual-play semantics if both custom and vanilla should overlap.
- [ ] Portrait during attack voicing (needs timed hide; no textbox).

## Limitations & Bugs

- **DPCM only in ROM** — playback quality matches signed 8-bit @ 21024 Hz; DPCM is lossy but tuned for speech. Disabling `trim_silence` keeps full WAV length in ROM.
- **Edge trim only** — build-time silence removal does not cut internal pauses; trim those in Audacity/SoX if needed.
- **`OpponentTurnTextAndVoice` is static** in vanilla source; LynJump patches use computed ROM offsets rather than ELF symbols.
- **`opponent_lp_below`** replaces the normal `turn_start` line for that duelist once opponent LP is below the threshold; it does not play mid-battle. If LP rises back above the threshold (heal), the normal `turn_start` clip is used again.
- **Custom song IDs** (601+) cannot use `PlayMusic()` directly; always use `PlayCustomVoiceClip()` or the debug menu path.
- **Voice portraits** only wrap turn-start textboxes; `UpdateDuelGfxExceptField` clears the OAM slot when the textbox closes.
