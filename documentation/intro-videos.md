# Intro Videos

---

## Index

- [Introduction](#introduction)
- [How it works](#how-it-works)
- [Adding a video](#adding-a-video)
- [Code locations](#code-locations)
- [Build pipeline](#build-pipeline)
- [TODO](#todo)
- [Limitations & bugs](#limitations--bugs)

---

## Introduction

The intro video player plays a short MP4 video on the title screen after 5 seconds of idle time. When a button is pressed during the video, playback stops immediately and the idle timer resets. After the video ends (or is skipped), the idle timer resets and the title screen remains active — another 5-second idle period triggers the video again.

This gives the title screen a subtle screensaver-like behaviour: the game shows a looping intro video whenever the player leaves it unattended.

## How it works

### Idle detection

The vanilla title screen calls `sub_80357F8()` in its idle loop (both `TitleScreenChooseOption` and `TitleScreenNewGameOnly` paths). The existing LynJump replacement `sub_80357F8__Replacement` in `src_custom/title_screen_hooks.c` has been extended to:

1. Run the vanilla idle animation function
2. Increment `gTitleScreenIdleFrames` (a u16 counter in EWRAM)
3. When the counter reaches 300 (~5 seconds at 60fps) and `enable_title_screen_video` is TRUE, call `VideoPlayer_Play()`
4. After the video returns, reset the counter to 0

### Video playback

`VideoPlayer_Play()` takes over the display:

1. Sets the VBlank callback to `VideoPlayer_VBlank`, which decompresses one frame per VBlank from ROM into an EWRAM buffer, copies the tiles to BG3 charblock 0, loads the frame palette, and sets up BG3 for fullscreen display
2. Main loop: sleeps for `fpsDivider` frames between frame advances, checks for button presses
3. Any button press during the loop aborts playback early
4. On completion or abort, restores the VBlank callback and returns

### Frame format

Each video is a binary blob with this layout:

| Offset | Size | Field |
|--------|------|-------|
| 0 | 2 | `u16 frame_count` |
| 2 | 1 | `u8 fps_divider` (VBlanks per frame; 2 = 30fps) |
| 3 | 1 | reserved |
| 4 | `frame_count * 8` | Frame index table |
| ... | varies | LZSS-compressed frame data |
| ... | `frame_count * 32` | Frame palettes (16 colors x 2 bytes each) |

Each frame index entry is 8 bytes: `u32 offset`, `u16 compressed_size`, `u16 palette_offset`. All offsets are relative to the blob start.

## Adding a video

1. Place an `.mp4` file in `src_custom/assets/videos/` (e.g. `src_custom/assets/videos/intro.mp4`)
2. Enable `enable_title_screen_video = TRUE` in `configs/runtime.c`
3. Rebuild: `make`
4. The encode tool (`tools/encode_video.py`) uses ffmpeg to extract frames at 30fps and quantize to 16 colors

The video player always plays the first entry in `sVideoAssets[]`. If multiple MP4s exist, only the first one (alphabetically) is used.

## Code locations

| Component | Location | Description |
|-----------|----------|-------------|
| Idle detection | `sub_80357F8__Replacement` in `src_custom/title_screen_hooks.c` | Increments idle counter and triggers video playback |
| Playback engine | `VideoPlayer_Play`, `VideoPlayer_VBlank` in `src_custom/video_player.c` | Main loop and VBlank frame-streaming callback |
| RAM allocation | `asm/ram_map.s` | `gTitleScreenIdleFrames` (u16), `gVideoPlayerState` (2 bytes), `gVideoPlayerFrameBuf` (0x4B00 bytes EWRAM) |
| Runtime toggle | `enable_title_screen_video` in `configs/runtime.h` / `configs/runtime.c` | Compile-time toggle, defaults to FALSE |
| Asset encoding | `tools/encode_video.py` | ffmpeg pipeline: MP4 -> indexed PNGs -> 4bpp GBA tiles -> LZSS compression -> binary blob |
| Generated include | `src_custom/generated/video_assets_generated.inc` | `sVideoAssets[]` table with symbols for each video |
| Build wiring | `Makefile`, `graphics.mk` | Generator stamp, object dependency, clean targets |

## Build pipeline

```
make
  -> python3 tools/encode_video.py
     -> ffmpeg extracts frames from *.mp4 in src_custom/assets/videos/
     -> quantizes to 16 colors, converts to 4bpp GBA tiles
     -> LZSS-compresses each frame
     -> outputs src_custom/generated/video_assets_generated.inc
  -> compile video_player.c (depends on generated include)
  -> link, apply LynJump patches
```

If no MP4s exist, the generator produces a stub with `VIDEO_COUNT 0` and an empty assets table, so the build does not fail.

## TODO

- Support multiple videos with a shuffle/rotation between idle cycles
- Per-frame palette (higher quality at the cost of more ROM space)
- Allow configuring the idle timeout in `RuntimeConfig` (currently hardcoded at 300 frames)
- Configurable target fps per video

## Limitations & bugs

- The frame buffer is 0x4B00 bytes, suitable for 240x160 4bpp tile data only. Changing the resolution or bit depth requires updating this buffer size.
- The encode tool's LZSS Python fallback is slower than the native gbagfx tool. For more than ~200 frames, install and use gbagfx for compression.
- ffmpeg is required in PATH to encode videos. No video is encoded at build time without it; the build silently produces a stub include.
- The player only supports one active video (first in alphabetical order). Adding multiple means dropping MP4s into `assets/videos/` and updating the player to cycle or select.
- Button checks use a direct read from `REG_KEYINPUT` rather than the frame-synced `gNewButtons`, so a very brief button press during a VBlank window could be missed. In practice, holding any button for 1+ frames is reliably detected.
- Palette is global (per-video) rather than per-frame. Per-frame palettes would reduce banding at the cost of ~1.9KB per frame extra for palette data (and slightly more complex palette loading in the VBlank callback).
- The RGB to 15-bit BGR conversion in `_read_palette_from_png` assumes 8-bit colour components, which is standard for most MP4 content.
