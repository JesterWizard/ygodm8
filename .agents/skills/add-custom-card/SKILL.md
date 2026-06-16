---
name: add-custom-card
description: "Use when adding a custom card to this Yu-Gi-Oh GBA ROM hack: manifest entry, trunk wiring, art, descriptions, runtime test hand, optional effect hooks, and duel_helpers for effect bodies. Read this skill first — do not broad-search the repo for trunk/art/build plumbing."
---

# Add Custom Card

Use this skill when the user asks to add a custom card, wire a card into the trunk, or add a card from Yugipedia.

## Do Not Search For

These are automatic once the manifest entry exists — **skip codebase exploration for them**:

| Topic | Why |
|-------|-----|
| Trunk / shop lists | `tools/add_card_art.py` → `src_custom/generated/card_trunk_generated.inc` |
| Card IDs / art tables / names | Regenerated into `include/constants/card_ids.h`, `src_custom/generated/*` |
| Description byte data | Regenerated into `src_custom/card_description_data_generated.inc` |
| Mini art (24×24) | Derived from 80×80 PNG unless a manual mini exists |
| `trunk_hooks.c`, `deck_menu_hooks.c` | Custom cards piggyback existing hooks |
| Draw / destroy / LP / summon boilerplate | Use `include/duel_helpers.h` — do not reinvent |

Only search when implementing **new effect behavior** (use **card-effect-hook-placement** skill), when **extending duel helpers**, or when art is missing.

## Fast Path Checklist

```
- [ ] 1. Scaffold manifest entry: `python3 tools/add_custom_card.py "Card Name" --write`
- [ ] 2. Confirm art: src_custom/assets/cards/80x80/<stem>.png (script reports OK/MISSING)
- [ ] 3. Effect hooks? → only if card has non-vanilla behavior (one table row in turn/spell/trap hooks)
- [ ] 3b. Effect body uses `duel_helpers.h` — extend `duel_helpers.c` if no helper fits (see below)
- [ ] 4. configs/runtime.c → `--runtime-hand N` or manual card_in_hand_* if user asked
- [ ] 5. make test-cards (manifest-only) or make test-cards-build (hooks/runtime)
```

Or from CARD_PROGRESS todo art:

```bash
python3 tools/add_custom_card.py --from-progress AMAZONESS_TIGER --write --runtime-hand 1
make test-cards-build
```

## Step 1 — Card Data (YGOProDeck)

Preferred: `python3 tools/add_custom_card.py --passcode 53530069` or pass the card name.

Fallback: Yugipedia `https://yugipedia.com/wiki/<Card_Name_Underscores>` when offline or API misses a card.

Record:

| Field | Source |
|-------|--------|
| `card_name` | Display name |
| `card_const` | `UPPER_SNAKE` from name (`Battle Footballer` → `BATTLE_FOOTBALLER`) |
| `atk` / `def` / `level` | Card page |
| `attribute` | `ATTRIBUTE_*` enum string |
| `type` | `TYPE_*` enum string |
| `color` | See table below |
| `password` | 8-digit passcode → one digit per array element (`48094997` → `[4,8,0,9,4,9,9,7]`) |
| `cost` | See cost heuristic below (or use value from `add_custom_card.py`) |
| `description.pages` | Flavor/effect text (2–3 short lines); **required for every custom card** |

`description.symbol` and `activation_description.symbol` are optional — derived automatically from `card_const` when omitted (`SPIRIT_OF_THE_BREEZE` → `gDescription_SpiritOfTheBreeze`).

### `color` by card kind

| Kind | `color` | `monsterEffect` | `spellEffect` | `trapEffect` |
|------|---------|-----------------|---------------|--------------|
| Normal monster | `NORMAL_CARD` | `0` | `2` | `0` |
| Effect monster | `EFFECT_CARD` | `0` or `MONSTER_EFFECT_*` | `2` | `0` |
| Spell | `SPELL_CARD` | `0` | `2` | `0` |
| Trap | `TRAP_CARD` | `0` | `2` | hook id |
| Field spell | `SPELL_CARD` + `customFieldSpell` | — | `2` | `0` |

Spells/traps use `atk`/`def` `65535`, `attribute` `0`, `level` `0`.

Activated monsters also need `activation_description`. Effect monsters with once-per-turn logic may need `effect_usage` (`once`, `once_per_turn`, `multiple_per_turn`, `continuous`).

## Step 2 — Art

**Stem** = `card_const.lower()` → file `src_custom/assets/cards/80x80/<stem>.png`.

```bash
ls src_custom/assets/cards/80x80/<stem>.png
```

If missing: check `src_custom/assets/cards/CARD_PROGRESS.md` todo list, or tell user art is needed. For PNG authoring specs, read `documentation/adding-custom-cards.md` (only then).

Do **not** hand-edit `build/cards/` or `src_custom/generated/card_art_generated.inc`.

## Step 3 — Manifest Entry

Append to the **end** of the `cards` array in `tools/card_data_manifest.json` (after the last entry). Manifest order = card ID; never reorder existing entries.

**Formatting is locked — do not change without explicit user approval:**

- Use `python3 tools/add_custom_card.py ... --write` to append; it calls `write_manifest()` in `tools/card_manifest.py`.
- Never run `json.dumps` on the manifest or hand-reorder keys.
- Every card object must use the canonical key order from `MANIFEST_CARD_KEY_ORDER` in `card_manifest.py`.
- `password` must always be a **single-line** array: `"password": [1, 3, 9, 4, 4, 4, 2, 2]`.
- Copy the nearest similar card in the manifest for field order; grep `GOBLIN_KING` or another recent custom entry as the template.

Copy the nearest template below; grep the manifest for one similar card only if a field is unclear (e.g. `trapEffect` for a trap clone).

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
  "activation_description": { "symbol": "gActivationDescription_BurningLand", "pages": ["..."] }
}
```

### Trap — e.g. Magic Jammer

Same shell as spell but `"type": "TYPE_TRAP"`, `"color": "TRAP_CARD"`, and set `"trapEffect"` to match an existing trap dispatcher id (grep manifest for a similar trap).

## Step 4 — Effect Hooks (only when needed)

| Card has… | Action |
|-----------|--------|
| No effect / normal monster | **Stop** — no hook files |
| Spell effect | **card-effect-hook-placement** → `src_custom/spell_effects/<stem>.c`, wire `src_custom/spell_effect_hooks.c` |
| Trap effect | trap hooks + `src_custom/trap_effects/` |
| Activated monster | `MONSTER_EFFECT_*` in manifest + activated hooks |
| Passive stat / always-on | `src_custom/permanent_effects/` |
| End-of-turn / standby | `src_custom/turn_effects/` + one row in `sTurnEffectOverrides[]` in `turn_effect_hooks.c` |

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

**Spell pattern** — resolve body callback + trap gate (see `src_custom/spell_effects/raregold_armor.c`, `sparks.c`):

```c
#include "duel_helpers.h"

static void MySpell_ResolveBody(void)
{
  if (Duel_ChangeLp(INACTIVE_DUELIST, -500, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  Duel_ShowEffectText(MY_SPELL);
}

APPEND_TEXT void EffectMySpell(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(MY_SPELL, 500, MySpell_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
  MySpell_ResolveBody();
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

## Step 5 — Runtime Test Hand (if requested)

`configs/runtime.c` → set `.card_in_hand_1` … `.card_in_hand_5` to the new `CARD_CONST`. Requires `#include "constants/card_ids.h"` (already present).

Trunk ownership at new game is already handled by `start_with_three_copies_of_every_card` in the same file — no trunk code changes.

## Step 6 — Progress + Build

```bash
make test-cards        # manifest-only (no C hook / runtime edits)
make test-cards-build  # manifest + effect hooks and/or configs/runtime.c
```

`test-cards` runs manifest validation, RAM card-growth check, trunk validators, and `card_art_progress.py`. It skips events, portraits, CG, opening screens, and the full ROM link — those are unrelated to adding a card.

Use `make test` only when the change also touches non-card systems (events, LynJump outside card hooks, RAM map, etc.).

## Cost Heuristic

Avoid inventing costs from scratch:

1. Grep manifest for same `level` + similar `atk`/`def` (±200) + same `color`.
2. Normal level-4 walls (~800/2000): often `319`.
3. Custom spells/traps: often `150` unless a vanilla analogue exists in manifest.

## Generated Outputs (verify, never edit)

After `make`, confirm grep hits for the new const in:

- `include/constants/card_ids.h`
- `src_custom/generated/card_trunk_generated.inc`
- `src_custom/generated/card_art_generated.inc`

## Related Skills / Docs

| Need | Read |
|------|------|
| Effect implementation | `.agents/skills/card-effect-hook-placement/SKILL.md` |
| Duel helper API | `include/duel_helpers.h`, `documentation/monster-card-effects.md` |
| Pre-reply validation | `.agents/skills/validate-before-reply/SKILL.md` |
| Art authoring / palette | `documentation/adding-custom-cards.md` |
| Description format | `documentation/card-descriptions.md` |
| Save/RAM growth (many cards) | `documentation/custom-card-memory.md` + `make memory-report` |
