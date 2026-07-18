#!/usr/bin/env python3
"""Post-link: relocate Meteo blob pointers and exit to title (not SoftReset).

The Meteo-generated video.gba is a standalone GBA ROM originally linked at
0x08000000.  When embedded elsewhere in ROM, literal-pool ROM addresses in
known code ranges must be shifted by the placement delta.

Stock COMET loops the video and SoftResets to 0x08000000 (full reboot through
copyright).  We:
  1. Point EOF / skip exits at the blob SoftReset cleanup (+0xAF1C).
  2. Rewrite that SoftReset tail to branch to MeteoExitTrampoline, which
     RegisterRamResets and jumps to MeteoReturnToTitle (title screen, no
     crt0 / copyright).
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

PATCH_RANGES = [
    (0x0000, 0x0310),
    (0x9C2C, 0x9C2C + 0x1524),
]

CODE_SCAN_SIZE = 0x10000


def arm_b(pc_off: int, dest_off: int) -> bytes:
    """ARM B (always); offsets are relative to the blob base."""
    imm24 = ((dest_off - (pc_off + 8)) >> 2) & 0xFFFFFF
    return struct.pack("<I", 0xEA000000 | imm24)


# Wrong prior patch at +0xA15C — restore if present.
A15C_BAD = bytes.fromhex("0100a0e3080081e5040081e51eff2fe1")
A15C_STOCK = bytes.fromhex(
    "0113a0e3011c81e20000a0e3b200c1e10113a0e3b60cc1e18c141fe5040081e5"
)

# End-of-stream / skip → SoftReset cleanup entry (then rewritten to trampoline)
AE3C_STOCK = bytes.fromhex("a2ffff1a")
AE3C_EXIT = arm_b(0xAE3C, 0xAF1C)

AE08_STOCK = bytes.fromhex("0100a0e3")
AE08_EXIT = arm_b(0xAE08, 0xAF1C)

AD54_STOCK = bytes.fromhex("0100a0e3")
AD54_EXIT = arm_b(0xAD54, 0xAF1C)

# Thumb: r1=0 so Play won't internally loop; SoftReset only if Play returns
# (EOF/skip normally take the IWRAM cleanup → trampoline path and never return).
THUMB_MAIN_OFF = 0x1FC
THUMB_MAIN_STOCK = bytes.fromhex("0121381cfff7b2fffae7")  # r1=1; play; b 1fc
THUMB_MAIN_EXIT = bytes.fromhex("0021381cfff7b2ff00df")  # r1=0; play; swi SoftReset

# SoftReset tail at +0xAF3C → ldr/bx MeteoExitTrampoline
AF3C_STOCK = bytes.fromhex(
    "0314a0e3"  # mov r1, #0x03000000
    "7f1c81e2"  # add r1, #0x7f00
    "fa1081e2"  # add r1, #0xfa
    "0000a0e3"  # mov r0, #0
    "b000c1e1"  # strh r0, [r1]
    "fd00a0e3"  # mov r0, #0xfd
    "000001ef"  # svc RegisterRamReset
    "000000ef"  # svc SoftReset
)


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


def patch_at(
    rom: bytearray,
    blob_start: int,
    off: int,
    stock: bytes,
    new: bytes,
    label: str,
) -> None:
    addr = blob_start + off
    if bytes(rom[addr : addr + len(new)]) == new:
        print(f"  {label} already patched at +{off:#06x}")
        return
    got = bytes(rom[addr : addr + len(stock)])
    if got != stock:
        print(
            f"  warning: {label} mismatch at +{off:#06x} "
            f"(got {got.hex()}, expected {stock.hex()}) — skip",
            file=sys.stderr,
        )
        return
    rom[addr : addr + len(new)] = new
    print(f"  {label} +{off:#06x}: patched")


def patch_softreset_to_trampoline(
    rom: bytearray, blob_start: int, trampoline: int
) -> None:
    """Replace BIOS SoftReset tail with bx MeteoExitTrampoline."""
    off = 0xAF3C
    addr = blob_start + off
    exit_code = (
        bytes.fromhex("00009fe5")  # ldr r0, [pc, #0] -> word at af44
        + bytes.fromhex("10ff2fe1")  # bx r0
        + struct.pack("<I", trampoline)
    )

    if bytes(rom[addr : addr + len(exit_code)]) == exit_code:
        print(f"  SoftReset->trampoline already patched at +{off:#06x}")
        return

    got = bytes(rom[addr : addr + len(AF3C_STOCK)])
    if got != AF3C_STOCK:
        if bytes(rom[addr : addr + 8]) == bytes.fromhex("00009fe510ff2fe1"):
            struct.pack_into("<I", rom, addr + 8, trampoline)
            print(f"  SoftReset->trampoline +{off:#06x}: updated addr {trampoline:#010x}")
            return
        print(
            f"  warning: SoftReset tail mismatch at +{off:#06x} "
            f"(got {got.hex()}) — skip",
            file=sys.stderr,
        )
        return

    rom[addr : addr + len(exit_code)] = exit_code
    print(f"  SoftReset->trampoline +{off:#06x}: {trampoline:#010x}")


def patch_no_loop(rom: bytearray, blob_start: int, trampoline: int) -> None:
    a15c = blob_start + 0xA15C
    if bytes(rom[a15c : a15c + len(A15C_BAD)]) == A15C_BAD:
        rom[a15c : a15c + len(A15C_STOCK)] = A15C_STOCK
        print("  restored stock +0xA15C (prior bad patch)")

    patch_at(rom, blob_start, 0xAE3C, AE3C_STOCK, AE3C_EXIT, "EOF->cleanup")
    patch_at(rom, blob_start, 0xAE08, AE08_STOCK, AE08_EXIT, "B-skip->cleanup")
    patch_at(rom, blob_start, 0xAD54, AD54_STOCK, AD54_EXIT, "key-exit->cleanup")
    patch_at(
        rom, blob_start, THUMB_MAIN_OFF, THUMB_MAIN_STOCK, THUMB_MAIN_EXIT, "thumb once"
    )
    patch_softreset_to_trampoline(rom, blob_start, trampoline)


def patch_blob_in_rom(
    rom_path: Path, blob_addr: int, map_path: Path, trampoline: int
) -> None:
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
    patch_no_loop(rom, blob_start, trampoline)

    rom_path.write_bytes(rom)
    print(f"  patched {rom_path.name}")


def _self_check() -> None:
    """ponytail: branch encodings and SoftReset stock fingerprint."""
    assert AE3C_EXIT == bytes.fromhex("360000ea")
    assert AE08_EXIT == bytes.fromhex("430000ea")
    assert AD54_EXIT == bytes.fromhex("700000ea")
    assert len(THUMB_MAIN_EXIT) == len(THUMB_MAIN_STOCK) == 10
    assert AF3C_STOCK == bytes.fromhex(
        "0314a0e37f1c81e2fa1081e20000a0e3b000c1e1fd00a0e3000001ef000000ef"
    )


def main() -> int:
    _self_check()
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

    trampoline = find_symbol(args.map, "MeteoExitTrampoline")
    if trampoline is None:
        print("meteo_integrate: MeteoExitTrampoline not in map — skip exit rewrite")
        return 1

    print(f"meteo_integrate: blob at 0x{blob_addr:08X}, exit {trampoline:#010x}")
    patch_blob_in_rom(args.rom, blob_addr, args.map, trampoline)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
