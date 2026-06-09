#!/usr/bin/env python3
"""Validate UPS patch generation and round-trip application."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from make_ups import UPS_MAGIC, apply_patch, build_patch  # noqa: E402

DEFAULT_SOURCE = ROOT / "baserom.gba"
DEFAULT_TARGET = ROOT / "ygodm8.gba"
DEFAULT_PATCH = ROOT / "ygodm8.ups"


def validate_patch_roundtrip(
    source_path: Path,
    target_path: Path,
    patch_path: Path | None = None,
) -> None:
    source = source_path.read_bytes()
    target = target_path.read_bytes()

    if patch_path is None or not patch_path.is_file():
        patch = build_patch(source, target)
    else:
        patch = patch_path.read_bytes()

    if not patch.startswith(UPS_MAGIC):
        raise ValueError(f"{patch_path or '<generated>'}: missing UPS1 header")

    applied = apply_patch(source, patch)
    if applied != target:
        first_diff = next(
            (index for index in range(len(target)) if applied[index] != target[index]),
            len(target),
        )
        raise ValueError(
            f"UPS round-trip mismatch at byte 0x{first_diff:X} "
            f"(applied {len(applied)} bytes, target {len(target)} bytes)"
        )


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=DEFAULT_SOURCE)
    parser.add_argument("--target", type=Path, default=DEFAULT_TARGET)
    parser.add_argument("--patch", type=Path, default=DEFAULT_PATCH)
    args = parser.parse_args(argv)

    missing = [
        path
        for path in (args.source, args.target)
        if not path.is_file()
    ]
    if missing:
        print(
            "validate_ups: skip — missing "
            + ", ".join(str(path.name) for path in missing),
            file=sys.stderr,
        )
        return 0

    try:
        validate_patch_roundtrip(args.source, args.target, args.patch)
    except ValueError as exc:
        print(f"validate_ups: {exc}", file=sys.stderr)
        return 1

    print("validate_ups: ok")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
