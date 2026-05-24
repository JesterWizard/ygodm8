# Duelist Level Shop Discounts

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

This feature adds an optional runtime discount to shop buy prices based on the player’s duelist level.

The goal is simple:

1. high-level saves should get cheaper shop prices
2. the discount should be easy to toggle at runtime
3. the existing shop price math should stay intact when the toggle is off

The discount uses a fixed step model:

- every 100 levels gives 5% off the buy price
- level `999` is treated as level `1000` for discount purposes
- the discount is capped at 50%

## Plan

The feature flow is:

| Stage | Location | Result |
|--------|----------|--------|
| Shop price scaling | `ScalePriceToQty__Replacement` | Keeps the vanilla or dynamic shop price calculation, then applies the level-based discount if enabled |
| Discount calculation | `ApplyDuelistLevelShopDiscount` | Converts the current duelist level into a 5% step count and applies the capped reduction to `gShopSelectedCard.buyPrice` |
| Runtime toggle | `gRuntimeConfig.discount_shop_costs_by_duelist_level` | Enables or disables the discount at runtime |

Behavior summary:

| Config | Level state | Buy price result |
|--------|-------------|------------------|
| `FALSE` | Any | Original shop price behavior |
| `TRUE` | Level below 100 | No discount |
| `TRUE` | Level 100-199 | 5% off |
| `TRUE` | Level 200-299 | 10% off |
| `TRUE` | Level 900-999 | 45% off |
| `TRUE` | Level 999 or higher | 50% off |

Implementation notes:

1. The discount is applied after the normal shop price has already been computed.
2. The feature only changes the buy price; sell price logic is left alone.
3. The runtime floor prevents the max-start-level configuration from dropping the discount below the top bucket.
4. The price is still clamped to at least `1` when discount math would round down to `0`.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle definition | `gRuntimeConfig.discount_shop_costs_by_duelist_level` in `configs/runtime.h` and `configs/runtime.c` | Controls whether the level-based shop discount is active |
| Shop discount logic | `ApplyDuelistLevelShopDiscount` in `src_custom/card_hooks.c` | Computes the level bucket and reduces `gShopSelectedCard.buyPrice` |
| Shop price hook | `ScalePriceToQty__Replacement` in `src_custom/card_hooks.c` | Runs the existing shop price calculation, then applies the optional discount |
| Shop hook wiring | `src_custom/LynJump.event` | Redirects the vanilla `ScalePriceToQty` entry to the replacement |