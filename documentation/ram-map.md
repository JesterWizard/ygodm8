# RAM Map

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

`asm/ram_map.s` is the central address registry for the project. It `.include`s three region sources that assemble into a single `ram_map.o`:

| File | Region |
|------|--------|
| `asm/ram_map_iwram.s` | IWRAM (`0x03001678`–`0x03007E00`) |
| `asm/ram_map_ewram.s` | EWRAM (`0x02025840`–`0x02040000`) |
| `asm/ram_map_sram.s` | Flash/SRAM (`0x0E000000`–`0x0E008000`) |

The fragments are not compiled as separate objects; they are included so bump-allocator cursors stay consistent across regions.

It exists so custom code can refer to concrete IWRAM, EWRAM, and Flash/SRAM locations by symbol instead of hard-coding addresses throughout the C code. That keeps the memory layout readable, keeps symbol names stable, and makes it easier to move allocations later without touching every call site.

The file does not contain runtime logic. It defines linker-visible symbols and helper macros that describe where each region begins, where free space starts, and how custom persistent data is laid out.

The current layout is organized by memory region:

| Region | Purpose | Notes |
|--------|---------|-------|
| IWRAM | Fast runtime state and small scratch buffers | Used for hot paths and transient data |
| EWRAM | Larger runtime arrays and slower state | Used when size matters more than access speed |
| Flash/SRAM | Persistent save data | Only the lower `0x8000` bytes are currently used |

## Plan

Use `ram_map.s` as a single source of truth for memory placement.

### Region model

| Region | How it is allocated | Typical use |
|--------|---------------------|-------------|
| IWRAM | Direct `SET_DATA` symbols or `_kernel_malloc` downward from `UsedFreeRamSpaceTop` | Small, performance-sensitive state |
| EWRAM | Direct `SET_DATA` symbols or `_kernel_malloc_ewram` downward from `UsedFreeEwramSpaceTop` | Larger mutable buffers |
| Flash/SRAM | Direct `SET_DATA`/`SET_ARRAY` symbols, `_kernel_malloc_flash` for mirrored save pairs, `_kernel_malloc_flash_free` for downward free-space allocations | Save data and mirrored persistent state |

### Macro usage

`SET_DATA`

- Use for a single absolute symbol.
- Use when the address is fixed and no `End` symbol is needed.

`SET_ARRAY`

- Use for a contiguous block.
- Emits both `name` and `nameEnd`.
- Use when the code treats the symbol as a byte range rather than a single pointer.

`_kernel_malloc`, `_kernel_malloc_ewram`, `_kernel_malloc_flash`, `_kernel_malloc_flash_free`

- Use for free-space allocations that should grow downward from the region’s free-space ceiling.
- `_kernel_malloc_flash` is special here: it allocates both flash mirrors for a named block and advances the primary/backup cursors together.
- `_kernel_malloc_flash_free` is the downward allocator for flash free space if you need an absolute scratch allocation.
- These are best for scratch buffers or internal runtime allocations that do not need a hard-coded absolute start.

### Practical rules

1. Put shared macros in `asm/ram_map.s` (before the `.include` lines).
2. Add symbols to the matching region file (`ram_map_iwram.s`, `ram_map_ewram.s`, or `ram_map_sram.s`).
3. Use `SET_DATA` for fixed addresses and `SET_ARRAY` for spans.
4. Prefer cursor-based placement only when a region contains a sequence of adjacent arrays.
5. Do not assume the whole nominal GBA SRAM window is available; this project only uses the lower `0x8000` bytes for save storage.

### Example

```asm
SET_DATA FreeFlashSpaceTop,    0x0E000000
SET_DATA FreeFlashSpaceBottom, 0x0E008000
SET_DATA UsedFreeFlashSpaceTop, FreeFlashSpaceBottom

SET_ARRAY gSaveSlotPrimary, 0x0E000040, 0x747
SET_ARRAY gSaveSlotBackup,   0x0E004020, 0x747

SET_DATA gCustomCardQtyFlashPrimaryStart, 0x0E000788
SET_DATA gCustomCardQtyFlashBackupStart,  0x0E004768
```

This layout means:

- the save slots are fixed at known flash offsets
- the custom mirrored arrays start from a defined point and advance in order
- the free-space boundary still reflects the portion of flash the game actually uses

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Core memory map | `asm/ram_map.s` + `asm/ram_map_{iwram,ewram,sram}.s` | Defines the IWRAM, EWRAM, and Flash/SRAM symbols used across the build |
| IWRAM free-space allocation | `ram_map_iwram.s` | Reserves fast runtime memory from the top of free IWRAM downward |
| EWRAM free-space allocation | `ram_map_ewram.s` | Reserves larger runtime buffers from the top of free EWRAM downward |
| Flash free-space and save slots | `ram_map_sram.s` | Defines the persistent save areas, usable flash window, and mirrored flash pairs |
| Custom flash mirrors | `ram_map_sram.s` | Places the custom trunk/shop/player-temp card quantity mirrors in flash |
| Symbol consumers | `src_custom/card_hooks.c`, `src_custom/code_800AC64_hooks.c`, `src_custom/card_shop_hooks.c` | Read and write the symbols defined in the map |
| Expanded graveyard buffers | `gExpandedGraveyard*`, `gAiSimSaved*`, `gAiBatchCheckpoint*` in `asm/ram_map_ewram.s` | Three EWRAM layers for live GY stacks and AI sim bookkeeping; see [expanded-graveyard.md](expanded-graveyard.md) |

## TODO

- Consider renaming the save-slot symbols to make the primary/backup relationship more explicit.
- Add a short comment near each region boundary explaining why that boundary is safe.
- If more persistent data is added, split the flash section into subgroups for save blocks, mirrored arrays, and one-off records.

## Limitations & Bugs

- `ram_map.s` is only a declaration file; it does not enforce bounds at runtime.
- If a symbol is assigned the wrong address, the compiler and linker will usually not catch the logic error.
- The flash region only reserves the lower `0x8000` bytes because that is the portion the current save code actually uses.
- Cursor-based placement is only safe when the sequence length is updated consistently with the backing storage and all consumers.
