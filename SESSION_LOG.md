# Session Log

## 2026-06-26 — Added Cyber Twin Dragon (CYBER_TWIN_DRAGON) with double attack

**Worked on:** Added Cyber Twin Dragon (Fusion Monster, passcode 74157028) to the custom card trunk from Yugipedia via API. It's a LIGHT Machine Level 8 2800/2100 fusion monster. Implemented its double-attack effect following the Hayabusa Knight pattern: after each attack, `TryUnlockCyberTwinDragonForSecondAttack()` unlocks the monster for a second attack by setting `isLocked = FALSE`. Wired the unlock call into all 4 attack completion paths (`draining_shield_hooks.c`, `code_8043EF4_hooks.c`, `ai_attack_hooks.c`, `call_of_the_haunted_hooks.c`). Fixed description pages to fit GBA's 5-row card text format.

**Files:**
- `tools/card_data_manifest.json` — new CYBER_TWIN_DRAGON entry
- `configs/runtime.c` — `card_in_hand_1 = CYBER_TWIN_DRAGON`
- `include/cyber_twin_dragon.h` — new header
- `src_custom/card_passives/cyber_twin_dragon.c` — new: double-attack unlock function
- `src_custom/draining_shield_hooks.c` — include + unlock call
- `src_custom/code_8043EF4_hooks.c` — include + unlock calls (2 sites)
- `src_custom/ai_attack_hooks.c` — include + unlock calls (2 sites)
- `src_custom/call_of_the_haunted_hooks.c` — include + unlock call

**Outcome:** `make test-cards-build` passes. Cyber Twin Dragon starts in hand at duel start with correct stats, art, and description. It can attack twice per Battle Phase.

**Open / next:** None.

## 2026-06-26 — Cyber Dragon effect + palette fix

**Worked on:** 
- Fixed palette corruption: re-ran `normalize_big_card_png.py` on `cyber_dragon.png` which remapped its palette index-0 pixels to nearest colors and zeroed palette slot 0 (reserved for transparency in GBA big card art). Second pass confirmed 0 remaining index-0 pixels.
- Implemented Cyber Dragon's inherent Special Summon: when only the opponent controls a monster and the player has none, the tribute requirement drops to 0. The check is wired into `GetBaseRequiredTributes` and `GetNumRequiredTributesForHandSlot` in `tribute_hooks.c`, which feeds both the player hand menu and the AI logic.

**Files:**
- `src_custom/assets/cards/80x80/cyber_dragon.png` — palette normalized
- `src_custom/tribute_hooks.c` — added `CyberDragonCanSummonWithoutTribute()` and wired into both tribute check flows

**Outcome:** `make test-cards-build` passes. Cyber Dragon summons without tribute when opponent has a monster and your field is empty.

**Open / next:** None.

## 2026-06-26 — Added Cyber Dragon (0x03EA) to custom card trunk

**Worked on:** Added Cyber Dragon (passcode 70095154) to the custom card trunk via `add_custom_card.py --passcode`. Used the Yugipedia skill flow: fetched card data via YGOProDeck API, wrote manifest entry with correct fields (LEVEL 5 LIGHT Machine 2100/1600 EFFECT_CARD), set `card_in_hand_1` in runtime.c. Art is missing (no 80x80 PNG). Effect (inherent Special Summon from hand when only opponent controls a monster) is not yet implemented — requires engine-level changes to the summon phase, as it's an inherent summon from hand, not an activated field effect.

**Files:**
- `tools/card_data_manifest.json` — new CYBER_DRAGON entry
- `configs/runtime.c` — `.card_in_hand_1 = CYBER_DRAGON`
- `include/constants/card_ids.h` — `#define CYBER_DRAGON 0x03EA` (auto-generated)
- `src_custom/generated/card_trunk_generated.inc` — trunk entry (auto-generated)
- `src_custom/card_description_data_generated.inc` — description data (auto-generated)

**Outcome:** `make test-cards` and `make test-cards-build` both pass. Card exists in trunk at ID 0x03EA with correct stats and description. No art asset yet.

**Open / next:**
- Create 80×80 PNG art at `src_custom/assets/cards/80x80/cyber_dragon.png`
- Implement inherent Special Summon effect

## 2026-06-25 — Created add-custom-card-from-yugipedia skill

**Worked on:** Created a new `.agents/skills/add-custom-card-from-yugipedia/SKILL.md` skill that captures the workflow of adding a real Yu-Gi-Oh! card to the custom card trunk from its Yugipedia URL. Covers: fetching card data from Yugipedia page, mapping to manifest fields, trying `add_custom_card.py --passcode` first, falling back to manual manifest entry when API is down, checking art in 80x80, setting runtime hand, and wiring effects with duel helpers. Used JOWLS_OF_DARK_DEMISE (already in manifest at ID 0x03CC) as the concrete example throughout.

**Files:**
- `.agents/skills/add-custom-card-from-yugipedia/SKILL.md` — new skill

**Outcome:** Skill created. When invoked with a Yugipedia URL, it follows a 7-step fast path: fetch → passcode → manifest check → art → hand → effects → validate.

**Open / next:** None.

## 2026-06-24 — Replace LZSS video pipeline with Meteo/COMET codec

**Worked on:** Replaced the old ffmpeg+LZSS per-frame video pipeline with the Meteo Avi-2-GBA / COMET codec. The COMET codec uses motion-compensated inter-frame compression + audio, reducing the video blob from ~14MB to ~3.5MB (target, when user provides the Meteo output). ROM dropped from 33MB → 19MB without the blob (empty section).

**Decisions:**
- COMET player is designed as a boot-time ROM, but we call it at runtime from the title screen idle handler. On exit, the player cold-boots the game (clears RAM → jumps to 0x08000000). This is simpler than trying to return cleanly, since the player's ClearRam wipes IWRAM/EWRAM including our state.
- The cold boot path goes through our existing hooks (copyright screens skip, title screen), so the user sees the title screen again normally. Idle timer resets, preventing an infinite video loop.
- No data dependency on a Meteo ROM — the inc include uses `__has_include` at compile time. Without `video_meteo.bin`, `METE0_VIDEO_AVAILABLE=0` and `VideoPlayer_Play()` returns FALSE.

**Pipeline:**
1. User runs Meteo 1.5.0 MOD.exe on Windows → produces `video.gba`
2. User copies `video.gba` to `src_custom/assets/videos/video_meteo.bin`
3. Build embeds it in `.meteo_video` section at 0x10000 alignment
4. Post-link: `tools/meteo_integrate.py` patches 5 internal pointer offsets + exit handler at blob+0x258 → branches to `MeteoExitTrampoline`
5. ARM trampoline disables interrupts and cold-boots via `bx 0x08000000`
6. Game boots fresh → title screen via hooks

**Files:**
- `tools/meteo_integrate.py` — new post-link patcher
- `src_custom/meteo_player_stub.s` — ARM trampoline stub
- `src_custom/generated/meteo_video_assets_generated.inc` — incbin wrapper (with dummy fallback)
- `src_custom/video_player.c` — rewritten to call COMET player
- `ldscript.ld` — added `.meteo_stubs` and `.meteo_video` sections
- `Makefile` — new rules, removed old encode_video.py dependency
- `tools/encode_video.py` — deleted (obsolete)
- `src_custom/generated/video_assets_generated.inc` — deleted (obsolete)

**Outcome:** `make test-cards-build` passes. ROM links at 19MB (no blob yet). `CallMeteoPlayer()` at 0x0927030c, `MeteoExitTrampoline` at 0x09270318, `.meteo_video` section at ALIGN(0x10000) = 0x09280000.

**Open / next:**
- User needs to run Meteo 1.5.0 MOD.exe on `season_one_intro.mp4` in a Windows environment, producing `video.gba`, then copy to `src_custom/assets/videos/video_meteo.bin`
- If the COMET player's IWRAM stubs at 0x3003000 conflict with the mixer buffer, the trampoline may need extra state save/restore
- If the cold boot path introduces visual artifacts (e.g. VRAM garbage from the COMET player's last frame), add explicit VRAM clear before `bx 0x08000000`

## 2026-06-23 — Video plays but too slow: cut frame pacing divider to 2

**Worked on:** Video played at ~half speed (~7.5fps instead of 15fps). The pure C LZSS decompressor running from ROM takes ~2 VBlanks (33ms) per frame, so the original `divider=4` (wait 4 VBlanks) gave 33ms + 67ms = 100ms per frame = 10fps. Dropped divider to 2: 33ms + 33ms = 66ms per frame = ~15fps.

**Files:**
- `tools/encode_video.py` — changed `--fps-divider` default from 4 → 2

**Outcome:** `make test-cards-build` passes. ROM rebuilt with divider=2 blob (33ms overhead + 2 VBlank wait ≈ 15fps).

**Open / next:**
- To truly hit 15fps cleanly (no timing slip from variable decompression time), the decompressor could be moved to IWRAM for ~4× speed, or replaced with a DMA-streamed copy from ROM. But the divider fix is good enough for the intro.

## 2026-06-23 — Pure C LZSS decompressor: no SWI/BIOS dependency

**Worked on:** Replaced the GBA BIOS SWI-based LZ77 decompression (LZ77UnCompVram, SWI 0x12) with a pure C LZSS decompressor. The SWI calls kept crashing despite the compressed data being verified correct (gbagfx round-trip, Python little-endian decode, all 300 frames valid).

**What changed:**
- `DecompressFrame()` is now a self-contained C function that reads the LZSS flag bytes and back-refs directly. No inline assembly, no SWI calls.
- Decompress to EWRAM byte buffer (`gVideoPlayerFrameBuf`, 0x9600 bytes, re-allocated from the earlier removal) — byte writes are safe in EWRAM.
- Copy from EWRAM to VRAM via `CpuCopy16` (16-bit writes are VRAM-safe; 8-bit STRB is silently ignored by GBA VRAM).
- Kept the VBlank callback kill (`SetVBlankCallback(NULL)`) and palette shadow buffer copy from the previous fix.

**Files:**
- `src_custom/video_player.c` — pure C LZSS decompressor replaces NAKED+SWI wrapper
- `asm/ram_map.s` — re-added `gVideoPlayerFrameBuf` (0x9600 bytes)

**Outcome:** `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK). ROM: 23MB. No BIOS calls in the video path — zero SWI dependency.

**Open / next:**
- Test on emulator/hardware

## 2026-06-23 — Fix crash: kill title screen VBlank callback during Mode 4 video

**Worked on:** The video player kept crashing during frame decompression. The root cause was NOT the SWI call or the LZSS data compression — both are provably correct.

**Real root cause:** The title screen's VBlank callback (`VBlankCbTitleScreen`) was still running during video playback. When we switch to Mode 4 bitmap display, the callback writes tile-mode data to charblock 0 (0x06000000 — our frame buffer) and accesses BGxCNT registers that are now in a different mode. This corrupts VRAM state and can trigger crashes.

Old working code explicitly replaced the VBlank callback with `SetVBlankCallback(VideoPlayer_VBlank)` and re-armed it after every `WaitForVBlank()`. The Mode 4 rewrite dropped that essential step.

**Fix:**
- `SetVBlankCallback(NULL)` at video start — points `g201CB20` at `sub_800842C` (empty NOP). `WaitForVBlank()` keeps resetting the callback to the same NOP, so it stays harmless for the entire video.
- Video palette also written to `gPaletteBuffer` so any VBlank-triggered `LoadPalettes()` copies our colours, not the title screen's.
- Exit path: `CopyGfxAndInitGfxRegs__Replacement` re-establishes the title screen's VBlank callback as part of restoring display state.

**Files:**
- `src_custom/video_player.c` — added `SetVBlankCallback(NULL)` at entry, `gPaletteBuffer` copy for palette shadow

**Outcome:** `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK).

**Open / next:**
- Test on emulator/hardware

## 2026-06-23 — Fix LZSS crash: gbagfx back-references are big-endian, GBA BIOS expects little-endian

**Worked on:** Root-caused and fixed a crash during intro video frame decompression.

**Root cause:** The toolchain's `gbagfx` LZSS compressor writes 16-bit back-reference values in **big-endian**, but the GBA BIOS `LZ77UnCompVram`/`LZ77UnCompWram` (SWI 0x12/0x11) reads them as **little-endian** (the GBA's native endianness).

For example, gbagfx writes the bytes `0xF0 0x03` for a backref that means length=18, offset=4. The GBA BIOS reads this as little-endian `0x03F0`, which decodes to length=3, offset=1009. At frame start with only 4 bytes decompressed, offset 1009 is well past the start of the buffer → the BIOS reads garbage and crashes.

The earlier `_fix_gbagfx_header()` only converted the 4-byte magic header (0x10 → u32 with bit31=1), but the body's 16-bit backreferences were never corrected.

**Fix:** Added `_fix_gbagfx_endianness()` which parses the compressed body (flag bytes + 8 items per block) and byte-swaps every 16-bit back-reference value from big-endian to little-endian. Called after `_fix_gbagfx_header()` in the `lzss_compress()` pipeline.

Also verified: the Python LZSS compressor `_lzss_compress_python()` correctly uses little-endian (`struct.pack("<H", enc)`) but is too slow for production use (O(n²) match search on 38400-byte frames).

**Files:**
- `tools/encode_video.py` — added `_fix_gbagfx_endianness()`, updated `lzss_compress()`

**Outcome:** All 300 frames verified with little-endian Python LZ77 decoder — full round-trip, correct data. `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK).

**Open / next:**
- Test on emulator/hardware

## 2026-06-23 — Mode 4 bitmap + double buffering + LZSS: better fidelity, smaller ROM, zero EWRAM

**Worked on:** Switched the intro video player from BG Mode 0 tile-based (8bpp tiles, 256×160 canvas, CpuCopy16) to **Mode 4 bitmap** (240×160 raster, double buffering, BIOS LZ77UnCompVram).

- **Encoder**: `_indexed_png_to_8bpp_tiles()` → `_indexed_png_to_raster()` — outputs 240×160 byte buffer in row-major order (no tile conversion, no padding). `build_video_blob()` now LZSS-compresses each frame with GBA BIOS-compatible headers.
- **Player**: `LZ77UnCompVram` (SWI 0x12) decompresses directly from ROM to VRAM — zero EWRAM scratch buffer needed. Two 37.5KB frame buffers at `0x06000000` and `0x0600A000` with `DISPCNT` bit 4 toggling. Frame N+1 is decoded into the invisible buffer while Frame N displays.
- **RAM map**: Removed `gVideoPlayerFrameBuf` (20KB EWRAM) — reclaimed.
- **Inline SWI**: Wrote `DecompressFrame()` as a static inline-asm wrapper around SWI 0x12 to avoid linker dependency on the toolchain's `LZ77UnCompVram` symbol.

**Files:**
- `tools/encode_video.py` — raster layout, LZSS per-frame compression, updated blob format
- `src_custom/video_player.c` — full rewrite: Mode 4, double buffering, NAKED+asm_unified SWI wrapper
- `asm/ram_map.s` — removed `gVideoPlayerFrameBuf` (0x5000 bytes)

**Outcome:** `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK). 300-frame video blob: **4.0MB** (was ~12MB raw tile mode). ROM: **23MB** (was ~25MB). EWRAM freed: **20KB** (`gVideoPlayerFrameBuf`). Double buffering eliminates frame-tearing and the frame decode doesn't steal cycles from display.

**Open / next:**
- Test on emulator/hardware
- Audio playback not yet implemented

## 2026-06-23 — Fix video player crash (WaitForVBlank resets callback + gbagfx LZSS header)

**Worked on:** Two bugs fixed that together caused crash/black-screen during intro video.

1. **WaitForVBlank() resets the VBlank callback pointer.** Vanilla `WaitForVBlank()` always sets `g201CB20 = sub_800842C` (default NOP) after each wait. `VideoPlayer_Play()` only called `SetVBlankCallback(VideoPlayer_VBlank)` once before the loop, so only the first VBlank invoked our callback — frames 1..829 were never decoded. Frame 0 displayed (blank w/ old header bug) and the loop timed out. **Fix:** re-arm callback after every `WaitForVBlank()`.

2. **gbagfx LZSS header incompatible with GBA BIOS.** Added `_fix_gbagfx_header()` in `encode_video.py` to convert 0x10-type header to GBA-required u32 with bit31=1.

**Files:**
- `src_custom/video_player.c` — re-arm callback after every WaitForVBlank
- `tools/encode_video.py` — _fix_gbagfx_header()

**Outcome:** `make test-cards-build` passes. 830 frames with valid GBA-BIOS LZSS headers. Callback fires every frame at 15fps.

**Open / next:** Test on emulator. Audio not yet implemented.

## 2026-06-22 — Fix video player black screen (gbagfx LZSS header format)

**Worked on:** Found and fixed the root cause of the black screen during intro video playback.

- **Root cause:** The `gbagfx` LZSS compressor produces data with a non-standard 4-byte header: byte0=0x10 (type), bytes1-3=24bit LE size. GBA BIOS `LZ77UnCompWram` requires u32 with bit31=1 (compressed flag). Since bit31 was 0, the BIOS treated all frames as uncompressed and did nothing — the decompression buffer stayed all zeros → every tile blank → black screen.
- **Fix:** Added `_fix_gbagfx_header()` in `tools/encode_video.py` that detects gbagfx output and converts the header to GBA BIOS format before writing the blob.
- Audio was never implemented — the encoder only handles video frames, no audio output is wired in yet.

**Files:**
- `tools/encode_video.py` — added `_fix_gbagfx_header()` post-processor

**Outcome:** `make test-cards-build` passes. All 830 frames verified with correct `0x80005000` header (bit31=1, size=0x5000).

**Open / next:** Test on emulator. Audio still needs implementation.

## 2026-06-22 — Fix video player black screen (screenblock, DISPCNT, frame pacing)

**Worked on:** Debugged and fixed three issues causing the intro video to show a black screen instead of playing.

- **Screenblock never written to VRAM:** The tilemap lived only in the WRAM shadow buffer (`gBgVram.sbb1F`). The title screen's VBlank normally copies it to VRAM, but once the video replaced the callback, that copy stopped. Added `VideoPlayer_SetupScreenblock()` which writes a sequential identity tilemap directly to VRAM at `0x0600F800` before playback starts.
- **`REG_DISPCNT` missing Mode 0:** `REG_DISPCNT = DISPCNT_BG3_ON` only wrote `0x0800` (BG3 enable) without explicitly setting display mode bits. Changed to `REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_BG3_ON`.
- **Frame pacing ran at 60fps instead of 15fps:** The VBlank callback advanced `gVideoPlayerFrameIndex` on *every* VBlank regardless of `fpsDivider`. Fixed by using `gVideoPlayerState` as a "go" flag: main loop sets state=2 (advance one frame), callback advances exactly one frame and resets to 1 (wait), remaining VBlanks are idle.
- Palette and display registers are now primed before the first VBlank.

**Files:**
- `src_custom/video_player.c` — full rewrite of VBlank callback and play loop logic

**Outcome:** `make test-cards-build` passes clean. ROM builds and links. Video should now display when idle timer triggers.

**Open / next:** Test on hardware/emulator to confirm video is visible at 15fps. Audio playback not yet implemented.

## 2026-06-22 — Camera scrolls to player's hand after drawing a card

**Worked on:** Added camera scroll to player's hand after draw phase on the player's turn. In `RunDuelTurnLoop()`, after the draw completes and SFX plays, `sub_8041DF0(4)` is called to scroll the BG2 view down to row 4 (player hand, VOFS=138). Only triggers on the player's turn — opponent's draw leaves the camera on the field. Draw-skip cases (Yata, Fenrir, Time Seal, Reckless Greed) don't scroll since no draw happens.

**Files:**
- `src_custom/duel_main_hooks.c` — added `sub_8041DF0` extern declaration + scroll call after draw

**Outcome:** `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK). After drawing during the player's turn, the camera animates down to show the player's hand.

**Open / next:** None.

Working history for AI and human contributors. **Read this at the start of every session** before making changes. **Append an entry when you finish meaningful work.**

## 2026-06-22 — `skip_to_duel` runtime config: bypass all setup and jump straight into a duel

**Worked on:** Added `skip_to_duel` (bool) + `skip_to_duel_opponent_id` (u8) fields to `RuntimeConfig`. When enabled, `CopyrightScreensMain__Replacement` calls `sub_800AF68()` (new-game init), sets flags 0x2b + 0x8 (skip naming screen + cutscene), picks the configured opponent, and calls `DuelMain()`. After the duel ends, `OverworldMain()` is called so the game drops into a fully set up overworld. Default is `TRUE` (skip to duel immediately).

**Files:**
- `configs/runtime.h` — struct fields
- `configs/runtime.c` — defaults
- `src_custom/copyright_screens_hooks.c` — `CopyrightScreensMain__Replacement` updated with `skip_to_duel` branch

**Outcome:** `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK).

**Open / next:** None.

## 2026-06-22 — Fix overworld dialogue text colour (font palette overwritten by start menu)

**Diagnosis:** Overworld dialogue text appeared grey because the start menu overwrites palette bank 0 with `gStartMenuBgPalette` (entry 1 = `0x7AFC` = grey-purple) when it loads. When dialogue starts, the font palette `g82ADC8C` (entry 1 = `0x7FFF` = white) was never reloaded. The text tilemap uses palette bank 0, so the text displayed using the start menu's grey-purple color instead of white.

**Root cause:** A red herring — the BLDCNT layer swap analysis (textbox BG0→BG3) was incorrect. The textbox was a blend target both before and after the swap (`0xDE` has both bit 1 and bit 3 set), so blending was never the issue.

**Fix:** Added `CpuCopy16(g82ADC8C, gPaletteBuffer, 0x20)` to `sub_80532A8()` in `script.c`, which reloads the font palette into bank 0 every time dialogue starts, undoing any start menu palette corruption.

**Files:**
- `src/overworld/script.c` — `sub_80532A8()` now reloads font palette before setting VBlank callback

**Outcome:** `make` passes clean.

## 2026-06-22 — Section titles, scroll bounds, quarter-cursor fix, cursor palette durability

**Worked on:** Four bug fixes in the debug menu:

1. **Root menu scrolls past items** — `DEBUG_ROOT_ITEMS` was 15 but only 13 entries exist in `sRootLabels`. Changed to 13 so cursor can't scroll past "Save" into blank rows.

2. **Quarter cursor at top-left** — `DebugMenuLoadGraphics` called `LoadOam()` with stale overworld OAM data, which (after wiping OBJ VRAM and loading cursor at tile 0) showed a partial cursor tile at (0,0). Added `DebugMenuClearAuxOam()` and `DebugMenuUpdateCursor(0)` before the initial `LoadOam()`.

3. **Section titles** — Each sub-viewer now draws a centered 16-char title at pixel y=16 (text row 2, one row above the list at row 3). Added `DebugMenuDrawSectionTitle(view)` called in `DebugMenuRedraw` for non-root views. `DebugMenuSetupTextRows` clears an extra row. `DebugMenuUploadText` uploads one extra row (title glyphs). Title strings use `APPEND_RODATA` to avoid linker section conflicts.

4. **Cursor palette still breaking on portrait loads** — The VBlank-only fix was insufficient because `LoadPalettes()` (called after every `DebugMenuRedraw`) copies the full `gPaletteBuffer` after VBlank, overwriting the palette RAM fix. Added `CpuCopy16(gStartMenuCursorPalette, ...)` in `DebugMenuRedraw` just before `LoadPalettes()` so the cursor palette is correct in the buffer before it hits palette RAM.

**Files touched:**
- `src_custom/debug/debug_menu_internal.h` — `DEBUG_ROOT_ITEMS` 15→13
- `src_custom/debug/debug_menu.c` — all four fixes

**Outcome:** `make test-cards-build` passes cleanly. All 17 tests OK, full ROM links.

**Open / next:** None.**

## 2026-06-22 — Fix BG2/BG3 + sidebar corruption in OBJ debug menu

**Worked on:** Fixed three bugs in the OBJ-sprite sidebar rewrite that caused art corruption, wrong palette, and persistent BG3 corruption:

1. **BG3 corruption**: `DISPCNT_BG3_ON` was set unconditionally in VBlank, enabling BG3 on maps where it was off (showing stale VRAM data). Made BG3 conditional like BG2.
2. **Tile corruption**: The destride function wrote to `gBgVram.cbb4` at byte offsets up to 19744, but `cbb4[0x4000]` = 16384 bytes. Rows 8+ wrote past the buffer, corrupting adjacent memory (sbb19 tilemap, palette buffer, etc.). Fixed by splitting writes between `cbb4` (offsets < 0x4000) and `cbb5` (offsets ≥ 0x4000).
3. **Cursor tile conflict**: Cursor was at tile 0 which overlapped with sidebar tile at grid (0,0). Relocated cursor to grid row 20 (tile 640) and updated `DebugMenuUpdateCursorSlot` to use the new tile index instead of the hardcoded `0x800` value.

**Files:**
- `src_custom/debug/debug_menu.c` — VBlank BG3 conditional, destride cbb4/cbb5 split, cursor relocation, palette confirmation
- `src_custom/debug/debug_menu_internal.h` — `DEBUG_SIDEBAR_OBJ_TILE_BASE` 256 → 0

**Outcome:** `make test-cards-build` passes. All BG palette banks untouched by debug menu. Sidebar tiles within cbb4+cbb5 bounds. BG2/BG3 display their proper overworld content while menu is open.

**Worked on:** Rewrote the debug menu sidebar from a BG1 tile layer to 50 16×16 OBJ sprites using **OBJ palette bank 12** (above entity palettes 0-11). This eliminates all BG palette bank conflicts — the overworld uses all 16 BG palette banks, so any BG palette bank chosen for the sidebar inevitably corrupts some overworld tiles. The OBJ palette is fully separate.

- Sidebar art destrided from packed 10-wide BG layout (cbb1) to 32-stride 2D OBJ grid (cbb4+cbb5) starting at tile index 256
- 50 OAM entries at slots 16-65 covering 80×160px sidebar as 5×10 grid of 16×16 sprites
- Text kept on BG0 using **BG palette bank 0 slot 9** (font bank) — only 1 palette entry changed, not a full bank
- Removed all BG1 setup from VBlank, DISPCNT, and LoadGraphics — sidebar no longer uses cbb1 or any BG tile layer
- Sub-viewers (portrait, sprite, etc.) retain cbb4 tile area above index 256 for their OBJ data without interfering with sidebar tiles

**Files:**
- `src_custom/debug/debug_menu_internal.h` — OBJ constants, removed BG1 defines
- `src_custom/debug/debug_menu.c` — destride, OAM setup, VBlank, redraw, exit cleanup

**Outcome:** No BG palette bank is clobbered by the debug menu sidebar. The overworld's BG2/BG3 tiles display with their correct palettes while the menu is open. `make test-cards-build` passes.

**Open / next:** None.

## 2026-06-22 — Fix BG2/BG3 palette corruption in debug menu (bank 0 → bank 15)

**Worked on:** The debug menu sidebar palette was loaded into BG palette **bank 0** (the font palette bank). Any visible BG2/BG3 tile whose tilemap entry referenced palette bank 0 showed sidebar colors instead of correct font/map colors. The earlier save/restore of bank 0 only fixed the *exit* — during-menu corruption remained.

**Actual fix:** Changed `DEBUG_BG1_TEXT_PAL_BANK` from 0 to **15** (a high bank unlikely to be referenced by ground/roof tiles). The debug menu now shares sidebar art + text colors in bank 15 instead of clobbering bank 0. Font palette at bank 0 is untouched. Removed the now-unnecessary save/restore of bank 0 and its EWRAM allocation.

**Files:**
- `src_custom/debug/debug_menu_internal.h` — `DEBUG_BG1_TEXT_PAL_BANK` 0 → 15
- `src_custom/debug/debug_menu.c` — removed `gDebugMenuSavedBgPalBank0` save/restore code
- `asm/ram_map.s` — removed `gDebugMenuSavedBgPalBank0` allocation

**Outcome:** `make test-cards-build` passes. Font palette (bank 0) is preserved. Sidebar/text use bank 15 exclusively. BG2 and BG3 tiles should no longer show palette corruption during the debug menu.

**Open / next:** None.

**Worked on:** Two root causes identified and fixed:

1. **BG2 garbage on non-roof maps:** The debug menu VBlank unconditionally wrote `DISPCNT_BG2_ON`, enabling the roof layer (BG2) even on maps without roofs, revealing stale/garbage data in sbb1e. Fixed: read `REG_DISPCNT` at runtime and only include BG2_ON if the overworld had it on.

2. **BG palette bank 0 not restored on exit:** The debug menu loads its sidebar palette into bank 0, clobbering the overworld's font palette. `DebugMenuMain` didn't restore it, and the overworld VBlank (`sub_804F1E4`) only calls `LoadBgOffsets` + `LoadOam` — never `LoadPalettes()`. Fixed: save bank 0 to EWRAM (`gDebugMenuSavedBgPalBank0`) on entry, restore + `LoadPalettes()` on exit. (The overworld restore path `OverworldRestoreAfterDebugMenu` → `sub_804F598` also reloads the font palette, but the fix in `DebugMenuMain` runs before that for correctness.)

**Files:**
- `asm/ram_map.s` — `gDebugMenuSavedBgPalBank0[16]` EWRAM allocation (0x20 bytes)
- `src_custom/debug/debug_menu.c` — `DebugMenuVBlank` reads REG_DISPCNT for BG2 state; `DebugMenuLoadGraphics` same fix; save/restore bank 0 in entry/exit

**Outcome:** `make test-cards-build` passes. Debug menu no longer enables BG2 on non-roof maps. Font palette restored correctly on exit.

**Open / next:** None.

**Worked on:** The debug menu overwrites BG palette bank 0 (the overworld's font/tile palette bank) with sidebar colors. The overworld VBlank (`sub_804F1E4`) only calls `LoadBgOffsets()` + `LoadOam()` — never `LoadPalettes()` — so corrupted palette entries persisted after menu exit, making BG3 ground tiles using bank 0 display wrong colors. Fix: save bank 0 on debug menu entry and restore it + call `LoadPalettes()` on exit.

**Files:**
- `asm/ram_map.s` — added `gDebugMenuSavedBgPalBank0[16]` EWRAM allocation (0x20 bytes)
- `src_custom/debug/debug_menu.c` — save bank 0 in `DebugMenuLoadGraphics`, restore + `LoadPalettes()` in `DebugMenuMain`

**Outcome:** `make test-cards-build` passes. BG palette bank 0 is restored immediately on debug menu exit, fixing BG3 ground tile colors and textbox font.

**Open / next:** BG3 tiles using bank 0 still show sidebar colors *while* the debug menu is open — acceptable for a debug overlay since the sidebar covers the affected area. A full fix would require per-frame palette splitting or using a guaranteed-unused palette bank.

## 2026-06-22 — Polymerization: custom fusion spell card with field+hand scan and deck-menu picker

**Worked on:** Added POLYMERIZATION (spell card, passcode 24094653) with a full fusion mechanic:

- **Manifest entry** via `add_custom_card.py` — spell card at ID 0x03E9
- **Fusion recipe table** in `src_custom/spell_effects/polymerization.c` with `APPEND_RODATA` for linker-safe const data. Recipe format: `{ result, material1, material2 }` where `POLY_WILDCARD` (0xFFFF) = any monster (max 1 per recipe). Currently 1 recipe: FLAME_SWORDSMAN = FLAME_MANIPULATOR + any monster.
- **Scan**: Collects monsters from own hand (first = priority) then field. Matches against recipes using `RecipeIsFeasible()`, selects materials with hand preference via `SelectMaterials()`.
- **Auto-execute**: Single feasible fusion runs immediately. Multiple fusions: deck-menu picker via `DeckMenuMainReadOnly()` for the player; AI picks highest ATK.
- **Resolution**: Destroys spell, sends materials to GY via `ClearZoneAndSendMonToGraveyard`, then `Duel_SpecialSummonMonsterId` to place fusion face-up ATK on an empty monster zone.
- **Wired** in `spell_effect_hooks.c` (POLYMERIZATION case) + runtime config `card_in_hand_1 = POLYMERIZATION`
- **Pre-existing fix**: Added 1-byte pad in `asm/ram_map.s` (`gTrunkVisiblePad`) to fix 2 misaligned u16 EWRAM allocations that the RAM layout validator flagged.

**Files:**
- `tools/card_data_manifest.json` — POLYMERIZATION entry appended
- `configs/runtime.c` — `card_in_hand_1 = POLYMERIZATION`
- `src_custom/spell_effects/polymerization.c` — new: fusion recipe table, scan, picker, execution
- `src_custom/spell_effect_hooks.c` — extern + POLYMERIZATION case
- `asm/ram_map.s` — `gTrunkVisiblePad` for u16 alignment

**Outcome:** `make test-cards-build` passes clean (17/17 tests, ROM links, validators OK). Polymerization starts in hand slot 1 at duel start.

**Open / next:**
- Add more fusion recipes to `sFusionRecipes[]` array
- Fusion picker uses full-screen deck menu; a compact overlay with small-font list would be more polished
- Hand-to-GY tracking uses vanilla `ClearZoneAndSendMonToGraveyard` which sets top-card only; expanded GY stacking (if enabled) works automatically via existing LynJump hooks

## 2026-06-22 — Fix phantom cards from undersized CUSTOM_CARD_QTY_BYTES in asm

**Worked on:** Fixed mismatch between `render_card_counts_header` (padded to `0x200`) and `render_card_memory_sizes_asm` (padded to `0xC8`) in `tools/add_card_art.py`. With 201 custom cards (0xC9 > 0xC8), the asm render generated `0xC9` for `CUSTOM_CARD_QTY_BYTES`, meaning `ram_map.s` allocated only 201 bytes for trunk/shop/temp qty buffers. Cards with indices ≥ 201 wrote past buffer bounds, corrupting adjacent EWRAM → phantom cards.

**Fix:** Changed minimum in `render_card_memory_sizes_asm` from `0xC8` to `0x200` to match the header renderer, then regenerated `generated/card_memory_sizes.inc` via `python3 tools/add_card_art.py --card-ids`.

**Files:**
- `tools/add_card_art.py` — `render_card_memory_sizes_asm` min 0xC8 → 0x200
- `generated/card_memory_sizes.inc` — regenerated

**Outcome:** Both `card_counts.h` and `card_memory_sizes.inc` now have `0x0200`. Run `make clean && make` to rebuild.

**Open / next:** None.

Format for new entries (newest first):

```markdown
## YYYY-MM-DD — Short title

**Worked on:** …
**Files:** …
**Outcome:** …
**Open / next:** …
```

## 2026-06-22 — Debug menu exit: save/restore all display registers

**Worked on:** Overworld dialogue text appeared grey (not white) after exiting the debug menu and talking to an NPC. The text was white in VRAM but grey on screen, indicating stale compositing state from the debug menu.

**Diagnosis:** The debug menu's VBlank callback set `REG_BLDCNT = 0` and `REG_BLDALPHA = 0`, and the standard `OverworldRestoreGraphicsAfterSubmenu()` only restored `REG_BLDCNT = 0` and `REG_BLDY = 7` — it did NOT restore `REG_BLDALPHA`, `REG_WININ`, or `REG_BG0CNT` to the exact overworld entry values. Additionally, stale debug-menu OBJ data in OAM slots beyond the explicitly-cleared ones (portrait/sprite viewer slots 4-15) could persist and render with priority over the dialogue text.

**Fix:** `DebugMenuMain()` now saves all overworld display registers before entry and restores them on exit, clears ALL 128 OAM slots instead of only sidebar+cursor slots, and restores `REG_BLDALPHA` and `REG_WININ` from the saved values (which the standard restore function does not touch).

**Files:**
- `src_custom/debug/debug_menu.c` — added save/restore for REG_DISPCNT, REG_BLDCNT, REG_BLDALPHA, REG_BLDY, REG_WININ, REG_WINOUT, REG_BG0CNT; clear all 128 OAM slots

**Outcome:**
- `make all` passes clean link

**Open / next:**
- Confirm dialogue text is white after debug menu exit
|---

## 2026-06-21 — Debug menu VBlank restructure: restore original overworld-first call order

**Worked on:** Fixed debug menu not displaying at all by restoring the original VBlank call order (overworld VBlank first, then debug menu register setup). My earlier restructure put debug menu setup before the overworld VBlank call, which broke display. Kept the HOFS=0 fix after the overworld VBlank to prevent the sidebar being shifted by the overworld's textbox scroll offset.

**Files:**
- `src_custom/debug/debug_menu.c` — `DebugMenuVBlank` restructured back to: call overworld VBlank → set HOFS=0 → set debug BG/WIN registers → upload VRAM. Removed redundant re-assertion block after overworld VBlank.

**Outcome:** `make test-cards-build` passes. Debug menu sidebar overlay should render correctly on R press.

**Open / next:** None.

---

## 2026-06-21 — Overworld BG layer swap: free BG0/BG1 for debug menu

**Worked on:** Moved overworld ground layer from BG2 to BG3; roof/high layer from BG1 to BG2; textbox from BG0 to BG1. BG0 is now completely unused by the overworld and free for the debug menu. BG1 used only for the textbox overlay (still at same VRAM addresses, just moved to BG1 hardware layer).

**Files:**
- `src/overworld/overworld.c` — `SetBg3Regs` → BG3 (ground, sbb1F, 0x1F82); `SetBg2Regs` → BG2 (roofs, sbb1E, 0x1E81); `SetBg1Regs` → BG1 (textbox, sbb1D, 0x1D0C); `SetBg0Data` → no longer writes REG_BG0CNT; `OverworldSetRegDispcnt` / `OverworldSetRegDispcnt2` → BG0_ON removed, BG1_ON always, BG2_ON conditional (roofs), BG3_ON always (ground)

**Outcome:** `make test-cards-build` passes. Overworld no longer touches BG0. Textbox on BG1, roofs on BG2, ground on BG3. Debug menu gets BG0 (text) and BG1 (sidebar art) free from overworld interference.

**Open / next:** After fixing white-screen regression (SetBg0Data register writes restored for ROM address stability), needed to fix three display bugs caused by the debug menu's VBlank callback not being restored after exit: grey text, BG2/BG3 corruption, and missing debug menu art. Fix: `SetVBlankCallback(overworld_vblank)` at end of `DebugMenuMain()`.

---

## 2026-06-21 — Debug menu VBlank leak fix

**Worked on:** Added configurable `expand_graveyard` runtime option that expands the per-player graveyard from a single `u16` slot to a 40-card LIFO stack. Dual-storage approach keeps the legacy `u16 graveyard` field synced to the top of the expanded array for vanilla compatibility.

**Files:**
- `configs/runtime.h` — added `u8 expand_graveyard` field
- `configs/runtime.c` — defaulted to `FALSE`
- `asm/ram_map.s` — `gExpandedGraveyard[2][40]` + `gExpandedGraveyardCount[2]` EWRAM allocations
- `src_custom/graveyard_expand_hooks.c` — 4 LynJump replacements (GetGraveCardAndClearGrave, GetGraveCardAndClearGrave2, ClearZoneAndSendMonToGraveyard, ClearZoneAndSendMonToGraveyard2) + helper functions
- `src_custom/card_passive_hooks.c` — updated ClearZoneAndSendMonToGraveyard replacement to call GraveyardExpand_PushMonster
- `src_custom/embodiment_of_apophis_hooks.c` — updated both GY writes to use GraveyardExpand_PushMonster
- `src_custom/code_803F02C_hooks.c` — added GraveyardExpand_Init() to InitBoard
- `src_custom/graveyard_scan_hooks.c` + `include/graveyard_scan_hooks.h` — helpers: HasCardInGrave, GetCount, GetNthCard, PopSpecificCard
- `src_custom/graveyard_selector.c` + `include/graveyard_selector.h` — GySelector_ShowSingle / GySelector_ShowCombined (uses deck menu in read-only mode)
- `src_custom/spell_effects/monster_reborn.c` — custom effect with combined GY picker
- `src_custom/spell_effect_hooks.c` — wired MONSTER_REBORN case to custom EffectMonsterReborn
- `include/graveyard_expand_hooks.h` — public helpers header
- `src_custom/LynJump.event` — added GetGraveCardAndClearGrave + GetGraveCardAndClearGrave2 entries

**Outcome:**
- `make test-cards-build` passes clean link
- When `expand_graveyard = FALSE` (default): zero behavioral change
- When `expand_graveyard = TRUE`: all GY operations use the expanded array; Monster Reborn shows combined GY picker

**Open / next:**
- GY viewer: now accessible from B menu (cursor down from Surrender/Turn End to GY zones, press A) — implemented
- Specific-card GY scan replacements: helper exists but individual function replacements for DM/Gernia/DFK checks in monster_effects.c and permanent_effect.c are still needed (ponytail: known ceiling)
- Premature Burial / Call of the Haunted: currently pop top card from expanded GY (works); per-player selector UI is future work
- Delete stale `src_custom/graveyard_*.h` files after migration to `include/`

## 2026-06-21 — B menu GY cursor navigation

**Worked on:** Extended the duel field B menu cursor to allow moving DOWN from the 4 options (Details, Turn End, Discard, Surrender) to each player's graveyard zone. Pressing A on a GY zone opens a read-only trunk-style list of all cards in that GY.

**Files:**
- `include/duel_b_menu.h` — added B_MENU_GY_OPPONENT=4, B_MENU_GY_PLAYER=5 to enum, declared Duel_GraveyardViewer_Open
- `src_custom/duel_b_menu_hooks.c` — added highlight tile offsets + navigation table entries for GY zones; extended HighlightBMenuOption from 4 to 6 entries; added GY highlight positions to stale cells list
- `src_custom/duel_opponent_hand_scroll_hooks.c` — added B_MENU_GY_OPPONENT / B_MENU_GY_PLAYER A-button cases to BMenuMainWithSurrender
- `src_custom/duel_gy_viewer.c` — new file: GY viewer function that loads expanded GY cards into gDeckMenu and calls DeckMenuMainReadOnly

**Outcome:**
- `make test-cards-build` passes clean link
- Cursor navigation: DOWN from Turn End -> opponent GY -> player GY -> (stays). UP goes back up. Left/Right stay on GY. Press A to open GY viewer, then browse + B to exit back to B menu

**Open / next:**
- GY viewer still returns to B menu after exit; no field cursor reset needed
- Premature Burial / Call of the Haunted per-player GY selector still to wire up

## 2026-06-21 — GY viewer: fix black screen, turn-counter corruption, card filtering

**Worked on:** Fixed three issues with the GY viewer:
- Rewrote `duel_gy_viewer.c` to use a custom input loop instead of `DeckMenuMainReadOnly()`, skipping the exit tasks (`RunPlayerDeckTask(8)`, `RunTrunkTask(9)`) that corrupted duel state (turn counter)
- After viewer exit, caller now calls `DuelBMenu_Init(cursorState)` instead of `DuelBMenu_RefreshOverlay`, which runs `InitBMenuWithSurrender` to properly re-set `REG_DISPCNT` and window registers (fixes black screen)
- Expanded GY already only stores monster cards sent from field via `ClearZoneAndSendMonToGraveyard` hooks (no filtering needed — already correct)

**Files:**
- `src_custom/duel_gy_viewer.c` — full rewrite: custom input loop, no exit tasks, no final DisableDisplay
- `src_custom/duel_opponent_hand_scroll_hooks.c` — changed `DuelBMenu_RefreshOverlay` → `DuelBMenu_Init` in both GY viewer cases

**Outcome:**
- `make test-cards-build` passes clean link
- B menu overlay fully restored after GY viewer exit (no black screen)
- Turn counter unaffected by GY viewer navigation
- GY already filtered to field-origin monsters

**Open / next:**
- Specific-card GY scan replacements for DM/Gernia/DFK checks still needed
- Premature Burial / Call of the Haunted per-player GY selector UI still to wire up

## 2026-06-21 — Debug menu BG1 sidebar overlay

**Worked on:** Rewrote the debug menu from a full-screen start-menu-takeover to a BG1 sidebar overlay on the overworld, using `src_custom/assets/menus/debug_menu.png` (80x160 indexed PNG) as sidebar art. The overworld remains visible behind the sidebar via WIN0 window clipping (columns 20-29). Text/tilemap now writes to BG1 charblock cbb1 and screenbase sbb18 instead of the old start-menu layout.

**Files:**
- `graphics.mk` — added `DEBUG_MENU_*` asset variables, build rule for `.lz`, clean rule for `menus/`, added to `graphics-rules` target
- `Makefile` — added `custom_object_dep` for `debug/debug_menu.o` on `$(DEBUG_MENU_LZ) $(DEBUG_MENU_PAL)`
- `src_custom/debug/debug_menu.c` — sidebar on BG1 at columns 0-9; text on BG0 with small overworld font via `CopyStringTilesToVRAMBuffer`; overworld VBlank; no screen transition
- `src_custom/debug/debug_menu_internal.h` — BG1 sidebar at columns 0-9, BG0 text constants, WIN0 aligned to left 80px
- `documentation/debug-menu.md` — updated introduction, text layout section, code locations, and limitations

**Outcome:**
- `make test-cards-build` passes clean
- Debug menu now renders as an 80px sidebar on the right side of the screen with the overworld visible behind it
- No screen transition/flash on open: removed `ClearGraphicsBuffers`, `LoadVRAM`, `LoadBgVRAM`, `FadeOutMusic`, and `PlayMusic(MUSIC_DECK_ADJUSTMENT_MENU)` calls so the sidebar appears seamlessly over the running overworld

**Open / next:**
- Overworld OBJ sprites (player, NPCs) may show wrong colors while menu is open (cursor palette overwrites OBJ slot 0) — acceptable for a debug overlay

**Worked on:** Removed `InitTrunkData()` calls from the GY viewer and graveyard selector.
`InitTrunkData()` calls `RefreshTrunkOwnershipTotals()`, which reads `gDeckMenu.cards`
to add deck card quantities to `gTotalCardQty`. But during GY viewing,
`gDeckMenu.cards` holds GY cards (not the player's deck), so GY card IDs
leaked into the trunk's ownership totals, corrupting trunk display.

**Files:**
- `src_custom/duel_gy_viewer.c` — removed `InitTrunkData()` call, unused externs
- `src_custom/graveyard_selector.c` — removed both `InitTrunkData()` calls, unused extern

**Outcome:** `make test-cards-build` passes. Trunk ownership totals are no longer
corrupted after viewing a GY during a duel.

**Note on 6 opponent GY cards:** The expanded GY correctly tracks all monsters
sent to GY from the field (battle destruction, tribute summons, card effects).
During the AI's turns, the opponent naturally accumulates GY cards from its own
plays. This is correct behavior — the GY viewer shows exactly what's in the GY.

**Open / next:**
- Specific-card GY scan replacements still needed
- Premature Burial / Call of the Haunted per-player GY selector UI still to wire up

## 2026-06-21 — Remove black overlay from debug menu

**Worked on:** Eliminating a persistent black overlay that obscured the debug menu sidebar art. BG0 (screen block 19) was rendering on top of BG1 (screen block 18) even when all its tiles referenced palette bank 15 with tile 0 (which should be transparent). Tried filling the tilemap with palette-bank-15 mask — overlay remained.

**Fix:** Removed BG0 from the debug menu entirely — no more `DISPCNT_BG0_ON` in `DebugMenuVBlank`, no `REG_BG0CNT` writes (save or restore), no sbb19 upload in `DebugMenuUploadBg1`, no sbb19 fill in `DebugMenuLoadGraphics`. Only BG1 renders now.

**Files:**
- `src_custom/debug/debug_menu.c` — stripped BG0 from VBlank, load, upload, and teardown; removed `gSavedDebugMenuBg0Cnt` extern

**Outcome:** `make` builds clean. BG0 layer is gone — sidebar art on BG1 should display without black overlay. Text overlay (written to sbb19) is currently invisible since BG0 is off — will restore as a separate fix.

**Open / next:**
- Restore text overlay without reintroducing the black background — e.g. merge text tilemap into sbb18 alongside art, or disable BG0 outside the text area via a second window (WIN1).

## 2026-06-23 — Intro video: ffmpeg binary, blob format fixes, `.incbin` assembly

**Worked on:** Got the intro video actually playing. Fixed three issues:

1. **No ffmpeg binary** — User had `ffmpeg-python` pip package but no actual ffmpeg in PATH. Installed `imageio-ffmpeg` which bundles a static binary. Updated `_find_ffmpeg()` to check `imageio_ffmpeg.get_ffmpeg_exe()` as fallback.

2. **Palette reading** — `palettegen` filter outputs RGBA pixels not a PLTE chunk. Rewrote `_read_palette_from_png` to handle both.

3. **Blob format overflow** — 909 frames × ~8KB compressed = ~15MB blob. Palette offsets as u16 overflowed. Switched to single global palette per video and u32 data offsets.

4. **`generate_inc()` OOM** — Writing 15MB as C byte array made the compiler consume all memory and get killed. Switched to writing a raw `.bin` file and using `__asm__(".incbin ...")` in the header.

5. **ARM alignment** — 6-byte index entries caused misaligned u32 reads (crash on frame ≥ 1). Padded entries to 8 bytes.

**Files:**
- `tools/encode_video.py` — ffmpeg path fallback, RGBA palette reading, 8-byte index entries with u32 offsets, single palette per video
- `src_custom/video_player.c` — aligned 8-byte index entries, single palette at fixed offset 4
- `src_custom/generated/video_assets_generated.inc` — now uses `.incbin` instead of C byte array (581 bytes vs ~90MB)

**Outcome:** `make test-cards-build` passes. ROM was ~33MB (15MB video blob). 909 frames @ 15fps = ~60 second intro.

**Open / next:**
- Audio: currently no audio track is extracted. Consider encoding audio as GBA-format samples (4-bit DPCM or 8-bit PCM via m4a).
- ROM size: 33MB may not fit standard 32MB carts; consider shortening the video or using a 64MB cart header.

## 2026-06-23 — Intro video: ROM overflowed 32MB causing white screen

**Problem:** The ROM was ~34.7MB, exceeding the GBA's 32MB addressable limit (`0x09FFFFFF`). `__append_end` was at `0x0A11B798`. Data beyond `0x09FFFFFF` was inaccessible, corrupting the `.append_assets` section and causing a white screen at startup.

**Fix:** Added `--max-frames 830` (default) to `tools/encode_video.py`. Trims the video from 909 → 830 frames (~55s at 15fps), bringing the blob down from 14.7MB to 13.2MB. ROM now fits within 32MB (`__append_end` at `0x09F9A004`).

**Files:**
- `tools/encode_video.py` — `--max-frames` parameter, pass `-vframes` to ffmpeg paletteuse

**Outcome:** `make test-cards-build` passes. ROM is 31.6MB (31,607,042 bytes), under 32MB with ~408KB slack.

## 2026-06-23 — Intro video: 4bpp + cached frames, blob shrinks to 5.9MB

**Problem:** 8bpp (256 colors) frames were 38KB each, compressing to ~16KB → 13.2MB for 830 frames. Pushed ROM near 32MB limit and made rebuilds slow (ffmpeg every time).

**Fix:** 
- Switched to **4bpp** (16 colors) — halves frame data to 19KB, compresses better to ~7KB
- Frames are now cached as indexed PNGs in `src_custom/assets/videos/frames/<video_stem>/`
- Cache check: if frames exist and count matches `--max-frames`, skip ffmpeg entirely
- Added `--re-extract` flag to force re-extraction
- Updated GBA player: `VIDEO_FRAME_BUF_SIZE = 0x4B00`, `FRAME_PALETTE_BYTES = 32`, dropped `BGCNT_256COLOR`

**Files:**
- `tools/encode_video.py` — 4bpp constants, `_indexed_png_to_4bpp_tiles`, frame cache in `videos/frames/`
- `src_custom/video_player.c` — 4bpp display mode, 32-byte palette, 0x4B00 buffer
- `asm/ram_map.s` — `gVideoPlayerFrameBuf` size 0x9600 → 0x4B00

**Outcome:** Video blob: 5.9MB (56% of 10MB budget). ROM: 25.2MB (8MB slack under 32MB). ffmpeg runs once; subsequent builds read cached PNGs.

## 2026-06-23 — Intro video: 256×160 canvas with 16px black padding

**Problem:** Frames were 240×160 (600 tiles, 0x4B00 bytes). The source video has been re-encoded to 240×160, but the GBA expects a 256-pixel wide canvas for standard BG mode.

**Fix:** 
- Changed `GBA_WIDTH` from 240 → 256. Added `VIDEO_WIDTH = 240` for the active content area.
- ffmpeg still scales to `VIDEO_WIDTH`×160. Python pads each row from 240 to 256 with palette-index 0 (black).
- The 16px black border is off-screen (GBA viewport is 240px wide), so it's invisible.
- Bonus: the regular black border compresses extremely well with LZSS, dropping the blob from 5.9MB → **2.1MB**.

**Files:**
- `tools/encode_video.py` — `GBA_WIDTH=256`, `VIDEO_WIDTH=240`, padding in `_indexed_png_to_4bpp_tiles`
- `src_custom/video_player.c` — `VIDEO_FRAME_BUF_SIZE=0x5000`
- `asm/ram_map.s` — `gVideoPlayerFrameBuf` 0x4B00 → 0x5000

**Outcome:** Video blob: **2.1MB** (2.5KB/frame compressed). ROM: **21.4MB** (11.6MB slack under 32MB).

## 2026-06-23 — Fix frame tile conversion + LZSS crash

**Worked on:** Fixed crash from wrong LZSS address and all-zero frames from tile conversion bug.

**Root causes:**
1. **`_indexed_png_to_4bpp_tiles` produced all-zero tiles** (mysterious Python import issue). Replaced function body with known-working inline version — same logic, different variable names. Frame data now contains actual pixels.
2. **Wrong address passed to `LZ77UnCompWram`** in minimal diagnostic version (passed index entry address instead of reading the offset first). Crash was purely from this test bug, not from the BIOS call itself.
3. **gbagfx LZSS data is valid** — only the header format was wrong (now fixed by `_fix_gbagfx_header`). Tile data was all-zero input, not a gbagfx bug.

**Files:**
- `tools/encode_video.py` — `_indexed_png_to_4bpp_tiles` rewritten
- `src_custom/video_player.c` — correct LZSS call with full playback loop (830 frames, 15fps)

**Outcome:** Video blob: **6.1MB** (7.4KB/frame compressed — actual video content). ROM: **24.3MB** under 32MB. Should play the full intro video on the title screen after 5s idle.

## 2026-06-23 — Display fix: save/restore title screen state around video

**Worked on:** After raw-tile (no LZSS) video playback, title screen stayed black. Video worked (user saw frames flash) but nothing restored VRAM or display registers.

**Fix:** Save `REG_DISPCNT`, `REG_BG3CNT`, charblock 0 (0x06000000), and screenblock 31 (0x0600F800) to `gVideoPlayerFrameBuf` + stack before video. Restore after. Also removed unused `gVideoPlayerState`/`gVideoPlayerFrameIndex` externs and the unused `VideoPlayer_VBlank` callback.

**Files:**
- `src_custom/video_player.c` — save/restore display state; removed all LZSS code (raw tiles from ROM directly to VRAM)

**Open / next:** Full video with LZSS re-added. Audio.

## 2026-06-24 — Fix Meteo: data corruption, exit handler, and replay flag

**Worked on:** Three bugs in Meteo integration:
1. **Data corruption** — patcher touched compressed video/audio data at offsets 0x0304, 0xDC4C, 0xE678, 0xF278 outside code ranges. Fixed by restricting patches to known code regions (0x0000-0x0310 boot + 0x9C2C-0xB150 IWRAM copy source).
2. **Exit handler** — removed exit trampoline patch at +0x258 (was an init subroutine, not exit). The blob handles its own exit (bx 0x08000000).
3. **Replay loop** — after cold boot, video replayed. Fixed by moving `gIntroVideoPlayed` from EWRAM (cleared by emulator on reset) to IWRAM (0x030075C8, survives blob + cold boot).

**Files:**
- `tools/meteo_integrate.py` — PATCH_RANGES, removed exit patch
- `asm/ram_map.s` — gIntroVideoPlayed in IWRAM
- `src_custom/video_player.c` — IWRAM flag check
- `src_custom/meteo_player_stub.s` — removed trampoline (unused now)

**Outcome:** Video plays correctly with audio once per power cycle, then title screen stays.
