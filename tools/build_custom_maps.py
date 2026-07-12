#!/usr/bin/env python3
"""Build-time generator for custom map backgrounds.

Reads tools/custom_map_manifest.json, validates assets in each manifest
folder, converts PNG tilesheets to LZ77-compressed 4bpp tilesets, CSV
tilemaps to u16 arrays, JSON collision data to binary, and generates
dispatch/connection tables into src_custom/generated/maps/.
"""

from __future__ import annotations

import json
import struct
import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    Image = None  # type: ignore[assignment]

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_PATH = ROOT / "tools" / "custom_map_manifest.json"
OUT_DIR = ROOT / "src_custom" / "generated" / "maps"
ASSETS_DIR = ROOT / "src_custom" / "assets" / "maps"

TILE_W = 8
TILE_H = 8
TILEMAP_W = 32
TILEMAP_H = 32
COLLISION_W = 120
COLLISION_H = 80
MAX_UNIQUE_TILES = 512
PALETTE_COUNT = 240  # 15 palettes x 16 colors


# ---------------------------------------------------------------------------
# LZ77 compression
# ---------------------------------------------------------------------------

def lz77_compress(data: bytes) -> bytes:
    """Compress data with GBA LZ77 (LZ77UnCompWram compatible).

    ponytail: naive greedy compressor, not optimal. Works for tilesets.
    Upgrade path: replace with a proper optimal LZ77 encoder if ROM space
    is tight.
    """
    uncomp_size = len(data)
    header = bytes([0x10,
                    uncomp_size & 0xFF,
                    (uncomp_size >> 8) & 0xFF,
                    (uncomp_size >> 16) & 0xFF])
    result = bytearray(header)
    pos = 0
    while pos < uncomp_size:
        # Build one block (max 8 flags)
        flags_byte = 0
        block_start = len(result)
        result.append(0)  # placeholder for flags
        literal_run = bytearray()

        def flush_literals():
            nonlocal literal_run
            if literal_run:
                result.extend(literal_run)
                literal_run = bytearray()

        for bit in range(7, -1, -1):
            if pos >= uncomp_size:
                break
            # Try to find a match: look back up to 4096 bytes
            best_len = 0
            best_disp = 0
            max_len = min(18, uncomp_size - pos)
            search_start = max(0, pos - 4096)
            if max_len >= 3:
                for disp in range(1, min(pos - search_start, 4096) + 1):
                    match_len = 0
                    while (match_len < max_len
                           and data[pos - disp + match_len] == data[pos + match_len]):
                        match_len += 1
                    if match_len > best_len:
                        best_len = match_len
                        best_disp = disp
                        if best_len == max_len:
                            break
            if best_len >= 3:
                flush_literals()
                flags_byte |= (1 << bit)
                count_minus_3 = best_len - 3
                disp_minus_1 = best_disp - 1
                result.append((count_minus_3 << 4) | ((disp_minus_1 >> 8) & 0xF))
                result.append(disp_minus_1 & 0xFF)
                pos += best_len
            else:
                literal_run.append(data[pos])
                pos += 1

        flush_literals()
        if block_start + 1 < len(result):
            result[block_start] = flags_byte
        else:
            # No data in this block (shouldn't happen)
            result[block_start] = 0

    return bytes(result)


# ---------------------------------------------------------------------------
# 4bpp tile encoding / decoding helpers
# ---------------------------------------------------------------------------

def split_tilesheet(png: Image.Image) -> list[list[list[int]]]:
    """Split a PNG into 8x8 tiles. Returns list of tiles, each as 8x8 pixel matrix."""
    w, h = png.size
    tiles_x = w // TILE_W
    tiles_y = h // TILE_H
    tiles = []
    pix = png.load()
    for ty in range(tiles_y):
        for tx in range(tiles_x):
            tile = []
            for py in range(TILE_H):
                row = []
                for px in range(TILE_W):
                    row.append(pix[tx * TILE_W + px, ty * TILE_H + py])
                tile.append(row)
            tiles.append(tile)
    return tiles


def tile_to_bytes(tile: list[list[int]]) -> bytes:
    """Convert an 8x8 pixel matrix to 32 bytes of 4bpp tile data."""
    buf = bytearray(32)
    for row in range(TILE_H):
        for col in range(TILE_W):
            pix = tile[row][col] & 0xF
            byte_idx = row * 4 + col // 2
            nibble_shift = (col % 2) * 4
            buf[byte_idx] |= pix << nibble_shift
    return bytes(buf)


def tiles_to_tileset(tiles: list[bytes], dedup: bool = True) -> tuple[bytes, list[int]]:
    """Convert tile byte blobs to tileset bytes + remap table.

    If dedup=True, deduplicates identical tiles. Returns (tileset_bytes, remap)
    where remap[n] = deduped_index for original tile n.
    """
    if not dedup:
        return b''.join(tiles), list(range(len(tiles)))

    seen: dict[bytes, int] = {}
    unique = bytearray()
    remap = []
    for tile_bytes in tiles:
        idx = seen.get(tile_bytes)
        if idx is None:
            idx = len(seen)
            seen[tile_bytes] = idx
            unique.extend(tile_bytes)
        remap.append(idx)

    if len(seen) > MAX_UNIQUE_TILES:
        raise ValueError(
            f"Tile budget exceeded: {len(seen)} unique tiles, max is {MAX_UNIQUE_TILES}"
        )

    return bytes(unique), remap


# ---------------------------------------------------------------------------
# Palette extraction
# ---------------------------------------------------------------------------

def extract_palette(png: Image.Image) -> list[tuple[int, int, int]]:
    """Extract up to 240 RGB colors from an indexed PNG palette.

    The PNG palette is organized as 15 banks of 16 colors. Color 0 should
    always be transparent/background and is typically black or the
    tilesheet background color.
    """
    if png.mode != "P":
        raise ValueError("tiles.png must be an indexed (palette) PNG")

    pal = png.getpalette()
    if pal is None:
        raise ValueError("tiles.png has no palette")

    # PIL returns flat list [R,G,B,R,G,B,...]
    colors = []
    num_colors = min(len(pal) // 3, PALETTE_COUNT)
    for i in range(num_colors):
        r, g, b = pal[i * 3], pal[i * 3 + 1], pal[i * 3 + 2]
        colors.append((r, g, b))
    # Pad to PALETTE_COUNT with black
    while len(colors) < PALETTE_COUNT:
        colors.append((0, 0, 0))
    return colors


def rgb_to_gba(color: tuple[int, int, int]) -> int:
    """Convert RGB888 to GBA RGB555 u16."""
    r, g, b = color
    return (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)


# ---------------------------------------------------------------------------
# CSV tilemap parsing
# ---------------------------------------------------------------------------

def parse_tilemap_csv(path: Path) -> list[list[int]]:
    """Read a 32x32 CSV tilemap. Returns list of rows, each row a list of tile indices."""
    rows = []
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            row_vals = []
            for cell in line.split(","):
                cell = cell.strip()
                if cell:
                    row_vals.append(int(cell, 0))  # auto-detect hex/decimal
            if row_vals:
                rows.append(row_vals)
    if len(rows) != TILEMAP_H:
        raise ValueError(f"{path}: expected {TILEMAP_H} rows, got {len(rows)}")
    for i, row in enumerate(rows):
        if len(row) != TILEMAP_W:
            raise ValueError(f"{path} row {i}: expected {TILEMAP_W} cols, got {len(row)}")
    return rows


# ---------------------------------------------------------------------------
# Collision JSON parsing
# ---------------------------------------------------------------------------

def parse_collision_json(path: Path) -> list[list[int]]:
    """Read a 120x80 collision grid from JSON. Returns list of rows."""
    data = json.loads(path.read_text())
    if isinstance(data, list):
        rows = data
    else:
        raise ValueError(f"{path}: expected a 2D array")

    if len(rows) != COLLISION_H:
        raise ValueError(f"{path}: expected {COLLISION_H} rows, got {len(rows)}")
    for i, row in enumerate(rows):
        if len(row) != COLLISION_W:
            raise ValueError(f"{path} row {i}: expected {COLLISION_W} cols, got {len(row)}")
    return rows


# ---------------------------------------------------------------------------
# .inc file generation helpers
# ---------------------------------------------------------------------------

def gen_inc_header(name: str) -> str:
    return f"// Auto-generated by tools/build_custom_maps.py for map '{name}'.\n// Do not edit.\n\n"


def gen_tileset_inc(name: str, compressed: bytes) -> str:
    """Generate .inc with LZ77-compressed tileset as const u8 array."""
    header = gen_inc_header(name)
    body = f"static const u8 sCustomTileset_{name}[] APPEND_ASSET = {{"
    for i in range(0, len(compressed), 16):
        chunk = compressed[i:i + 16]
        body += "\n   "
        for b in chunk:
            body += f" {b:#04x},"
    body += "\n};\n"
    return header + body


def gen_tilemap_inc(name: str, layer: str, tilemap: list[list[int]],
                    remap: list[int] | None = None) -> str:
    """Generate .inc for a tilemap as const u16 array.

    If remap is provided, tile indices are remapped through it.
    """
    header = gen_inc_header(name)
    body = f"static const u16 sCustom{layer.capitalize()}Tilemap_{name}[]{APPEND_RODATA} = {{"
    for row in tilemap:
        body += "\n  "
        for val in row:
            tile_idx = val & 0x3FF
            attrs = val & ~0x3FF
            if remap:
                tile_idx = remap[tile_idx]
            mapped = (tile_idx & 0x3FF) | attrs
            body += f" {mapped:#06x},"
        body += ""
    body += "\n};\n"
    return header + body


def gen_palette_inc(name: str, colors: list[tuple[int, int, int]]) -> str:
    """Generate .inc for palette as const u16 array (240 RGB555 entries)."""
    header = gen_inc_header(name)
    body = f"static const u16 sCustomPalette_{name}[]{APPEND_ASSET} = {{"
    for i, color in enumerate(colors):
        if i % 16 == 0:
            body += f"\n  /* bank {i // 16} */"
        body += f" {rgb_to_gba(color):#06x},"
    body += "\n};\n"
    return header + body


def gen_collision_inc(name: str, grid: list[list[int]]) -> str:
    """Generate .inc for collision grid as const u16 array."""
    header = gen_inc_header(name)
    body = f"static const u16 sCustomCollision_{name}[]{APPEND_RODATA} = {{"
    for row in grid:
        body += "\n  "
        for val in row:
            body += f" {val:#06x},"
    body += "\n};\n"
    return header + body


def gen_dispatch_inc(entries: list[dict]) -> tuple[str, str, str]:
    """Generate dispatch .inc: tileset/tilemap/palette/collision pointer arrays.

    Returns (pointer_tables_inc, connections_inc, mapdata_inc).
    """
    map_count = len(entries)
    names = [e["name"] for e in entries]

    # Pointer tables
    ptr_lines = [
        f"// {map_count} custom maps\n",
        f"#define CUSTOM_MAP_COUNT {map_count}\n",
        "\n// Tileset pointers\n",
        f"static const u8 *const sCustomTilesets[CUSTOM_MAP_COUNT] APPEND_RODATA = {{",
    ]
    for n in names:
        ptr_lines.append(f"  sCustomTileset_{n},")
    ptr_lines.append("};\n")

    ptr_lines.append("\n// Ground tilemap pointers\n")
    ptr_lines.append(f"static const u16 *const sCustomGroundTilemaps[CUSTOM_MAP_COUNT] APPEND_RODATA = {{")
    for n in names:
        ptr_lines.append(f"  sCustomGroundTilemap_{n},")
    ptr_lines.append("};\n")

    ptr_lines.append("\n// Roof tilemap pointers (NULL = no roof layer)\n")
    ptr_lines.append(f"static const u16 *const sCustomRoofTilemaps[CUSTOM_MAP_COUNT] APPEND_RODATA = {{")
    for n in names:
        has_roof = any(
            (ROOT / e.get("manifest_folder", "") / "roof.csv").exists()
            for e in entries if e["name"] == n
        )
        if has_roof:
            ptr_lines.append(f"  sCustomRoofTilemap_{n},")
        else:
            ptr_lines.append("  NULL,")
    ptr_lines.append("};\n")

    ptr_lines.append("\n// Palette pointers\n")
    ptr_lines.append(f"static const u16 *const sCustomPalettes[CUSTOM_MAP_COUNT] APPEND_RODATA = {{")
    for n in names:
        ptr_lines.append(f"  sCustomPalette_{n},")
    ptr_lines.append("};\n")

    ptr_lines.append("\n// Collision pointers\n")
    ptr_lines.append(f"static const u16 *const sCustomCollisions[CUSTOM_MAP_COUNT] APPEND_RODATA = {{")
    for n in names:
        ptr_lines.append(f"  sCustomCollision_{n},")
    ptr_lines.append("};\n")

    # Music table
    ptr_lines.append("\n// Music IDs per custom map\n")
    ptr_lines.append(f"static const u16 sCustomMapMusic[CUSTOM_MAP_COUNT] APPEND_RODATA = {{")
    for e in entries:
        ptr_lines.append(f"  {e.get('music', 1)},")
    ptr_lines.append("};\n")

    ptr_tables = "\n".join(ptr_lines)

    # Connections
    conn_lines = [
        f"// Vanilla → custom map transition patches\n",
        f"#if CUSTOM_MAP_COUNT > 0\n",
        f"static const struct {{ u16 vanillaLocation; u16 edge; u8 triggerX; u8 triggerYMin; u8 triggerYMax; u16 customMapId; }} sCustomMapConnections[] APPEND_RODATA = {{",
    ]
    conn_count = 0
    for e in entries:
        conns = e.get("connections", {}).get("from_vanilla", [])
        for c in conns:
            conn_lines.append(
                f"  {{ {c['vanilla_location']}, {c['edge']}, {c['trigger_x']}, "
                f"{c['trigger_y_range'][0]}, {c['trigger_y_range'][1]}, "
                f"CUSTOM_MAP_BASE + {entries.index(e)} }},"
            )
            conn_count += 1
    conn_lines.append("};\n")
    conn_lines.append(f"#define CUSTOM_MAP_CONNECTION_COUNT {conn_count}")
    conn_lines.append("#endif\n")
    connections_inc = "\n".join(conn_lines)

    # MapData entries (per-map: dummy with no NPCs, player starts from connections)
    md_lines = [
        f"// Custom map dummy MapData entries\n",
        f"#if CUSTOM_MAP_COUNT > 0\n",
    ]
    for e in entries:
        n = e["name"]
        md_lines.append(
            f"static const struct MapData sCustomMapData_{n} = {{\n"
            f"  .objects = {{ {{ .spriteId = -1 }} }},  /* no NPCs — use event scripts */\n"
            f"  .music = {e.get('music', 1)},\n"
            f"}};\n"
        )
    md_lines.append(
        f"\nstatic const struct MapData *const sCustomMapData[CUSTOM_MAP_COUNT] APPEND_RODATA = {{"
    )
    for e in entries:
        md_lines.append(f"  &sCustomMapData_{e['name']},")
    md_lines.append("};\n#endif\n")
    mapdata_inc = "\n".join(md_lines)

    return ptr_tables, connections_inc, mapdata_inc


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> int:
    if Image is None:
        print("error: Pillow (PIL) is required — pip install Pillow")
        return 1

    if not MANIFEST_PATH.exists():
        print(f"error: {MANIFEST_PATH} not found")
        return 1

    manifest = json.loads(MANIFEST_PATH.read_text())
    if not isinstance(manifest, list):
        print("error: manifest must be a JSON array")
        return 1

    if not manifest:
        # Empty manifest — generate empty dispatch tables
        OUT_DIR.mkdir(parents=True, exist_ok=True)
        empty_src = gen_empty_dispatch()
        (OUT_DIR / "custom_map_dispatch.inc").write_text(empty_src)
        (OUT_DIR / "custom_map_connections.inc").write_text(
            "// No custom maps defined.\n"
            "#define CUSTOM_MAP_COUNT 0\n"
            "#define CUSTOM_MAP_CONNECTION_COUNT 0\n"
        )
        print("No custom maps in manifest — generated empty dispatch tables.")
        return 0

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    processed = []

    for entry in manifest:
        name = entry.get("name", "unnamed")
        folder_str = entry.get("manifest_folder", f"src_custom/assets/maps/{name}/")
        folder = ROOT / folder_str
        if not folder.exists():
            print(f"warning: folder {folder} does not exist — skipping '{name}'")
            continue

        assets_dir = ROOT / "src_custom" / "assets" / "maps"
        is_vanilla_extract = (folder.resolve().parent == assets_dir.resolve()
                              and folder.name.startswith("map_"))

        tiles_png = folder / "tiles.png"
        ground_csv = folder / "ground.csv"
        roof_csv = folder / "roof.csv"
        collision_json = folder / "collision.json"

        if not tiles_png.exists():
            # For vanilla extracts, skip
            if is_vanilla_extract:
                continue
            print(f"warning: {tiles_png} not found — skipping '{name}'")
            continue

        print(f"Building map '{name}'...")

        # Read tilesheet
        png = Image.open(tiles_png)
        if png.mode != "P":
            print(f"error: {tiles_png} must be indexed (palette) PNG")
            return 1

        # Extract palette
        palette = extract_palette(png)

        # Split tiles and deduplicate
        tiles = split_tilesheet(png)
        tile_bytes = [tile_to_bytes(t) for t in tiles]
        tileset_data, remap = tiles_to_tileset(tile_bytes)
        print(f"  Tiles: {len(tiles)} original -> {len(set(tile_bytes))} unique (max {MAX_UNIQUE_TILES})")

        # Check tile budget
        if len(set(tile_bytes)) > MAX_UNIQUE_TILES:
            print(f"error: {name} has {len(set(tile_bytes))} unique tiles, exceeds max {MAX_UNIQUE_TILES}")
            return 1

        # Parse ground tilemap
        ground = parse_tilemap_csv(ground_csv)

        # Parse roof tilemap (optional)
        roof: list[list[int]] | None = None
        if roof_csv.exists():
            roof = parse_tilemap_csv(roof_csv)

        # Parse collision
        collision: list[list[int]] = []
        if collision_json.exists():
            collision = parse_collision_json(collision_json)
        else:
            # Default: all passable
            collision = [[0] * COLLISION_W for _ in range(COLLISION_H)]

        # LZ77 compress tileset
        compressed = lz77_compress(tileset_data)
        print(f"  Tileset: {len(tileset_data)} -> {len(compressed)} compressed")

        # Write per-map .inc files
        (OUT_DIR / f"tileset_{name}.inc").write_text(gen_tileset_inc(name, compressed))
        (OUT_DIR / f"ground_tilemap_{name}.inc").write_text(
            gen_tilemap_inc(name, "ground", ground, remap))
        if roof is not None:
            (OUT_DIR / f"roof_tilemap_{name}.inc").write_text(
                gen_tilemap_inc(name, "roof", roof, remap))
        (OUT_DIR / f"palette_{name}.inc").write_text(gen_palette_inc(name, palette))
        (OUT_DIR / f"collision_{name}.inc").write_text(gen_collision_inc(name, collision))

        processed.append(entry)

    # Generate dispatch tables
    ptr_inc, conn_inc, md_inc = gen_dispatch_inc(processed)
    combined = ptr_inc + "\n" + conn_inc + "\n" + md_inc
    (OUT_DIR / "custom_map_dispatch.inc").write_text(combined)
    (OUT_DIR / "custom_map_connections.inc").write_text(conn_inc)

    print(f"\nDone — {len(processed)} maps built. Output in {OUT_DIR}")
    return 0


def gen_empty_dispatch() -> str:
    return (
        "// No custom maps defined.\n"
        "#define CUSTOM_MAP_COUNT 0\n"
        "#define CUSTOM_MAP_CONNECTION_COUNT 0\n"
    )


if __name__ == "__main__":
    sys.exit(main())
