---
name: add-custom-card
description: "Add a real Yu-Gi-Oh! card to the custom card trunk. Primary path: YGOProDeck API via add_custom_card.py. Fallback: Yugipedia page fetch when API misses a card or offline. Covers: data, manifest, art, runtime test hand, effect implementation (wire + logic, not stubs), build validation."
---

# Add Custom Card

Use when the user asks to add a custom card, wire a card into the trunk, or add a card from Yugipedia.

## Do Not Search For

These are automatic once the manifest entry exists — **skip codebase exploration for them**:

| Topic | Why |
|-------|-----|
| Trunk / shop lists | `tools/add_card_art.py` → `src_custom/generated/card_trunk_generated.inc` |
| Card IDs / art tables / names | Regenerated into `include/constants/card_ids.h`, `src_custom/generated/*` |
| Description byte data | Regenerated into `src_custom/card_description_data_generated.inc` |
| Mini art (24×24) | Derived from 80×80 PNG unless a manual mini exists |
| `trunk_hooks.c`, `deck_menu_hooks.c` | Custom cards piggyback existing hooks |
| Spell dispatch / activation gates | `tools/generate_spell_effect_dispatch.py` → `src_custom/generated/spell_effect_dispatch_*.inc`, `spell_activation_gates.c` (run via `make`) |
| Draw / destroy / LP / summon boilerplate | Use `include/duel_helpers.h` — do not reinvent |
| **Next cost / total cards / last card** | Read `tools/.card_state` (written by `write_manifest()`) |
| **Session state** | Read `documentation/CARD_STATE.md` — latest session in 1 tool call |

Search when **classifying or implementing effects** (grep similar cards in `src_custom/*_effects/`), when **extending duel helpers**, or when art is missing. Use **card-effect-hook-placement** for non-standard dispatch paths.

## Fast Path Checklist

```
[ ] 1. Fetch card data — try YGOProDeck first, Yugipedia fallback
[ ] 2. Scaffold manifest (+ optional wire): `python3 tools/add_custom_card.py --passcode XXXXXXXX --write --type spell --wire --runtime-hand 1`
[ ] 3. Check art: `512x512/<stem>.png` (preferred) or `80x80/<stem>.png`
[ ] 4. Implement effects (required for spells/traps/effect monsters — see Step 6)
[ ] 5. Build: `make test-cards-link` (or `make test-cards-build` for full ROM)
```

**Default expectation:** adding a card means the card **works in duel**, not just exists in the trunk. Normal monsters with no effect text are the only skip.

## Step 1 — Fetch Card Data

**Primary** — YGOProDeck API via `add_custom_card.py` (preferred):

```bash
python3 tools/add_custom_card.py --passcode 53530069 --write --runtime-hand 1
```

This calls YGOProDeck API for accurate data and writes the manifest entry + runtime hand in one command.

**Fallback** — Yugipedia page when the API is offline or misses the card:

`https://yugipedia.com/wiki/<Card_Name_Underscores>`

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
| etc. | See `RACE_MAP` in `tools/add_custom_card.py` |

**Color** from card kind:

| Kind | `color` | `monsterEffect` | `spellEffect` | `trapEffect` |
|------|---------|-----------------|---------------|--------------|
| Normal Monster | `NORMAL_CARD` | `0` | `2` | `0` |
| Effect Monster | `EFFECT_CARD` | `0` or `MONSTER_EFFECT_*` | `2` | `0` |
| Fusion Monster | `FUSION_CARD` | `0` or `MONSTER_EFFECT_*` | `2` | `0` |
| Ritual Monster | `RITUAL_CARD` | `0` | `2` | `0` |
| Spell | `SPELL_CARD` | `0` | `2` | `0` |
| Trap | `TRAP_CARD` | `0` | `2` | hook id |
| Field spell | `SPELL_CARD` + `customFieldSpell` | — | `2` or `8` | `0` |

Spells/traps use `atk`/`def` `65535`, `attribute` `0`, `level` `0`.

Activated monsters also need `activation_description`. Effect monsters with once-per-turn logic may need `effect_usage` (`once`, `once_per_turn`, `multiple_per_turn`, `continuous`).

## Step 2 — Check if Already in Manifest

The card may already exist. Check:

```bash
python3 -c "
import json
m = json.load(open('tools/card_data_manifest.json'))
cards = [c for c in m['cards'] if c['card_const'] == '${CARD_CONST}']
if cards: print(f\"Already in manifest: {cards[0]['card_const']} at cost {cards[0]['cost']}\")
else: print('NOT_FOUND')
"
```

If already in manifest: skip to art check, then runtime hand.

## Step 3 — Manifest Entry

**Preferred:** `python3 tools/add_custom_card.py ... --write` — it calls `write_manifest()` in `tools/card_manifest.py`.

**Formatting is locked — do not change without explicit user approval:**
- Every card object must use the canonical key order from `MANIFEST_CARD_KEY_ORDER` in `card_manifest.py`.
- `password` must always be a **single-line** array: `"password": [1, 3, 9, 4, 4, 4, 2, 2]`.
- Append to the **end** of the `cards` array. Manifest order = card ID; never reorder existing entries.

**Fallback** — manual entry when API is down. Append `tools/card_data_manifest.json`:

### Normal monster (no effect) — e.g. Battle Footballer

```json
{
  "card_const": "BATTLE_FOOTBALLER",
  "card_name": "Battle Footballer",
  "atk": 1000,
  "def": 2100,
  "level": 4,
  "attribute": "ATTRIBUTE_FIRE",
  "type": "TYPE_MACHINE",
  "color": "NORMAL_CARD",
  "monsterEffect": 0,
  "spellEffect": 2,
  "trapEffect": 0,
  "cost": 319,
  "password": [4, 8, 0, 9, 4, 9, 9, 7],
  "description": {
    "symbol": "gDescription_BattleFootballer",
    "pages": [
      "A cyborg with high defense power.",
      "Originally it was invented for a football machine."
    ]
  }
}
```

`symbol` = `gDescription` + PascalCase card name (drop spaces/punctuation).

### Spell — e.g. Burning Land

```json
{
  "card_const": "BURNING_LAND",
  "card_name": "Burning Land",
  "atk": 65535,
  "def": 65535,
  "level": 0,
  "attribute": 0,
  "type": "TYPE_SPELL",
  "color": "SPELL_CARD",
  "monsterEffect": 0,
  "spellEffect": 2,
  "trapEffect": 0,
  "cost": 150,
  "password": [5, 1, 2, 6, 3, 4, 6, 3],
  "description": { "symbol": "gDescription_BurningLand", "pages": ["...", "..."] },
  "effect_texts": { "popup_1": "..." }
}
```

### Trap — e.g. Magic Jammer

Same shell as spell but `"type": "TYPE_TRAP"`, `"color": "TRAP_CARD"`, and set `"trapEffect"` to match an existing trap dispatcher id (grep manifest for a similar trap).

### Description & popup formatting

Add **after** the manifest entry is in place — the `description.pages` and `effect_texts.popup_1` fields need careful sizing to render correctly in-game.

**Main description (card detail screen):**
- Each page is 5 rows (widths: 12, 14, 14, 14, 12). Max ~66 chars per page.
- Write each page as natural text — wrapping is automatic.
- Aim for ~55–65 chars per page so text fills the rows (no huge gaps).
- 2–5 pages per card. The last page can be shorter.
- Validate with `wrap_description_page()` from `add_card_art.py`.

**Popup / activation text (`effect_texts.popup_1`):**
- Max 4 lines of 27 characters each = 108 chars total.
- Condense wording to fit. Lines beyond 4 wrap off-screen.
- Validate with `wrap_activation_page()` from `add_card_art.py`.

**Quotes around card names:**
- Leave out `"` quotation marks around monster card names. The in-game font cannot render `"` — they display as garbage characters. Write `add 1 Harpie Lady from your Deck`, not `add 1 "Harpie Lady" from your Deck`.

**Quick validation in terminal:**
```bash
python3 -c "
from tools.add_card_art import wrap_description_page, wrap_activation_page
print(wrap_description_page('Your text here...'))
wrapped = wrap_activation_page('Your popup text...')
lines = wrapped.split('#0')
print(f'{len(lines)} lines: {\"OK\" if len(lines) <= 4 else \"FAIL\"}')
"
```

## Step 4 — Art

**Stem** = `card_const.lower()`. Prefer `src_custom/assets/cards/512x512/<stem>.png`; `make` runs `batch_80x80.py` to fill missing `80x80/<stem>.png`. Hand-authored `80x80/` is also fine (not overwritten).

```bash
ls src_custom/assets/cards/512x512/<stem>.png src_custom/assets/cards/80x80/<stem>.png
```

If both missing: check `src_custom/assets/cards/CARD_PROGRESS.md` todo list, or tell user art is needed. For PNG authoring specs, read `documentation/adding-custom-cards.md` (only then).

Do **not** hand-edit `build/cards/` or `src_custom/generated/card_art_generated.inc`.

## Step 5 — Runtime Test Hand (if requested)

`configs/runtime.c` → set `.card_in_hand_1` … `.card_in_hand_5` to the new `CARD_CONST`. Requires `#include "constants/card_ids.h"` (already present).

```bash
python3 tools/add_custom_card.py --passcode <passcode> --runtime-hand 1
# (no --write, just sets the runtime C field)
```

Or manually:
```c
.card_in_hand_1 = CARD_CONST,
```

Trunk ownership at new game is already handled by `start_with_three_copies_of_every_card` in the same file — no trunk code changes.

## Step 6 — Implement Effects (required by default)

**Do not stop at manifest + art.** For every spell, trap, and effect monster (anything with card text beyond flavor), wire the hook **and implement the effect logic** before calling the card done.

**Skip only:** `NORMAL_CARD` monsters with no effect text (vanilla stat stick).

### 6a — Classify effect type from card text

Read `effect_texts.popup_1` / API `desc` / Yugipedia text. Pick the primary hook category:

| Card text signals | `--type` | Notes |
|-------------------|----------|-------|
| Spell Card | `spell` | Manifest keeps `spellEffect: 2`; dispatch is by card ID in `spell_effect_hooks.c` |
| Trap Card | `trap` | Manifest keeps `trapEffect: 0` until wired; dispatch by card ID |
| `FLIP:`, `You can` (ignition), once-per-turn menu effect | `activated` | Add `MONSTER_EFFECT_*` to `monster_effects.h`; set manifest `monsterEffect` |
| Continuous / while face-up / when Summoned field trigger | `permanent` | Standby/End Phase on-field triggers often land here |
| Standby / End Phase / maintenance timing only | `turn` | Also add row in `sTurnEffectOverrides[]` in `turn_effect_hooks.c` |
| Battle damage / when this card attacks or is attacked | `battle` | |
| Cannot be negated, immunity, name override, rules-layer hook | `passive` | May also need engine hooks beyond the passive file |
| Quick effect from hand/GY, non-menu ignition | — | Grep `code_8043EF4_hooks.c` / existing hand-activation cards (e.g. `hecatrice.c`) |

Cards with **multiple effects** (e.g. FLIP + ignition) may need more than one `--type` run or extra wiring — implement each part that has a dispatch path.

### 6b — Find a similar card, then wire

1. **Grep** `src_custom/*_effects/` for the same verb (burn, draw, destroy, tribute, search, flip, etc.) or a card with similar text.
2. **Scaffold:** `python3 tools/add_custom_card.py --passcode <passcode> --write --type <type> --wire --runtime-hand 1` — manifest, runtime hand, effect `.c`, and (for spells) regenerated dispatch in one step. Or: `python3 tools/wire_card_effect.py <CARD_CONST> --type <type>` after manifest exists.
3. **Implement** — replace every `/* TODO */` in the new file. Copy structure from the similar card; adapt targets, amounts, and conditions to match the real card text. Do **not** leave stub bodies.
4. **Manifest fields** (after wiring):
   - Spells: no `spell_effect_hooks.c` edit — dispatch is generated from `src_custom/spell_effects/*.c` at build time. Export `u8 CanActivate*(void)` in the spell file when the card needs an activation gate (auto-wired via generated table).
   - Activated monsters: append `MONSTER_EFFECT_<CARD>` to `include/constants/monster_effects.h`, set manifest `monsterEffect`, add `effect_usage` (`once`, `once_per_turn`, etc.) and `activation_description` when the card ignites from the menu.
   - Field spells: `"customFieldSpell": "CUSTOM_FIELD_SPELL_*"` only when using the custom field-spell pipeline (see `documentation/custom-field-spells.md`).
5. **Non-template paths** — hand/GY quick effects, equip registration, flip triggers: read **card-effect-hook-placement** and grep the card name in `src_custom/` before inventing a new entry point.

| `--type` | Dispatcher | Effect dir |
|----------|------------|------------|
| `spell` | `spell_effect_hooks.c` | `src_custom/spell_effects/` |
| `trap` | `trap_effect_hooks.c` | `src_custom/trap_effects/` |
| `activated` | `monster_effect_hooks.c` | `src_custom/activated_effects/` |
| `permanent` | `permanent_effect_hooks.c` | `src_custom/permanent_effects/` |
| `battle` | `battle_damage_hooks.c` | `src_custom/battle_effects/` |
| `turn` | `turn_effect_hooks.c` | `src_custom/turn_effects/` |
| `passive` | (none) | `src_custom/card_passives/` |

The `activated` and `permanent` templates include a `Duel_PickZone` targeting skeleton — **no header file, cursor constant, or `code_8043EF4_hooks.c` edit needed** for standard cursor-targeting ignitions.

### 6c — Implementation bar

- Match the card's printed effect text (TCG/OCG errata from API/Yugipedia).
- Use `duel_helpers.h` for draw/destroy/LP/summon/text/trap gates (see cheat sheet below).
- Show effect text **before** state changes (`Duel_ShowEffectText` / `Duel_ShowEffectTextTyped` first).
- If part of the effect needs missing engine support (banish zone, global name override, etc.), implement what you can and mark the gap with a `ponytail:` comment naming the ceiling — do **not** ship an empty `TODO` body for behavior that is implementable today.
- **Data-only add** (user explicitly asked for trunk entry only): skip Step 6 and say so in the session log.

### Duel helpers (required for effect bodies)

**Every effect file that touches duel state must `#include "duel_helpers.h"` and call shared helpers instead of copying vanilla duel APIs or static local helpers** (`DrawCards`, `CountCardsInHand`, `InitSummonedMonsterZone`, `SetPlayerLifePointsTo*`, etc.).

Duelist args use `ACTIVE_DUELIST` / `INACTIVE_DUELIST`. Check `enum DuelActionResult` and early-return on `DUEL_ACTION_DUEL_OVER` / `DUEL_ACTION_BLOCKED` / `DUEL_ACTION_NO_TARGET` / `DUEL_ACTION_NO_ZONE` as appropriate.

| Verb | Helper |
|------|--------|
| Count hand | `Duel_CountCardsInHand(handRow)` |
| Draw | `Duel_DrawCards(duelist, count, updateGfx)` |
| Mill deck | `Duel_MillTopDeckCards(duelist, count, updateGfx)` |
| Destroy zone | `Duel_DestroyZone(zone, graveyardDuelist, updateGfx)` |
| Destroy row | `Duel_DestroyAllMonstersMatching(turnRow, pred, updateGfx)` |
| Discard | `Duel_DiscardFromHand(duelist, count, pred, updateGfx)` |
| Discard all hand | `Duel_DestroyAllHandCards(duelist, updateGfx)` |
| LP change | `Duel_ChangeLp(targetDuelist, delta, updateGfx)` — opponent burn from active player: `Duel_ChangeLp(INACTIVE_DUELIST, -amount, TRUE)` |
| Effect text | `Duel_ShowEffectText(cardId)` |
| Typed effect text | `Duel_ShowEffectTextTyped(cardId, textType)` — spell `1`, activated monster `2`, battle `3`, trap `3`, permanent `8`, turn `9` |
| Spell vs traps | `Duel_TryResolveSpellThroughTraps(spellId, resolveBody)` or `Duel_TryResolveSpellThroughTrapsEx(spellId, trapLp, resolveBody)` |
| Deck search / remove / shuffle | `Duel_FindDeckCardIndex`, `Duel_RemoveDeckCardAt`, `Duel_ShuffleDeckFromDrawn` |
| Special summon | `Duel_SpecialSummonFromHand/Grave/Deck/HandZone/MonsterId(...)` + `Duel_DefaultSpecialSummonOpts(updateGfx)` |
| Locked special summon | set `opts.lockMonster = TRUE` on `struct DuelSummonOpts` |
| Normal summon | `Duel_NormalSummonFromHand(..., Duel_DefaultNormalSummonOpts(updateGfx))` |
| Return to hand | `Duel_ReturnMonsterZoneToOwnerHand(zone, updateGfx)` |

Pass `updateGfx=TRUE` only when the card should call `UpdateDuelGfxExceptField()` after that step; use `FALSE` on intermediate steps when the original flow updated gfx once at the end.

### Effect text ordering (required)

**Always show effect text before any gameplay resolution** — the textbox must appear and advance before draw, destroy, LP change, summon, or other state changes.

1. Call `Duel_ShowEffectText(cardId)` or `Duel_ShowEffectTextTyped(cardId, textType)` at the **start** of the resolve body (after trap gates pass), not after the effect finishes.
2. If the textbox can end the duel or block further steps, check `IsDuelOver()` before continuing.
3. **Do not** use `Duel_ResolveBurnSpell` for new cards — it shows text after burn/spell destruction (legacy). For burn spells, show text first, then `Duel_ChangeLp`, then send the spell to the GY with `Duel_DestroyZone`.

**Spell pattern** — resolve body callback + trap gate:

```c
#include "duel_helpers.h"

static void MySpell_ResolveBody(void)
{
  Duel_ShowEffectText(MY_SPELL);

  if (Duel_ChangeLp(INACTIVE_DUELIST, -500, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectMySpell(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(MY_SPELL, 500, MySpell_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
```

**Keep vanilla calls in the card file only for card-specific logic** — equip registration, field/target selection UI, flip/set position, battle-context `gDuelLifePoints` mutation, `cardId2` effect text, tribute paths using `ClearZoneAndSendMonToGraveyard2`, custom deck/hand UI that helpers do not model.

### When to add a new duel helper

Before writing more than a few lines of duel plumbing in a card file:

1. Grep `src_custom/*_effects/` for the same pattern — if another card does it, a helper probably already exists.
2. If the action is a **reusable duel verb** (draw, destroy, discard, LP, summon, deck op, effect text, trap gate) and fits an existing helper signature, **use that helper**.
3. If the card needs duel logic that **no helper covers** and would otherwise be copied (or is non-trivial inline vanilla), **add a helper** to `include/duel_helpers.h` + `src_custom/duel_helpers.c` first, then call it from the card file.
   - Put the implementation in `duel_helpers.c`; keep the card file to activation checks + card-specific rules.
   - Return `enum DuelActionResult`; fold in `IsDuelOver()` / gfx updates like existing helpers.
   - Extend `DUEL_HELPERS_SELF_CHECK` or add a minimal assert when the logic is non-obvious.
   - Update the cheat sheet in `documentation/monster-card-effects.md`.
4. Do **not** add a helper for one-off card quirks (single-file UI, unique equip wiring, battle-only LP hacks) — keep those in the card file.

| Situation | Action |
|-----------|--------|
| Same pattern as existing cards | Use existing `Duel_*` |
| New pattern, likely reused | Add `Duel_*` in `duel_helpers` |
| Truly unique card logic | Vanilla in card file only |

Full API reference: `include/duel_helpers.h` and `documentation/monster-card-effects.md` (Duel helpers cheat sheet).

### Existing examples

See `src_custom/activated_effects/jowls_of_dark_demise.c` for a complete example: it uses `Duel_ShowEffectTextTyped()`, checks `IsDuelOver()`, has `CanActivate`/`Activate` entry points, and wires through `monster_effect_hooks.c` dispatch table.

## Step 7 — Validate

```bash
make test-cards          # manifest-only (normal monsters, no hook files)
make test-cards-link     # default after adding a card with effects
make test-cards-build    # full ROM link (use when hooks touch LynJump / broad gameplay)
```

`test-cards` runs manifest validation, RAM card-growth check, trunk validators, and `card_art_progress.py`. It skips events, portraits, CG, opening screens, and the full ROM link — those are unrelated to adding a card.

| After a change affecting… | Run |
|---------------------------|-----|
| Manifest only (normal monster, no effect) | `make test-cards` |
| Manifest + effect implementation (usual path) | `make test-cards-link` |
| Full ROM link needed | `make test-cards-build` |
| Events, LynJump, RAM map, or broad gameplay | `make test` |

## Cost Heuristic

Avoid inventing costs from scratch:

1. **`make card-cost LEVEL=N ATK=N DEF=N COLOR=COLOR`** — queries the manifest for the 5 most similar cards and prints the suggested cost.
2. Grep manifest for same `level` + similar `atk`/`def` (±200) + same `color`.
3. Normal level-4 walls (~800/2000): often `319`.
4. Custom spells/traps: often `150` unless a vanilla analogue exists in manifest.
5. Jowls of Dark Demise (level 2, 200/100, effect): `29`.

Prefer `make card-cost` over manual grepping — it saves tool calls.

## Generated Outputs (verify, never edit)

After `make`, confirm grep hits for the new const in:

- `include/constants/card_ids.h`
- `src_custom/generated/card_trunk_generated.inc`
- `src_custom/generated/card_art_generated.inc`

## Session Log

When finishing meaningful card work, append a log entry:

```bash
python3 tools/log_session.py --task "Added {CardName} with effect" \
  --files "tools/card_data_manifest.json,configs/runtime.c,src_custom/spell_effects/{stem}.c" \
  --outcome "make test-cards-link passes; {brief effect summary}" \
  --next "playtest edge cases"
```

## Related Skills / Docs

| Need | Read |
|------|------|
| Effect implementation | `.agents/skills/card-effect-hook-placement/SKILL.md` |
| Duel helper API | `include/duel_helpers.h`, `documentation/monster-card-effects.md` |
| Pre-reply validation | `.agents/skills/validate-before-reply/SKILL.md` |
| Art authoring / palette | `documentation/adding-custom-cards.md` |
| Description format | `documentation/card-descriptions.md` |
| Save/RAM growth (many cards) | `documentation/custom-card-memory.md` + `make memory-report` |
