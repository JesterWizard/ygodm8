#!/usr/bin/env python3
"""Build one event CG into LZ tileset and palette under build/cgs/."""

from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CG_DIR = ROOT / "src_custom" / "assets" / "cgs"
CG_BUILD_DIR = ROOT / "build" / "cgs"
GBAGFX = ROOT / "tools/gbagfx/gbagfx"
CG_TILE_COUNT = 600


def run_gbagfx(src: Path, dst: Path, *extra: str) -> None:
    cmd = [str(GBAGFX), str(src), str(dst), *extra]
    subprocess.run(cmd, check=True, cwd=ROOT)


def build_cg(png_path: Path) -> tuple[Path, Path]:
    sys.path.insert(0, str(ROOT / "tools"))
    from validate_cg import validate_cg_png  # noqa: E402

    errors = validate_cg_png(png_path)
    if errors:
        raise SystemExit("\n".join(errors))

    CG_BUILD_DIR.mkdir(parents=True, exist_ok=True)
    stem = png_path.stem
    lz_path = CG_BUILD_DIR / f"{stem}.lz"
    pal_path = CG_BUILD_DIR / f"{stem}.gbapal"

    with tempfile.NamedTemporaryFile(suffix=".8bpp", delete=False) as raw_tmp:
        raw_path = Path(raw_tmp.name)
    with tempfile.NamedTemporaryFile(suffix=".8bpp", delete=False) as shifted_tmp:
        shifted_path = Path(shifted_tmp.name)

    try:
        run_gbagfx(
            png_path,
            raw_path,
            "-num_tiles",
            str(CG_TILE_COUNT),
            "-Werror=num_tiles",
        )
        subprocess.run(
            [
                sys.executable,
                str(ROOT / "tools/offset_cg_8bpp.py"),
                str(png_path),
                str(raw_path),
                str(shifted_path),
            ],
            check=True,
            cwd=ROOT,
        )
        run_gbagfx(shifted_path, lz_path)
    finally:
        raw_path.unlink(missing_ok=True)
        shifted_path.unlink(missing_ok=True)

    subprocess.run(
        [sys.executable, str(ROOT / "tools/build_cg_palette.py"), str(png_path), str(pal_path)],
        check=True,
        cwd=ROOT,
    )
    return lz_path, pal_path


def discover_cg_pngs(directory: Path = CG_DIR) -> list[Path]:
    if not directory.is_dir():
        return []
    return sorted(path for path in directory.glob("*.png") if path.is_file())


def build_all(png_paths: list[Path] | None = None) -> list[tuple[Path, Path]]:
    paths = png_paths if png_paths is not None else discover_cg_pngs()
    built: list[tuple[Path, Path]] = []
    for png_path in paths:
        built.append(build_cg(png_path.resolve()))
        print(f"build_cg: ok ({png_path.name})")
    return built


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "png",
        type=Path,
        nargs="*",
        help="CG PNG paths (default: all PNGs under src_custom/assets/cgs/)",
    )
    args = parser.parse_args()

    png_paths = args.png if args.png else discover_cg_pngs()
    if not png_paths:
        raise SystemExit(f"no CG PNGs found under {CG_DIR}")

    build_all(png_paths)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
