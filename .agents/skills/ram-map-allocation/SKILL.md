---
name: ram-map-allocation
description: "Use when implementing features whose results must persist in RAM or save data (IWRAM, EWRAM, Flash/SRAM), adding globals, scratch buffers, or mirrored save fields in this repo. Read documentation/ram-map.md first; declare symbols in asm/ram_map.s instead of hard-coding addresses in C."
---

# RAM Map Allocation

Use this skill when a feature needs runtime state, scratch memory, or persistent save data that must survive across scenes, battles, or power cycles.

## Required Reading

Read **`documentation/ram-map.md`** before allocating memory. It covers region choice (IWRAM / EWRAM / Flash), macros (`SET_DATA`, `SET_ARRAY`, `_kernel_malloc*`), layout rules, examples, consumers, and limitations.

## Core Rule

**`asm/ram_map.s`** includes the region `.s` fragments; add symbols to the matching `asm/ram_map_{iwram,ewram,sram}.s`. Reference them by name from C. Do not scatter hard-coded `0x02…` / `0x0E…` addresses through hook code.

## When To Use Which Region

| Need | Region | Typical mechanism |
|------|--------|-------------------|
| Small, hot runtime state | IWRAM | `SET_DATA` or `_kernel_malloc` |
| Larger buffers | EWRAM | `SET_DATA` or `_kernel_malloc_ewram` |
| Save data / mirrors | Flash (lower `0x8000` only) | `SET_DATA`, `SET_ARRAY`, `_kernel_malloc_flash` |

See the doc’s “Region model” and “Practical rules” sections before picking a macro.

## Where To Look First

| Concern | Location |
|---------|----------|
| Symbol definitions | `asm/ram_map.s`, `asm/ram_map_{iwram,ewram,sram}.s` |
| Example consumers | `src_custom/card_hooks.c`, `src_custom/code_800AC64_hooks.c`, `src_custom/card_shop_hooks.c` |

## Workflow

1. Read `documentation/ram-map.md`.
2. Decide region: IWRAM (fast/small), EWRAM (large), or Flash (persistent / mirrored save).
3. Add the symbol with the appropriate macro in the matching `asm/ram_map_*.s` file (keep region blocks grouped and labeled).
4. Declare `extern` symbols in the hook header or `.c` that consumes them.
5. For mirrored flash pairs, follow existing `_kernel_malloc_flash` patterns in the doc.
6. Run `make` and verify nothing overlaps existing save slots or free-space cursors.

## Notes

- `ram_map.s` does not enforce bounds at runtime; wrong addresses usually link but break at runtime.
- Flash allocations must stay within the project’s usable lower `0x8000` save window.
- Cursor-based sequences must stay consistent with every consumer and backing storage size.
