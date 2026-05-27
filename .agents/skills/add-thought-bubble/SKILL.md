---
name: add-thought-bubble
description: "Use when adding or changing overworld thought bubbles, thought.png assets, or event-flag-driven bubble art in this repo. Read documentation/thought-bubbles.md first; register bubbles in src_custom/thought_bubble_table.inc under src_custom/assets/thought_bubbles/."
---

# Add Thought Bubble

Use this skill when adding, changing, or debugging world-map thought bubbles.

## Required Reading

Read **`documentation/thought-bubbles.md`** before editing. It covers the asset layout, build rules, registration table, runtime selection, code locations, and known limitations.

## Core Rule

Register every new bubble in **`src_custom/thought_bubble_table.inc` only**. Do not hand-edit `INCBIN`, enums, or asset tables in `overworld_hooks.c` for new bubbles.

## Where To Look First

| Step | Location |
|------|----------|
| Bubble folders | `src_custom/assets/thought_bubbles/<event_name>/thought.png` |
| Build rules | `graphics.mk` (recursive `thought.dmp` / `thought.gbapal`) |
| Registration | `src_custom/thought_bubble_table.inc` |
| Runtime loader | `LoadThoughtBubbleGfx`, `GetThoughtBubbleIdForFlag` in `src_custom/overworld_hooks.c` |
| Latest-flag tracking | `SetFlag__Replacement` in `src_custom/flag_hooks.c` |
| Public API | `include/thought_bubble.h` |

## Workflow

1. Read `documentation/thought-bubbles.md`.
2. Create a folder under `src_custom/assets/thought_bubbles/` with `thought.png` (128×64 layout per doc).
3. Add a row to `THOUGHT_BUBBLE_ASSET_LIST` in `src_custom/thought_bubble_table.inc`.
4. Add `_(0x??, SYMBOL)` entries to `THOUGHT_BUBBLE_FLAG_LIST` for the event flag(s) that should show that bubble.
5. Run `make`.

## Notes

- Selection uses the **most recently triggered** event flag, not the “most important” active flag.
- Unmatched flags fall back to the `DEFAULT` bubble.
- Repack step uses `tools/repack_128x64_obj.py`; see the doc for image constraints.
