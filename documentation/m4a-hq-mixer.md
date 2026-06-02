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

This build integrates [ipatix/gba-hq-mixer](https://github.com/ipatix/gba-hq-mixer) (rev 4.0, GPLv3) in place of the vanilla m4a Direct Sound mixer. At boot, `sub_80595C4` copies the HQ mixer blob from append ROM into `MixerBuffer` in IWRAM (linker-placed via `asm/ram_map.s`), and `SoundMain` branches into that buffer instead of the vanilla `0x03000000` slot.

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
| `M4A_HQ_MIXER_IW_RAM_BYTES` | `0xC00` | Reserved headroom for `MixerBuffer` |

`gM4aHqMixBuffer` and `MixerBuffer` are allocated from IWRAM free space via `asm/ram_map.s` (~2.1 KiB total HQ overhead). `MixerSize` is computed automatically in `asm/m4a_hq_mixer.s`.

`g3000400` (the `IntrMain` IWRAM stub) stays at the vanilla address `0x03000400`; the HQ mixer no longer occupies low IWRAM. See `documentation/iwram-free-space.md`.

## Code locations

| Piece | Path |
|-------|------|
| Mixer source | `asm/m4a_hq_mixer.s` |
| Config | `asm/m4a_hq_mixer_config.inc` |
| Public API | `include/m4a_hq_mixer.h` |
| ROM patch | `tools/apply_lynjump.py` (`apply_m4a_hq_mixer_patches`) |

At boot, vanilla `sub_80595C4` still runs unchanged. After linking, `apply_lynjump.py` retargets its `CpuSet` literal pool (`$59618` / `$5961C` / `$59620`) so the mixer ROM source is `M4aHqMixerIwramStart` in append space, the destination is `MixerBuffer`, and the copy size covers the full HQ blob (~`0xB24` bytes). It also patches `SoundMain`'s IWRAM entry (`$58988`) to `MixerBuffer + 1`.

## Custom voices

Custom duelist clips remain **DPCM in main ROM** with tone-table patches and `m4aSongNumStart()` playback (`src_custom/voice_dpcm.c`). No large EWRAM PCM decode buffer is required: the HQ mixer reads DPCM from ROM like vanilla, with cleaner mixing when multiple voices play.

The HQ mix buffer is zeroed at the start of each frame before channels accumulate into it.

Uncompressed BGM PCM (key-split percussion on Clock Tower Square and Your Home) keeps full channel volume; only `MODE_COMP` / DPCM paths halve volume before interpolation, matching vanilla balance against the CGB layers.

## License

`asm/m4a_hq_mixer.s` is GPLv3 (see upstream `LICENSE.txt`). The rest of this project remains under its existing license; ensure compliance if you redistribute ROMs built with the mixer enabled.
