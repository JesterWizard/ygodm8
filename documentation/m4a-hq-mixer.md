# m4a HQ Mixer (ipatix)

---

## Index

- [Introduction](#introduction)
- [What it does](#what-it-does)
- [Configuration](#configuration)
- [Code locations](#code-locations)
- [Custom voices](#custom-voices)
- [License](#license)

## Introduction

This build integrates [ipatix/gba-hq-mixer](https://github.com/ipatix/gba-hq-mixer) (rev 4.0, GPLv3) in place of the vanilla m4a Direct Sound mixer that is copied to IWRAM at `0x03000000` during `sub_80595C4`.

The game runs m4a at **21024 Hz** (`m4aSoundMode(0x0097FC00)`), matching vanilla duel voice `WaveData.freq`.

## What it does

- Mixes voices in a **16-bit** intermediate buffer, then downsamples once to the 8-bit DMA buffers (less quantization noise than vanilla per-voice 8-bit mixing).
- Supports **DPCM type 1** waves directly from ROM (same family as vanilla duel VO and custom voice DPCM blobs).
- Optional **DMA** prefetch of ROM samples into stack scratch (enabled by default).
- Reverb path enabled (`ENABLE_REVERB = 1`) to stay close to vanilla behaviour.

## Configuration

Edit `asm/m4a_hq_mixer_config.inc`:

| Symbol | Value | Meaning |
|--------|-------|---------|
| `POKE_CHN_INIT` | `0` | Non-Pokémon channel init (this game) |
| `ENABLE_REVERB` | `1` | Apply reverb like vanilla |
| `ENABLE_DMA` | `1` | DMA ROM sample prefetch (disable if unstable) |
| `M4A_HQ_MIX_FRAME_SAMPLES` | `0x160` | Samples per VBlank @ 21024 Hz |
| `M4A_HQ_MIX_BUFFER_BYTES` | `0x580` | HQ mix buffer in IWRAM (`frame × 4`) |
| `M4A_HQ_MIXER_IW_RAM_BYTES` | `0xC00` | Max bytes copied to `0x03000000` |

`gM4aHqMixBuffer` is allocated from IWRAM free space via `asm/ram_map.s` (~1.4 KiB total HQ overhead).

The mixer IWRAM image is ~0xAB8 bytes (vanilla was ~0x400). That span must not overlap `g3000400` (the `IntrMain` IWRAM stub). `ldscript.ld` places `g3000400` at `0x03001A00` instead of `0x03000400` for that reason. See `documentation/iwram-free-space.md`.

## Code locations

| Piece | Path |
|-------|------|
| Mixer source | `asm/m4a_hq_mixer.s` |
| Config | `asm/m4a_hq_mixer_config.inc` |
| Public API | `include/m4a_hq_mixer.h` |
| ROM patch | `tools/apply_lynjump.py` (`apply_m4a_hq_mixer_patches`) |

At boot, vanilla `sub_80595C4` still runs unchanged. After linking, `apply_lynjump.py` retargets its `CpuSet` literal pool (`$59618` / `$59620`) so the mixer ROM source is `M4aHqMixerIwramStart` in append space and the copy size covers the full HQ blob (~0xAB8 bytes) instead of the stock `0x08058999` / `0x04000100` (~1 KiB).

## Custom voices

Custom duelist clips remain **DPCM in main ROM** with tone-table patches and `m4aSongNumStart()` playback (`src_custom/voice_dpcm.c`). No large EWRAM PCM decode buffer is required: the HQ mixer reads DPCM from ROM like vanilla, with cleaner mixing when multiple voices play.

## License

`asm/m4a_hq_mixer.s` is GPLv3 (see upstream `LICENSE.txt`). The rest of this project remains under its existing license; ensure compliance if you redistribute ROMs built with the mixer enabled.
