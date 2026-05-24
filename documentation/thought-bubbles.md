# Thought Bubbles

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

World-map thought bubbles now swap art based on the most recently triggered event flag.

The system is built to keep the common workflow short:

1. add a new event folder with a `thought.png`
2. register that folder in one table
3. assign one or more event flags to that bubble in the same table
4. run `make`

The goal is to avoid hand-editing multiple declarations in `overworld_hooks.c` every time a new bubble is added.

## Plan

The feature has three layers:

1. asset build
2. latest-flag tracking
3. runtime bubble selection

### Asset Workflow

Each bubble lives in its own folder under `src_custom/assets/thought_bubbles/`.

Expected layout:

```text
src_custom/assets/thought_bubbles/
  event_01/
    thought.png
  event_02/
    thought.png
```

During build:

- `graphics.mk` finds every `thought.png` recursively
- each image becomes a `thought.dmp`
- each image also gets a `thought.gbapal`
- temporary `4bpp` files are created under `/tmp` and are not kept as normal outputs

### Registration Workflow

All bubble registration and flag assignment now lives in:

- `src_custom/thought_bubble_table.inc`

It exposes two lists:

```c
#define THOUGHT_BUBBLE_ASSET_LIST(_) \
  _(DEFAULT, "src_custom/assets/thought_bubbles/event_01/thought.dmp", "src_custom/assets/thought_bubbles/event_01/thought.gbapal") \
  _(MILLENNIUM_NECKLACE, "src_custom/assets/thought_bubbles/event_02/thought.dmp", "src_custom/assets/thought_bubbles/event_02/thought.gbapal")

#define THOUGHT_BUBBLE_FLAG_LIST(_) \
  _(0x2B, MILLENNIUM_NECKLACE)
```

What each list means:

- `THOUGHT_BUBBLE_ASSET_LIST`: symbolic bubble id to asset paths
- `THOUGHT_BUBBLE_FLAG_LIST`: event flag to symbolic bubble id

To add a new bubble:

1. create a new folder like `event_03`
2. place `thought.png` inside it
3. add a `THOUGHT_BUBBLE_ASSET_LIST` row pointing at the new `thought.dmp` and `thought.gbapal`
4. add one or more `_(0x??, SOME_NAME)` entries to `THOUGHT_BUBBLE_FLAG_LIST`
5. run `make`

You do not need to manually add new `INCBIN` declarations, enum values, or asset table rows in `overworld_hooks.c`.

### Runtime Model

At runtime:

- `SetFlag__Replacement` records the latest event flag seen
- `GetLatestThoughtBubbleEventFlag()` exposes that value
- `overworld_hooks.c` resolves the latest flag through the flag table
- if no flag matches, the `DEFAULT` bubble is used

Current behavior matrix:

| Latest Event Flag | Bubble |
|--------|----------|
| `0x2B` | `MILLENNIUM_NECKLACE` / `event_02` |
| none or unmatched | `DEFAULT` / `event_01` |

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Bubble asset folders | `src_custom/assets/thought_bubbles/` | Holds one `thought.png` per event bubble folder |
| Bubble build rules | `graphics.mk` | Recursively generates `thought.dmp` and `thought.gbapal` for every thought bubble folder |
| Bubble registration table | `src_custom/thought_bubble_table.inc` | Single source of truth for bubble ids, folders, and event-flag assignments |
| Runtime bubble loader | `LoadThoughtBubbleGfx` in `src_custom/overworld_hooks.c` | Loads the selected bubble tiles and palette into OBJ VRAM |
| Runtime bubble selection | `GetThoughtBubbleIdForFlag` in `src_custom/overworld_hooks.c` | Converts the most recent event flag into a bubble id |
| Latest-flag tracking | `SetFlag__Replacement` in `src_custom/flag_hooks.c` | Records the newest event flag that has been triggered |
| Reset behavior | `InitFlags__Replacement` in `src_custom/flag_hooks.c` | Clears the tracked latest flag when flags are reinitialized |
| Public accessor | `include/thought_bubble.h` | Exposes the latest thought-bubble event flag to the overworld hook |

## TODO

- Replace raw numeric flags in `src_custom/thought_bubble_table.inc` with named constants if a dedicated event-flag header is added.
- Add more event-specific bubbles once the desired progression flags are identified.
- Consider supporting multiple bubble images per event if the system needs map- or character-specific variants.

## Limitations & Bugs

- The system keys off the most recently triggered event flag, not the most narratively important active flag.
- If unrelated code sets another event flag after a story reward flag, that newer flag will control bubble selection.
- Bubble folders must contain a `thought.png` with the expected 128x64 layout used by `tools/repack_128x64_obj.py`.
- The current table is manual data entry. It is simpler than the previous flow, but it is not generated from script data yet.
