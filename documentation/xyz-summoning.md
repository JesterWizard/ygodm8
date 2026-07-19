# XYZ Summoning

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Player flow](#player-flow)
- [Material count](#material-count)
- [Overlay units](#overlay-units)
- [API](#api)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Extra Deck already stores XYZ monsters (`COLOR_XYZ` / `XYZ_CARD`) with blue frames, but there was no in-duel XYZ Summon procedure. Synchro uses level-sum + Tuner; XYZ needs same-level materials matching rank, with a printed material count, and materials become overlay units under the result.

This feature adds a minimal playable XYZ path, first exercised with Gagagigo the Risen (Rank 4, 3 Level 4 monsters). Gagagigo’s effect remains stubbed.

## Plan

### Rules (v1, TCG-lite)

| Rule | Behavior |
|------|----------|
| Materials | Face-up-for-summon monsters on the **active** monster row (`isFaceUp \|\| !isDefending`) |
| Match | Each material’s level equals the XYZ’s rank (`gCardData_NEW[].level`) |
| Count | Exactly `gCardXyzMaterialCount_Hook[id]` materials (manifest `xyz_materials`) |
| Result | Must be `COLOR_XYZ` and present in the active Extra Deck |
| Extra Deck | Whitelist only; copy is **not** consumed |
| Pay | Materials cleared from field (not sent to GY); card IDs attached as overlays |
| Leave field | Overlays dump to GY when the XYZ zone is cleared |
| Restrictions | No attribute/type limits; no AI XYZ yet |

### Recipe model

**Same-level engine**: N face-up monsters of level = rank, where N is per-card from the manifest. Feasibility is computed from field + Extra Deck each time the player opens XYZ.

### Entry point

Sixth monster-menu action (**XYZ**), right column under Effect. Drawn when `XyzDuel_PlayerCanSummon()`. LynJump of `HandlePlayerMonsterAction`.

Menu grid:

```
Attack   Tribute
Defend   Effect
Synchro  XYZ
```

## Player flow

| Step | What happens |
|------|----------------|
| A on own monster | Monster menu |
| XYZ | If `XyzDuel_PlayerCanSummon()`, open Extra Deck XYZ pick list |
| Pick + confirm | Deck-menu list of feasible XYZs; confirm **XYZ Summon** |
| Pay | Auto-selected materials cleared; IDs attached as overlays on the summon zone |
| Summon | Result Special Summoned face-up ATK via `Duel_SpecialSummonMonsterId` |

Toggle: when `enable_extra_deck` is off, XYZ acts as forbidden.

## Material count

XYZ procedure cards are tagged in the manifest (`"xyz_materials": N`). The card-data generator emits `gCardXyzMaterialCount_Hook[]`. Runtime: `Card_XyzMaterialCount(cardId)` (0 = not summonable via this procedure).

Gagagigo the Risen uses `xyz_materials: 3`.

## Overlay units

EWRAM arrays keyed by fixed duelist × monster column:

- `gXyzOverlayCount[2][5]`
- `gXyzOverlayIds[2][5][5]` (max 5 overlays per zone)

Cleared on board init. Dump-to-GY runs from `ClearZoneAndSendMonToGraveyard` / `ClearZoneAndSendMonToGraveyard2` replacements before the zone is wiped.

## API

Public header: `include/xyz_duel.h`.

| Function | Purpose |
|----------|---------|
| `Card_XyzMaterialCount` | Manifest-driven material count |
| `XyzDuel_CollectFaceUpFieldSources` | Active row, face-up-for-summon monsters |
| `XyzDuel_BuildFeasibleExtraDeckTargets` | Extra Deck XYZs with enough same-level mats |
| `XyzDuel_PlayerPickTarget` | Deck-menu pick + XYZ Summon confirm |
| `XyzDuel_SelectMaterialsForRank` | Auto-pick N monsters of level = rank |
| `XyzDuel_Execute` | Clear mats, SS result, attach overlays |
| `XyzDuel_PlayerCanSummon` | Menu enable gate |
| `XyzDuel_RunPlayerFlow` | Full player XYZ path from the menu |
| `XyzOverlays_*` | Attach / detach-one / dump-all / clear / board init |

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Core XYZ API | `XyzDuel_*` in `src_custom/xyz_duel.c` | Collect, match, pick, execute |
| Public API | `include/xyz_duel.h` | Declarations |
| Material-count table | `gCardXyzMaterialCount_Hook` in `src_custom/generated/card_data_hooks.c` | Generated from manifest |
| Generator | `tools/add_card_art.py` | Emits hook table |
| Overlay RAM | `asm/ram_map_ewram.s` | `gXyzOverlayCount` / `gXyzOverlayIds` |
| Leave-field dump | `ClearZoneAndSendMonToGraveyard*__Replacement` | Dump overlays before clear |
| Monster menu | `HandlePlayerMonsterAction__Replacement` | XYZ under Effect |
| Menu dispatch | `MonsterActionMenu__Replacement` | `case 7` → `XyzDuel_RunPlayerFlow` |
| Extra Deck whitelist | Extra Deck arrays / `enable_extra_deck` | Same gate as Fusion/Synchro |

## TODO

- Overlay count UI / mini-card markers.
- Detach costs for XYZ effects (Gagagigo has none).
- AI XYZ Summon candidates.
- Consume Extra Deck copies on summon.
- Non-standard material wording (named mats, “2+”, Tokens).

## Limitations & Bugs

- Materials use the same face-up-for-summon rule as Synchro (`isFaceUp \|\| !isDefending`).
- Only the active duelist’s monster row is scanned.
- Auto material selection picks the first N matching-level monsters.
- Extra Deck is a whitelist — summoning does not remove the XYZ from the Extra Deck.
- Overlay detach for effects is stubbed (`XyzOverlays_DetachToGraveyard`).
- No AI path in v1.
