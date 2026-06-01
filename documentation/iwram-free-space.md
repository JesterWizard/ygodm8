# IWRAM Free Space Map

## Introduction

The game uses on-chip work RAM, or IWRAM, as a mix of fixed globals, stack, interrupt state, and temporary buffers.

For this build, the first safe free byte in the `0x03000000-0x03007FFF` range is:

`0x03001678`

The last safe byte before the reserved stack/vector area is:

`0x03007DFF`

So the current free range is:

`0x03001678-0x03007DFF`

Everything before `0x03001478` is not general-purpose free space because it is already assigned to fixed IWRAM symbols in the linker layout. The region `0x03001478-0x03001677` is also occupied by two 256-byte `CpuSet` buffers.

## Plan

The current IWRAM layout is best understood in three layers:

| Layer | Range | Meaning |
|--------|--------|---------|
| HQ mixer (IWRAM image) | `0x03000000-0x03000AB7` | Copied from ROM at `sub_80595C4` (~0xAB8 bytes; vanilla was ~0x400) |
| Fixed runtime globals | `0x03000AB8-0x03001477` | Directly referenced IWRAM state and work areas (layout shifted vs. vanilla) |
| IntrMain IWRAM stub (`g3000400`) | `0x03001A00-0x030021FF` | Relocated from `0x03000400` so the HQ mixer does not clobber it |
| Temporary buffers | `0x03001478-0x03001677` | Two `0x100`-byte blocks copied by `sub_80327C8` |
| Free space | `0x03001678-0x03007DFF` | Currently unused by the linker layout and safe for new IWRAM allocations |
| Reserved startup area | `0x03007E00-0x03007FFF` | Stack and IRQ vector area reserved by startup code |

Why `0x03001478` is the first point where the free space discussion changes:

1. The linker script already fixes several IWRAM globals below that address, including `g3000C00`, `g3000C38`, `g3000C6C`, `g3000C78`, and `g3001078`.
2. Startup code and runtime code use the region above that point for dedicated buffers and state.
3. The code at `sub_80327C8` copies two 256-byte blocks into `0x03001478` and `0x03001578`, so that span is occupied by design.

Why `0x03007E00-0x03007FFF` is not free:

1. `InitWRAM()` only clears IWRAM up to `0x7E00` bytes from `0x03000000`.
2. `asm/crt0.s` sets stack pointers inside the top of IWRAM.
3. `asm/crt0.s` also stores the IRQ handler pointer at `0x03007FFC`.