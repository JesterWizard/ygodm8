# Event Pipeline

Vanilla overworld events can be extracted from `baserom.gba` into YAML for cataloging or regenerating C macro files:

## Which Files To Edit

Edit small C macro files under `events/scripts/`.

`make` compiles `events/scripts/*.c` when present and rebuilds `ygodm8.gba`.

Do not edit `events/vanilla/vanilla_event_catalog.md` for ROM changes. The catalog is generated from the YAML and exists only as a readable reference while you search for scenes, object ids, script addresses, dialogue, and visible actions.

## Edit Order

The vanilla catalog is already arranged in the game-defined progression order.
When editing multiple events, work top to bottom through
`events/vanilla/vanilla_event_catalog.md`, then mirror those entries in
`events/scripts/`.

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

## C Macro Workflow

Create one file per event or scene in `events/scripts/`, for example:

```c
#include "event_macros.h"
#include "overworld.h"

EVENT_SCRIPT_REPLACEMENT(0x08E12345, SCENE_01_YUGI_01, 0, 0)
  PORTRAIT(1, 0, PORTRAIT_LEFT)
  TEXT("It's time to duel!")
  MOVE_OBJECT(2, 1, 4, 0)
  END()
END_EVENT_SCRIPT()
```

For long dialogue, `TEXT("""...""")` is accepted and usually easier to read than escaping every line break.

## Extraction Workflow

1. Use `vanilla_event_catalog.md` to find the map/state/object/script you want.
2. Edit the matching C macro file under `events/scripts/`.
3. Run `make`.

The compiler writes `src_custom/generated/event_script_replacements.inc` from the C macro files.

After editing C macro files, rebuild the event replacements and ROM:

If you only want vanilla overworld behavior at runtime, set
`disable_custom_events = TRUE` in `configs/runtime.c`. That bypasses the
custom event resolver without touching the event files themselves.
