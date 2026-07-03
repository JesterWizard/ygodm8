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
  update_file(.../src_custom/generated/card_activation_text_generated.inc)
src_custom/generated/card_activation_text_generated.inc
  const u8 gActivationDescription_<Card>[] APPEND_TEXT = {...}
src_custom/effect_text_hooks.c
  #include "generated/card_activation_text_generated.inc"
  ShowCardOfSanctityText()
```

How the data flows:

1. Add or edit a card's `activation_description` block in `tools/card_data_manifest.json`.
2. `tools/add_card_art.py` reads the `pages` array and wraps it into duel-text bytes with `#1` waits between pages.
3. The generator writes `src_custom/generated/card_activation_text_generated.inc`.
4. `src_custom/effect_text_hooks.c` includes the generated file and passes the bytes to the effect-text renderer.

Current shape of the manifest entry:

| Field | Meaning |
|--------|---------|
| `symbol` | C symbol emitted for the activation text payload |
| `pages` | One or more strings that become the activation textbox pages |

For cards with **multiple** effect popups, use `effect_texts` with generic keys (`popup_1`, `popup_2`, …):

```json
"effect_texts": {
  "popup_1": { "pages": ["After battle, destroy 1 monster."] },
  "popup_2": { "pages": ["Special Summon 1 Level 8 or lower Elemental HERO Fusion from GY."] }
}
```

Each key becomes:
- payload symbol `gActivationDescription_<CardPascal>_Popup1`
- enum `CARD_EFFECT_TEXT_<CARD_CONST>_POPUP_1` in `include/constants/card_effect_texts.h`

Call sites:

```c
#include "constants/card_effect_texts.h"
Duel_ShowCardEffectText(CARD_ID, CARD_EFFECT_TEXT_CARD_CONST_POPUP_1);
```

`activation_description` remains the default text for `GetCardActivationText` / `ActivatePermanentEffectCardText` (single-effect cards).

Example multi-effect card: `Elemental HERO Core` (`popup_1` = post-battle destroy, `popup_2` = GY revive).

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Activation-text source data | `activation_description` entries in `tools/card_data_manifest.json` | Human-readable source strings for activation messages |
| Activation-text generator | `render_activation_description_inc` in `tools/add_card_art.py` | Converts manifest pages into packed runtime text bytes |
| Generated activation include | `src_custom/generated/card_activation_text_generated.inc` | Build output that defines `gActivationDescription_*` arrays |
| Runtime include site | `#include "generated/card_activation_text_generated.inc"` in `src_custom/effect_text_hooks.c` | Makes the generated activation text available to the hook code |
| Activation-text playback | `ShowCardOfSanctityText` in `src_custom/effect_text_hooks.c` | Plays the current custom activation textbox |
| Effect-text dispatch | `sub_801CF08__Replacement` in `src_custom/effect_text_hooks.c` | Routes the Card of Sanctity special-case flow to the activation text path |

## TODO

- Migrate more multi-effect cards from a single `activation_description` to `effect_texts`.

## Limitations & Bugs

- The generated includes are build artifacts and should not be edited by hand.
- Activation text is emitted as plain duel text; it does not use the card-description `^n` header or leading padding.
- Activation text is word-wrapped at 27 columns and words are moved whole to the next line when they do not fit.
- If the manifest text does not fit the renderer's expected layout, the generator will fail and the wording must be shortened.
