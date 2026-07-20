# CARD_STATE — latest session

**Last worked on:** 2026-07-20 — Fix memory-report EWRAM align false positives

**Outcome:** `make` OK; `make memory-report` OK. Simulator now applies EWRAM `& ~3` like `_kernel_malloc_ewram`.

**Open / next:** Partial ceilings in PARTIAL_EFFECTS.md; no more STUB_EFFECTS batches unless new stubs appear.
