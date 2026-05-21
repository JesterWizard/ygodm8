# Event Pipeline

Vanilla overworld events can be extracted from `baserom.gba` into YAML for cataloging or regenerating C macro files:

```bash
make event-extract
```

This writes:

- `events/vanilla/vanilla_events.yaml`
- `events/vanilla/vanilla_event_catalog.md`

## Which Files To Edit

Edit small C macro files under `events/scripts/`.

`make event-compile` compiles `events/scripts/*.c` when present and rebuilds `ygodm8.gba`. YAML is only an extraction/interchange format now; run `make event-extract` if you need to recreate it from `baserom.gba`.

Do not edit `events/vanilla/vanilla_event_catalog.md` for ROM changes. The catalog is generated from the YAML and exists only as a readable reference while you search for scenes, object ids, script addresses, dialogue, and visible actions.

## C Macro Workflow

Create one file per event or scene in `events/scripts/`, for example:

```c
#include "event_macros.h"
#include "overworld.h"

EVENT_SCRIPT_REPLACEMENT(0x08E12345, SCENE_01_YUGI_01, 0, 0)
  PORTRAIT(1, 0, 0)
  DIALOGUE("It's time to duel!")
  MOVE_OBJECT(2, 1, 4, 0)
  END()
END_EVENT_SCRIPT()
```

Then run:

```bash
make event-compile
```

Use `EVENT_SCRIPT(name, on_false, on_true)` for local branch targets that are not direct vanilla replacements, and reference them by `name` from another script's `on_false` or `on_true`.

To seed macro files from extracted YAML replacements:

```bash
make event-extract
make event-export-c
```

For a full split of every reachable vanilla script, run:

```bash
make event-extract
python3 tools/vanilla_events.py export-c events/vanilla/vanilla_events.yaml --out-dir events/scripts --all
```

## Extraction Workflow

1. Run `make event-extract` to refresh the YAML and catalog from `baserom.gba`.
2. Use `vanilla_event_catalog.md` to find the map/state/object/script you want.
3. Edit the matching C macro file under `events/scripts/`.
4. Run `make event-compile`.

The compiler writes `src/hooks/generated/event_script_replacements.inc` from the C macro files.

After editing C macro files, rebuild the event replacements and ROM:

```bash
make event-compile
```

Validate extracted raw byte round trips with:

```bash
make event-validate
```

`make event-validate` checks extracted vanilla `raw_bytes` against `baserom.gba`. Use it before edits, or on a fresh extraction. It is expected to fail after you intentionally change `raw_bytes`.
