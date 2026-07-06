# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Soul Taker: rewritten as standard cursor-targeting card (like Block Attack)

**Files touched:**
- `src_custom/spell_effects/soul_taker.c` — rewritten from PickZone to traditional cursor targeting (IsSoulTakerCard, FieldHasSoulTakerTarget, BeginSoulTakerTargeting, TrySelectSoulTakerTarget, CancelSoulTakerTargeting, EffectSoulTaker)
- `include/soul_taker.h` — defines DUEL_CURSOR_SOUL_TAKER_TARGET (45), declares all 6 functions
- `src_custom/code_8043EF4_hooks.c` — added SOUL_TAKER if-block in HandlePlayerBackrowAction, A/B button case dispatch

**How it works:** Matches the proven Block Attack pattern. HandlePlayerBackrowAction shows popup + sets cursor state. Main input loop handles movement. On A: validates target, calls ActivateSpellEffect → EffectSoulTaker → trap check → destroy target + give opponent 1000 LP + self-destruct. On B: cancel.

**Outcome:** `make test-cards-build` passes clean. Ready to playtest.
