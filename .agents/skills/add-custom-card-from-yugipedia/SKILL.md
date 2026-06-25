---
name: add-custom-card-from-yugipedia
description: "Add a real Yu-Gi-Oh! card to the custom card trunk from its Yugipedia URL. Fetches data from the page, checks art, adds manifest entry, sets runtime test hand, and wires effects with duel helpers."
---

# Add Custom Card from Yugipedia

Use when the user provides a card name like Jowels of Dark Demise and says to add it to the custom card trunk. Find its Yupedia URL like `https://yugipedia.com/wiki/Jowls_Of_Dark_Demise`

## Do Not Search For

| Topic | Why |
|-------|------|
| Card IDs / trunk tables | `add_custom_card.py` + `make` regenerate these |
| Mini art (24×24) | Derived from 80×80 PNG |
| `trunk_hooks.c`, `deck_menu_hooks.c` | Custom cards piggyback existing hooks |
| Description byte data | Regenerated into `src_custom/card_description_data_generated.inc` |

Only search when the card is already in manifest (just check art + runtime hand) or when implementing a new effect.

## Fast Path

```
[ ] 1. Fetch card data from Yugipedia URL
[ ] 2. Pass to add_custom_card.py with passcode
[ ] 3. Check if already in manifest → skip to art + hand
[ ] 4. Check art in src_custom/assets/cards/80x80/
[ ] 5. Set card_in_hand_1 in configs/runtime.c
[ ] 6. Wire effect with duel helpers (if non-vanilla)
[ ] 7. make test-cards (or test-cards-build if hooks changed)
```

## Step 1 — Fetch Card Data from Yugipedia

Fetch the URL and extract:

| Field | How to get from page |
|-------|---------------------|
| `card_name` | `<h1>` / page title after "wiki/" |
| `card_const` | `card_name` → `UPPER_SNAKE` via `card_name_to_const()` |
| `passcode` | Look for "passcode", "Password", or card database number. Usually 8 digits. May appear as "05257687" |
| `atk` / `def` | "ATK" / "DEF" in stat table or infobox |
| `level` | "Level" in infobox |
| `attribute` | "Attribute" → map: WATER→ATTRIBUTE_WATER, DARK→ATTRIBUTE_SHADOW, etc. |
| `type` / `race` | Type line: e.g. "Fiend / Flip / Effect" → TYPE_FIEND. Check RACE_MAP in add_custom_card.py |
| `effect text` | Card text below stats. Usually starts with "FLIP:" or bullet points |
| `card kind` | "Spell Card" / "Trap Card" / "Effect Monster" / "Normal Monster" |

**Attribute mapping** (same as `add_custom_card.py`):

| Yugipedia | Manifest value |
|-----------|---------------|
| DARK | `ATTRIBUTE_SHADOW` |
| LIGHT | `ATTRIBUTE_LIGHT` |
| FIRE | `ATTRIBUTE_FIRE` |
| WATER | `ATTRIBUTE_WATER` |
| WIND | `ATTRIBUTE_WIND` |
| EARTH | `ATTRIBUTE_EARTH` |
| DIVINE | `ATTRIBUTE_DIVINE` |

**Type mapping** (same as `add_custom_card.py`):

| Yugipedia | Manifest value |
|-----------|---------------|
| Dragon | `TYPE_DRAGON` |
| Spellcaster | `TYPE_SPELLCASTER` |
| Zombie | `TYPE_ZOMBIE` |
| Warrior | `TYPE_WARRIOR` |
| Fiend | `TYPE_FIEND` |
| Fairy | `TYPE_FAIRY` |
| Machine | `TYPE_MACHINE` |
| Rock | `TYPE_ROCK` |
| etc. | See `RACE_MAP` in `tools/add_custom_card.py` |

**Color** from card kind:

| Kind | `color` |
|------|---------|
| Normal Monster | `NORMAL_CARD` |
| Effect Monster | `EFFECT_CARD` |
| Fusion Monster | `FUSION_CARD` |
| Ritual Monster | `RITUAL_CARD` |
| Spell | `SPELL_CARD` |
| Trap | `TRAP_CARD` |

**Spells/traps**: `atk=65535`, `def=65535`, `level=0`, `attribute=0`.

## Step 2 — Try add_custom_card.py with passcode

```bash
python3 tools/add_custom_card.py --passcode <8-digit-passcode> --write --runtime-hand 1
```

This calls YGOProDeck API for accurate data and writes the manifest entry + runtime hand in one command.

If the API fails (offline, card not found), fall through to Step 3 (manual entry).

## Step 3 — Check if Already in Manifest

The card may already exist (like JOWLS_OF_DARK_DEMISE at ID 0x03CC). Check:

```bash
python3 -c "
import json
m = json.load(open('tools/card_data_manifest.json'))
cards = [c for c in m['cards'] if c['card_const'] == '${CARD_CONST}']
if cards: print(f\"Already in manifest: {cards[0]['card_const']} at cost {cards[0]['cost']}\")
else: print('NOT_FOUND')
"
```

If already in manifest:
- Go directly to Step 4 (art check)
- Then Step 5 (set runtime hand) — the card already works in trunk

## Step 4 — Check Art

```bash
ls src_custom/assets/cards/80x80/<stem>.png
```

`<stem>` = `card_const.lower()` (e.g. `jowls_of_dark_demise.png`).

If missing: check `src_custom/assets/cards/CARD_PROGRESS.md` for art todo, or tell user art is needed. For art authoring specs, read `documentation/adding-custom-cards.md`.

Do **not** hand-edit `build/cards/` or `src_custom/generated/card_art_generated.inc`.

## Step 5 — Set Runtime Test Hand

```bash
python3 tools/add_custom_card.py --passcode <passcode> --runtime-hand 1
```

Or manually edit `configs/runtime.c`:

```c
.card_in_hand_1 = CARD_CONST,
```

Requires `#include "constants/card_ids.h"` (already present).

## Step 6 — Effect with Duel Helpers

| Card has… | Action |
|-----------|--------|
| No effect / normal monster | Stop — no hook files |
| Spell effect | `card-effect-hook-placement` → `src_custom/spell_effects/<stem>.c` |
| Trap effect | `src_custom/trap_effects/` |
| Activated monster effect | `MONSTER_EFFECT_*` in manifest + `src_custom/activated_effects/` |
| Flip effect | Activated monster effect — triggered on flip |
| Passive stat / always-on | `src_custom/permanent_effects/` |

**Every effect file must**:

1. `#include "duel_helpers.h"`
2. Use `Duel_ShowEffectText(cardId)` or `Duel_ShowEffectTextTyped(cardId, textType)` **before** gameplay resolution
3. Check `IsDuelOver()` after effect text
4. Use `Duel_*` helpers (draw, destroy, LP, summon, etc.) instead of vanilla APIs

See the existing `jowls_of_dark_demise.c` in `src_custom/activated_effects/` for a complete example: it uses `Duel_ShowEffectTextTyped()`, checks `IsDuelOver()`, has `CanActivate`/`Activate` entry points, and wires through `monster_effect_hooks.c` dispatch table.

For the effect body workflow, use `card-effect-hook-placement` skill.

## Step 7 — Validate

```bash
make test-cards          # manifest-only (no hooks/runtime changes)
make test-cards-build    # + effect hooks and/or configs/runtime.c
```

## Fallback: Manual Manifest Entry (when API is down)

If Step 2 fails, create a manual entry. Append to `tools/card_data_manifest.json` using the scraped data.

Copy the nearest template from `.agents/skills/add-custom-card/SKILL.md` (normal monster, effect monster, spell, or trap). Then set the runtime hand manually:

```bash
python3 tools/add_custom_card.py --passcode <passcode> --runtime-hand 1
# (no --write, just sets the runtime C field)
```

Then regenerate derived files:

```bash
make test-cards
```

This runs `add_card_art.py --card-ids` which regenerates `card_ids.h`, trunk tables, and art includes.

## Cost Heuristic

When the API is down and you need a manual cost:

1. Grep manifest for same `level` + similar `atk`/`def` (±200) + same `color`.
2. Normal level-4 walls (~800/2000): often `319`.
3. Custom spells/traps: often `150` unless a vanilla analogue exists.
4. Jowls of Dark Demise (level 2, 200/100, effect): `29`.

## Related Skills / Docs

| Need | Read |
|------|------|
| Existing card skill (YGOProDeck path) | `.agents/skills/add-custom-card/SKILL.md` |
| Effect implementation | `.agents/skills/card-effect-hook-placement/SKILL.md` |
| Duel helper API | `include/duel_helpers.h`, `documentation/monster-card-effects.md` |
| Pre-reply validation | `.agents/skills/validate-before-reply/SKILL.md` |
| Art authoring / palette | `documentation/adding-custom-cards.md` |
