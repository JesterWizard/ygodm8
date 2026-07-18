# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Fix duel icon cache in ROM

**Files touched:**
- `src_custom/overworld_hooks.c`
- `asm/ram_map_ewram.s`
- `documentation/repeatable-duel-icon.md`

**Outcome:** make exits 0. Cache moved to EWRAM (`gDuelIconCache`); GFX load restored per-frame. Icons should show again.

**Open / next:**
- Confirm train station icons visible + still smooth
