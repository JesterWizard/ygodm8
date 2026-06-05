# Duel Shop Card Drops

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

After winning an overworld duel, the game silently adds up to three cards to the card shop. This feature adds an optional duel textbox page that lists what was actually stocked this win, using the same popup panel as deck capacity and domino rewards.

The feature is controlled by `gRuntimeConfig.show_duel_shop_card_drops` in `configs/runtime.c` (default **on**).

## Plan

### Win reward order

When `gDuelData.unk2d` is set, the custom win handler shows rewards in this order:

| Step | Popup / action |
|------|----------------|
| 1 | Duel victory |
| 2 | Deck capacity increase |
| 3 | Domino / money reward |
| 4 | **Shop card drop list** (this feature) |
| 5 | Ante trunk card popups |

Shop stock is updated **before** any of these popups. `AddCardDropsToShop()` runs at the start of `HandleWin__Replacement`, so the popup reads recorded results rather than re-rolling drops.

### Recording model

`AddCardDropsToShop__Replacement` mirrors vanilla’s three-roll loop (`sub_8020050` → `AddCardQtyToShop2`). For each roll it compares `GetShopCardQty` before and after the add. Only cards whose shop quantity actually increased are recorded. Duplicate rolls merge into one line with a higher `(xN)` count.

The scratch buffer `gDuelShopDropRecord` lives in **IWRAM** (`asm/ram_map.s`). It must not use `APPEND_DATA`; that section is ROM-backed and writes would not persist at runtime.

### Popup layout

The popup is built as duel textbox control codes and displayed through `sub_8041C94` (same path as other duel reward text).

| Line | Content |
|------|---------|
| 1 | `Added to shop:` |
| 2 | First card `Name (xN)` |
| 3 | Second card `Name (xN)` |
| 4 | Third card `Name (xN)` |

Each line is capped at **28 glyphs** (`SHOP_DROP_LINE_WIDTH`), matching the duel textbox row width. The ` (xN)` suffix is reserved first; if the localized card name would overflow, the name is truncated and ends with `...`.

Example:

```
Added to shop:
Swords of Revealing Light (x1)
Hane Hane (x2)
```

If nothing was added (for example all rolls were `CARD_NONE`, or every target card was already at shop max quantity):

```
Added to shop:
No new cards added
```

Card names are copied as literal text from `gCardInfo.name` (via `SetCardInfo` and `GetCurrentLanguageStringOffset`), not `#2` card-name tokens, so up to three aggregated lines are supported without the two-slot embedded-name limit.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `show_duel_shop_card_drops` in `configs/runtime.h` and `configs/runtime.c` | Enables or disables recording and the popup |
| Drop recording | `AddCardDropsToShop__Replacement` in `src_custom/code_801EF30_hooks.c` | Runs the vanilla shop roll loop and records `gShopCardQty` deltas |
| Popup text | `DisplayDuelShopDropText` in `src_custom/code_801EF30_hooks.c` | Builds the text buffer and calls `sub_8041C94` |
| Line formatting | `AppendCardShopDropLine`, `AppendTruncatedName` in `src_custom/code_801EF30_hooks.c` | Per-line 28-glyph limit and `...` truncation |
| Win hook call site | `HandleWin__Replacement` in `src_custom/code_801EF30_hooks.c` | Calls `DisplayDuelShopDropText` after `DisplayMoneyRewardText` |
| Scratch RAM | `gDuelShopDropRecord` in `asm/ram_map.s` | IWRAM buffer for up to three `(cardId, qty)` pairs |
| Shop quantity helpers | `GetShopCardQty`, `AddCardQtyToShop2__Replacement` in `src_custom/card_shop_hooks.c` | Source of truth for what the shop accepted |
| Hook wiring | `src_custom/LynJump.event` (`ORG $20030`) | Redirects `AddCardDropsToShop` to the replacement |
| Vanilla roll source | `sub_8020050` in `src/code_801EF30.c` | Weighted pick from `gDuelData.duelist.shopCards` |

## TODO

- Add custom per-duelist shop drop tables (trunk rewards are already customizable separately; shop rolls still use vanilla `shopCards`).
- Consider a debug-only mode that lists skipped rolls (for example `CARD_NONE` or shop-at-max) when nothing was recorded.

## Limitations & Bugs

- Shop drops still use vanilla `gDuelData.duelist.shopCards` via `sub_8020050`. Custom duel reward entries do not override shop rolls today.
- At most three cards are rolled per win, so the popup never lists more than three unique IDs.
- Truncation uses a simple glyph count; it does not mirror the duel textbox’s word-wrap-at-space behavior for embedded `#2` card names.
- If a card is already at `SHOP_MAX_CARD_QTY`, the roll does not increase stock and that card is omitted from the popup (the empty state shows `No new cards added` when every roll fails to add stock).
- The popup only appears when `gDuelData.unk2d` is set (same gate as capacity and money reward text).
