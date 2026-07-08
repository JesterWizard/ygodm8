# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Fixed Dark Armed Dragon effect text display

**Files touched:**
- `src_custom/activated_effects/dark_armed_dragon.c`
- `src_custom/effect_text_hooks.c`

**Outcome:** make test-cards-link passes. Changed from Duel_ShowEffectTextTyped → Duel_ShowCardEffectText with direct popup_1 ID. Excluded DAD from sub_801CF08 auto-popup path (like BLS/Chaos Emperor) so it shows only the popup text without the 'was activated.' prefix + #1 page break. Added include for card_effect_texts.h.

**Open / next:**
- playtest both effect text and targeting flow
