# CARD_STATE — latest session

**Last worked on:** 2026-07-05 — Hourglass defers field gfx until popup finishes

**Files touched:**
- `src_custom/activated_effects/hourglass_of_life.c`
- `src_custom/activated_effects/injection_fairy_lily.c`
- `src_custom/activated_effects/karate_man.c`

**Outcome:** LP pay uses `Duel_ChangeLp(..., FALSE)`; field refresh happens when `sub_8041CCC` completes after popup; `make all` passes

**Open / next:** Playtest Hourglass — stats should update only after dismissing popup
