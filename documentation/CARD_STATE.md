# CARD_STATE — latest session

**Last worked on:** 2026-07-19 — Pack art no transparent holes (skip pal index 0)

**Files touched:**
- `tools/build_card_packs.py` — opaque pixels never map to palette index 0
- regenerated pack `.8bpp` assets

**Outcome:** `make` OK. Machine/Rare pack holes fixed (light pixels no longer → transparent index 0).

**Open / next:** Playtest Machine + Rare packs look solid.
