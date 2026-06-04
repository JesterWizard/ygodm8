# Duelist Deck Viewer

---

## Index

- [Introduction](#introduction)
- [Access](#access)
- [Controls](#controls)
- [Deck List Sources](#deck-list-sources)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

On the overworld, the player can inspect an opponent’s full duel deck before starting a duel. Press **START** while facing an NPC with duel dialogue; the game opens the same deck list UI used from the status menu, but editing is disabled.

Design goals:

- Reuse the existing deck menu graphics, sorting, and card detail flow.
- Do not change the player’s real deck or trunk.
- Avoid conflicting with **L**, which toggles world-map thought bubbles.

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_duelist_deck_viewer` in `configs/runtime.c` (default **on**) |
| Input | On the overworld field, press **START** while facing a duelist |
| Hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` |
| Target | An overworld object in talk range with a separate duel script (`scriptR`) |
| Data | A resolvable opponent deck (manifest, vanilla duelist table, custom card-shop deck, or Tea’s deck) |

When the viewer opens successfully, overworld state is restored the same way as after the debug menu (`OverworldRestoreAfterDebugMenu()`, field music via `PlayOverworldMusic()`).

If **START** is pressed while not facing a duelist, or the deck cannot be resolved, vanilla behavior applies and the status menu opens instead.

## Controls

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor through the deck list |
| **Up** / **Down** + **R** | Page the list by 10 rows |
| **L** | Cycle deck display mode (ATK/DEF, attribute, cost, etc.) |
| **A** | Open full card detail view; **B** returns to the list |
| **SELECT** | Change sort mode |
| **START** | Open sort submenu (same as deck editor) |
| **B** | Close the viewer and return to the field |

Trunk actions (move card to trunk, move all to trunk) are not available in this mode.

## Deck List Sources

Resolution order in `ResolveDuelistDeck` (`src_custom/duelist_deck_viewer.c`):

| Case | Source |
|------|--------|
| Tea NPC | `TeaCustomDeck_GetDuelDeck()` |
| Custom card-shop duel | `CustomDecks_GetPendingCardShopDuelDeck()` |
| Manifest entry | `GetManifestDuelDeck(duelistId)` from `duelist_deck_manifest.json` |
| Vanilla duelist | `gUnk8E00B30[duelistId]->deck` |

The duelist id is read from the duel script (`@0` command) the same way as the ante card viewer.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Public API | `DuelistDeckViewer_TryOpen` in `include/duelist_deck_viewer.h`, `src_custom/duelist_deck_viewer.c` | Saves the player deck, loads the opponent list, runs the viewer |
| Read-only menu loop | `DeckMenuMainReadOnly` in `src_custom/deck_menu_hooks.c` | Deck menu input without trunk editing |
| Post-detail restore | `DeckMenuRestoreAfterCardDetails` in `deck_menu_hooks.c` | Rebuilds deck menu VRAM after `ShowCardDetailView` |
| Overworld **START** hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` | Opens viewer when facing a duelist; otherwise opens status menu |
| Runtime toggle | `enable_duelist_deck_viewer` in `configs/runtime.h`, `configs/runtime.c` | Gates overworld **START** behavior when facing a duelist |
| Opponent deck data | `tools/duelist_deck_manifest.json`, `src_custom/generated/duelist_decks_generated.inc` | Manifest decks used at duel start and in this viewer |

## TODO

- Hide or relabel deck capacity header values when viewing an opponent deck (currently shows player capacity limits).
- Add a short on-screen hint when facing a duelist that **START** opens their deck list.

## Limitations & Bugs

- Viewer is overworld-only; not available from duel, trunk, or shop screens.
- **START** while facing a duelist always prefers the deck viewer over the status menu when a deck resolves.
- Empty or invalid opponent decks do not open the viewer; **START** falls through to the status menu.
- Card detail palette extension may briefly touch deck tilemaps; the restore path reloads deck menu graphics afterward.
