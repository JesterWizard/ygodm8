#!/usr/bin/env python3
"""Post-link: scan Meteo blob for internal ROM addresses and shift them.

The Meteo-generated video.gba is a standalone GBA ROM originally linked at
0x08000000.  When embedded elsewhere in ROM, all 32-bit aligned literal pool
entries that point within the blob's code section must have their upper
halfword shifted by the placement delta.

We only patch literal pools in known code regions:
  - Boot code + literal pools: 0x0000 - 0x0310
  - IWRAM player engine source: 0x9C2C - 0xB150
Everything outside these ranges is compressed video/audio data and MUST
not be touched.

The blob's own exit handler does bx 0x08000000 to cold-boot, which in
our ROM jumps to the game entry -- no separate trampoline patch needed.
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Only patch literal pools in these known code regions.
# Boot code (ARM) + literal pools span 0x0000-0x0310.
# The IWRAM player engine is copied from ROM 0x9C2C to 0xB150.
PATCH_RANGES = [
    (0x0000, 0x0310),                          # boot code + literal pools
    (0x9C2C, 0x9C2C + 0x1524),                 # IWRAM copy source
]

CODE_SCAN_SIZE = 0x10000  # safe upper bound for sanity


def in_patch_range(offset: int) -> bool:
    return any(start <= offset < end for start, end in PATCH_RANGES)


def find_symbol(map_path: Path, *names: str) -> int | None:
    text = map_path.read_text()
    for line in text.splitlines():
        parts = line.strip().split()
        if len(parts) >= 2 and parts[1] in names:
            try:
                addr = int(parts[0], 16)
                if 0x08000000 <= addr <= 0x09FFFFFF:
                    return addr
            except ValueError:
                pass
    return None


def patch_blob_in_rom(rom_path: Path, blob_addr: int, map_path: Path) -> None:
    rom = bytearray(rom_path.read_bytes())
    file_base = blob_addr & 0x01FFFFFF

    blob_end_addr = find_symbol(map_path, "__meteo_video_end")
    if blob_end_addr is None:
        print("meteo_integrate: warning: __meteo_video_end not found", file=sys.stderr)
        return
    blob_size = blob_end_addr - blob_addr

    blob_start = file_base
    code_end = min(blob_start + CODE_SCAN_SIZE, blob_start + blob_size)
    code_slice = rom[blob_start:code_end]

    delta = blob_addr - 0x08000000
    patched = 0

    for i in range(0, len(code_slice) - 3, 4):
        file_offset = blob_start + i
        raw_u32 = struct.unpack_from("<I", code_slice, i)[0]
        upper = (raw_u32 >> 16) & 0xFFFF
        if upper != 0x0800:
            continue
        if not (0x08000000 <= raw_u32 <= 0x09FFFFFF):
            continue
        # ONLY patch if within known code ranges
        if not in_patch_range(i):
            if patched < 10:
                print(f"  SKIP +{i:#06x}: {raw_u32:#010x} (outside code range)")
            continue

        new_val = raw_u32 + delta
        struct.pack_into("<I", rom, file_offset, new_val)
        if patched < 10:
            print(f"  +{i:#06x}: {raw_u32:#010x} -> {new_val:#010x}")
        patched += 1

    print(f"  patched {patched} address references in valid code ranges")

    # No exit handler patch needed -- the blob's own exit does
    # bx 0x08000000 which cold-boots the game ROM at 0x08000000.

    rom_path.write_bytes(rom)
    print(f"  patched {rom_path.name}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=ROOT / "ygodm8.gba")
    parser.add_argument("--map", type=Path, default=ROOT / "ygodm8.map")
    args = parser.parse_args()

    if not args.rom.is_file():
        print("meteo_integrate: no ROM found, skipping")
        return 0

    blob_addr = find_symbol(args.map, "__meteo_video_start", "sMeteoVideoData")
    if blob_addr is None:
        print("meteo_integrate: no Meteo blob in ROM, skipping")
        return 0

    print(f"meteo_integrate: blob at 0x{blob_addr:08X}")
    patch_blob_in_rom(args.rom, blob_addr, args.map)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
