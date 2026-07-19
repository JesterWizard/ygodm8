# CARD_STATE — latest session

**Last worked on:** 2026-07-19 — Fast AI: light attacks + full-sim budget

**Files touched:**
- `src_custom/ai_sim_fast.c` — light-score face-up/direct/FD attacks (vanilla formulas); preferred-zone prune
- `src_custom/ai_hooks.c` — ≤16 full save/exec sims (high-impact first); skip batch GFX
- `src_custom/ai_simulation_hooks.c` — skip GY RefreshDisplay under fast_ai
- tests, `configs/runtime.h`

**Outcome:** `make` OK; host AI tests pass.

**Open / next:** Playtest — decisions should be much snappier; winning attacks still via light score.
