# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Fix trunk not showing cards from ID 1444+

**Files touched:**
- `Makefile` (deps: trunk/shop/code_801EF30_hooks → `card_trunk_generated.inc`)

**Outcome:** Root cause was stale `gCustomTrunkCards` in ROM (ended at 0x5A3) while loops used NUM=651 — not EWRAM/SRAM sizing (those were already correct at 0x28C / 0x4410). Relinked; trunk list now ends 0x5A4–0x5AB.

**Open / next:**
- Reload ROM; new game if save qty looks wrong after CUSTOM_CARD_QTY growth past 0x200 floor
- Implement real effect logic for the 8 stubbed cards
