# Custom Card Memory

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Custom cards begin after `TALONS_OF_SHURILANE`; in code this is the `SORCERER_OF_DARK_MAGIC` / `CUSTOM_CARD_START` boundary. Any card added after that point in `tools/card_data_manifest.json` increases `NUM_CUSTOM_CARDS`.

The generated card count now drives the save-memory mirrors and the card shop list buffer. Contributors no longer need to manually resize the fixed `0x20` custom-card save blocks or the shop list allocation when adding cards past the vanilla 800.

The SRAM quantity mirrors keep a minimum `0x20` byte stride for save compatibility with existing builds. They grow past `0x20` only when the manifest has more than 32 custom cards.

## Plan

`make` runs `tools/add_card_art.py --card-ids` before compiling generated-dependent code. That writes:

| Generated file | Purpose |
|----------------|---------|
| `include/constants/card_counts.h` | C constants for total and custom card counts |
| `generated/card_counts.ld` | Linker constants used by `ldscript.ld` |
| `generated/card_memory_sizes.inc` | Assembler constants used by `asm/ram_map.s` |

Memory is split by lifetime:

| Region | Use | Growth rule |
|--------|-----|-------------|
| IWRAM | Hot custom runtime state | Fixed unless a new fast buffer is added |
| EWRAM | Runtime custom arrays and card shop list | Shop list grows to fit every generated card in 7-card rows |
| SRAM | Persistent save mirrors | Custom card quantity mirrors keep a 32-card minimum, then grow by `NUM_CUSTOM_CARDS` |

The live custom quantity arrays (`gCustomTrunkCardQty`, `gCustomShopCardQty`, `gCustomPlayerTempCardQty`) are linker-sized from `NUM_CUSTOM_CARDS`. Their persistent SRAM mirrors are allocated in `asm/ram_map.s` from `CUSTOM_CARD_QTY_BYTES`.

Run this after adding custom cards:

```sh
make memory-report
```

The report prints IWRAM, EWRAM, and SRAM usage against the available custom allocation windows. Rows are white below 50%, yellow from 50% up to 90%, and red at 90% or higher.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Custom card boundary | `render_card_ids_header` in `tools/add_card_art.py` | Emits `CUSTOM_CARD_START`, `NUM_TOTAL_CARDS`, and `NUM_CUSTOM_CARDS` |
| Generated memory sizes | `render_card_memory_sizes_asm` in `tools/add_card_art.py` | Converts manifest card count into assembler allocation constants |
| Runtime custom arrays | `ldscript.ld` | Places live custom quantity arrays using `NUM_CUSTOM_CARDS` |
| SRAM mirrors and shop list | `asm/ram_map.s` | Allocates custom save mirrors and `gCustomShopCardList` from generated sizes |
| Build wiring | `Makefile` | Regenerates card memory constants and exposes `make memory-report` |
| Memory report | `tools/memory_report.py` | Reads ELF symbols and reports IWRAM/EWRAM/SRAM usage |

## TODO

- Add a hard build-time failure if any custom free-space window exceeds its available range.
- Extend the report with per-allocation detail if a region approaches the red threshold.

## Limitations & Bugs

The report measures the custom allocation windows exported by `asm/ram_map.s`, not every byte used by the original game engine. SRAM usage is calculated from exported save ranges and custom persistent mirrors, so new SRAM allocations should use `SET_ARRAY` if they need to appear in the report automatically.
