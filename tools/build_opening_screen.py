#!/usr/bin/env python3
"""Build one 8bpp opening screen into LZ tileset and palette."""

from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASSET_DIR = ROOT / "src_custom" / "assets" / "opening_screens"
OPENING_BUILD_DIR = ROOT / "build" / "opening_screens"
GBAGFX = ROOT / "tools/gbagfx/gbagfx"
OPENING_TILE_COUNT = 600
OPENING_TILE_BYTES = OPENING_TILE_COUNT * 64


def run_gbagfx(src: Path, dst: Path, *extra: str) -> None:
    cmd = [str(GBAGFX), str(src), str(dst), *extra]
    subprocess.run(cmd, check=True, cwd=ROOT)


def build_screen(png_path: Path) -> tuple[Path, Path]:
    sys.path.insert(0, str(ROOT / "tools"))
    from validate_opening_screen import validate_opening_png  # noqa: E402

    errors = validate_opening_png(png_path)
    if errors:
        raise SystemExit("\n".join(errors))

    OPENING_BUILD_DIR.mkdir(parents=True, exist_ok=True)
    stem = png_path.stem
    lz_path = OPENING_BUILD_DIR / f"{stem}.lz"
    pal_path = OPENING_BUILD_DIR / f"{stem}.gbapal"

    with tempfile.NamedTemporaryFile(suffix=".8bpp", delete=False) as tmp:
        raw_path = Path(tmp.name)

    try:
        run_gbagfx(
            png_path,
            raw_path,
            "-num_tiles",
            str(OPENING_TILE_COUNT),
            "-Werror=num_tiles",
        )
        raw = raw_path.read_bytes()
        if len(raw) != OPENING_TILE_BYTES:
            raise SystemExit(
                f"{png_path.name}: expected {OPENING_TILE_BYTES} 8bpp bytes, got {len(raw)}"
            )
        run_gbagfx(raw_path, lz_path)
    finally:
        raw_path.unlink(missing_ok=True)

    subprocess.run(
        [sys.executable, str(ROOT / "tools/build_opening_palette.py"), str(png_path), str(pal_path)],
        check=True,
        cwd=ROOT,
    )
    return lz_path, pal_path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "png",
        type=Path,
        nargs="*",
        help="Opening screen PNG paths (default: all three required screens)",
    )
    args = parser.parse_args()

    png_paths = args.png if args.png else [
        ASSET_DIR / f"opening_screen_{index}.png" for index in range(1, 4)
    ]

    for png_path in png_paths:
        build_screen(png_path.resolve())
        print(f"build_opening_screen: ok ({png_path.name})")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
