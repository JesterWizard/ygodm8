# CARD_STATE — latest session

**Last worked on:** 2026-07-12 — Maps: manifest restructure, collision overrides, docs

**Files touched:**
- `tools/custom_map_manifest.json` — restructured with `images` grouping, collision support
- `tools/regenerate_manifest.py` — created
- `tools/build_custom_maps.py` — generates `manifest_collision_overrides.inc`
- `src_custom/debug/overworld_debug_overlay_hooks.c` — collision override redirect
- `configs/runtime.h` / `runtime.c` — `enable_manifest_map_overrides` toggle
- `Makefile` — added generated inc files
- `documentation/custom-maps.md` — created
- `documentation/CARD_STATE.md` — this update

**Outcome:** Map editing is fully documented. User can swap graphics, add collision rects, create new maps — all from a single JSON manifest.
