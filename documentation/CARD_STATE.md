# CARD_STATE — latest session

**Last worked on:** 2026-07-12 — Maps: connection overrides, slot tracking, runtime redirects

**Files touched:**
- `tools/custom_map_manifest.json` — regenerated: all connections include `slot` index
- `tools/regenerate_manifest.py` — added `slot` to each connection dict
- `tools/build_custom_maps.py` — added `generate_manifest_connection_overrides()`, builds `u8[61][5]` table
- `src_custom/map_transition_hooks.c` — includes override table, checks in `sub_80523EC__Replacement`
- `Makefile` — added `manifest_connection_overrides.inc` to `CUSTOM_MAP_GENERATED`
- `documentation/session_logs/2026-07-12.md` — added connection override entry

**Outcome:** Changing a connection target in the manifest actually redirects map transitions. Zero overrides by default (matches ROM), override only when manifest target differs from ROM. Gated by `enable_manifest_map_overrides`.
