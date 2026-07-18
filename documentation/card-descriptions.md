# Card Descriptions

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Card description text in this repo is edited in the card art manifest and converted into the stricter in-game format automatically.

There are two layers involved:

1. human-readable source strings in `tools/card_data_manifest.json`
2. generated runtime byte data in `src_custom/card_description_data_generated.inc`

The goal is simple:

- keep the text pleasant to edit
- keep the game-side format automatic
- avoid hand-writing packed byte data

The build now regenerates the runtime include automatically when the manifest changes.

Description **typeface** (vanilla / small / Emerald VWF) is separate — see [card-description-fonts.md](card-description-fonts.md).

## Plan

Use this workflow when adding or editing a custom card description:

1. Open `tools/card_data_manifest.json`.
2. Add or edit a card entry with a `description` object:
   - `symbol`: optional; derived from `card_const` when omitted
   - `pages`: one continuous prose string (not split by hand)
3. Point the relevant `gCardData_NEW` entry at `<Symbol>Data`.
4. Run `make` as normal.
5. Test the card in-game.

What happens automatically during build:

- `make` runs `python3 tools/add_card_art.py`
- the script reads the manifest description prose
- it auto-paginates into the current in-game layout model (2–5 pages)
- it writes the runtime byte data into `src_custom/card_description_data_generated.inc`
- the generated include provides the correct symbol at link time

After that, you call the runtime symbol in your card entry in `src_custom/generated/card_data_hooks.c`:

```c
.description = gMilusRadiantDescriptionData,
```

Files you normally edit:

- `tools/card_data_manifest.json`
- `src_custom/card_data_hooks.c`

Files you normally do not edit by hand:

- `src_custom/card_description_data_generated.inc`

How conversion works:

- The generator script reads every `description.pages` string in `tools/card_data_manifest.json`.
- It paginates the prose into vanilla detail pages (row widths below), then wraps each page.
- It emits raw byte data for `<Symbol>Data` into `card_description_data_generated.inc`.
- The page-count token is emitted automatically as `^2` through `^5`.
- Legacy `pages` arrays are still accepted and joined into one string on load.

Current layout constraints:

### Main description (card detail screen)

Each emitted page is 5 rows with these widths:

| Row | Width (chars) |
|-----|---------------|
| 1 | 12 |
| 2 | 14 |
| 3 | 14 |
| 4 | 14 |
| 5 | 12 |

Write the full effect text as one string. The generator fills pages up to the 5-page / ~330-character ceiling. Short text that fits on one screen still emits two pages (empty second page) because the runtime format requires at least `^2`.

### Popup / activation text (in-duel popup box)

Each popup is max 4 lines of 27 characters each (108 chars total).

Use `wrap_activation_page()` to validate. Popups exceeding 4 lines wrap off-screen and must be condensed.

### Quotes

Leave out quotation marks around monster card names. The in-game font cannot render `"` — they show as garbage or blank. Write `add 1 Harpie Lady from your Deck` not `add 1 "Harpie Lady" from your Deck`.

## Control Tokens

These tokens are interpreted by the duel textbox renderer:

- `#0`: line break
- `#1`: wait for A, B, or R input before closing the textbox
- `#2`: insert the current card name for the first card argument
- `#3`: insert the current card name for the second card argument
- `#4`: clear the textbox and advance
- `#5`: insert the player name
- `#6`: insert the description for the first card argument
- `#7`: insert the description for the second card argument
- `#8<n>`: wait `n` VBlanks before continuing
- `$...`: switch to the active language block in a localized string

Important constraints:

- Manifest `pages` is one prose string; the generator emits 2 to 5 runtime pages.
- Wrapping is word-based. The generator will not split a word across rows (except hyphenating words longer than a row).
- If any word is longer than its row width (max 14 in middle rows) and cannot be hyphenated, generation fails.
- If the prose needs more than 5 pages, generation fails — shorten the wording.
- The generated include is runtime data. It is not meant to be edited manually.

Practical advice for newcomers:

- Start by writing the text naturally as one string.
- Run `make`.
- If the generator fails, shorten the wording rather than forcing awkward punctuation.
- If the text compiles but looks wrong in-game, adjust the wording until it fits the current row model cleanly.
- For popup (activation) text: keep it ≤4 lines of 27 chars. Use `wrap_activation_page()` from `add_card_art.py` to validate.
- Omit `"` quotes around monster card names — the in-game font cannot render them.

Build behavior:

- `Makefile` declares `src_custom/card_description_data_generated.inc` as a generated dependency.
- `make` runs `python3 tools/add_card_art.py` before compiling the generated card hooks.
- Editing `tools/card_data_manifest.json` is therefore enough to trigger regeneration on the next build.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Editable source strings | `tools/card_data_manifest.json` | Holds the human-readable source strings per custom description |
| Generated runtime data | `src_custom/card_description_data_generated.inc` | Auto-generated raw byte data used by the game at runtime |
| Generator script | `tools/add_card_art.py` | Wraps source strings to the current row model and emits `<Symbol>Data` byte arrays |
| Build trigger | `Makefile` | Regenerates the include before compiling the generated card hooks |
| Runtime lookup | `GetCardDescription_Hook` in `src_custom/card_hooks.c` | Uses custom description data when present and falls back to vanilla otherwise |
| Card data wiring | `gCardData_NEW` in `src_custom/card_data_hooks.c` | Connects a card entry to its custom description runtime symbol |
| In-game card detail renderer | `sub_800BCB0` and surrounding card-detail flow in `src/card.c` | Displays the description data on the card details screen |

## TODO

- Improve the generator error output so it reports the exact row where text overflow starts.
- Add a helper mode that prints the wrapped rows for quick review without writing files.

## Limitations & Bugs

- The current row widths are based on observed in-game behavior, not a fully reverse-engineered format spec.
- Description fit is currently strict. Text that needs more than 5 vanilla pages must be shortened manually.
- The generator supports 2-page through 5-page runtime descriptions (auto-paginated from one prose string).
- If the in-game renderer turns out to use different widths for some cards or languages, the generator will need to be updated.
