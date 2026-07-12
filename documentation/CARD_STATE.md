# CARD_STATE — latest session

**Last worked on:** 2026-07-12 — Maps: player start positions in manifest

**Files touched:**
- `tools/custom_map_manifest.json` — regenerated: all entries include `start` dict with player spawn per-slot
- `tools/regenerate_manifest.py` — added `_read_player_start()`, wired into entry generation
- `tools/build_custom_maps.py` — added `_read_base_spawn()`, `generate_manifest_spawn_overrides()`, wired into main
- `src_custom/debug/overworld_debug_overlay_hooks.c` — includes `manifest_spawn_overrides.inc`, applies overrides in `OverworldLoadGraphics__Replacement`
- `Makefile` — added `manifest_spawn_overrides.inc` to `CUSTOM_MAP_GENERATED`
- `documentation/session_logs/2026-07-12.md` — added spawn entry

**Outcome:** Each manifest entry has a `start` dict mapping slot index to `{x, y, dir}`. Edit any value and rebuild to override the player's spawn position/direction for that connection slot. Zero ROM overhead by default.
