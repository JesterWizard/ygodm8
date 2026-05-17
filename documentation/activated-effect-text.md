# Activated Effect Text

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Activated effect text is the short textbox shown when a card's activation message is displayed.

This repo keeps that text in the card manifest, generates the packed runtime bytes during build, and includes the generated output from the hook that plays effect text.

The goal is to keep activation copy editable in one place while still feeding the game the exact byte format it expects.

## Plan

Use this hierarchy when adding or changing activation text:

```text
tools/card_data_manifest.json
  cards[*].activation_description
    symbol
    pages[]
tools/add_card_art.py
  render_activation_description_inc()
  update_file(.../src/hooks/generated/card_activation_text_generated.inc)
src/hooks/generated/card_activation_text_generated.inc
  const u8 gActivationDescription_<Card>[] APPEND_TEXT = {...}
src/hooks/effect_text_hooks.c
  #include "generated/card_activation_text_generated.inc"
  ShowCardOfSanctityText()
```

How the data flows:

1. Add or edit a card's `activation_description` block in `tools/card_data_manifest.json`.
2. `tools/add_card_art.py` reads the `pages` array and wraps it into the in-game text format.
3. The generator writes `src/hooks/generated/card_activation_text_generated.inc`.
4. `src/hooks/effect_text_hooks.c` includes the generated file and passes the bytes to the effect-text renderer.

Current shape of the manifest entry:

| Field | Meaning |
|--------|---------|
| `symbol` | C symbol emitted for the activation text payload |
| `pages` | One or more strings that become the activation textbox pages |

The current in-repo example is `Card Of Sanctity`.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Activation-text source data | `activation_description` entries in `tools/card_data_manifest.json` | Human-readable source strings for activation messages |
| Activation-text generator | `render_activation_description_inc` in `tools/add_card_art.py` | Converts manifest pages into packed runtime text bytes |
| Generated activation include | `src/hooks/generated/card_activation_text_generated.inc` | Build output that defines `gActivationDescription_*` arrays |
| Runtime include site | `#include "generated/card_activation_text_generated.inc"` in `src/hooks/effect_text_hooks.c` | Makes the generated activation text available to the hook code |
| Activation-text playback | `ShowCardOfSanctityText` in `src/hooks/effect_text_hooks.c` | Plays the current custom activation textbox |
| Effect-text dispatch | `sub_801CF08__Replacement` in `src/hooks/effect_text_hooks.c` | Routes the Card of Sanctity special-case flow to the activation text path |

## TODO

- Add a second activation-text example so the hierarchy is not tied to one card.
- Split the current special-case playback into a small helper table if more cards need activation text.
- Add a short build note next to the manifest entry format if more activation text is added often.

## Limitations & Bugs

- Only `Card Of Sanctity` currently uses custom activation text in runtime code.
- The generated include is a build artifact and should not be edited by hand.
- If the manifest text does not fit the renderer's expected layout, the generator will fail and the wording must be shortened.
