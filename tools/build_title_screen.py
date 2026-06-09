#!/usr/bin/env python3
"""Build one 8bpp title screen into LZ tileset and palette."""

from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASSET_DIR = ROOT / "src_custom" / "assets" / "title_screens"
TITLE_BUILD_DIR = ROOT / "build" / "title_screens"
GBAGFX = ROOT / "tools/gbagfx/gbagfx"
TITLE_TILE_COUNT = 600
TITLE_TILE_BYTES = TITLE_TILE_COUNT * 64


def run_gbagfx(src: Path, dst: Path, *extra: str) -> None:
    cmd = [str(GBAGFX), str(src), str(dst), *extra]
    subprocess.run(cmd, check=True, cwd=ROOT)


def build_screen(png_path: Path) -> tuple[Path, Path]:
    sys.path.insert(0, str(ROOT / "tools"))
    from validate_title_screen import validate_title_png  # noqa: E402

    errors = validate_title_png(png_path)
    if errors:
        raise SystemExit("\n".join(errors))

    TITLE_BUILD_DIR.mkdir(parents=True, exist_ok=True)
    stem = png_path.stem
    lz_path = TITLE_BUILD_DIR / f"{stem}.lz"
    pal_path = TITLE_BUILD_DIR / f"{stem}.gbapal"

    with tempfile.NamedTemporaryFile(suffix=".8bpp", delete=False) as tmp:
        raw_path = Path(tmp.name)

    try:
        run_gbagfx(
            png_path,
            raw_path,
            "-num_tiles",
            str(TITLE_TILE_COUNT),
            "-Werror=num_tiles",
        )
        raw = raw_path.read_bytes()
        if len(raw) != TITLE_TILE_BYTES:
            raise SystemExit(
                f"{png_path.name}: expected {TITLE_TILE_BYTES} 8bpp bytes, got {len(raw)}"
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
        nargs="?",
        help="Title screen PNG path (default: title_screen.png)",
    )
    args = parser.parse_args()

    png_path = args.png.resolve() if args.png else (ASSET_DIR / "title_screen.png").resolve()
    build_screen(png_path)
    print(f"build_title_screen: ok ({png_path.name})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
