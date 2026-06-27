# Custom Field Spells

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Graphics spec](#graphics-spec)
- [Contributor workflow](#contributor-workflow)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Custom field spells extend the duel board terrain beyond the seven vanilla fields (`FIELD_ARENA` … `FIELD_YAMI`). Each custom field spell gets:

- its own scrolling duel-board background (BG2)
- a manifest-linked custom card
- a dedicated effect file under `src_custom/field_spell_effects/`
- runtime tracking in EWRAM for which field spell is active

When the active field spell leaves the board, the terrain reverts to `FIELD_ARENA`.

v1 ships the framework only: no pilot field spell is registered yet.

## Plan

| Layer | Responsibility |
|-------|----------------|
| Asset build | Convert one indexed PNG per field into `.4bpp`, `.gbapal`, `.huff`, and a generated tilemap |
| Registration | `src_custom/field_spell_table.inc` maps spell IDs, field IDs, card constants, and effect functions |
| Activation | `TryActivateCustomFieldSpell()` in `spell_effect_hooks.c` dispatches before vanilla spell effects |
| Gfx load | `SetDuelFieldGfx__Replacement()` loads custom assets when `gDuel.field` is a custom index |
| Lifecycle | `ClearZone__Replacement()` reverts to arena when the tracked field spell zone clears |
| Stats | Custom fields use `gCustomFieldStatMods` (neutral by default) instead of ROM `gUnk8094FE4` |

Future per-field callbacks (`OnFieldSpellEndTurn`, etc.) are stubbed in `field_spell_effect_hooks.c` for ongoing effects beyond activation.

## Graphics spec

| Requirement | Value |
|-------------|-------|
| Source PNG path | `src_custom/assets/field_spells/<stem>/<stem>.png` (preferred), `src_custom/assets/field_spells/<stem>.png`, or `src_custom/assets/field_spells/<stem>/field.png` (legacy) |
| Dimensions | **248 × 304 px** |
| Color mode | Indexed PNG (`mode P`) |
| Max colors | **48** (96-byte `.gbapal`) |
| Tile grid | 31 × 38 tiles (8×8 px each) |
| Tile format | 4bpp character tiles with palette banks, same BG mode as vanilla (`REG_BG2CNT = 0x9B02`) |
| Compressed tiles | `.huff` via `tools/gbagfx/gbagfx field.4bpp field.huff -depth 4` |
| Tile budget | At most **1024** unique 8×8 tiles (32768 bytes, below duel UI char data at `0x8040`) |
| Palette banks | Colors 0–15, 16–31, and 32–47 map to BG palette banks 0, 1, and 2 in the tilemap |
| Multi-bank tiles | Each 8×8 tile picks one bank and remaps pixels to the nearest color in that bank |

`<stem>` is the manifest `card_const` in lowercase with underscores (`ANCIENT_FOREST` → `ancient_forest`).

## Contributor workflow

1. Add `src_custom/assets/field_spells/<stem>/<stem>.png` (248×304, ≤48 colors). (`<stem>.png` or `<stem>/field.png` also work as fallback paths.) Generated `.4bpp`/`.huff`/tilemap files land in `src_custom/assets/field_spells/<stem>/` and are cached under `.cache/field_spells/`.
2. Add enum entries to `include/constants/custom_field_spells.h` (spell ID) and uncomment a row in `src_custom/field_spell_table.inc`:

   ```c
   _(CUSTOM_FIELD_SPELL_ANCIENT_FOREST, FIELD_CUSTOM_ANCIENT_FOREST, ANCIENT_FOREST, EffectActivateAncientForest)
   ```

3. Add matching `#define FIELD_CUSTOM_ANCIENT_FOREST` via the generated header (automatic once the table row exists).
4. Create `src_custom/field_spell_effects/<stem>.c`:

   ```c
   void EffectActivateAncientForest(void)
   {
     ActivateCustomFieldSpell(CUSTOM_FIELD_SPELL_ANCIENT_FOREST);
   }
   ```

5. Append a manifest card with `"customFieldSpell": "CUSTOM_FIELD_SPELL_ANCIENT_FOREST"`.
6. Run `make`.

The build runs `tools/build_field_spell_gfx.py`, which validates PNGs, emits compressed assets, and regenerates the tables in `src_custom/generated/`. Converted assets are cached under `.cache/field_spells/` (kept by `make clean-build`; cleared by `make clean-cache` or full `make clean`).

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Asset folders | `src_custom/assets/field_spells/` | Source `<stem>/<stem>.png` (or `<stem>.png` / `<stem>/field.png`); generated assets under `<stem>/` |
| Gfx build script | `tools/build_field_spell_gfx.py` | PNG validation, asset conversion, generated tables |
| Build rules | `graphics.mk`, `Makefile` | Wires gfx generation into `make` |
| Registration table | `src_custom/field_spell_table.inc` | Single source of truth for spell/field/card/effect mapping |
| Spell IDs | `include/constants/custom_field_spells.h` | `CUSTOM_FIELD_SPELL_*` enum |
| Field IDs | `include/constants/custom_fields_generated.h` | Extends `NUM_FIELDS` past vanilla |
| EWRAM state | `asm/ram_map.s` | `gActiveCustomFieldSpellId`, zone row/col |
| Gfx loader | `SetDuelFieldGfx__Replacement` in `src_custom/field_spell_gfx_hooks.c` | Loads custom or vanilla duel field layers |
| Effect dispatcher | `src_custom/field_spell_effect_hooks.c` | Activation, revert, future lifecycle stubs |
| Spell routing | `src_custom/spell_effect_hooks.c` | Calls `TryActivateCustomFieldSpell()` before vanilla effects |
| Terrain stats | `SetFinalStat__Replacement` in `src_custom/card_hooks.c` | Uses `gCustomFieldStatMods` for custom fields |
| Zone cleanup | `ClearZone__Replacement` in `src_custom/code_803F02C_hooks.c` | Reverts terrain when the active field spell zone clears |
| Manifest key | `tools/card_data_manifest.json` | Optional `"customFieldSpell": "CUSTOM_FIELD_SPELL_*"` |
| Public API | `include/custom_field_spell.h` | Runtime helpers and asset accessors |

## TODO

- Add the first real custom field spell card and artwork.
- Author per-field stat modifiers in generated `gCustomFieldStatMods` metadata when custom terrain boosts/penalties are needed.
- Implement ongoing effect callbacks (`OnFieldSpellEndTurn`, etc.) for fields that need more than activation-only behavior.
- Add R-button opponent-hand gfx for custom fields (v1 falls back to arena).
- Add AI heuristics for custom terrains.

## Limitations & Bugs

- R-button opponent-hand view still uses vanilla arena gfx for custom field indices.
- Vanilla AI hard-codes checks for the seven vanilla fields only.
- Custom field stat tables default to neutral (no ATK/DEF change) until explicitly authored.
- Only one custom field spell is tracked at a time; activating another replaces the previous terrain state.
