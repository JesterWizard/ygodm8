# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Overworld map fade mid-transition flash

**Files touched:**
- `src_custom/debug/overworld_debug_overlay_hooks.c`
- `src_custom/event_system_hooks.c`

**Outcome:** Fade-out no longer undoes blend; custom map override runs while display is off. `make` OK.

**Open / next:**
- Playtest door/edge fade — should stay black until next map
