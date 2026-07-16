# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — XYZ white text: revert 8bpp index bug

**Files touched:**
- deleted `src_custom/print_card_hooks.c` — `0x4BB` / nibble remap were wrong
- `src_custom/LynJump.event` — removed PrintCard hook

**Outcome:** Card BG is 256-color; glyph color low byte is a direct palette index. Vanilla `0x4A` → index 74 = frame bank 4 slot 10 = white in `xyz.gbapal`. `0xBB` was index 187 = UI blue. Digits already use `0x46`–`0x4A`. `make` exits 0.

**Open / next:** Confirm white name/ATK/DEF in-game; Pendulum/Link mini borders still NULL.
