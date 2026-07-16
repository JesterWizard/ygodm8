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
# Gap between opaque content of adjacent icons (not between 32x32 containers).
CONTENT_GAP_PX = 8
# Status blend window horizontal span (matches StatusMenuApplyMillenniumWindows).
LAYOUT_LEFT_PX = 8
LAYOUT_RIGHT_PX = 240
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


def content_bbox(image) -> tuple[int, int, int, int]:
    """Inclusive (left, top, right, bottom) of non-zero palette indices."""
    pixels = image.load()
    left, top, right, bottom = ICON_SIZE, ICON_SIZE, -1, -1
    for y in range(ICON_SIZE):
        for x in range(ICON_SIZE):
            if pixels[x, y] != 0:
                if x < left:
                    left = x
                if y < top:
                    top = y
                if x > right:
                    right = x
                if y > bottom:
                    bottom = y
    if right < 0:
        raise SystemExit("empty millennium item icon (no opaque pixels)")
    return left, top, right, bottom


def remaster_icon(image, new_left: int, top: int):
    """Copy opaque pixels into a fresh 32x32 so content left/top match targets."""
    src = image.convert("P")
    out = Image.new("P", (ICON_SIZE, ICON_SIZE))
    out.putpalette(src.getpalette())
    sp = src.load()
    op = out.load()
    left, old_top, right, bottom = content_bbox(src)
    dx = new_left - left
    dy = top - old_top
    for y in range(old_top, bottom + 1):
        for x in range(left, right + 1):
            if sp[x, y] == 0:
                continue
            nx, ny = x + dx, y + dy
            if not (0 <= nx < ICON_SIZE and 0 <= ny < ICON_SIZE):
                raise SystemExit(
                    f"remaster out of bounds: ({nx},{ny}) from shift dx={dx} dy={dy}"
                )
            op[nx, ny] = sp[x, y]
    return out


# Deferred import so --help works without Pillow on path issues
Image = None  # type: ignore


def ensure_pil():
    global Image
    if Image is not None:
        return
    try:
        from PIL import Image as PilImage
    except ImportError as exc:  # pragma: no cover
        raise SystemExit("generate_millennium_item_assets.py requires Pillow") from exc
    Image = PilImage


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


def build_silhouette_tiles_from_image(image, stem: str) -> bytes:
    ensure_pil()
    with tempfile.TemporaryDirectory(prefix="millennium_sil_") as tmp_dir:
        tmp = Path(tmp_dir)
        sil_png = tmp / f"{stem}_sil.png"
        tile_path = tmp / f"{stem}_sil.4bpp"

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
            f"{stem}: expected {ICON_TILE_BYTES} bytes of silhouette tiles, got {len(data)}"
        )
    return data


def build_panel_tile() -> bytes:
    ensure_pil()
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
    ensure_pil()
    with Image.open(png_path) as image:
        if image.size != (ICON_SIZE, ICON_SIZE):
            raise SystemExit(
                f"{png_path.name}: expected {ICON_SIZE}x{ICON_SIZE}px, got {image.size[0]}x{image.size[1]}px"
            )
        if image.mode != "P":
            raise SystemExit(f"{png_path.name}: expected indexed PNG (mode P), got {image.mode}")


def compute_layout(bboxes: list[tuple[int, int, int, int]]) -> tuple[list[int], list[int]]:
    """Return (map_cols, content_left_in_tile) for each icon.

    Packs icons so opaque content is CONTENT_GAP_PX apart, centered in the
    status blend window. Remasters each 32x32 so content_left = cursor % 8,
    then places the tile block at cursor // 8.
    """
    widths = [right - left + 1 for left, _t, right, _b in bboxes]
    span = sum(widths) + CONTENT_GAP_PX * (len(widths) - 1)
    usable = LAYOUT_RIGHT_PX - LAYOUT_LEFT_PX
    if span > usable:
        raise SystemExit(f"millennium icons need {span}px but window only has {usable}px")
    cursor = LAYOUT_LEFT_PX + (usable - span) // 2

    map_cols: list[int] = []
    lefts_in_tile: list[int] = []
    for i, width in enumerate(widths):
        _l, top, _r, bottom = bboxes[i]
        height = bottom - top + 1
        left_in_tile = cursor % 8
        if left_in_tile + width > ICON_SIZE:
            raise SystemExit(
                f"{ITEMS[i]}: content width {width} does not fit at offset {left_in_tile}"
            )
        if top + height > ICON_SIZE:
            raise SystemExit(f"{ITEMS[i]}: content height {height} overflows vertically")
        map_cols.append(cursor // 8)
        lefts_in_tile.append(left_in_tile)
        cursor += width + CONTENT_GAP_PX
    return map_cols, lefts_in_tile


def generate() -> str:
    ensure_pil()
    if not GBAGFX.is_file():
        raise SystemExit(f"missing gbagfx tool: {GBAGFX}")

    lines = [
        "/* Generated by tools/generate_millennium_item_assets.py. Do not edit. */",
        "",
        f"#define STATUS_MILLENNIUM_ITEM_COUNT {len(ITEMS)}",
        f"#define STATUS_MILLENNIUM_ITEM_TILE_BYTES {ICON_TILE_BYTES}",
        f"#define STATUS_MILLENNIUM_PANEL_TILE_BYTES {PANEL_TILE_BYTES}",
        f"#define STATUS_MILLENNIUM_CONTENT_GAP_PX {CONTENT_GAP_PX}",
        "",
    ]

    palette_data: bytes | None = None
    tile_symbols: list[str] = []
    silhouette_symbols: list[str] = []
    bboxes: list[tuple[int, int, int, int]] = []
    source_images = []

    for stem in ITEMS:
        png_path = ASSET_DIR / f"{stem}.png"
        if not png_path.is_file():
            raise SystemExit(f"missing millennium item PNG: {png_path}")
        validate_png(png_path)
        image = Image.open(png_path).convert("P")
        source_images.append(image)
        bboxes.append(content_bbox(image))
        pal_data = build_palette(png_path)
        if palette_data is None:
            palette_data = pal_data
        elif pal_data != palette_data:
            raise SystemExit(f"{png_path.name}: palette must match {ITEMS[0]}.png")

    map_cols, lefts_in_tile = compute_layout(bboxes)

    with tempfile.TemporaryDirectory(prefix="millennium_layout_") as tmp_dir:
        tmp = Path(tmp_dir)
        for i, stem in enumerate(ITEMS):
            _l, top, _r, _b = bboxes[i]
            remastered = remaster_icon(source_images[i], lefts_in_tile[i], top)
            remaster_path = tmp / f"{stem}.png"
            remastered.save(remaster_path)

            tile_data = build_item_tiles(remaster_path)
            sil_data = build_silhouette_tiles_from_image(remastered, stem)

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
        "/* BG2 map column for each 4x4 icon block (content packed with "
        f"{CONTENT_GAP_PX}px gaps). */"
    )
    lines.append(
        "static const u8 sMillenniumItemMapCols[STATUS_MILLENNIUM_ITEM_COUNT] APPEND_RODATA = {"
    )
    lines.append("    " + ", ".join(str(c) for c in map_cols) + ",")
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
