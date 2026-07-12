#!/usr/bin/env python3
"""Build-time generator for custom map backgrounds.

Reads tools/custom_map_manifest.json, validates assets in each manifest
folder, converts PNG tilesheets to LZ77-compressed 4bpp tilesets, CSV
tilemaps to u16 arrays, JSON collision data to binary, and generates
dispatch/connection tables into src_custom/generated/maps/.
"""

from __future__ import annotations

import json
import re
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
ROM_PATH = ROOT / "baserom.gba"
ROM_BASE = 0x08000000

TILE_W = 8
TILE_H = 8
TILEMAP_W = 32
TILEMAP_H = 32
COLLISION_W = 120
COLLISION_H = 80
MAX_UNIQUE_TILES = 512
PALETTE_COUNT = 240  # 15 palettes x 16 colors

# Direction constant names → numeric values (matching overworld.h enum)
DIRECTION_VALUES = {"DIRECTION_DOWN": 0, "DIRECTION_LEFT": 1,
                    "DIRECTION_UP": 2, "DIRECTION_RIGHT": 3}

# Music constant name → value lookup
_MUSIC_VALUES: dict[str, int] = {}
_music_header = (ROOT / "include" / "constants" / "music_ids.h").read_text()
for m in re.finditer(r'(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', _music_header):
    _MUSIC_VALUES[m.group(1)] = int(m.group(2), 16)


def _music_value(name: str) -> int:
    """Convert a music constant name like 'MUSIC_HOME' to its integer value."""
    if name in _MUSIC_VALUES:
        return _MUSIC_VALUES[name]
    try:
        return int(name, 0)
    except ValueError:
        return 1


def _read_base_collision(mid: int) -> list[int] | None:
    """Read original collision grid from ROM by map ID.
    Returns flat list of u16 values (120*80) or None on failure."""
    try:
        rom = ROM_PATH.read_bytes()
        ptr_off = 0x08E11DC4 - ROM_BASE
        ptr = struct.unpack_from("<I", rom, ptr_off + mid * 4)[0]
        off = ptr - ROM_BASE
        return list(struct.unpack_from("<9600H", rom, off))
    except (FileNotFoundError, struct.error):
        return None


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
            f"  .music = {_music_value(e.get('music', 'MUSIC_TITLE_SCREEN'))},\n"
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

    # Always generate the manifest map sources table (for vanilla map overrides)
    generate_manifest_map_sources(manifest, OUT_DIR)
    generate_manifest_collision_overrides(manifest, OUT_DIR)
    generate_manifest_connection_overrides(manifest, OUT_DIR)
    generate_manifest_spawn_overrides(manifest, OUT_DIR)

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
        name = entry.get("name")
        if not name:
            # Skip entries without a name (e.g. vanilla map entries in manifest)
            continue
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


def generate_manifest_collision_overrides(manifest: list, out_dir: Path) -> None:
    """Generate manifest_collision_overrides.inc — collision data for maps
    that specify custom collision in the manifest.

    Reads each entry's `collision.blocked` array (rects [x, y, w, h] in
    tile coordinates, 120x80 grid). Starts from ROM collision base, stamps
    blocked rects with 4096 (0x1000, wall flag). Generates static u16 arrays
    and a lookup pointer table.

    The runtime hook checks sManifestCollisionOverrides[mapId] and
    redirects gOverworld.unk23C when non-NULL.
    """
    cw = 120
    ch = 80
    blocks: list[list[int] | None] = [None] * 61

    for entry in manifest:
        mid = entry.get("id")
        if not isinstance(mid, int) or mid < 0 or mid >= 61:
            continue
        col = entry.get("collision")
        if not col:
            continue

        # blocked rects [x, y, w, h] in tile coordinates
        rects = col.get("blocked", [])
        if not rects:
            continue

        # Start from ROM's original collision to preserve void(0)/walkable(1)
        base = _read_base_collision(mid)
        if base is None:
            print(f"warning: map {mid}: cannot read ROM collision, skipping")
            continue
        grid = base[:]  # copy

        # Stamp blocked rects with 4096 (= 0x1000, wall flag)
        for rect in rects:
            if not isinstance(rect, (list, tuple)) or len(rect) < 4:
                print(f"warning: map {mid}: invalid collision rect {rect}")
                continue
            rx, ry, rw, rh = rect[:4]
            for dy in range(rh):
                for dx in range(rw):
                    cx, cy = rx + dx, ry + dy
                    if 0 <= cx < cw and 0 <= cy < ch:
                        grid[cy * cw + cx] = 4096
                    else:
                        print(f"warning: map {mid}: rect {rect} extends beyond 120x80")

        # Only generate an override if passability actually differs from ROM.
        # Value changes like 8192→4096 (both blocked) don't count.
        diff = False
        for i in range(cw * ch):
            bv = grid[i] >= 4096
            rv = base[i] >= 4096
            if bv != rv:
                diff = True
                break
        if not diff:
            continue
        blocks[mid] = grid

    lines = [
        "// Auto-generated collision overrides from tools/custom_map_manifest.json\n",
        "#ifndef COLLISION_OVERRIDE_W\n",
        f"#define COLLISION_OVERRIDE_W {cw}\n",
        f"#define COLLISION_OVERRIDE_H {ch}\n",
        "#endif\n\n",
    ]

    # Emit data arrays for maps with overrides
    any_override = False
    for mid in range(61):
        b = blocks[mid]
        if b is None:
            continue
        any_override = True
        lines.append(f"// Map {mid} custom collision\n")
        lines.append(f"static const u16 sColOverrideMap{mid}[] APPEND_RODATA = {{\n")
        for row in range(ch):
            start = row * cw
            chunk = ",".join(str(v) for v in b[start:start + cw])
            lines.append(f"  {chunk},\n")
        lines.append("};\n\n")

    # Pointer lookup table (NULL for maps without overrides)
    lines.append("// Collision override pointer table — NULL = use ROM default\n")
    lines.append("static const u16 *const sManifestCollisionOverrides[61] APPEND_RODATA = {\n")
    for mid in range(61):
        if blocks[mid] is not None:
            lines.append(f"  sColOverrideMap{mid},\n")
        else:
            lines.append("  NULL,\n")
    lines.append("};\n")

    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "manifest_collision_overrides.inc").write_text("".join(lines))
    count = sum(1 for b in blocks if b is not None)
    print(f"  collision: {count} maps with custom collision data")


def gen_empty_dispatch() -> str:
    return (
        "// No custom maps defined.\n"
        "#define CUSTOM_MAP_COUNT 0\n"
        "#define CUSTOM_MAP_CONNECTION_COUNT 0\n"
    )


def generate_manifest_map_sources(manifest: list, out_dir: Path) -> None:
    """Generate manifest_map_sources.inc — maps each vanilla map ID (0-60) to
    the source map ID whose graphics data to load at runtime.

    Reads each manifest entry's `images.ground` PNG filename.
    If the source map ID differs from the entry's own id, the entry is an
    override. Identity mappings (id == source) are the default.

    Gated by gRuntimeConfig.enable_manifest_map_overrides in the hook.
    """
    sources = list(range(61))
    for entry in manifest:
        mid = entry.get("id")
        if not isinstance(mid, int) or mid < 0 or mid >= 61:
            continue
        images = entry.get("images", {})
        ground = images.get("ground", entry.get("ground", ""))
        m = re.search(r"map_(\d+)_ground\.png", ground)
        if m:
            src = int(m.group(1))
            if src != mid and 0 <= src < 61:
                sources[mid] = src

    lines = [
        "// Auto-generated from tools/custom_map_manifest.json\n",
        "// Maps each vanilla map ID to the source map ID whose graphics\n",
        "// data to load. When source == id no override occurs.\n",
        "#ifndef MANIFEST_MAP_SOURCE_COUNT\n",
        "#define MANIFEST_MAP_SOURCE_COUNT 61\n",
        "#endif\n\n",
        "static const u16 sManifestMapSources[MANIFEST_MAP_SOURCE_COUNT] APPEND_RODATA = {\n",
    ]
    for i in range(61):
        comma = "," if i < 60 else ""
        lines.append(f"  {sources[i]}{comma}\n")
    lines.append("};\n")

    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "manifest_map_sources.inc").write_text("".join(lines))


def generate_manifest_connection_overrides(manifest: list, out_dir: Path) -> None:
    """Generate manifest_connection_overrides.inc — per-slot target map
    overrides for vanilla map transitions.

    For each map (0-60), builds a u8[5] table.  0xFF means "use ROM default".
    Only non-default slot targets are stored.

    The runtime hook in map_transition_hooks.c checks this table to redirect
    edge and script-driven map transitions.
    """
    # Build constant → numeric ID lookup from manifest entries
    const_to_id: dict[str, int] = {}
    for entry in manifest:
        c = entry.get("constant")
        mid = entry.get("id")
        if isinstance(mid, int) and isinstance(c, str):
            const_to_id[c] = mid

    # Read ROM base slot targets (gMapData[mid][0]->unk168[slot].unk4)
    rom_slot_targets: list[list[int | None]] = [[None] * 5 for _ in range(61)]
    try:
        rom_bytes = ROM_PATH.read_bytes()
        for mid in range(61):
            off = 0x08E19274 - ROM_BASE
            mapdata_ptr = struct.unpack_from("<I", rom_bytes, off + mid * 4)[0]
            state0_ptr = struct.unpack_from("<I", rom_bytes, mapdata_ptr - ROM_BASE)[0]
            base = state0_ptr - ROM_BASE
            for slot in range(5):
                rom_slot_targets[mid][slot] = struct.unpack_from(
                    "<B", rom_bytes, base + 0x168 + slot * 8 + 4)[0]
    except (FileNotFoundError, struct.error):
        print("warning: cannot read ROM — connection overrides will be empty")
        rom_slot_targets = []

    # Build override table
    overrides: list[list[int]] = [[0xFF] * 5 for _ in range(61)]
    override_count = 0

    for entry in manifest:
        mid = entry.get("id")
        if not isinstance(mid, int) or mid < 0 or mid >= 61:
            continue

        for conn in entry.get("connections", []):
            slot = conn.get("slot")
            if not isinstance(slot, int) or slot < 0 or slot >= 5:
                continue

            target_const = conn.get("target", "")
            if target_const == "WORLD_MAP":
                continue

            target_id = const_to_id.get(target_const)
            if target_id is None:
                continue

            # Only override if different from ROM base
            if (rom_slot_targets
                    and rom_slot_targets[mid][slot] is not None
                    and rom_slot_targets[mid][slot] == target_id):
                continue

            overrides[mid][slot] = target_id
            override_count += 1

    lines = [
        "// Auto-generated connection overrides from tools/custom_map_manifest.json\n",
        "// Per-map per-slot (5) target map overrides. 0xFF = use ROM default.\n\n",
        "#ifndef GUARD_MANIFEST_CONNECTION_OVERRIDES\n",
        "#define GUARD_MANIFEST_CONNECTION_OVERRIDES\n\n",
        "static const u8 gManifestConnectionOverrides[61][5] APPEND_RODATA = {\n",
    ]
    for mid in range(61):
        ov = overrides[mid]
        vals = ", ".join(f"0x{v:02X}" for v in ov)
        lines.append(f"  {{{vals}}},\n")
    lines.append("};\n\n#endif /* GUARD_MANIFEST_CONNECTION_OVERRIDES */\n")

    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "manifest_connection_overrides.inc").write_text("".join(lines))
    print(f"  connections: {override_count} overrides across {sum(1 for m in overrides if any(v != 0xFF for v in m))} maps")


def _read_base_spawn(mid: int) -> list[tuple[int, int, int]]:
    """Read ROM playerInitialState for a map.

    Returns list of (x, y, dir) for each of 5 slots.
    """
    try:
        rom = ROM_PATH.read_bytes()
        off = 0x08E19274 - ROM_BASE
        mapdata_ptr = struct.unpack_from("<I", rom, off + mid * 4)[0]
        state0_ptr = struct.unpack_from("<I", rom, mapdata_ptr - ROM_BASE)[0]
        base = state0_ptr - ROM_BASE
        slots = []
        for slot in range(5):
            sp, dp, _, xp, yp, _, _, _ = struct.unpack_from(
                "<h B B H H I I I", rom, base + 0x190 + slot * 20)
            slots.append((xp, yp, dp))
        return slots
    except (FileNotFoundError, struct.error):
        return [(0xFF, 0xFF, 0xFF)] * 5


def generate_manifest_spawn_overrides(manifest: list, out_dir: Path) -> None:
    """Generate manifest_spawn_overrides.inc — player spawn (x, y, dir)
    overrides per connection slot.

    Three parallel u8[61][5] tables. 0xFF = use ROM default.
    Only emits overrides where the manifest value differs from ROM base.
    """
    x_table: list[list[int]] = [[0xFF] * 5 for _ in range(61)]
    y_table: list[list[int]] = [[0xFF] * 5 for _ in range(61)]
    d_table: list[list[int]] = [[0xFF] * 5 for _ in range(61)]
    override_count = 0

    for entry in manifest:
        mid = entry.get("id")
        if not isinstance(mid, int) or mid < 0 or mid >= 61:
            continue

        base = _read_base_spawn(mid)

        for conn in entry.get("connections", []):
            slot = conn.get("slot")
            spawn = conn.get("spawn")
            if not isinstance(slot, int) or slot < 0 or slot >= 5 or spawn is None:
                continue

            mx = spawn.get("x")
            my = spawn.get("y")
            md_str = spawn.get("dir")
            md = DIRECTION_VALUES.get(md_str, 0xFF) if isinstance(md_str, str) else md_str
            bx, by, bd = base[slot]

            changed = False
            if isinstance(mx, int) and mx != bx:
                x_table[mid][slot] = mx
                changed = True
            if isinstance(my, int) and my != by:
                y_table[mid][slot] = my
                changed = True
            if isinstance(md, int) and md != bd:
                d_table[mid][slot] = md
                changed = True
            if changed:
                override_count += 1

    def _row(vals: list[int]) -> str:
        parts = []
        for v in vals:
            if v == 0xFF:
                parts.append("0xFF")
            else:
                parts.append(str(v))
        return "{" + ", ".join(parts) + "}"

    lines = [
        "// Auto-generated spawn overrides from tools/custom_map_manifest.json\n",
        "// 0xFF = use ROM default position for this slot.\n\n",
        "#ifndef GUARD_MANIFEST_SPAWN_OVERRIDES\n",
        "#define GUARD_MANIFEST_SPAWN_OVERRIDES\n\n",
        "static const u8 gManifestSpawnOverrideX[61][5] APPEND_RODATA = {\n",
    ]
    for mid in range(61):
        lines.append(f"  {_row(x_table[mid])},\n")
    lines.append("};\n\n")
    lines.append("static const u8 gManifestSpawnOverrideY[61][5] APPEND_RODATA = {\n")
    for mid in range(61):
        lines.append(f"  {_row(y_table[mid])},\n")
    lines.append("};\n\n")
    lines.append("static const u8 gManifestSpawnOverrideDir[61][5] APPEND_RODATA = {\n")
    for mid in range(61):
        lines.append(f"  {_row(d_table[mid])},\n")
    lines.append("};\n\n#endif /* GUARD_MANIFEST_SPAWN_OVERRIDES */\n")

    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "manifest_spawn_overrides.inc").write_text("".join(lines))
    has = sum(1 for m in range(61)
              if any(x_table[m][s] != 0xFF or y_table[m][s] != 0xFF or d_table[m][s] != 0xFF for s in range(5)))
    print(f"  spawn: {override_count} overrides across {has} maps")


if __name__ == "__main__":
    sys.exit(main())
