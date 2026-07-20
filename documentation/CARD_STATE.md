# CARD_STATE — latest session

**Last worked on:** 2026-07-20 — Effect CCTO (YGOPRO-shaped C registry)

**Outcome:** Uniform `struct Effect` (type + code + cond/cost/target/op). All 30 JSON scripts emit ACTIVATE rows; damage-calc ATK boosts are CONTINUOUS Effects. Dispatch/events go through `Effect_*`. Unconverted LynJump cards still legacy.

**Open / next:** Wrap more legacy cards as Effect rows (≥10/pack); Heavy Storm / Crush Card / battle continuous as CCTO.
