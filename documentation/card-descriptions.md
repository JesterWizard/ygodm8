# Card Descriptions

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Card description text in this repo is meant to be edited in one friendly place and then converted into the stricter in-game format automatically.

There are two layers involved:

1. human-readable source strings in `src/hooks/card_description_data.c`
2. generated runtime byte data in `src/hooks/card_description_data_generated.inc`

If you are adding or changing a description, you usually only need to touch the first one.

The goal is simple:

- keep the text pleasant to edit
- keep the game-side format automatic
- avoid making contributors hand-write packed byte data

The build now regenerates the runtime include automatically when `card_description_data.c` changes.

## Plan

Use this workflow when adding or editing a custom card description:

1. Open `src/hooks/card_description_data.c`.
2. Add or edit a `static const char *const <Symbol>[] = { ... }` block with exactly 2 strings:
   - the first string is page 1
   - the second string is page 2
3. Point the relevant `gCardData_NEW` entry at `<Symbol>Data`.
4. Run `make` as normal.
5. Test the card in-game.

What happens automatically during build:

- `make` runs `python3 tools/generate_card_description.py --update-file src/hooks/card_description_data.c`
- the script reads the 2 source strings
- it wraps them to the current in-game layout model
- it writes the runtime byte data into `src/hooks/card_description_data_generated.inc`
- `card_description_data.c` includes that generated file, so the game gets the correct symbol at link time

For a first edit, this is an example of how the text struct for your card should look:

```c
static const char *const gMilusRadiantDescription[] = {
    "Page 1 text here.",
    "Page 2 text here.",
};
```

After that, you call the text struct in your card entry in card_data_hooks.c:

```c
.description = gMilusRadiantDescriptionData,
```

Files you normally edit:

- `src/hooks/card_description_data.c`
- `src/hooks/card_data_hooks.c`

Files you normally do not edit by hand:

- `src/hooks/card_description_data_generated.inc`

There is also a commented reference block in `card_description_data.c`. Treat that as a known-good example and formatting reference, not as the live runtime source.

Current authoring pattern:

```c
static const char *const gMilusRadiantDescription[] = {
    "Page 1 text here.",
    "Page 2 text here.",
};
```

Current runtime symbol pattern:

```c
.description = gMilusRadiantDescriptionData,
```

How conversion works:

- The generator script reads every `static const char *const <Symbol>[] = { "page1", "page2" };` block in `card_description_data.c`.
- It wraps each page into the currently observed in-game row widths.
- It emits raw byte data for `<Symbol>Data` into `card_description_data_generated.inc`.
- `card_description_data.c` includes that generated file so the runtime symbol is available to the build.

Current layout constraints:

| Row | Observed width |
|--------|----------|
| 1 | 12 |
| 2 | 14 |
| 3 | 14 |
| 4 | 14 |
| 5 | 12 |

Important constraints:

- Each description currently assumes exactly 2 pages.
- Wrapping is word-based. The generator will not split a word across rows.
- If any word is longer than the row width it needs to fit in, generation fails.
- If the page text does not fit within the 5 available rows, generation fails.
- The generated include is runtime data. It is not meant to be edited manually.
- The commented example/reference block in `card_description_data.c` is documentation, not the runtime source of truth.

Practical advice for newcomers:

- Start by writing the text naturally.
- Run `make`.
- If the generator fails, shorten the wording rather than forcing awkward punctuation.
- If the text compiles but looks wrong in-game, compare it against the commented reference block and adjust the wording until it fits the current row model cleanly.

Build behavior:

- `Makefile` declares `src/hooks/card_description_data_generated.inc` as a generated dependency.
- `make` runs `python3 tools/generate_card_description.py --update-file src/hooks/card_description_data.c` before compiling `src/hooks/card_description_data.c`.
- Editing `card_description_data.c` is therefore enough to trigger regeneration on the next build.

Manual regeneration command:

```bash
python3 tools/generate_card_description.py --update-file src/hooks/card_description_data.c
```

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Editable source strings | `src/hooks/card_description_data.c` | Holds the 2 human-readable source strings per custom description |
| Generated runtime data | `src/hooks/card_description_data_generated.inc` | Auto-generated raw byte data used by the game at runtime |
| Generator script | `tools/generate_card_description.py` | Wraps source strings to the current row model and emits `<Symbol>Data` byte arrays |
| Build trigger | `Makefile` | Regenerates the include before compiling `card_description_data.c` |
| Runtime lookup | `GetCardDescription_Hook` in `src/hooks/card_hooks.c` | Uses custom description data when present and falls back to vanilla otherwise |
| Card data wiring | `gCardData_NEW` in `src/hooks/card_data_hooks.c` | Connects a card entry to its custom description runtime symbol |
| In-game card detail renderer | `sub_800BCB0` and surrounding card-detail flow in `src/card.c` | Displays the description data on the card details screen |

## TODO

- Extend the generator if the project needs 3-page or longer descriptions.
- Improve the generator error output so it reports the exact row where text overflow starts.
- Add a helper mode that prints the wrapped rows for quick review without writing files.

## Limitations & Bugs

- The current row widths are based on observed in-game behavior, not a fully reverse-engineered format spec.
- Description fit is currently strict. Text that barely misses the row model must be shortened manually.
- The generator only supports 2-page descriptions right now.
- If the in-game renderer turns out to use different widths for some cards or languages, the generator will need to be updated.
