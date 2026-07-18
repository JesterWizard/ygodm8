#!/usr/bin/env python3
"""Build custom map assets from custom_map_manifest.json.

Reads baserom.gba for original collision data, processes the custom map
manifest, converts PNG tilesheets to LZ77-compressed 8bpp tilesets, CSV
tilemaps to u16 arrays, JSON collision data to binary, and generates
dispatch/connection tables into src_custom/generated/maps/.
"""

from __future__ import annotations

import csv
import json
import pathlib
import re
import sys
from collections import Counter

from PIL import Image

ROOT = pathlib.Path(__file__).resolve().parent.parent
BASEROM = ROOT / "baserom.gba"
ROM_BASE = 0x08000000
# Vanilla gMapCollisions[] pointer table (u32[61]) in baserom.
COLLISION_PTR_TABLE = 0x08E11DC4
# Vanilla gMapData[] pointer table (u32[61]) — MapData* per map.
MAPDATA_PTR_TABLE = 0x08E19274
VANILLA_MAP_COUNT = 61
CUSTOM_MAP_BASE = 61
CONNECTION_SLOTS = 5

# Python string constant used as literal text in generated C files
# Must be referenced via {APPEND_RODATA} inside f-strings else it stays literal.
APPEND_RODATA_ATTR = "__attribute__((section(\".append_rodata\"), aligned(4)))"

# Legacy name — do NOT use in f-strings expecting f-string expansion.
# Kept so old literal-APPEND_RODATA references still compile when
# the attribute is spelled out in the generated C (they appear as
# a bare identifier, NOT as the attribute).
APPEND_RODATA = APPEND_RODATA_ATTR
APPEND_ASSET = "__attribute__((section(\".append_assets\"), aligned(4)))"

TILE_W = 8
TILE_H = 8
TILEMAP_W = 32
TILEMAP_H = 32
COLLISION_W = 120
COLLISION_H = 80
SPAWN_NO_OVERRIDE = 0xFF

# 8bpp: 64 bytes/tile. Vanilla LoadVRAM uploads cbb0+cbb1+cbb2 = 768 tiles.
# (Old 512 = cbb0+cbb1 only was a custom-pipeline underestimate.)
MAX_UNIQUE_TILES = 768
TILE_BYTES_8BPP = 64
PALETTE_COUNT = 240  # 240 colors at palette offset 0x10 (slots 16-255)
PALETTE_OFFSET = 16  # font occupies slots 0-15

# Direction constant names -> numeric values (matching overworld.h enum)
DIRECTION_VALUES = {"DIRECTION_DOWN": 0, "DIRECTION_LEFT": 1,
                    "DIRECTION_UP": 2, "DIRECTION_RIGHT": 3}

# Music constant name -> value lookup
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


def _read_ptr_table(rom: bytes, addr: int, count: int) -> list[int]:
    import struct
    off = addr - ROM_BASE
    return [struct.unpack_from("<I", rom, off + i * 4)[0] for i in range(count)]


def _read_base_collision(mid: int) -> list[int] | None:
    """Read the original GBA collision grid for map `mid` from baserom.gba.

    Uses the vanilla gMapCollisions[] pointer table (same as regenerate_manifest.py).
    """
    import struct
    if mid < 0 or mid >= VANILLA_MAP_COUNT or not BASEROM.exists():
        return None
    try:
        rom = BASEROM.read_bytes()
        ptrs = _read_ptr_table(rom, COLLISION_PTR_TABLE, VANILLA_MAP_COUNT)
        off = ptrs[mid] - ROM_BASE
        return list(struct.unpack_from("<" + "H" * (COLLISION_W * COLLISION_H), rom, off))
    except Exception:
        return None


def _read_rom_connection_targets(mid: int) -> list[int] | None:
    """Return 5 target map IDs for vanilla connection slots, or None."""
    import struct
    if mid < 0 or mid >= VANILLA_MAP_COUNT or not BASEROM.exists():
        return None
    try:
        rom = BASEROM.read_bytes()
        mapdata_ptrs = _read_ptr_table(rom, MAPDATA_PTR_TABLE, VANILLA_MAP_COUNT)
        state0_ptr = struct.unpack_from("<I", rom, mapdata_ptrs[mid] - ROM_BASE)[0]
        base = state0_ptr - ROM_BASE
        targets = []
        for i in range(CONNECTION_SLOTS):
            tgt_id, _tgt_conn = struct.unpack_from("<BB", rom, base + 0x168 + i * 8 + 4)
            targets.append(tgt_id)
        return targets
    except Exception:
        return None


# ---------------------------------------------------------------------------
# LZ77 compression (we do our own to stay pipeline-friendly)
# ---------------------------------------------------------------------------

def lz77_compress(data: bytes) -> bytes:
    """Simple LZ77 compression (GBA-compatible format).

    Header: 0x10, then 24-bit uncompressed size little-endian.
    ponytail: not optimal — fine for tilesets under 48 KB.
    """
    if not data:
        return b'\x10\x00\x00\x00'

    result = bytearray()
    result.append(0x10)
    # GBA LZ77 size is little-endian (was big-endian — crashed when
    # size & 0xFF != 0, e.g. 745*64=0xBA40 → decompressor wrote 0x40BA00).
    result.append(len(data) & 0xFF)
    result.append((len(data) >> 8) & 0xFF)
    result.append((len(data) >> 16) & 0xFF)

    pos = 0
    n = len(data)

    while pos < n:
        flags_pos = len(result)
        result.append(0)
        flags = 0

        for bit in range(8):
            if pos >= n:
                break
            # Look for longest match in [-4096, pos)
            window_start = max(0, pos - 4096)
            best_disp = 1
            best_len = 0
            max_mlen = min(18, n - pos)
            if max_mlen >= 3:
                for ms in range(window_start, pos):
                    ml = 0
                    while ml < max_mlen and data[ms + ml] == data[pos + ml]:
                        ml += 1
                    if ml > best_len:
                        best_len = ml
                        best_disp = pos - ms
                        if ml == max_mlen:
                            break

            if best_len >= 3:
                flags |= (0x80 >> bit)
                enc = min(best_len - 3, 15)
                # BIOS LZ77: Disp = stored + 1 (GBATEK). Store distance-1.
                store = best_disp - 1
                result.append(((store >> 8) & 0x0F) | (enc << 4))
                result.append(store & 0xFF)
                pos += best_len
            else:
                result.append(data[pos])
                pos += 1

        result[flags_pos] = flags

    while len(result) % 4:
        result.append(0)
    return bytes(result)


# ---------------------------------------------------------------------------
# 8bpp tile encoding / decoding helpers
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


def tile_to_bytes_8bpp(tile: list[list[int]],
                       *,
                       zero_is_transparent: bool = False) -> bytes:
    """Convert an 8x8 pixel matrix to 64 bytes of 8bpp tile data.

    Map palette is loaded at gPaletteBuffer+0x10, so PNG indices are stored
    as (index + 16). Index 0 in the PNG is often opaque black — only keep it
    as GBA 0 (transparent) when zero_is_transparent (roof/high layer).
    """
    buf = bytearray(64)
    for row in range(TILE_H):
        for col in range(TILE_W):
            p = tile[row][col]
            if not isinstance(p, int):
                raise TypeError(
                    "indexed (palette) PNG required; got RGB/RGBA pixel "
                    f"{type(p).__name__}. Convert the layer to mode P, 256x256.")
            if p == 0 and zero_is_transparent:
                buf[row * 8 + col] = 0
            else:
                buf[row * 8 + col] = p + PALETTE_OFFSET
    return bytes(buf)


def encode_tiles_8bpp(tiles: list[list[list[int]]],
                      *,
                      zero_is_transparent: bool = False) -> list[bytes]:
    """Convert tiles to 8bpp byte arrays (+16 palette offset)."""
    return [tile_to_bytes_8bpp(t, zero_is_transparent=zero_is_transparent)
            for t in tiles]


def tiles_to_tileset(tiles: list[bytes],
                     dedup: bool = True) -> tuple[bytes, list[int]]:
    """Convert tile byte blobs to tileset bytes + remap table.

    The all-zero (transparent) tile is forced to tileset index 0 so that
    screenblocks filled with 0x0000 display as transparent backdrop.

    Returns (tileset_bytes, remap) where remap[n] = deduped_index for original tile n.
    """
    ts = TILE_BYTES_8BPP
    zero_bytes = b'\x00' * ts

    if not dedup:
        return b''.join(tiles), list(range(len(tiles)))

    # Dedup, tracking frequency
    seen: dict[bytes, int] = {}
    freq: dict[bytes, int] = {}
    unique_order: list[bytes] = []
    for tile_bytes in tiles:
        freq[tile_bytes] = freq.get(tile_bytes, 0) + 1
        if tile_bytes not in seen:
            seen[tile_bytes] = len(seen)  # placeholder
            unique_order.append(tile_bytes)

    # Always reserve index 0 as the all-zero (transparent) tile. Roof clear
    # and empty sbb entries point at 0; without this, opaque tile 0 covers BG2.
    final: list[bytes] = [zero_bytes]
    if zero_bytes in unique_order:
        unique_order.remove(zero_bytes)
    final.extend(unique_order)

    if len(final) > MAX_UNIQUE_TILES:
        raise ValueError(
            f"Tile budget exceeded: {len(final)} unique tiles, max is {MAX_UNIQUE_TILES}"
        )

    # Remap: original index -> final index
    order = {tb: i for i, tb in enumerate(final)}
    remap = [order[tb] for tb in tiles]

    return b''.join(final), remap


def _reduce_tiles(ground_bytes: list[bytes],
                  max_tiles: int) -> tuple[bytes, list[int], list[int]]:
    """Reduce unique tiles to fit within max_tiles by replacing rare tiles.

    Ensures the all-zero tile is always at tileset index 0.

    Returns (tileset_data, remap, original_to_tileset).
    """
    ts = TILE_BYTES_8BPP
    zero_bytes = b'\x00' * ts

    # Phase 1: dedup with frequency tracking
    uniq_order: list[bytes] = []
    freq: dict[bytes, int] = {}
    seen_set = set()
    for tb in ground_bytes:
        freq[tb] = freq.get(tb, 0) + 1
        if tb not in seen_set:
            seen_set.add(tb)
            uniq_order.append(tb)

    # Reserve one slot for the mandatory transparent tile at index 0.
    has_zero = zero_bytes in seen_set
    budget = max_tiles if has_zero else max_tiles - 1
    need_reduction = len(uniq_order) > budget
    if need_reduction:
        seen = list(uniq_order)
        while len(seen) > budget:
            rarest = min(seen, key=lambda tb: freq[tb])
            seen.remove(rarest)
            best_idx = 0
            best_dist = 0x7FFFFFFF
            for i, candidate in enumerate(seen):
                dist = sum((a - b) * (a - b) for a, b in zip(rarest, candidate))
                if dist < best_dist:
                    best_dist = dist
                    best_idx = i
                    if best_dist == 0:
                        break
            freq[seen[best_idx]] += freq[rarest]
        final = seen
    else:
        final = list(uniq_order)

    # Transparent tile always at index 0 (insert if ground never used it).
    if zero_bytes in final:
        final.remove(zero_bytes)
    final.insert(0, zero_bytes)

    order = {tb: i for i, tb in enumerate(final)}
    tileset_data = b"".join(final)

    remap_list = []
    for tb in ground_bytes:
        if tb in order:
            remap_list.append(order[tb])
        else:
            best_idx = 0
            best_dist = 0x7FFFFFFF
            for i, candidate in enumerate(final):
                dist = sum((a - b) * (a - b) for a, b in zip(tb, candidate))
                if dist < best_dist:
                    best_dist = dist
                    best_idx = i
            remap_list.append(best_idx)

    return tileset_data, remap_list, remap_list


def _tileset_prefer_roof(ground_bytes: list[bytes],
                         roof_bytes: list[bytes],
                         max_tiles: int) -> tuple[bytes, list[int], list[int]]:
    """Build a shared tileset that keeps every roof tile exact.

    Roof overhangs must not nearest-match into opaque ground tiles (that
    produces black/green garbage). Ground fills the remaining budget by
    frequency; rare ground tiles nearest-match.
    """
    ts = TILE_BYTES_8BPP
    zero = b'\x00' * ts

    roof_uniq: list[bytes] = []
    seen: set[bytes] = set()
    for tb in roof_bytes:
        if tb not in seen:
            seen.add(tb)
            roof_uniq.append(tb)

    final: list[bytes] = [zero]
    for tb in roof_uniq:
        if tb != zero:
            final.append(tb)

    if len(final) > max_tiles:
        raise ValueError(
            f"Roof alone needs {len(final)} tiles (incl. transparent), "
            f"max is {max_tiles}")

    freq: dict[bytes, int] = {}
    for tb in ground_bytes:
        freq[tb] = freq.get(tb, 0) + 1
    for tb, _ in sorted(freq.items(), key=lambda kv: -kv[1]):
        if len(final) >= max_tiles:
            break
        if tb not in seen:
            seen.add(tb)
            final.append(tb)

    order = {tb: i for i, tb in enumerate(final)}
    tileset_data = b"".join(final)

    def remap_one(tb: bytes) -> int:
        if tb in order:
            return order[tb]
        best_idx = 0
        best_dist = 0x7FFFFFFF
        for i, candidate in enumerate(final):
            dist = sum((a - b) * (a - b) for a, b in zip(tb, candidate))
            if dist < best_dist:
                best_dist = dist
                best_idx = i
                if best_dist == 0:
                    break
        return best_idx

    ground_remap = [remap_one(tb) for tb in ground_bytes]
    roof_remap = [order[tb] for tb in roof_bytes]  # exact by construction
    return tileset_data, ground_remap, roof_remap


def _stamp_roof_behind_sprites(flat_coll: list[int],
                               roof_img: Image.Image) -> int:
    """OR COLLISION_PASSABLE (0x1000) under opaque roof pixels.

    Vanilla sub_804EEAC gives sprites priority 2 when this bit is set, so
    BG1 (roof, priority 1) draws over the player — walk-behind overhangs.
    map pixel = collision*2 + 8 (matches gBG*HOFS = 8).
    """
    rp = roof_img.load()
    stamped = 0
    for cy in range(COLLISION_H):
        for cx in range(COLLISION_W):
            px = cx * 2 + 8
            py = cy * 2 + 8
            opaque = False
            for dy in range(2):
                for dx in range(2):
                    x = min(255, px + dx)
                    y = min(255, py + dy)
                    pix = rp[x, y]
                    if isinstance(pix, int):
                        if pix != 0:
                            opaque = True
                            break
                    elif sum(pix[:3]) > 0:
                        opaque = True
                        break
                if opaque:
                    break
            if not opaque:
                continue
            idx = cy * COLLISION_W + cx
            if flat_coll[idx] & 0x1000:
                continue
            flat_coll[idx] |= 0x1000
            stamped += 1
    return stamped


def _match_tiles_to_tileset(tiles: list[bytes], tileset: bytes) -> list[int]:
    """For each tile, find the closest match in tileset by SSE over pixel bytes.

    Exact matches via set lookup; approximate falls back to scanning all tiles.
    ponytail: O(n*m) scan for misses; fine for 512 tiles.
    """
    ts = TILE_BYTES_8BPP
    n = len(tileset) // ts
    exact: dict[bytes, int] = {}
    for i in range(n):
        chunk = tileset[i * ts:(i + 1) * ts]
        exact.setdefault(chunk, i)

    result = []
    for tile in tiles:
        idx = exact.get(tile)
        if idx is not None:
            result.append(idx)
            continue
        best_idx = 0
        best_dist = 0x7FFFFFFF
        for i in range(n):
            chunk = tileset[i * ts:(i + 1) * ts]
            dist = sum((a - b) * (a - b) for a, b in zip(tile, chunk))
            if dist < best_dist:
                best_dist = dist
                best_idx = i
                if best_dist == 0:
                    break
        result.append(best_idx)
    return result


# ---------------------------------------------------------------------------
# Palette extraction
# ---------------------------------------------------------------------------

def extract_palette(png: Image.Image) -> list[tuple[int, int, int]]:
    """Extract up to 240 RGB colors from an indexed PNG palette.

    Color 0 is transparent/backdrop (typically black or tilesheet bg color).
    The palette is loaded at gPaletteBuffer + 0x10 on the GBA.
    """
    if png.mode != "P":
        raise ValueError("tiles.png must be an indexed (palette) PNG")

    pal = png.getpalette()
    if pal is None:
        raise ValueError("tiles.png has no palette")

    colors = []
    num_colors = min(len(pal) // 3, PALETTE_COUNT)
    for i in range(num_colors):
        r, g, b = pal[i * 3:(i + 1) * 3]
        colors.append((r, g, b))

    while len(colors) < PALETTE_COUNT:
        colors.append((0, 0, 0))
    return colors


def rgb_to_gba(color: tuple[int, int, int]) -> int:
    """Convert RGB888 to GBA RGB555."""
    r, g, b = color
    return (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)


# ---------------------------------------------------------------------------
# CSV / JSON parsers
# ---------------------------------------------------------------------------

def parse_tilemap_csv(path: pathlib.Path) -> list[list[int]]:
    """Parse a 32x32 CSV tilemap into list of lists of ints."""
    rows: list[list[int]] = []
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            stripped = line.strip(",")
            rows.append([int(v.strip()) for v in stripped.split(",") if v.strip()])
    return rows


def parse_collision_json(path: pathlib.Path) -> list[list[int]]:
    """Parse collision JSON into a 120x80 grid of u16 values."""
    with open(path) as f:
        data = json.load(f)

    # Expect a 2D array [[v00,v01,...], [v10,...], ...]
    if isinstance(data, list) and len(data) == COLLISION_H:
        grid = data
    elif isinstance(data, dict) and "grid" in data:
        grid = data["grid"]
    else:
        raise ValueError(f"Unrecognised collision format in {path}")

    # Ensure all integers
    parsed = [[int(v) & 0xFFFF for v in row] for row in grid]
    return parsed


# ---------------------------------------------------------------------------
# .inc file generators
# ---------------------------------------------------------------------------

def gen_inc_header(name: str) -> str:
    """Generate a short header comment for .inc files."""
    return f"// Auto-generated for custom map: {name}\n"


def gen_tileset_inc(name: str, compressed: bytes) -> str:
    """Generate .inc for an LZ77-compressed tileset as a const u8 array."""
    header = gen_inc_header(name)
    hex_bytes = ", ".join(f"0x{b:02x}" for b in compressed)
    body = (
        f"static const u8 sCustomTileset_{name}[]{APPEND_ASSET} = {{\n"
        f"  {hex_bytes}\n"
        f"}};\n"
    )
    return header + body


def gen_tilemap_inc(name: str, layer: str, tilemap: list[list[int]],
                    remap: list[int] | None = None) -> str:
    """Generate .inc for a tilemap as const u16 array.

    If remap is provided, tile indices are remapped through it.
    Tilemap entries are plain indices 0-511 (no palette bank bits — 8bpp mode).
    """
    header = gen_inc_header(name)
    arr_name = f"sCustom{layer.capitalize()}Tilemap_{name}"
    body = f"static const u16 {arr_name}[]{APPEND_RODATA} = {{"
    for row in tilemap:
        body += "\n  "
        for val in row:
            idx = val & 0x3FF
            attrs = val & ~0x3FF
            if remap:
                idx = remap[idx]
            mapped = (idx & 0x3FF) | attrs
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


def gen_dispatch_inc(entries: list[dict], all_entries: list[dict]) -> tuple[str, str, str]:
    """Generate dispatch .inc: tileset/tilemap/palette/collision pointer arrays.

    Returns (pointer_tables_inc, connections_inc, mapdata_inc).
    """
    map_count = len(entries)
    names = [e["name"] for e in entries]

    # Generate includes
    includes_lines = []
    ptr_lines_tileset = []
    ptr_lines_ground = []
    ptr_lines_palette = []
    ptr_lines_collision = []
    ptr_lines_roof = []
    tile_type_lines = []  # ground-only vs full-map (0=ground-only, 1=full-map)

    for e in entries:
        name = e["name"]
        includes_lines.append(f'#include "src_custom/generated/maps/tileset_{name}.inc"')
        includes_lines.append(f'#include "src_custom/generated/maps/ground_tilemap_{name}.inc"')
        includes_lines.append(f'#include "src_custom/generated/maps/palette_{name}.inc"')
        includes_lines.append(f'#include "src_custom/generated/maps/collision_{name}.inc"')

        ptr_lines_tileset.append(f"  sCustomTileset_{name},")
        ptr_lines_ground.append(f"  sCustomGroundTilemap_{name},")
        ptr_lines_palette.append(f"  sCustomPalette_{name},")
        ptr_lines_collision.append(f"  sCustomCollision_{name},")

        has_roof = e.get("_has_roof", False)
        if has_roof:
            includes_lines.append(f'#include "src_custom/generated/maps/roof_tilemap_{name}.inc"')
            ptr_lines_roof.append(f"  sCustomRoofTilemap_{name},")
        else:
            ptr_lines_roof.append("  NULL,")

        tile_type_lines.append(f"  {1 if has_roof else 0},")  # 1=full-map with roof

    includes_str = "\n".join(includes_lines)

    ptr_table = f"""
// Custom map pointer tables ({map_count} maps)
static const u8* const sCustomTilesets[] {APPEND_RODATA_ATTR} = {{
{chr(10).join(ptr_lines_tileset)}
}};
static const u16* const sCustomGroundTilemaps[]{APPEND_RODATA_ATTR} = {{
{chr(10).join(ptr_lines_ground)}
}};
static const u16* const sCustomRoofTilemaps[]{APPEND_RODATA_ATTR} = {{
{chr(10).join(ptr_lines_roof)}
}};
static const u16* const sCustomPalettes[]{APPEND_RODATA_ATTR} = {{
{chr(10).join(ptr_lines_palette)}
}};
static const u16* const sCustomCollisions[]{APPEND_RODATA_ATTR} = {{
{chr(10).join(ptr_lines_collision)}
}};
static const u8 sCustomTileTypes[]{APPEND_RODATA_ATTR} = {{
{chr(10).join(tile_type_lines)}
}};
"""

    # Generate connection override table
    conn_lines = [f"// Connection overrides for {map_count} custom maps"]
    conn_lines.append(f"static const u16 sCustomConnectionTargets[{map_count}][4] = {{")
    for e in entries:
        # Build slot->target lookup from list of connection objects
        slot_targets: dict[int, int] = {}
        for conn in e.get("connections", []):
            raw = conn.get("target", 0)
            slot_targets[conn.get("slot", 0)] = _resolve_target_id(raw, all_entries)
        conns = []
        for slot in range(4):
            conns.append(str(slot_targets.get(slot, 0)))
        conn_lines.append("  { " + ", ".join(conns) + " },")
    conn_lines.append("};")
    connections_str = "\n".join(conn_lines)

    # Music IDs parallel to sCustomTilesets[] (index = mapId - CUSTOM_MAP_BASE)
    mapdata_lines = [
        f"// Music IDs for {map_count} custom maps",
        f"static const u16 sCustomMapMusic[{map_count}] {APPEND_RODATA_ATTR} = {{",
    ]
    for e in entries:
        music = _music_value(e.get("music", "MUSIC_NONE"))
        mapdata_lines.append(f"  {music}, /* {e.get('name', '?')} */")
    mapdata_lines.append("};")
    mapdata_str = "\n".join(mapdata_lines)

    return includes_str + ptr_table, connections_str, mapdata_str


# ---------------------------------------------------------------------------
# Main build
# ---------------------------------------------------------------------------

def main() -> int:
    manifest_path = ROOT / "tools" / "custom_map_manifest.json"
    out_dir = ROOT / "src_custom" / "generated" / "maps"
    out_dir.mkdir(parents=True, exist_ok=True)

    with open(manifest_path) as f:
        manifest = json.load(f)

    entries = manifest if isinstance(manifest, list) else manifest.get("entries", [])

    # Filter to active entries with a name
    active = [e for e in entries if e.get("name") and e.get("active", True)]
    if not active:
        print("No active custom maps found.")
        return 0

    print(f"Building {len(active)} custom map(s)...\n")

    # -----------------------------------------------------------------------
    # Phase 1: Asset generation
    # -----------------------------------------------------------------------
    for entry in active:
        name = entry["name"]
        print(f"=== {name} ===")

        asset_base = ROOT / "src_custom" / "assets" / "maps"
        map_dir = asset_base / name
        ground_png = asset_base / f"map_{name}_ground.png"
        roof_png = asset_base / f"map_{name}_roof.png"
        map_dir_ground = map_dir / "ground.png"
        map_dir_roof = map_dir / "roof.png"
        tiles_png = map_dir / "tiles.png"
        ground_csv = map_dir / "ground.csv"
        roof_csv = None
        tiles = None
        roof_grid = None

        def _usable_layer_png(path: pathlib.Path) -> bool:
            if not path.exists():
                return False
            im = Image.open(path)
            return im.mode == "P" and im.size == (256, 256)

        # Manifest paths win when they are real indexed map sheets.
        imgs = entry.get("images") or {}
        for key in ("ground", "roof"):
            raw = imgs.get(key)
            if not raw:
                continue
            p = ROOT / raw
            if _usable_layer_png(p):
                if key == "ground":
                    ground_png = p
                else:
                    roof_png = p
            elif p.exists():
                im = Image.open(p)
                print(f"  warning: ignoring images.{key}={raw} "
                      f"(need indexed 256x256 PNG, got {im.mode} {im.size})")

        if _usable_layer_png(map_dir_ground):
            ground_png = map_dir_ground
        if _usable_layer_png(map_dir_roof):
            roof_png = map_dir_roof
        elif map_dir_roof.exists():
            print(f"  warning: ignoring {map_dir_roof.relative_to(ROOT)} "
                  f"(need indexed 256x256 PNG)")

        # Roof only if we have a usable indexed sheet.
        has_roof_manifest = bool(imgs.get("roof"))
        entry["_has_roof"] = has_roof_manifest and _usable_layer_png(roof_png)

        # Prefer ground.png hybrid when present: tiles.png+csv can drift.
        if _usable_layer_png(ground_png) and (
                ground_png == map_dir_ground
                or not (tiles_png.exists() and ground_csv.exists())):
            print(f"  Hybrid: using {ground_png.relative_to(ROOT)}")
            ground_img = Image.open(ground_png)
            ground_tiles_raw = split_tilesheet(ground_img)
            palette = extract_palette(ground_img)

            ground_bytes = encode_tiles_8bpp(ground_tiles_raw)
            n_unique = len(set(ground_bytes))
            if n_unique <= MAX_UNIQUE_TILES:
                tileset_data, ground_indices = tiles_to_tileset(ground_bytes)
                print(f"  Ground: {len(ground_tiles_raw)} tiles -> "
                      f"{len(tileset_data) // TILE_BYTES_8BPP} unique "
                      f"(exact, max {MAX_UNIQUE_TILES})")
            else:
                tileset_data, ground_indices, _ = _reduce_tiles(
                    ground_bytes, MAX_UNIQUE_TILES)
                print(f"  Ground: {len(ground_tiles_raw)} tiles -> "
                      f"{len(tileset_data) // TILE_BYTES_8BPP} unique "
                      f"(reduced from {n_unique}, max {MAX_UNIQUE_TILES})")

            ground = [[ground_indices[y * 32 + x] for x in range(32)] for y in range(32)]

            roof = None
            roof_grid = None
            if entry["_has_roof"]:
                roof_img = Image.open(roof_png)
                roof_tiles_raw = split_tilesheet(roof_img)
                roof_bytes = encode_tiles_8bpp(
                    roof_tiles_raw, zero_is_transparent=True)
                # Shared CBB0 tileset. Exact shared bake when it fits; otherwise
                # keep every roof tile exact and trim rare ground tiles.
                combined = set(ground_bytes) | set(roof_bytes)
                if len(combined) <= MAX_UNIQUE_TILES:
                    all_bytes = ground_bytes + roof_bytes
                    tileset_data, remap = tiles_to_tileset(all_bytes)
                    ground_indices = remap[:len(ground_bytes)]
                    roof_indices = remap[len(ground_bytes):]
                    print(f"  Roof: {len(roof_tiles_raw)} tiles "
                          f"in shared tileset "
                          f"({len(tileset_data) // TILE_BYTES_8BPP} unique)")
                else:
                    tileset_data, ground_indices, roof_indices = (
                        _tileset_prefer_roof(
                            ground_bytes, roof_bytes, MAX_UNIQUE_TILES))
                    print(f"  Roof: {len(roof_tiles_raw)} tiles exact; "
                          f"ground trimmed for shared budget "
                          f"({len(tileset_data) // TILE_BYTES_8BPP} unique, "
                          f"would need {len(combined)})")
                ground = [[ground_indices[y * 32 + x] for x in range(32)]
                          for y in range(32)]
                roof = [roof_indices[i * 32 + j]
                        for i in range(32) for j in range(32)]
                roof_grid = [roof[i * 32:(i + 1) * 32] for i in range(32)]

        elif tiles_png.exists() and ground_csv.exists():
            ts_img = Image.open(tiles_png)
            ground_tiles = split_tilesheet(ts_img)

            # Dump palette from tiles.png
            palette = extract_palette(ts_img)

            # Encode tiles as 8bpp + dedup (tilesheet index 0 = transparent)
            tile_bytes = encode_tiles_8bpp(ground_tiles, zero_is_transparent=True)
            tileset_data, remap = tiles_to_tileset(tile_bytes)
            unique_count = len(tileset_data) // TILE_BYTES_8BPP
            print(f"  Tiles: {len(ground_tiles)} original -> {unique_count} unique (max {MAX_UNIQUE_TILES})")

            if unique_count > MAX_UNIQUE_TILES:
                print(f"error: {name} has {unique_count} unique tiles, exceeds max {MAX_UNIQUE_TILES}")
                return 1

            # Parse ground tilemap CSV
            ground_raw = parse_tilemap_csv(ground_csv)

            # Remap ground indices to tileset indices
            flat_ground = [v for row in ground_raw for v in row]
            remapped_ground = [remap[v] if v < len(remap) else 0 for v in flat_ground]
            ground = [remapped_ground[i * 32:(i + 1) * 32] for i in range(32)]

            # Roof: auto-generate from roof.png by matching to tileset
            roof = None
            if entry["_has_roof"]:
                roof_img = Image.open(roof_png)
                roof_tiles = split_tilesheet(roof_img)
                # Match roof palette to same palette (roof uses same colors)
                roof_bytes = encode_tiles_8bpp(roof_tiles, zero_is_transparent=True)
                roof_indices = _match_tiles_to_tileset(roof_bytes, tileset_data)
                exact = sum(1 for tb, idx in zip(roof_bytes, roof_indices)
                            if tb == tileset_data[idx*TILE_BYTES_8BPP:(idx+1)*TILE_BYTES_8BPP])
                print(f"  Roof: {len(roof_tiles)} tiles ({exact} exact) matched to tileset")
                roof = [roof_indices[i * 32 + j] for i in range(32) for j in range(32)]
                roof_grid = [roof[i * 32:(i + 1) * 32] for i in range(32)]
        else:
            print(f"error: {name}: no usable ground.png or tiles.png+ground.csv")
            return 1

        # Build collision from JSON if available, else base collision
        collision_json = map_dir / "collision.json"
        if collision_json.exists():
            collision_grid = parse_collision_json(collision_json)
            print(f"  Collision: custom ({len(collision_grid)} rows)")
        else:
            mid = entry.get("id", 0)
            base = _read_base_collision(mid)
            if base:
                collision_grid = [base[i * COLLISION_W:(i + 1) * COLLISION_W]
                                  for i in range(COLLISION_H)]
                print(f"  Collision: base map {mid}")
            else:
                collision_grid = [[0] * COLLISION_W for _ in range(COLLISION_H)]
                print(f"  Collision: zero-filled (no base)")

        # Manifest blocked rects (COLLISION_IMPASSABLE = 1) for custom maps.
        flat_coll = [v for row in collision_grid for v in row]
        for br in (entry.get("collision") or {}).get("blocked") or []:
            if isinstance(br, dict):
                x, y, w, h = br["x"], br["y"], br["width"], br["height"]
            else:
                x, y, w, h = br[0], br[1], br[2], br[3]
            for cy in range(y, y + h):
                for cx in range(x, x + w):
                    idx = cy * COLLISION_W + cx
                    if 0 <= idx < len(flat_coll) and not (flat_coll[idx] & 0x2000):
                        flat_coll[idx] = 1

        # Walk-behind: opaque roof → 0x1000 so sprites draw under BG1.
        if entry.get("_has_roof") and _usable_layer_png(roof_png):
            n_behind = _stamp_roof_behind_sprites(flat_coll, Image.open(roof_png))
            print(f"  Roof walk-behind: {n_behind} cells |= 0x1000")

        # Stamp manifest connection exits onto the custom collision grid.
        for conn in entry.get("connections", []) or []:
            if "rect" in conn:
                _stamp_connection_rect(
                    flat_coll, conn.get("rect", []), conn.get("slot", 0))
        collision_grid = [
            flat_coll[i * COLLISION_W:(i + 1) * COLLISION_W]
            for i in range(COLLISION_H)
        ]

        # Compress tileset
        compressed = lz77_compress(tileset_data)
        # Guard: LE size header must match (wrong endian → BIOS decompress OOB).
        hdr_size = compressed[1] | (compressed[2] << 8) | (compressed[3] << 16)
        if compressed[0] != 0x10 or hdr_size != len(tileset_data):
            print(f"error: {name} LZ77 header size {hdr_size} != {len(tileset_data)}")
            return 1
        print(f"  Tileset: {len(tileset_data)} uniq bytes -> {len(compressed)} lz77 bytes")

        # Write .inc files
        (out_dir / f"tileset_{name}.inc").write_text(gen_tileset_inc(name, compressed))
        (out_dir / f"ground_tilemap_{name}.inc").write_text(
            gen_tilemap_inc(name, "ground", ground))
        (out_dir / f"palette_{name}.inc").write_text(
            gen_palette_inc(name, palette))
        (out_dir / f"collision_{name}.inc").write_text(
            gen_collision_inc(name, collision_grid))

        if roof_grid is not None:
            (out_dir / f"roof_tilemap_{name}.inc").write_text(
                gen_tilemap_inc(name, "roof", roof_grid))

        print()

    # -----------------------------------------------------------------------
    # Phase 2: Dispatch / connection tables
    # -----------------------------------------------------------------------
    dispatch_inc, connections_inc, mapdata_inc = gen_dispatch_inc(active, entries)
    (out_dir / "custom_map_dispatch.inc").write_text(dispatch_inc)
    (out_dir / "custom_map_connections.inc").write_text(connections_inc)
    (out_dir / "custom_map_mapdata.inc").write_text(mapdata_inc)

    # -----------------------------------------------------------------------
    # Phase 3: Collision / connection / spawn overrides
    # -----------------------------------------------------------------------
    generate_manifest_collision_overrides(manifest, out_dir)
    generate_manifest_map_sources(manifest, out_dir)
    generate_manifest_connection_overrides(manifest, out_dir)
    generate_manifest_spawn_overrides(manifest, out_dir)

    # Post-process generated .inc files to rename symbols to what C hooks expect
    _fixup_inc_symbols(out_dir)

    print("All custom map assets generated successfully.")
    return 0


def _fixup_inc_symbols(out_dir: pathlib.Path) -> None:
    """Rename symbols in generated .inc files to match C hook expectations."""
    # Spawn overrides are emitted with final symbol names already.

    # Connection overrides: must be map-ID-indexed u8 array (0xFF = use ROM).
    conn_path = out_dir / "manifest_connection_overrides.inc"
    max_maps = VANILLA_MAP_COUNT + 1
    if conn_path.exists():
        import re
        text = conn_path.read_text()
        entries: list[tuple[int, int, int, int]] = []
        for m in re.finditer(r'\{(\s*\d+\s*,\s*\d+\s*,\s*\d+\s*,\s*\d+\s*)\}', text):
            vals = [int(v) for v in re.findall(r'\d+', m.group(1))]
            if len(vals) == 4:
                entries.append((vals[0], vals[1], vals[2], vals[3]))
        # Always emit the runtime table (even when empty).
        override_by_map: dict[int, list[int]] = {}
        for mid, slot, target, _ in entries:
            if mid not in override_by_map:
                override_by_map[mid] = [0xFF] * CONNECTION_SLOTS
            if 0 <= slot < CONNECTION_SLOTS:
                override_by_map[mid][slot] = target
        lines = [
            "// Auto-generated connection overrides (map-ID-indexed). Do not edit.",
            f"#define CUSTOM_CONNECTION_OVERRIDE_COUNT {len(entries)}",
            "",
            f"static const u8 gManifestConnectionOverrides[{max_maps}][{CONNECTION_SLOTS}] "
            f"{APPEND_RODATA_ATTR} = {{",
        ]
        for mid in range(max_maps):
            slots = override_by_map.get(mid, [0xFF] * CONNECTION_SLOTS)
            vals = ", ".join(
                "0xFF" if s == 0xFF else str(s) for s in slots
            )
            lines.append(f"  {{ {vals} }},")
        lines.append("};")
        conn_path.write_text("\n".join(lines) + "\n")

    # Collision overrides: generate sManifestCollisionOverrides pointer array
    coll_path = out_dir / "manifest_collision_overrides.inc"
    if coll_path.exists():
        import re
        text = coll_path.read_text()
        if "sManifestCollisionOverrides" not in text:
            map_ids: list[int] = []
            for m in re.finditer(r'sCustomCollisionOverrideMaps\[\]\s*=\s*\{([^}]+)\}', text, re.DOTALL):
                vals = re.findall(r'(\d+)', m.group(1))
                map_ids = [int(v) for v in vals]
            max_coll_maps = max(map_ids) + 1 if map_ids else max_maps
            max_coll_maps = max(max_coll_maps, max_maps)
            ptrs: list[str] = []
            for mid in range(max_coll_maps):
                if mid in map_ids:
                    idx = map_ids.index(mid)
                    ptrs.append(f"  (u16*)&sCustomCollisionData[{idx}],")
                else:
                    ptrs.append("  NULL,")
            ptr_block = (
                f"\nstatic u16* const sManifestCollisionOverrides[{max_coll_maps}] "
                f"{APPEND_RODATA_ATTR} = {{\n"
                + "\n".join(ptrs) + "\n};\n"
            )
            text += ptr_block
            coll_path.write_text(text)


# ---------------------------------------------------------------------------
# Collision override generation
# ---------------------------------------------------------------------------

def _stamp_connection_rect(grid: list[int], rect: list[int], slot: int) -> None:
    """Stamp a map-connection trigger onto a flat 120×80 collision grid.

    Bits (from code_8051958.c):
      0x2000 = connected map, 0x0700 = slot << 8.
    Connection tiles must not keep COLLISION_IMPASSABLE (1) or IsImpassable
    treats them as walls before the transition check runs.
    """
    if not rect or len(rect) < 4:
        return
    if slot < 0 or slot >= CONNECTION_SLOTS:
        return
    rx, ry, rw, rh = rect[0], rect[1], rect[2], rect[3]
    if rw <= 0 or rh <= 0:
        return
    if rx < 0 or ry < 0 or rx + rw > COLLISION_W or ry + rh > COLLISION_H:
        sys.exit(
            f"error: connection rect ({rx},{ry},{rw}x{rh}) slot {slot} exceeds "
            f"collision grid ({COLLISION_W}x{COLLISION_H})")
    conn_val = 0x2000 | (slot << 8)
    for cy in range(ry, ry + rh):
        for cx in range(rx, rx + rw):
            idx = cy * COLLISION_W + cx
            # Keep elevation/passable high bits (0xF000 except conn/world), drop
            # impassable low bit and old slot field.
            prev = grid[idx]
            grid[idx] = (prev & 0xF000 & ~0x6000) | conn_val


def _connection_needs_collision_stamp(
    mid: int, conn: dict, entries: list
) -> bool:
    """True when this connection rect must be written into collision data."""
    if "rect" not in conn:
        return False
    target_spec = conn.get("target", -1)
    if target_spec == "WORLD_MAP":
        return False
    target = _resolve_target_id(target_spec, entries)
    if target < 0:
        return False
    if target >= CUSTOM_MAP_BASE:
        return True
    rom_targets = _read_rom_connection_targets(mid)
    if rom_targets is None:
        return True
    slot = conn.get("slot", 0)
    if slot < 0 or slot >= len(rom_targets):
        return True
    return target != rom_targets[slot]


def generate_manifest_collision_overrides(manifest: list, out_dir: pathlib.Path) -> None:
    """Generate collision override include files for maps with custom collision.

    Starts from baserom collision (via gMapCollisions[]), applies blocked rects,
    then stamps connection rects that target custom maps (or otherwise differ
    from ROM). Only emits maps whose final grid differs from ROM.
    """
    entries = manifest if isinstance(manifest, list) else manifest.get("entries", [])
    overrides = []

    for entry in entries:
        mid = entry.get("id", -1)
        if mid < 0 or mid >= VANILLA_MAP_COUNT:
            continue
        rects = entry.get("collision", {}) or {}
        blocked = rects.get("blocked") or []
        conn_list = entry.get("connections", []) or []
        stamp_conns = [
            c for c in conn_list
            if _connection_needs_collision_stamp(mid, c, entries)
        ]
        if not blocked and not rects.get("data") and not stamp_conns:
            continue

        base = _read_base_collision(mid)
        if base is None:
            base = [0] * (COLLISION_W * COLLISION_H)
        grid = list(base)

        # Optional full hex rows (lossless). Prefer over blocked when present.
        data_rows = rects.get("data")
        if data_rows:
            flat: list[int] = []
            for row in data_rows:
                for i in range(0, len(row), 4):
                    flat.append(int(row[i:i + 4], 16))
            if len(flat) == COLLISION_W * COLLISION_H:
                grid = flat
            else:
                print(f"warning: map {mid} collision.data length {len(flat)}, "
                      f"expected {COLLISION_W * COLLISION_H}; ignoring")

        # Stamp blocked rectangles — can be [{x,y,w,h},...] or [[x,y,w,h],...]
        for br in blocked:
            if isinstance(br, dict):
                x, y, w, h = br["x"], br["y"], br["width"], br["height"]
            else:
                x, y, w, h = br[0], br[1], br[2], br[3]
            for cy in range(y, y + h):
                for cx in range(x, x + w):
                    idx = cy * COLLISION_W + cx
                    if 0 <= idx < len(grid):
                        if grid[idx] < 4096:
                            grid[idx] = 4096

        # Custom / redirected exits (e.g. map 11 → graveyard) after blocked.
        for conn in stamp_conns:
            _stamp_connection_rect(
                grid, conn.get("rect", []), conn.get("slot", 0))

        if grid == base:
            continue
        overrides.append((mid, grid))

    if not overrides:
        (out_dir / "manifest_collision_overrides.inc").write_text(
            "// No collision overrides\n"
            "#define CUSTOM_COLLISION_OVERRIDE_COUNT 0\n"
            f"\nstatic u16* const sManifestCollisionOverrides[{VANILLA_MAP_COUNT + 1}] "
            f"{APPEND_RODATA_ATTR} = {{\n"
            + "".join("  NULL,\n" for _ in range(VANILLA_MAP_COUNT + 1))
            + "};\n")
        return

    lines = [
        "// Auto-generated collision overrides. Do not edit.",
        f"#define CUSTOM_COLLISION_OVERRIDE_COUNT {len(overrides)}",
        "",
        f"static const u16 sCustomCollisionData[CUSTOM_COLLISION_OVERRIDE_COUNT]"
        f"[120*80] {APPEND_RODATA} = {{"
    ]
    mid_overrides = []
    for mid, grid in overrides:
        mid_overrides.append(str(mid))
        lines.append("  {")
        for i, val in enumerate(grid):
            lines[-1] += f" {val:#06x},"
            if i % 30 == 29 and i < len(grid) - 1:
                lines.append(" ")
        lines.append("  },")
    lines.append("};")
    lines.append("")
    lines.append("static const u16 sCustomCollisionOverrideMaps[] = {")
    for m in mid_overrides:
        lines.append(f"  {m},")
    lines.append("};")

    (out_dir / "manifest_collision_overrides.inc").write_text("\n".join(lines) + "\n")


def generate_manifest_map_sources(manifest: list, out_dir: pathlib.Path) -> None:
    """Update CUSTOM_MAP_COUNT and slot/source arrays based on manifest entries.

    Generates a 62-element sManifestMapSources array indexed by map ID,
    where each entry is the source map for graphics loading.
    """
    entries = manifest if isinstance(manifest, list) else manifest.get("entries", [])
    max_maps = max((e.get("id", 0) for e in entries), default=0) + 1
    max_maps = max(max_maps, 62)

    active = [(e.get("name"), e.get("id", -1), e.get("slot", 0xFF))
              for e in entries if e.get("name") and e.get("active", True)]

    # Build source map: for each map ID, the map whose graphics to use
    sources = list(range(max_maps))  # default: each map uses its own graphics

    lines = [
        "// Auto-generated map source table. Do not edit.",
        f"#define CUSTOM_MAP_COUNT ({len(active)})",
        "",
        f"static const u16 sManifestMapSources[{max_maps}] {APPEND_RODATA_ATTR} = {{",
    ]
    for mid in range(max_maps):
        lines.append(f"  {sources[mid]},")
    lines.append("};")
    lines.append("")
    lines.append("static const u16 sCustomSourceMaps[] = {")
    for _, mid, _ in active:
        lines.append(f"  {mid},")
    lines.append("};")
    lines.append("")
    lines.append("static const u16 sCustomSlots[] = {")
    for _, _, slot in active:
        lines.append(f"  {slot},")
    lines.append("};")

    (out_dir / "manifest_map_sources.inc").write_text("\n".join(lines) + "\n")


def generate_manifest_connection_overrides(manifest: list, out_dir: pathlib.Path) -> None:
    """Generate connection override include with target map per slot.

    Only emits slots whose target differs from the ROM (custom redirects).
    """
    entries = manifest if isinstance(manifest, list) else manifest.get("entries", [])
    overrides = []

    for entry in entries:
        mid = entry.get("id", -1)
        if mid < 0:
            continue
        rom_targets = _read_rom_connection_targets(mid)
        for conn in entry.get("connections", []):
            slot = conn.get("slot", 0)
            if slot < 0 or slot >= CONNECTION_SLOTS:
                continue
            target_spec = conn.get("target", -1)
            # World-map exits are collision-flag driven (0x4000); MapData
            # "target" holds a region id, not a map id. Never override those.
            if target_spec == "WORLD_MAP":
                continue
            target_map = _resolve_target_id(target_spec, entries)
            if target_map < 0:
                continue
            # Skip when identical to ROM (vanilla maps only — custom maps have no ROM row).
            if rom_targets is not None and slot < len(rom_targets):
                if target_map == rom_targets[slot]:
                    continue
            direction = conn.get("direction", DIRECTION_VALUES.get("DIRECTION_DOWN", 0))
            overrides.append((mid, slot, target_map, direction))

    if not overrides:
        (out_dir / "manifest_connection_overrides.inc").write_text(
            "// No connection overrides\n"
            "#define CUSTOM_CONNECTION_OVERRIDE_COUNT 0\n")
        return

    lines = [
        "// Auto-generated connection overrides. Do not edit.",
        f"#define CUSTOM_CONNECTION_OVERRIDE_COUNT {len(overrides)}",
        "",
        "static const u16 sCustomConnectionOverrideData[CUSTOM_CONNECTION_OVERRIDE_COUNT]"
        f"[4] {APPEND_RODATA_ATTR} = {{",
    ]
    for mid, slot, target, direction in overrides:
        lines.append(f"  {{ {mid}, {slot}, {target}, {direction} }},")
    lines.append("};")

    (out_dir / "manifest_connection_overrides.inc").write_text("\n".join(lines) + "\n")


def _resolve_target_id(target_spec, entries: list) -> int:
    """Convert target specification to numeric map ID.

    Handles: int, string int, manifest entry 'name', manifest entry 'constant',
    or LOCATION_* constant name.
    """
    if isinstance(target_spec, int):
        return target_spec
    if isinstance(target_spec, str):
        try:
            return int(target_spec)
        except ValueError:
            pass
        # Look up by name or constant in manifest
        for e in entries:
            if e.get("name") == target_spec or e.get("constant") == target_spec:
                return e.get("id", -1)
        # Try LOCATION_* constant in overworld.h
        ok_path = ROOT / "include" / "overworld.h"
        text = ok_path.read_text()
        m = re.search(rf'#define\s+{target_spec}\s+(\d+)', text)
        if m:
            return int(m.group(1))
        # Fallback
        print(f"warning: could not resolve target '{target_spec}', using 0")
        return 0
    return -1


def _extract_location_int(name: str) -> int:
    """Extract integer value from a LOCATION_ constant name in overworld.h."""
    ok_path = ROOT / "include" / "overworld.h"
    text = ok_path.read_text()
    m = re.search(rf'#define\s+{name}\s+(\d+)', text)
    if m:
        return int(m.group(1))
    return 0


# ---------------------------------------------------------------------------
# Spawn override generation
# ---------------------------------------------------------------------------

def generate_manifest_spawn_overrides(manifest: list, out_dir: pathlib.Path) -> None:
    """Generate spawn override tables indexed by map ID.

    0xFF = no override (leave InitOverworld's ROM spawn alone).
    Only fills slots that have an explicit spawn in the manifest.
    """
    entries = manifest if isinstance(manifest, list) else manifest.get("entries", [])
    max_maps = max((e.get("id", 0) for e in entries), default=0) + 1
    max_maps = max(max_maps, VANILLA_MAP_COUNT + 1)

    spawn_x = [[SPAWN_NO_OVERRIDE] * CONNECTION_SLOTS for _ in range(max_maps)]
    spawn_y = [[SPAWN_NO_OVERRIDE] * CONNECTION_SLOTS for _ in range(max_maps)]
    spawn_dir = [[SPAWN_NO_OVERRIDE] * CONNECTION_SLOTS for _ in range(max_maps)]
    any_override = False

    for entry in entries:
        mid = entry.get("id", -1)
        if mid < 0 or mid >= max_maps:
            continue

        for conn in entry.get("connections", []):
            slot = conn.get("slot", 0)
            if slot < 0 or slot >= CONNECTION_SLOTS:
                continue
            spawn = conn.get("spawn")
            if not spawn:
                continue
            x = spawn.get("x", SPAWN_NO_OVERRIDE)
            y = spawn.get("y", SPAWN_NO_OVERRIDE)
            dr = spawn.get("dir", SPAWN_NO_OVERRIDE)
            if isinstance(dr, str):
                dr = DIRECTION_VALUES.get(dr, SPAWN_NO_OVERRIDE)
            # ponytail: always record manifest spawn; runtime no-ops when equal to ROM.
            spawn_x[mid][slot] = int(x)
            spawn_y[mid][slot] = int(y)
            spawn_dir[mid][slot] = int(dr)
            any_override = True

    if not any_override:
        (out_dir / "manifest_spawn_overrides.inc").write_text(
            "// No spawn overrides\n"
            f"static const u16 gManifestSpawnOverrideX[][{CONNECTION_SLOTS}] "
            f"{APPEND_RODATA_ATTR} = {{ {{ 0xFF }} }};\n"
            f"static const u16 gManifestSpawnOverrideY[][{CONNECTION_SLOTS}] "
            f"{APPEND_RODATA_ATTR} = {{ {{ 0xFF }} }};\n"
            f"static const u16 gManifestSpawnOverrideDir[][{CONNECTION_SLOTS}] "
            f"{APPEND_RODATA_ATTR} = {{ {{ 0xFF }} }};\n")
        return

    def _rows(table: list[list[int]]) -> list[str]:
        return [
            "  { " + ", ".join(
                f"0x{v:X}" if v == SPAWN_NO_OVERRIDE else str(v) for v in row
            ) + " },"
            for row in table
        ]

    text = "\n".join([
        "// Auto-generated spawn overrides. Do not edit.",
        "// 0xFF = no override (keep InitOverworld position/direction).",
        f"#define CUSTOM_SPAWN_OVERRIDE_COUNT {max_maps}",
        f"static const u16 gManifestSpawnOverrideX[][{CONNECTION_SLOTS}] "
        f"{APPEND_RODATA_ATTR} = {{",
        *_rows(spawn_x),
        "};",
        "",
        f"static const u16 gManifestSpawnOverrideY[][{CONNECTION_SLOTS}] "
        f"{APPEND_RODATA_ATTR} = {{",
        *_rows(spawn_y),
        "};",
        "",
        f"static const u16 gManifestSpawnOverrideDir[][{CONNECTION_SLOTS}] "
        f"{APPEND_RODATA_ATTR} = {{",
        *_rows(spawn_dir),
        "};",
    ]) + "\n"

    (out_dir / "manifest_spawn_overrides.inc").write_text(text)


if __name__ == "__main__":
    sys.exit(main())
