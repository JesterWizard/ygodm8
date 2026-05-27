---
name: add-custom-portrait
description: "Use when adding or changing dialogue portraits, PORTRAIT() event art, or portrait assets in this repo. Read documentation/custom-portraits.md first; wire assets through src_custom/assets/portraits/, Makefile rules, include/overworld.h, and src_custom/portrait_hooks.c."
---

# Add Custom Portrait

Use this skill when adding, changing, or debugging custom dialogue portraits.

## Required Reading

Read **`documentation/custom-portraits.md`** before editing. It covers asset requirements, the build pipeline, registration, event usage, code locations, and known limitations.

## Core Rule

Follow the doc’s workflow end to end. Do not guess palette or tile format requirements.

## Where To Look First

| Step | Location |
|------|----------|
| Source PNG | `src_custom/assets/portraits/` |
| Build rules | `Makefile` (follow existing `player` portrait rules) |
| Palette shift | `tools/offset_portrait_8bpp.py` |
| Portrait ids | `enum Portrait` in `include/overworld.h` |
| Runtime loader | `DisplayPortrait__Replacement` in `src_custom/portrait_hooks.c` |
| Event macro | `PORTRAIT` in `events/scripts/event_macros.h` |
| Example usage | `events/scripts/map_09_state_01.c` |

## Workflow

1. Read `documentation/custom-portraits.md`.
2. Add a 64×64 indexed PNG (≤64 colors) under `src_custom/assets/portraits/`.
3. Add matching Makefile rules for `8bpp`, `shifted.8bpp`, `lz`, and `gbapal`; add outputs to `portrait_hooks` object deps.
4. Add a portrait id in `include/overworld.h`.
5. Add `INCBIN` and a branch in `src_custom/portrait_hooks.c`.
6. Use `PORTRAIT(...)` in event scripts; call `HIDE_PORTRAIT()` when leaving the scene.
7. Run `make` (regenerates event replacements and patches the ROM).

## Notes

- Dialogue portraits are 64×64 8bpp OBJ art, not 128×64.
- Vanilla OAM setup stays in `sub_804EB04`; custom code only loads tiles and palette.
- If replacing a vanilla entrypoint, also use the vanilla-function-replacements skill.
