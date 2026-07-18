# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Game Shop flat pitch root cause

**Files touched:**
- `tools/generate_voices.py`, `tools/generate_music.py` (private voicegroups; no global tone patches)
- `tests/host/test_music.py`
- regenerated `src_custom/generated/{voice,music}_*`

**Outcome:** Flat pitch was corrupted Game Shop key-split tables (voice/music tone patches). Fixed; HQ mixer re-enabled. `make` OK.

**Open / next:**
- Playtest Game Shop BGM pitch vs baserom
