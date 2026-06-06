# Map Events — One File Per Scene

---

## Index

- [Introduction](#introduction)
- [Authoring Map Enter Events](#authoring-map-enter-events)
- [Story Sequence](#story-sequence)
- [Runtime Dispatch](#runtime-dispatch)
- [Object And NPC Scripts](#object-and-npc-scripts)
- [Player Choice Branching (Future)](#player-choice-branching-future)
- [Code Locations](#code-locations)
- [Tooling](#tooling)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

---

## Introduction

Custom overworld scenes are edited as C macro files under `events/scripts/`. Each file is named `map_<id>_state_<state>.c`. The **filename is the scene id** — no wrapper macro is required.

Put a linear map-enter cutscene at the top of the file. Object talk scripts, save prompts, and similar interactions still use `EVENT_SCRIPT_REPLACEMENT` at the bottom when they must override a specific vanilla script address.

---

## Authoring Map Enter Events

Write event macros directly at the top of `events/scripts/map_NN_state_MM.c`:

```c
#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_09_state_01: map 9 state 1 */

PLAY_MUSIC(MUSIC_KAIBACORP)
SET_FLAG(EVENT_FLAG_SAW_INTRO_CUTSCENE)
PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Alright guys, I'm gonna\n"
    "totally rock with this deck!\n\n"
)
FADE_SCREEN(4)
WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTH, 1, 4, 0)
```

Use normal event macros (`TEXT`, `MOVE_OBJECT`, `PORTRAIT`, `WARP`, etc.). Do **not** embed `{CARD_1}` / `{CARD_2}` choice text in linear map enter scripts.

After editing, run `make`. The compiler regenerates `src_custom/generated/event_script_replacements.inc`.

---

## Story Sequence

[`events/story_sequence.txt`](../events/story_sequence.txt) lists **every** map scene (catalog order). Uncomment a scene to enable it; only uncommented scenes are in the active play queue.

When the story catalog file is present, **vanilla map enter scripts are never loaded**. Map enters that are not the next pending story scene run an empty no-op script instead.

Regenerate skeletons and the master list:

```bash
python3 tools/vanilla_events.py generate-story-skeleton
```

To add a new story beat:

1. Uncomment `map_NN_state_MM` in `events/story_sequence.txt` (or run `generate-story-skeleton` first).
2. Edit `events/scripts/map_NN_state_MM.c` with enter macros at the top.
3. Run `make`.

---

## Runtime Dispatch

When the overworld runs a map's enter script (`InitiateScript(gOverworld.unk1F4[...])`), `InitiateScript__Replacement` resolves the script in this order:

When `events/story_sequence.txt` lists catalog scenes, **vanilla map enter scripts are never loaded**. Map enters that are not the next pending story scene run an empty no-op script instead.

1. **Story sequence** — If `gStorySequenceMode` and the current map/state matches `gStorySequence[gStorySequenceProgress]`, run that scene and advance progress.
2. **Story mode, no match** — Empty no-op enter (`gEventScriptNopEnterNode`); vanilla cutscenes are not loaded.
3. **No story catalog** — `gMapEventBindings[]` when present (legacy).
4. **Vanilla** — Original enter script pointer (legacy only).

| Trigger | Resolution |
|--------|------------|
| Map enter (story mode) | Pending scene in `gStorySequence[]` only |
| Map enter (story mode, wrong map) | Vanilla |
| Map enter (no story file) | `gMapEventBindings[mapId, state]` |
| Object / exit / duel | `gEventScriptReplacements[vanillaAddr]` |

Runtime progress is tracked in `gStorySequenceProgress` (IWRAM).

---

## Object And NPC Scripts

Keep `EVENT_SCRIPT_REPLACEMENT` blocks **after** the map enter macros:

```c
EVENT_SCRIPT_REPLACEMENT(0x08E62154, map_09_state_01_replay, 0x08F04040, 0x08F04040)
END_EVENT_SCRIPT()
```

Files that only customize NPCs (no enter macros at the top) contain replacements only. That is expected when vanilla enter is the shared no-op script `0x08F04034`.

---

## Player Choice Branching (Future)

Linear map enter scripts intentionally skip player choices. When you need branching dialogue again, use **`EVENT_SCRIPT` helper nodes** wired from a **single** enter replacement.

See the choice text format and branching pattern in the previous docs revision — use `EVENT_SCRIPT_REPLACEMENT` + `EVENT_SCRIPT` instead of top-level enter macros when choices are required.

| Style | Use when |
|-------|----------|
| Top-level enter macros | Map enter is linear; no player choices |
| `EVENT_SCRIPT_REPLACEMENT` + `EVENT_SCRIPT` | Map enter needs `{CARD_1}` / `{CARD_2}` choices |
| `EVENT_SCRIPT_REPLACEMENT` only | Object dialogue, save prompts, duels, NPC warps |

---

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Map enter dispatch | `EventSystem_ResolveMapEnterScript` in `src_custom/event_system_hooks.c` | Story queue first, then map bindings |
| Story sequence table | `gStorySequence[]` in `src_custom/generated/event_script_replacements.inc` | Generated from `events/story_sequence.txt` |
| Story progress | `gStorySequenceProgress` in `asm/ram_map.s` | Index of next main-story scene |
| Address replacements | `EventSystem_ResolveScript` in `src_custom/event_system_hooks.c` | Object/NPC vanilla pointer overrides |
| Binding table | `gMapEventBindings[]` in `src_custom/generated/event_script_replacements.inc` | Generated `{mapId, mapState, script}` rows |
| Macro authoring | `events/scripts/event_macros.h` | `TEXT`, `WARP`, etc. |
| Compiler | `tools/vanilla_events.py` | Parses C macros, emits bindings and bytecode |

---

## Tooling

```bash
# Regenerate ROM hooks after editing events/scripts/*.c
make

# Refresh all scene skeletons + catalog-ordered story_sequence.txt
python3 tools/vanilla_events.py generate-story-skeleton

# Validate all event C sources
python3 tools/vanilla_events.py test-c events/scripts/*.c
```

Find vanilla script addresses and object ids in `events/vanilla/vanilla_event_catalog.md` (reference only—do not edit for ROM changes).

---

## TODO

- [ ] Optional branch compilation for choice-heavy enter scenes without manual `EVENT_SCRIPT` graphs
- [ ] Object-script dispatch table (map + object id) to drop remaining NPC address hooks
- [ ] Exit-script bindings similar to map enter

---

## Limitations & Bugs

- **Linear enter only:** Top-level map enter scripts must not contain `{CARD_1}` / `{CARD_2}` choice text.
- **Shared vanilla nop:** `0x08F04040` is the terminal no-op script; branch tails should point to it when a path ends.
- **Custom events toggle:** `disable_custom_events = TRUE` in `configs/runtime.c` bypasses custom resolution entirely.

Report issues with scene flow, missing bindings, or migration glitches in the project issue tracker.
