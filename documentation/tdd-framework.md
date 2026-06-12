# Test-Driven Development Framework

---

## Index

- [Introduction](#introduction)
- [Why We Have This](#why-we-have-this)
- [What It Is](#what-it-is)
- [Plan](#plan)
- [Workflow](#workflow)
- [Commands](#commands)
- [Manual Smoke Checklist](#manual-smoke-checklist)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

`ygodm8` is a GBA ROM hack built from decompiled C and assembly. Most features are wired through **generators** (card manifests, duelist decks, voice WAV→DPCM), **linker RAM maps** (`asm/ram_map.s`), and **LynJump hooks** in `src_custom/`. A small mistake in any of those layers can corrupt saves, break audio, or ship silent deck bugs—and you might not notice until you play for twenty minutes.

The **TDD framework** is the project’s answer: a repeatable way to catch regressions **before** you boot the ROM, plus a short manual checklist for things only an emulator can judge (UI feel, playback, duel flow).

It is **local-first** today: run `make test` on your machine. The layout is ready for CI later, but we deliberately did not gate every push on a full ROM hash while the hack is still moving quickly.

## Why We Have This

| Problem | Without tests | With this framework |
|---------|---------------|---------------------|
| Card manifest typo | Broken build or wrong stats in-game | `validate_manifest` fails in seconds |
| Generator output drift | Silent `.inc` changes, hard-to-spot diffs | Golden files under `tests/goldens/` |
| Flash/RAM overlap | Corrupted saves or crashes after new feature | `validate_ram_map.py` on every `make test-host` |
| Deck save layout change | Deck 2/3 wiped or wrong active index | Round-trip tests + fixture blob + `validate_player_decks.py` |
| Voice pipeline tweak | Crackle, trim bugs, invalid DPCM | Host tests on trim/encode/clip rules |
| Portrait PNG format | Black borders, stray pixels, wrong OBJ indices | `validate_portrait.py` + `tests/host/test_portraits.py` |
| LynJump / event macro error | Link failure or wrong script patch | Existing validators run inside `make test` |

**Why strict TDD (red → green → refactor)?**  
For manifest, codegen, and persistence logic, the cost of writing a test first is tiny compared to debugging a bad ROM in mGBA. The rule is: **if Python or the build can check it, it should fail in `make test-host` before you rely on playtesting.**

**Why not only `make compare` (SHA-1)?**  
A matching ROM hash proves the binary is *unchanged*, not that your *new* card or voice feature is correct. During active hacking, the ROM changes every feature branch; SHA-1 is kept as an optional milestone check (`make compare`), not the daily gate.

**Why not full emulator automation yet?**  
Scripted playthroughs are expensive to maintain for a duel game with hundreds of cards. We automate what is **deterministic on the host** and keep a **lightweight manual smoke list** for UX. Emulator tests can be added later if manual checks become a bottleneck.

**Pilot coverage (first wave):** custom cards/decks, save/RAM persistence, custom voices/audio pipeline—the areas where generator and layout bugs hurt the most.

## What It Is

Three layers that work together:

1. **Host unit tests** (`tests/host/`, `unittest`)  
   Fast checks on the dev PC: manifest validation, golden generator output, DPCM helpers, flash layout, save blob layout. No `agbcc` required for this step alone (`make test-host`).

2. **Build gates** (`make test`)  
   Everything in `test-host`, plus a **full ROM link**, LynJump validation, custom event C checks (when present), and a memory report. This proves the hack still compiles and fits in RAM/flash budgets.

3. **Manual ROM smoke** (short checklist in this doc)  
   Load `ygodm8.gba` in an emulator when you change player-visible behavior: trunk UI, duel decks, save slots, voice playback.

Supporting pieces:

| Piece | Role |
|-------|------|
| `tests/fixtures/` | Tiny manifests and save blobs so tests do not depend on the full production JSON |
| `tests/goldens/` | Committed “expected output” for generators; refresh with `make update-goldens` |
| `tools/card_manifest.py`, `duelist_deck_validate.py`, etc. | Logic extracted so tests and CLIs share one implementation |
| `src_custom/persist/` | Small C helpers (e.g. deck completeness) testable in spirit via Python mirrors |

**Strict TDD** applies to layer 1: write a failing test, implement, refactor, then run `make test` before you consider the change done.

Whole-ROM SHA-1 compare (`make compare`) is intentionally **not** part of `make test` while the project is under active development.

## Plan

| Layer | What it proves | How |
|--------|----------------|-----|
| Host unit tests | Manifest rules, generator output, audio helpers, flash layout, save record layout | `make test-host` |
| Build gates | LynJump wiring, custom event C macros, full ROM link | `make test` |
| Manual ROM checks | Trunk/shop UI, duel decks, voice playback | Checklist below |

```text
failing host test → implement → make test-host → manual smoke (when UX matters) → make test
```

## Workflow

1. For data/generator changes, add or update a test under `tests/host/` first.
2. Run `make test-host` for a fast loop (no ROM link).
3. When flash/RAM symbols or C hooks change, run full `make test`.
4. After intentional generator output changes, run `make update-goldens` and commit `tests/goldens/`.
5. For player-visible behavior, run the [manual smoke checklist](#manual-smoke-checklist).

## Commands

| Command | Purpose |
|---------|---------|
| `make test-host` | Python tests + `validate_ram_map` + `validate_lynjump` + `event-test` (if event C sources exist) |
| `make test` | `test-host` + full ROM build + `memory_report` |
| `make update-goldens` | Regenerate committed golden files under `tests/goldens/` |
| `make compare` | Optional ROM SHA-1 check for release snapshots (not in `make test`) |

**Requirements:** Linux, WSL, or Windows (devkitPro MSYS2), plus `baserom.gba`, `agbcc`, and the normal build dependencies from [README.md](../README.md).

## Manual Smoke Checklist

Run these in an emulator after `make test` passes when you touched the related feature:

| Area | Steps | Expected |
|------|-------|----------|
| Custom cards | New game → trunk/shop | Known custom card shows correct art, name, and stats |
| Trunk sort (compressed) | Trunk with hide-unowned enabled → cycle sort modes | Owned-only list reorders (name, ATK, qty, etc.) and stays owned-only |
| Custom decks | Duel a manifest duelist | Opponent deck matches manifest |
| Save / decks | New game → edit deck 2/3 → save → reload | Extra decks and active index persist |
| Voices | Debug menu or duel trigger | Custom clip plays; no mixer crash |

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Host tests | `tests/host/*.py` | `unittest` modules discovered by `make test-host` |
| Golden files | `tests/goldens/` | Committed expected generator/output snapshots |
| Fixtures | `tests/fixtures/` | Minimal manifests and save blobs for tests |
| Card manifest validation | `tools/card_manifest.py` | Shared manifest schema checks |
| Deck manifest codegen | `tools/duelist_deck_validate.py` | Deck validation and `.inc` generation |
| Flash layout validator | `tools/validate_ram_map.py` | Parses `asm/ram_map.s` for overlaps |
| Deck persist (host) | `tools/player_deck_persist.py` | Serialize/deserialize layout used in tests |
| Multiple player decks validator | `tools/validate_player_decks.py` | RAM map, switch invariants, save-buffer rules |
| Deck persist (ROM) | `src_custom/persist/player_deck_persist.c` | `IsCompleteDeck` / magic checks used by `player_decks.c` |
| Player deck switch tests | `tests/host/test_player_decks.py` | Host mirror of deck 1/2/3 flush/load behavior |
| Player deck validator tests | `tests/host/test_validate_player_decks.py` | Source + ELF checks for multi-deck layout |
| Voice pipeline tests | `tests/host/test_voices.py` | Trim, DPCM, note encoder, clip validation |
| Portrait validator | `tools/validate_portrait.py` | 64×64 indexed PNG rules, palette index 0, shifted tile bytes |
| Portrait tests | `tests/host/test_portraits.py` | Validates `src_custom/assets/portraits/*.png` |
| Compressed trunk sort validator | `tools/validate_trunk_sort.py` | Ensures hide-unowned trunk lists keep dynamic/vanilla sort order |
| Trunk sort tests | `tests/host/test_trunk_sort.py` | Source invariants for compressed trunk + dynamic sorting |
| Test entrypoints | `Makefile` targets `test`, `test-host`, `update-goldens` | Local automation |

## TODO

- Add `make test-fast` alias if contributors want host-only checks documented separately.
- Add GitHub Actions mirroring `make test` when CI is enabled.
- Expand golden coverage for additional generators (rewards, shiny zones) as those areas gain strict TDD.

## Limitations & Bugs

- No emulator automation yet; manual checklist covers in-ROM UX.
- `tools/player_deck_persist.py` models the extra-deck flash record as one contiguous blob for tests; ROM code still writes separate flash fields via `sub_80588C4`.
- Full golden files can churn when generators change; always review `make update-goldens` diffs.
- `make test` requires a full ROM build and is slower than `make test-host`.
