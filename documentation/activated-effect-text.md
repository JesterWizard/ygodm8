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
  cards[*].effect_texts
    popup_1: "…"
    popup_2: "…"   (optional)
tools/add_card_art.py
  render_activation_description_inc()
  update_file(.../src_custom/generated/card_activation_text_generated.inc)
src_custom/generated/card_activation_text_generated.inc
  const u8 gActivationDescription_<Card>_Popup1[] APPEND_TEXT = {...}
src_custom/effect_text_hooks.c
  #include "generated/card_activation_text_generated.inc"
```

How the data flows:

1. Add or edit `effect_texts` in `tools/card_data_manifest.json`.
2. `tools/add_card_art.py` wraps each popup into duel-text bytes (`CARD was activated.` then the page(s)).
3. The generator writes activation text payloads, `GetCardActivationText` (defaults to `popup_1`), and `CARD_EFFECT_TEXT_*` enums.
4. Runtime shows text via `ActivatePermanentEffectCardText(cardId)` (uses `popup_1`) or `Duel_ShowCardEffectText(cardId, CARD_EFFECT_TEXT_*_POPUP_N)`.

Manifest shape:

```json
"effect_texts": {
  "popup_1": "After battle, destroy 1 monster.",
  "popup_2": "Special Summon 1 Level 8 or lower Elemental HERO Fusion from GY."
}
```

Each key becomes:
- payload symbol `gActivationDescription_<CardPascal>_PopupN`
- enum `CARD_EFFECT_TEXT_<CARD_CONST>_POPUP_N` in `include/constants/card_effect_texts.h`

Single-popup cards only need `popup_1`. `ActivatePermanentEffectCardText` still works and resolves `popup_1` automatically.

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
