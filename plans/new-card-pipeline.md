# New Card Pipeline

---

## Index
- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The current card pipeline is still bounded by the original card set and several parts of the trunk UI assume a fixed card count. That makes it risky to add cards beyond the standard 800 because new data can be added in one place while the generated IDs, art tables, and trunk behavior remain out of sync.

This design makes `tools/card_data_manifest.json` the single source of truth for new cards. A contributor should be able to add a card by adding PNG assets and one manifest entry, then regenerate every derived file without touching the trunk logic by hand.

The target behavior is:

- add new mini art and big art PNGs for a card
- add a matching manifest entry
- regenerate IDs, data, names, and art includes
- make the trunk and card detail views render the new card automatically
- preserve existing card data and ID stability for the current set

## Plan

### Source model

The manifest defines card order. That order becomes the card ID order.

| Stage | Input | Output |
|---|---|---|
| Authoring | PNGs in the card asset folders | Raw art assets for the new card; see `documentation/adding-custom-cards.md` for 80×80 big art (512→80, 64-color indexed PNG) |
| Data entry | One manifest entry in `tools/card_data_manifest.json` | Canonical card metadata |
| Generation | Manifest + assets | `card_ids.h`, generated includes, and hook tables |
| Runtime | Generated card arrays | Trunk list, cursor logic, and details rendering |

### Implementation steps

1. Make the manifest the only accepted source for new card additions.
2. Regenerate `include/constants/card_ids.h` from the manifest with sequential values starting at `0x0000`.
3. Regenerate the generated include files in `src_custom/generated` from the same manifest:
   - `card_data_generated.inc`
   - `card_name_generated.inc`
   - `card_art_generated.inc`
   - any related generated lookup data
4. Replace fixed trunk limits in `src_custom/trunk_hooks.c` with a dynamic card-count source derived from the generated arrays.
5. Update trunk list rendering so every manifest card appears with mini art.
6. Update the card details view so every manifest card resolves the big art correctly.
7. Add validation so missing assets, duplicate card constants, or ID mismatches fail during generation instead of at runtime.

### Runtime rules

| Rule | Behavior |
|---|---|
| Card count | Derived from generated card data length, not a hard-coded constant |
| Cursor wrap | Uses the runtime count for list navigation |
| Sorting | Uses the full generated card list |
| Trunk display | Renders the entire manifest-backed card set |
| Card details | Resolves big art from the same generated ID mapping |

### Data safety

Existing data must not be disrupted. The migration should keep the current 800-card behavior intact while extending the total card space in a deterministic way. If a card is removed from the manifest later, that should be treated as a deliberate breaking change because it would shift IDs.

## Code Locations

| Feature | Location | Description |
|---|---|---|
| Manifest source | `tools/card_data_manifest.json` | Authoritative list of cards and metadata |
| Card IDs | `include/constants/card_ids.h` | Regenerated sequential ID definitions |
| Card data generation | `src_custom/generated/card_data_generated.inc` | Regenerated card stat records |
| Card name generation | `src_custom/generated/card_name_generated.inc` | Regenerated card name lookup |
| Card art generation | `src_custom/generated/card_art_generated.inc` | Regenerated art lookup tables |
| Trunk logic | `src_custom/trunk_hooks.c` | Trunk count, cursor wrap, and sorting behavior |
| Card data runtime | `src_custom/generated/card_data_hooks.c` | Runtime hook entry for generated card data |
| Card assets | `src_custom/assets/cards/` | Mini and big art PNG sources |

## TODO

- Define the exact generator entry point and command line for regenerating all derived files.
- Confirm whether `NUM_TRUE_CARDS` can be removed entirely or must remain as a compatibility alias.
- Add a verification step that checks every manifest card has both required art assets.
- Update any build scripts that still assume the original card cap.
- Test trunk navigation, sorting, and card detail rendering with cards beyond the old limit.

## Limitations & Bugs

- Card ordering becomes part of the ID contract, so manifest reordering must be treated as a breaking change.
- The current trunk code still contains fixed-card assumptions that need to be replaced before this is safe.
- Any missing or malformed generated file will affect multiple runtime paths, so generation must fail early.
- If the big art and mini art naming conventions drift, the generator needs a strict mapping rule rather than filename guessing.
