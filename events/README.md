# Event Pipeline

Vanilla overworld events can be extracted from `baserom.gba` into YAML for cataloging or regenerating C macro files:

## Which Files To Edit

Edit small C macro files under `events/scripts/`.

`make` compiles `events/scripts/*.c` when present and rebuilds `ygodm8.gba`.

Do not edit `events/vanilla/vanilla_event_catalog.md` for ROM changes. The catalog is generated from the YAML and exists only as a readable reference while you search for scenes, object ids, script addresses, dialogue, and visible actions.

## Story Sequence Drives All Map Enter Events

[`events/story_sequence.txt`](story_sequence.txt) is the **only** source of map enter cutscenes. It lists every map scene in catalog order (416 scenes). Each line is commented by default:

- **Uncomment** a scene to enable its custom enter script from `events/scripts/<name>.c`
- **Commented** scenes run **no** map enter event — vanilla enter cutscenes are never loaded
- Active scenes play **in file order** when the player enters that map/state

Refresh the full skeleton and catalog-ordered list:

```bash
python3 tools/vanilla_events.py generate-story-skeleton
```

This creates missing `events/scripts/map_NN_state_MM.c` skeletons (with `END()` placeholder) and rewrites `story_sequence.txt` from the vanilla catalog. Currently active (uncommented) scenes are preserved unless you pass `--reset-active`.

## C Macro Workflow

See [documentation/map-events.md](../documentation/map-events.md) for the full guide.

Each map/state file is named `map_<id>_state_<state>.c`. Put the map enter cutscene at the **top** of the file:

```c
#include "event_macros.h"
#include "overworld.h"

/* map_09_state_01: map 9 state 1 */

PLAY_MUSIC(MUSIC_KAIBACORP)
TEXT("It's time to duel!")
WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTH, 1, 4, 0)
```

Object and NPC scripts that still need a vanilla address override go in `EVENT_SCRIPT_REPLACEMENT` blocks after the enter script.

## Extraction Workflow

1. Use `vanilla_event_catalog.md` to find the map/state/object/script you want.
2. Uncomment the scene in `events/story_sequence.txt`.
3. Edit the matching C macro file under `events/scripts/`.
4. Run `make`.

If you only want vanilla overworld behavior at runtime, set
`disable_custom_events = TRUE` in `configs/runtime.c`. That bypasses the
custom event resolver without touching the event files themselves.
