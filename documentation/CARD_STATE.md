# CARD_STATE — latest session

**Last worked on:** 2026-07-17 — Menu cursor icon picker

**Files touched:**
- `include/menu_cursor.h`, `src_custom/menu_cursor.c`
- `src_custom/debug/debug_menu_cursor.c`, `debug_menu.c`, `debug_menu_internal.h`
- `src_custom/start_menu_hooks.c`, `debug/debug_menu_startmenu.c`, `debug/ante_card_viewer.c`
- `src_custom/code_800AC64_hooks.c`, `asm/ram_map_ewram.s`, `asm/ram_map_sram.s`
- `graphics.mk`, `Makefile`, `src_custom/assets/cursors/*.png`

**Outcome:** `make` exits 0. Debug → Cursor: Eye / Kuriboh / Puzzle; saved to EWRAM+Flash.

**Open / next:** Playtest picker + save/load persistence on start menu
