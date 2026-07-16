#!/usr/bin/env python3
"""Build status-menu millennium item tiles from indexed PNG sources."""

from __future__ import annotations

import argparse
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASSET_DIR = ROOT / "src_custom" / "assets" / "millenium_items"
GENERATED_INC = ROOT / "src_custom" / "generated" / "millennium_item_assets_generated.inc"
GBAGFX = ROOT / "tools" / "gbagfx" / "gbagfx"
BYTES_PER_LINE = 12
ICON_SIZE = 32
ICON_TILE_BYTES = 512
PANEL_TILE_BYTES = 32
# Matches baserom status palette bank 15 color 2 (panel fill).
PANEL_FILL_COLOR = 0x00D6
SILHOUETTE_BLACK = 0x0000  # RGB555 black (palette index 0 stays transparent)

ITEMS: tuple[str, ...] = (
    "puzzle",
    "ring",
    "key",
    "scale",
    "rod",
    "eye",
    "necklace",
)


def format_byte_lines(data: bytes, indent: str = "    ") -> list[str]:
    lines: list[str] = []
    chunk: list[str] = []
    for byte in data:
        chunk.append(f"0x{byte:02X}")
        if len(chunk) == BYTES_PER_LINE:
            lines.append(f"{indent}{', '.join(chunk)},")
            chunk = []
    if chunk:
        lines.append(f"{indent}{', '.join(chunk)},")
    return lines


def format_palette_lines(data: bytes, indent: str = "    ") -> list[str]:
    words = [struct.unpack_from("<H", data, offset)[0] for offset in range(0, len(data), 2)]
    lines: list[str] = []
    chunk: list[str] = []
    for word in words:
        chunk.append(f"0x{word:04X}")
        if len(chunk) == BYTES_PER_LINE:
            lines.append(f"{indent}{', '.join(chunk)},")
            chunk = []
    if chunk:
        lines.append(f"{indent}{', '.join(chunk)},")
    return lines


def run_gbagfx(src: Path, dst: Path, *extra: str) -> None:
    cmd = [str(GBAGFX), str(src), str(dst), *extra]
    subprocess.run(cmd, check=True, cwd=ROOT)


def symbol_for(stem: str, suffix: str) -> str:
    parts = stem.split("_")
    camel = "".join(part[:1].upper() + part[1:] for part in parts)
    return f"sMillenniumItem{camel}{suffix}"


def build_item_tiles(png_path: Path) -> bytes:
    with tempfile.TemporaryDirectory(prefix="millennium_item_") as tmp_dir:
        tmp = Path(tmp_dir)
        tile_path = tmp / f"{png_path.stem}.4bpp"
        run_gbagfx(png_path, tile_path)
        data = tile_path.read_bytes()
    if len(data) != ICON_TILE_BYTES:
        raise SystemExit(
            f"{png_path.name}: expected {ICON_TILE_BYTES} bytes of 4bpp tiles, got {len(data)}"
        )
    return data


def build_palette(png_path: Path) -> bytes:
    with tempfile.TemporaryDirectory(prefix="millennium_item_pal_") as tmp_dir:
        tmp = Path(tmp_dir)
        pal_path = tmp / f"{png_path.stem}.gbapal"
        run_gbagfx(png_path, pal_path)
        data = pal_path.read_bytes()
    if len(data) < 32:
        raise SystemExit(f"{png_path.name}: expected at least 32-byte palette, got {len(data)}")
    return data[:32]


def build_silhouette_tiles(png_path: Path) -> bytes:
    try:
        from PIL import Image
    except ImportError as exc:  # pragma: no cover
        raise SystemExit("generate_millennium_item_assets.py requires Pillow") from exc

    with tempfile.TemporaryDirectory(prefix="millennium_sil_") as tmp_dir:
        tmp = Path(tmp_dir)
        sil_png = tmp / f"{png_path.stem}_sil.png"
        tile_path = tmp / f"{png_path.stem}_sil.4bpp"

        with Image.open(png_path) as image:
            if image.size != (ICON_SIZE, ICON_SIZE):
                raise SystemExit(
                    f"{png_path.name}: expected {ICON_SIZE}x{ICON_SIZE}px, got {image.size[0]}x{image.size[1]}px"
                )
            sil = Image.new("P", image.size)
            sil.putpalette([0, 0, 0, 0, 0, 0] + [0] * (256 * 3 - 6))
            src = image.convert("P")
            pixels = src.load()
            out = sil.load()
            for y in range(ICON_SIZE):
                for x in range(ICON_SIZE):
                    out[x, y] = 1 if pixels[x, y] != 0 else 0
            sil.save(sil_png)

        run_gbagfx(sil_png, tile_path)
        data = tile_path.read_bytes()
    if len(data) != ICON_TILE_BYTES:
        raise SystemExit(
            f"{png_path.name}: expected {ICON_TILE_BYTES} bytes of silhouette tiles, got {len(data)}"
        )
    return data


def build_panel_tile() -> bytes:
    try:
        from PIL import Image
    except ImportError as exc:  # pragma: no cover
        raise SystemExit("generate_millennium_item_assets.py requires Pillow") from exc

    with tempfile.TemporaryDirectory(prefix="millennium_panel_") as tmp_dir:
        tmp = Path(tmp_dir)
        panel_png = tmp / "panel.png"
        tile_path = tmp / "panel.4bpp"

        panel = Image.new("P", (8, 8))
        panel.putpalette([0, 0, 0, 0, 0, 0] + [0] * (256 * 3 - 6))
        pixels = panel.load()
        for y in range(8):
            for x in range(8):
                pixels[x, y] = 1
        panel.save(panel_png)
        run_gbagfx(panel_png, tile_path)
        data = tile_path.read_bytes()
    if len(data) != PANEL_TILE_BYTES:
        raise SystemExit(f"panel tile: expected {PANEL_TILE_BYTES} bytes, got {len(data)}")
    return data


def build_panel_palette() -> bytes:
    words = [0x0000] + [PANEL_FILL_COLOR] + [0x0000] * 14
    return struct.pack("<16H", *words)


def build_silhouette_palette() -> bytes:
    words = [0x0000, SILHOUETTE_BLACK] + [0x0000] * 14
    return struct.pack("<16H", *words)


def validate_png(png_path: Path) -> None:
    try:
        from PIL import Image
    except ImportError as exc:  # pragma: no cover
        raise SystemExit("generate_millennium_item_assets.py requires Pillow") from exc

    with Image.open(png_path) as image:
        if image.size != (ICON_SIZE, ICON_SIZE):
            raise SystemExit(
                f"{png_path.name}: expected {ICON_SIZE}x{ICON_SIZE}px, got {image.size[0]}x{image.size[1]}px"
            )
        if image.mode != "P":
            raise SystemExit(f"{png_path.name}: expected indexed PNG (mode P), got {image.mode}")


def generate() -> str:
    if not GBAGFX.is_file():
        raise SystemExit(f"missing gbagfx tool: {GBAGFX}")

    lines = [
        "/* Generated by tools/generate_millennium_item_assets.py. Do not edit. */",
        "",
        f"#define STATUS_MILLENNIUM_ITEM_COUNT {len(ITEMS)}",
        f"#define STATUS_MILLENNIUM_ITEM_TILE_BYTES {ICON_TILE_BYTES}",
        f"#define STATUS_MILLENNIUM_PANEL_TILE_BYTES {PANEL_TILE_BYTES}",
        "",
    ]

    palette_data: bytes | None = None
    tile_symbols: list[str] = []
    silhouette_symbols: list[str] = []

    for stem in ITEMS:
        png_path = ASSET_DIR / f"{stem}.png"
        if not png_path.is_file():
            raise SystemExit(f"missing millennium item PNG: {png_path}")
        validate_png(png_path)
        tile_data = build_item_tiles(png_path)
        sil_data = build_silhouette_tiles(png_path)
        pal_data = build_palette(png_path)
        if palette_data is None:
            palette_data = pal_data
        elif pal_data != palette_data:
            raise SystemExit(f"{png_path.name}: palette must match {ITEMS[0]}.png")

        tile_symbol = symbol_for(stem, "Tiles")
        sil_symbol = symbol_for(stem, "SilhouetteTiles")
        tile_symbols.append(tile_symbol)
        silhouette_symbols.append(sil_symbol)
        lines.append(f"static const u8 {tile_symbol}[] APPEND_ASSET = {{")
        lines.extend(format_byte_lines(tile_data))
        lines.append("};")
        lines.append("")
        lines.append(f"static const u8 {sil_symbol}[] APPEND_ASSET = {{")
        lines.extend(format_byte_lines(sil_data))
        lines.append("};")
        lines.append("")

    if palette_data is None:
        raise SystemExit(f"no millennium item PNGs found in {ASSET_DIR}")

    panel_tile = build_panel_tile()
    panel_palette = build_panel_palette()
    silhouette_palette = build_silhouette_palette()

    lines.append("static const u8 sMillenniumTrackerPanelTile[] APPEND_ASSET = {")
    lines.extend(format_byte_lines(panel_tile))
    lines.append("};")
    lines.append("")

    lines.append("static const u16 sMillenniumItemPalette[] APPEND_ASSET = {")
    lines.extend(format_palette_lines(palette_data))
    lines.append("};")
    lines.append("")

    lines.append("static const u16 sMillenniumTrackerPanelPalette[] APPEND_ASSET = {")
    lines.extend(format_palette_lines(panel_palette))
    lines.append("};")
    lines.append("")

    lines.append("static const u16 sMillenniumSilhouettePalette[] APPEND_ASSET = {")
    lines.extend(format_palette_lines(silhouette_palette))
    lines.append("};")
    lines.append("")

    lines.append(
        "static const u8 *const sMillenniumItemTileSets[STATUS_MILLENNIUM_ITEM_COUNT] APPEND_RODATA = {"
    )
    for symbol in tile_symbols:
        lines.append(f"    {symbol},")
    lines.append("};")
    lines.append("")

    lines.append(
        "static const u8 *const sMillenniumItemSilhouetteTileSets[STATUS_MILLENNIUM_ITEM_COUNT] APPEND_RODATA = {"
    )
    for symbol in silhouette_symbols:
        lines.append(f"    {symbol},")
    lines.append("};")
    lines.append("")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--out",
        type=Path,
        default=GENERATED_INC,
        help=f"output include path (default: {GENERATED_INC.relative_to(ROOT)})",
    )
    args = parser.parse_args()
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(generate(), encoding="utf-8")
    print(f"wrote {args.out.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
