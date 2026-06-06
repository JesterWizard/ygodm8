# Duel Low-LP BGM Tempo

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Duel background music normally plays at a fixed tempo for the whole fight. This feature optionally speeds up the duel BGM when the player's life points drop to a configured threshold, then restores normal tempo when LP rises above it again.

It is controlled by two fields in `gRuntimeConfig` (`configs/runtime.c`):

| Field | Default | Role |
|-------|---------|------|
| `increase_bgm_tempo_when_lp_at_or_below` | `0` | LP threshold; **0** disables the feature |
| `increase_bgm_tempo_speed_percent` | `125` | Boosted tempo as a percent of normal (`100` = unchanged, `200` = 2×) |

Example: set the threshold to `2000` and speed to `150` to play duel music 1.5× faster while player LP is 2000 or below.

## Plan

### Behavior

Each duel graphics refresh, the hook reads `gDuelLifePoints[DUEL_PLAYER]` and adjusts the main music player (`g2025840`) when needed.

| Player LP vs threshold | BGM tempo |
|----------------------|-----------|
| LP > threshold | Normal (`tempoU = 0x100`) |
| LP ≤ threshold | Boosted (`tempoU = 0x100 × speed_percent / 100`) |
| Threshold = 0 | Feature off; music untouched |

The boost applies to **duel BGM only** (the track started by `PlayMusic(gDuelData.duelMusic)`). It does not affect overworld music.

### m4a tempo model

The GBA m4a driver speeds music through a multiplier chain, not a single BPM write:

| Field | Role |
|-------|------|
| `tempoD` | Base tempo from the song; updated by in-song MIDI tempo commands |
| `tempoU` | Speed multiplier (`0x100` = 100%) |
| `tempoI` | Tick rate used by the sequencer: `(tempoD × tempoU) >> 8` |
| `tempoC` | Internal tick accumulator (not written by this feature) |

`ApplyM4aTempoMultiplier` mirrors vanilla `m4aMPlayTempoControl`: it sets `tempoU`, recomputes `tempoI`, and leaves `tempoC` alone.

### Drift correction

The hook does not only apply tempo once when LP crosses the threshold. On each refresh it checks whether `tempoU` and `tempoI` still match the desired values. If the song's MIDI tempo commands or other engine activity changed them, the boost is re-applied. This keeps playback steady instead of jittering between boosted and normal speed.

### Configuration examples

```c
// Disabled (default)
.increase_bgm_tempo_when_lp_at_or_below = 0,
.increase_bgm_tempo_speed_percent = 125,

// Boost at 4000 LP or below, 1.25× speed
.increase_bgm_tempo_when_lp_at_or_below = 4000,
.increase_bgm_tempo_speed_percent = 125,

// Boost at 1000 LP or below, 2× speed
.increase_bgm_tempo_when_lp_at_or_below = 1000,
.increase_bgm_tempo_speed_percent = 200,
```

Rebuild after editing `configs/runtime.c` so the ROM `gRuntimeConfig` section matches.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| LP threshold config | `increase_bgm_tempo_when_lp_at_or_below` in `configs/runtime.h` and `configs/runtime.c` | Master on/off via `0`; otherwise LP cutoff for the boost |
| Speed config | `increase_bgm_tempo_speed_percent` in `configs/runtime.h` and `configs/runtime.c` | Boost multiplier as percent of normal tempo |
| Tempo update | `UpdateDuelBgmTempoForLifePoints` in `src_custom/duel_bgm_tempo.c` | Reads LP, computes desired `tempoU`, corrects drift |
| m4a apply | `ApplyM4aTempoMultiplier` in `src_custom/duel_bgm_tempo.c` | Sets `tempoU` and `tempoI` on the active music player |
| Public API | `include/duel_bgm_tempo.h` | Declares `UpdateDuelBgmTempoForLifePoints` |
| Duel hook call site | `sub_80411D4__Replacement` in `src_custom/duel_board_lp_hooks.c` | Invokes tempo update each duel graphics refresh |
| Hook wiring | `src_custom/LynJump.event` (`ORG $411D4`) | Redirects `sub_80411D4` to the replacement |
| Vanilla refresh | `sub_80411D4` in `src/duel/duel_textbox.c` | Called from `UpdateDuelGfxExceptField` during duels |
| Main BGM player | `g2025840` in `ldscript.ld` | EWRAM music player used by `PlayMusic` for duel tracks |
| m4a types | `include/gba/m4a_internal.h` | `MusicPlayerInfo`, `ID_NUMBER`, tempo field layout |

## TODO

- Restore normal tempo explicitly when a duel ends (currently relies on fade-out / next `PlayMusic` call).
- Consider a separate multiplier for opponent LP if dual-sided tension music is desired later.

## Limitations & Bugs

- **Duel BGM only.** Overworld and menu music are unaffected.
- **Main player only.** Short duel voice lines and SFX that temporarily take over the music player are not boosted; when duel BGM resumes, the hook re-applies the multiplier if LP is still low.
- **No boost while music is inactive.** If `g2025840.ident != ID_NUMBER` (no active track), the hook returns without changes.
- **Speed floor.** Values below `100` in `increase_bgm_tempo_speed_percent` are clamped to `100` (no slow-motion).
- **In-song tempo changes are scaled, not replaced.** MIDI tempo commands still run; the boost is applied as a multiplier on top of whatever `tempoD` the song sets. Musical tempo ramps inside a track are preserved, just faster.
- **CPU cost is negligible.** Per-frame work is a few comparisons; tempo is only rewritten when `tempoU`/`tempoI` drift from the target.
