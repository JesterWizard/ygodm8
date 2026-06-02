# IWRAM Free Space Map

## Introduction

The game uses on-chip work RAM, or IWRAM, as a mix of fixed globals, stack, interrupt state, and temporary buffers.

For this build, the first byte reserved for custom HQ mixer buffers in the `0x03000000-0x03007FFF` range is:

`0x03001678`

The last safe byte before the reserved stack/vector area is:

`0x03007DFF`

The `_kernel_malloc` region still begins at `FreeRamSpaceBottom` (`0x03007E00`) and grows downward. HQ mixer buffers sit at the low end of free space; everything from `0x030027F8` up to the malloc tail remains available for new fixed allocations.

## Plan

The current IWRAM layout is best understood in three layers:

| Layer | Range | Meaning |
|--------|--------|---------|
| IntrMain IWRAM stub (`g3000400`) | `0x03000400-0x03000BFF` | Vanilla address; copied from ROM in `sub_800818C` |
| Fixed runtime globals | `0x03000C00-0x03001477` | Directly referenced IWRAM state and work areas |
| Temporary buffers | `0x03001478-0x03001677` | Two `0x100`-byte blocks copied by `sub_80327C8` |
| HQ mix buffer (`gM4aHqMixBuffer`) | `0x03001678-0x03001BF7` | 16-bit intermediate mix buffer (`0x580` bytes) |
| HQ mixer code buffer (`MixerBuffer`) | `0x03001BF8-0x030027F7` | Copied from ROM at init (`~0xB24` bytes; `0xC00` reserved) |
| Free space | `0x030027F8-0x03007DFF` | Unused by the linker layout and safe for new IWRAM allocations |
| Reserved startup area | `0x03007E00-0x03007FFF` | Stack and IRQ vector area reserved by startup code |

Why `0x03001478` is the first point where the free space discussion changes:

1. The linker script already fixes several IWRAM globals below that address, including `g3000C00`, `g3000C38`, `g3000C6C`, `g3000C78`, and `g3001078`.
2. Startup code and runtime code use the region above that point for dedicated buffers and state.
3. The code at `sub_80327C8` copies two 256-byte blocks into `0x03001478` and `0x03001578`, so that span is occupied by design.

Why `0x03007E00-0x03007FFF` is not free:

1. `InitWRAM()` only clears IWRAM up to `0x7E00` bytes from `0x03000000`.
2. `asm/crt0.s` sets stack pointers inside the top of IWRAM.
3. `asm/crt0.s` also stores the IRQ handler pointer at `0x03007FFC`.
