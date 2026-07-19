# Event Pipeline

Vanilla overworld events can be extracted from `baserom.gba` into YAML for cataloging or regenerating C macro files:

## Which Files To Edit

Edit small C macro files under `events/scripts/`.

`make` compiles `events/scripts/*.c` when present and rebuilds `ygodm8.gba`.

Do not edit `events/vanilla/vanilla_event_catalog.md` for ROM changes. The catalog is generated from the YAML and exists only as a readable reference while you search for scenes, object ids, script addresses, dialogue, and visible actions.

## Preferred authoring style

Reference scene: [`events/scripts/map_09_state_01.c`](scripts/map_09_state_01.c).

For multi-beat cutscenes, write **one sequential** `EVENT_SCRIPT_REPLACEMENT` and use `CHOICE` / `ELSE` / `END_CHOICE` for player options. The compiler expands that into the Script-node graph the VM needs.

| Prefer | Over |
|--------|------|
| One scene body + `CHOICE`/`ELSE`/`END_CHOICE` | Many hooked mid-address replacements |
| `TALK(portrait, "page", "page")` | `PORTRAIT` + `TEXT`, or triple-quoted blobs |
| `TEXT("page", "page")` | Manual `\n` / blank-line page markup |
| `EVENT_NOP` (or omit branches on 2-arg replacement) | Raw `0x08F04040` |

Notes:

- **Each string arg = one textbox page.** Soft wraps inside a page are unnecessary — the compiler word-wraps to 28 chars / 2 rows (overflow spills to the next page).
- Legacy `\n` soft-wraps still compile (unwrapped automatically); prefer one string per page when editing.
- Choice prompts keep an internal newline: `"{CARD_1}Yes\nNo{CARD_2}"`.
- `TALK(portrait, ...)` defaults to `EXPRESSION_NEUTRAL` + `PORTRAIT_LEFT`. Pass expression and/or position when needed: `TALK(p, expr, pos, "...")`.
- A single word longer than 28 characters fails the build with a console error naming the offending line.
- `{CARD_1}` / `{CARD_2}` in the text before `CHOICE()`; first arm = option 1, `ELSE` arm = option 2; both merge after `END_CHOICE()`.
- Nested `CHOICE` is allowed.
- Keep `HIDE_PORTRAIT()` before movement / reactions / stage business.
- Keep `PORTRAIT` + `TEXT` only when something (e.g. `PLAY_MUSIC`) must sit between them.
- Only the enter vanilla address needs a replacement; mid-scene vanilla hooks are unnecessary once enter is fully custom.
- Small NPCs can still use multiple named `EVENT_SCRIPT_REPLACEMENT` / `EVENT_SCRIPT` nodes (casino pattern).
- Bulk rewrite helper: `python3 tools/vanilla_events.py migrate-dialogue-style`.

```c
#include "event_macros.h"
#include "overworld.h"

EVENT_SCRIPT_REPLACEMENT(0x08E12345, scene_duel_offer)
  TALK(PORTRAIT_YUGI,
      "It's time to duel!",
      "{CARD_1}Yes\nNo{CARD_2}")
  CHOICE()
    TALK(PORTRAIT_YUGI, "Let's go!")
  ELSE()
    TALK(PORTRAIT_YUGI, "Maybe later.")
  END_CHOICE()
END_EVENT_SCRIPT()
```

## Edit Order

STORY (the map order may not match the story order)
```
map_09_state_01.c - Joey talks to player
map_01_state_01.c - Clocktower 1 - Ishizu speech
map_07_state_01.c - Game shop inside
map_12_state_12.c - Kaiba corp Rebecca
map_14_state_01.c - Train station entrance 1
map_14_state_07.c - Train station entrance 1 - post duel - Joey - copy 1?
map_14_state_08.c - Train station entrance 1 - post duel - Joey - copy 2?
map_14_state_09.c - Train station entrance 1 - post duel - Yugi - copy 1?
map_14_state_10.c - Train station entrance 1 - post duel - Yugi - copy 2?
map_15_state_01.c - Train station inside 1
map_16_state_01.c - Duel Express 1 - Cart 1
map_17_state_01.c - Duel Express 1 - Cart 2
map_18_state_01.c - Duel Express 1 - Cart 3
map_20_state_01.c - Egypt Exhibit Train Station stop 1
map_21_state_01.c - Egypt Exhibit ticket hall 1
map_23_state_01.c - Millenium Guardian 1
map_22_state_03.c - Egypt Exhibit main hall 1 (Seto arrives with Mokuba)
```

## Extraction Workflow

1. Use `vanilla_event_catalog.md` to find the map/state/object/script you want.
2. Edit the matching C macro file under `events/scripts/`.
3. Run `make`.

The compiler writes `src_custom/generated/event_script_replacements.inc` from the C macro files.

If you only want vanilla overworld behavior at runtime, set
`enable_custom_events = FALSE` in `configs/runtime.c`. That bypasses the
custom event resolver without touching the event files themselves.
