#!/usr/bin/env python3
"""Convert MP4 intro videos to GBA frame blobs for the intro video player.

Pipeline:
  1. ffmpeg decodes MP4, extracts 256-color indexed PNG frames
  2. Cached in src_custom/assets/videos/frames/ so ffmpeg runs once
  3. Each cached PNG is converted to 8bpp GBA tile data
  4. Output: a single binary blob + a generated C include with extern symbols

8bpp (256-color) gives full quality per frame but uses 0xA000 bytes/frame.

Requires ffmpeg in PATH. Gracefully handles missing MP4s (generates stub).
"""

from __future__ import annotations

import argparse
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VIDEO_DIR = ROOT / "src_custom" / "assets" / "videos"
FRAMES_DIR = VIDEO_DIR / "frames"
GENERATED_INC = ROOT / "src_custom" / "generated" / "video_assets_generated.inc"

GBA_WIDTH = 256        # Canvas width (standard GBA BG width, 32 tiles)
GBA_HEIGHT = 160
VIDEO_WIDTH = 240       # Active video content width; padded to GBA_WIDTH with 16px black
TILES_PER_FRAME = (GBA_WIDTH // 8) * (GBA_HEIGHT // 8)  # 640
RAW_FRAME_BYTES = TILES_PER_FRAME * 64  # 40960 (0xA000, 8bpp: 1 pixel/byte, 64 bytes/tile)
PALETTE_COLORS = 256
PALETTE_BYTES = PALETTE_COLORS * 2  # 512
SCREENBLOCK_BYTES = 0
BYTES_PER_LINE = 12


def _find_ffmpeg() -> str:
    import shutil
    path = shutil.which("ffmpeg")
    if path:
        return path
    try:
        import imageio_ffmpeg
        return imageio_ffmpeg.get_ffmpeg_exe()
    except Exception:
        sys.exit("error: ffmpeg not found. Install ffmpeg or imageio-ffmpeg (pip install imageio-ffmpeg) to encode videos.")


def frame_cache_path(mp4_stem: str, frame_idx: int) -> Path:
    """Return path for a cached 256-color indexed frame PNG."""
    return FRAMES_DIR / f"{mp4_stem}_256c" / f"frame_{frame_idx:04d}.png"


def extract_frames(mp4_path: Path, fps_divider: int, ffmpeg_bin: str,
                   max_frames: int = 0) -> list[tuple[bytes, bytes]]:
    """Extract frames from MP4 as (8bpp_tiles, gba_palette) tuples.

    Caches extracted 256-color indexed PNGs in FRAMES_DIR/<mp4_stem>_256c/.
    If all cached frames exist, skips ffmpeg entirely.
    """
    mp4_stem = mp4_path.stem
    cache_dir = FRAMES_DIR / f"{mp4_stem}_256c"

    # Check if we already have cached frames
    if cache_dir.is_dir():
        cached = sorted(cache_dir.glob("frame_*.png"))
        if cached and (max_frames == 0 or len(cached) >= max_frames):
            n = len(cached) if max_frames == 0 else min(len(cached), max_frames)
            print(f"encode_video: using {n} cached frames from {cache_dir.relative_to(ROOT)}/")
            palette_data = _read_palette_from_frame_png(cached[0])
            frames: list[tuple[bytes, bytes]] = []
            for png in cached[:n]:
                tiles = _indexed_png_to_8bpp_tiles(png)
                frames.append((tiles, palette_data))
            return frames

    # Extract via ffmpeg
    extract_fps = 60 // fps_divider
    cache_dir.mkdir(parents=True, exist_ok=True)

    palette_png = cache_dir / "palette.png"
    palettegen_args = [
        ffmpeg_bin, "-i", str(mp4_path),
        "-vf", f"fps={extract_fps},scale={VIDEO_WIDTH}:{GBA_HEIGHT}:flags=bilinear,"
               f"palettegen=max_colors=256:stats_mode=diff",
        "-y", str(palette_png),
    ]
    subprocess.run(palettegen_args, capture_output=True, check=True)

    paletteuse_args = [
        ffmpeg_bin,
        "-i", str(mp4_path),
        "-i", str(palette_png),
        "-filter_complex",
        f"fps={extract_fps},scale={VIDEO_WIDTH}:{GBA_HEIGHT}:flags=bilinear"
        f"[s];[s][1:v]paletteuse=dither=bayer:bayer_scale=3",
        "-pix_fmt", "pal8",
    ]
    if max_frames > 0:
        paletteuse_args.extend(["-vframes", str(max_frames)])
    paletteuse_args.extend(["-y", str(cache_dir / "frame_%04d.png")])
    subprocess.run(paletteuse_args, capture_output=True, check=True)

    pngs = sorted(cache_dir.glob("frame_*.png"))
    if not pngs:
        raise SystemExit(f"error: ffmpeg produced no frames from {mp4_path}")

    frame_count = min(len(pngs), max_frames) if max_frames > 0 else len(pngs)
    print(f"encode_video: extracted {frame_count} frames to {cache_dir.relative_to(ROOT)}/")

    palette_data = _read_palette_from_png(palette_png)
    if len(palette_data) != PALETTE_BYTES:
        palette_data = palette_data + b"\x00" * (PALETTE_BYTES - len(palette_data))

    frames = []
    for png in pngs[:frame_count]:
        tiles = _indexed_png_to_8bpp_tiles(png)
        frames.append((tiles, palette_data))

    return frames


def _read_palette_from_png(png_path: Path) -> bytes:
    """Read palette from a palettegen output PNG and convert to GBA 15-bit BGR."""
    data = png_path.read_bytes()

    plte_idx = data.find(b"PLTE")
    if plte_idx >= 0:
        pal_len = struct.unpack_from(">I", data, plte_idx - 4)[0]
        pal_start = plte_idx + 4
        pal_rgb = data[pal_start:pal_start + pal_len]
        gba_palette = bytearray(PALETTE_BYTES)
        num_colors = min(pal_len // 3, PALETTE_COLORS)
        for i in range(num_colors):
            r = pal_rgb[i * 3]
            g = pal_rgb[i * 3 + 1]
            b = pal_rgb[i * 3 + 2]
            gba_color = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)
            struct.pack_into("<H", gba_palette, i * 2, gba_color)
        return bytes(gba_palette)

    # Fallback: RGBA palettegen output
    ihdr_idx = data.find(b"IHDR")
    if ihdr_idx < 0:
        return b"\x00" * PALETTE_BYTES

    width = struct.unpack_from(">I", data, ihdr_idx + 4)[0]
    height = struct.unpack_from(">I", data, ihdr_idx + 8)[0]
    pixel_count = width * height
    import zlib
    idat_idx = data.find(b"IDAT")
    if idat_idx < 0:
        return b"\x00" * PALETTE_BYTES
    chunk_len = struct.unpack_from(">I", data, idat_idx - 4)[0]
    raw_pixels = zlib.decompress(data[idat_idx + 4:idat_idx + 4 + chunk_len])
    row_len = width * 4 + 1
    gba_palette = bytearray(PALETTE_BYTES)
    num_colors = min(pixel_count, PALETTE_COLORS)
    for i in range(num_colors):
        row = i // width
        col = i % width
        px_offset = row * row_len + 1 + col * 4
        if px_offset + 3 > len(raw_pixels):
            break
        r = raw_pixels[px_offset]
        g = raw_pixels[px_offset + 1]
        b = raw_pixels[px_offset + 2]
        gba_color = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)
        struct.pack_into("<H", gba_palette, i * 2, gba_color)

    return bytes(gba_palette)


def _read_palette_from_frame_png(png_path: Path) -> bytes:
    """Read the PLTE chunk from a cached indexed frame PNG, convert to GBA 15-bit BGR."""
    data = png_path.read_bytes()
    plte_idx = data.find(b"PLTE")
    if plte_idx < 0:
        return b"\x00" * PALETTE_BYTES
    pal_len = struct.unpack_from(">I", data, plte_idx - 4)[0]
    pal_start = plte_idx + 4
    pal_rgb = data[pal_start:pal_start + pal_len]
    gba_palette = bytearray(PALETTE_BYTES)
    num_colors = min(pal_len // 3, PALETTE_COLORS)
    for i in range(num_colors):
        r = pal_rgb[i * 3]
        g = pal_rgb[i * 3 + 1]
        b = pal_rgb[i * 3 + 2]
        gba_color = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)
        struct.pack_into("<H", gba_palette, i * 2, gba_color)
    return bytes(gba_palette)


def _indexed_png_to_8bpp_tiles(png_path: Path) -> bytes:
    """Read an indexed 256-color PNG and convert to 8bpp GBA tile data.

    The PNG may be VIDEO_WIDTH (240) wide; right-padded to GBA_WIDTH (256)
    with palette index 0 (black) before tiling.

    Returns exactly RAW_FRAME_BYTES (0xA000) bytes.
    One byte per pixel, stored tile-major (64 bytes per 8x8 tile).
    """
    raw = png_path.read_bytes()
    ih = raw.find(b"IHDR")
    if ih < 0:
        raise ValueError(f"no IHDR in {png_path.name}")
    w = struct.unpack_from(">I", raw, ih + 4)[0]
    h = struct.unpack_from(">I", raw, ih + 8)[0]
    if h != GBA_HEIGHT:
        raise ValueError(f"expected {GBA_HEIGHT} rows, got {h}")
    if w > GBA_WIDTH:
        raise ValueError(f"png width {w} exceeds GBA canvas {GBA_WIDTH}")

    import zlib
    comp = bytearray()
    pos = ih + 4 + 13 + 4
    while pos < len(raw):
        cl = struct.unpack_from(">I", raw, pos)[0]
        ct = raw[pos + 4:pos + 8]
        if ct == b"IEND":
            break
        if ct == b"IDAT":
            comp.extend(raw[pos + 8:pos + 8 + cl])
        pos += 12 + cl
    dec = zlib.decompress(bytes(comp))

    # De-filter into flat pixel buffer, right-padded to GBA_WIDTH
    pixel = bytearray(GBA_WIDTH * GBA_HEIGHT)
    ro = 0
    for y in range(GBA_HEIGHT):
        f = dec[ro]
        rd = list(dec[ro + 1:ro + 1 + w])
        if f == 1:
            for x in range(1, w):
                rd[x] = (rd[x] + rd[x - 1]) & 0xFF
        dst = y * GBA_WIDTH
        pixel[dst:dst + w] = rd
        ro += 1 + w

    # Convert to tile-major 8bpp: each tile = 8*8 = 64 bytes
    td = bytearray(RAW_FRAME_BYTES)
    for ty in range(GBA_HEIGHT // 8):
        for tx in range(GBA_WIDTH // 8):
            ti = ty * (GBA_WIDTH // 8) + tx
            for row in range(8):
                sy = ty * 8 + row
                src_start = sy * GBA_WIDTH + tx * 8
                dst_start = ti * 64 + row * 8
                td[dst_start:dst_start + 8] = pixel[src_start:src_start + 8]
    return bytes(td)


def _fix_gbagfx_header(data: bytes) -> bytes:
    """Convert gbagfx LZSS header to GBA BIOS format.

    gbagfx header:  byte0=0x10 (type), bytes1-3=24bit LE decompressed size
    GBA BIOS header: u32 with bit31=1, bits23-0=decompressed size
    """
    if len(data) >= 4 and data[0] == 0x10:
        size = data[1] | (data[2] << 8) | (data[3] << 16)
        return struct.pack("<I", size | 0x80000000) + data[4:]
    return data


def lzss_compress(data: bytes) -> bytes:
    """Compress data using the toolchain's gbagfx LZSS compressor if available."""
    gbagfx = ROOT / "tools" / "gbagfx" / "gbagfx"
    if gbagfx.is_file():
        with tempfile.TemporaryDirectory() as tmpdir:
            tmp = Path(tmpdir)
            raw = tmp / "raw.bin"
            lz = tmp / "out.lz"
            raw.write_bytes(data)
            result = subprocess.run(
                [str(gbagfx), str(raw), str(lz)],
                capture_output=True, timeout=30,
            )
            if result.returncode == 0 and lz.is_file() and lz.stat().st_size > 0:
                return _fix_gbagfx_header(lz.read_bytes())

    return _lzss_compress_python(data)


def _lzss_compress_python(data: bytes) -> bytes:
    """LZSS compressor producing GBA-compatible LZ77 format.

    GBA LZ77 header: u32 (uncompressed_size | 0x80000000).
    Compressed blocks: 1 flag byte + up to 8 items (literal byte or u16 ref).
    """
    in_len = len(data)
    out = bytearray()
    out.extend(struct.pack("<I", in_len | 0x80000000))

    i = 0
    while i < in_len:
        flag = 0
        block = bytearray()
        for bit in range(8):
            if i >= in_len:
                block.append(0)
                continue
            match_positions = []
            search_pos = i - 1
            limit = max(0, i - 0x1000)
            while search_pos >= limit:
                if data[search_pos] == data[i]:
                    match_positions.append(search_pos)
                search_pos -= 1
            best_off = 0
            best_len = 0
            for mp in match_positions:
                length = 1
                while length < 18 and i + length < in_len and data[mp + length] == data[i + length]:
                    length += 1
                if length > best_len:
                    best_len = length
                    best_off = i - mp
            if best_len >= 3:
                flag |= 1 << (7 - bit)
                enc = ((best_len - 3) << 12) | ((best_off - 1) & 0xFFF)
                block.extend(struct.pack("<H", enc))
                i += best_len
            else:
                block.append(data[i])
                i += 1
        out.append(flag)
        out.extend(block)
    return bytes(out)


def build_video_blob(frames: list[tuple[bytes, bytes]], fps_divider: int) -> bytes:
    """Build the binary blob for one video (raw 8bpp tiles, 256-color palette).

    Layout:
      u16 frame_count
      u8  fps_divider
      u8  reserved
      palette (PALETTE_BYTES = 512 bytes)
      frame index (frame_count * 8 bytes): u32 offset, u16 size, u16 reserved
      ... raw 8bpp tile data (RAW_FRAME_BYTES = 0xA000 per frame)
    """
    frame_count = len(frames)

    palette_data = frames[0][1] if frames else b""
    if len(palette_data) < PALETTE_BYTES:
        palette_data = palette_data + b"\x00" * (PALETTE_BYTES - len(palette_data))

    header_size = 4 + PALETTE_BYTES
    index_size = frame_count * 8
    data_start = header_size + index_size

    blob = bytearray()
    blob.extend(struct.pack("<H", frame_count))
    blob.extend(struct.pack("<B", fps_divider))
    blob.extend(b"\x00")
    blob.extend(palette_data[:PALETTE_BYTES])

    offset = data_start
    for _ in frames:
        blob.extend(struct.pack("<IHH", offset, RAW_FRAME_BYTES, 0))
        offset += RAW_FRAME_BYTES

    for tiles, _pal in frames:
        blob.extend(tiles)

    return bytes(blob)

    return bytes(blob)


def generate_inc(video_blobs: list[tuple[str, bytes]], gen_dir: Path) -> str:
    """Generate the C include file with `.incbin` assembly for each video blob."""
    for idx, (stem, blob) in enumerate(video_blobs):
        bin_path = gen_dir / f"video{idx}.bin"
        bin_path.write_bytes(blob)

    lines = [
        "/* Generated by tools/encode_video.py. Do not edit. */",
        "",
        "#define VIDEO_COUNT {}".format(len(video_blobs)),
        "",
    ]

    for idx, (stem, _blob) in enumerate(video_blobs):
        symbol = f"sVideo{idx}Data"
        bin_rel = gen_dir.relative_to(ROOT) / f"video{idx}.bin"
        lines.append(f'__asm__(".section .append_assets, \\"a\\"\\n"')
        lines.append(f'        ".global {symbol}\\n"')
        lines.append(f'        ".balign 4\\n"')
        lines.append(f'        "{symbol}:\\n"')
        lines.append(f'        ".incbin \\"{bin_rel}\\"\\n"')
        lines.append(f'        ".size {symbol}, . - {symbol}\\n"')
        lines.append(f'        ".previous\\n");')
        lines.append(f"extern const u8 {symbol}[];")
        lines.append("")

    lines.append("struct VideoAsset {")
    lines.append("    const u8 *data;")
    lines.append("    u16 totalFrames;")
    lines.append("    u8 fpsDivider;")
    lines.append("};")
    lines.append("")
    lines.append("const struct VideoAsset sVideoAssets[VIDEO_COUNT] APPEND_RODATA = {")
    for idx, (stem, blob) in enumerate(video_blobs):
        frame_count = struct.unpack_from("<H", blob, 0)[0]
        fps_div = struct.unpack_from("<B", blob, 2)[0]
        lines.append(f"    {{ .data = sVideo{idx}Data, .totalFrames = {frame_count}, .fpsDivider = {fps_div} }},")
    lines.append("};")
    lines.append("")
    return "\n".join(lines)


def generate_no_videos_inc() -> str:
    return (
        "/* Generated by tools/encode_video.py. Do not edit. */\n"
        "#define VIDEO_COUNT 0\n"
        "struct VideoAsset { const u8 *data; u16 totalFrames; u8 fpsDivider; };\n"
        "const struct VideoAsset sVideoAssets[0] APPEND_RODATA = {};\n"
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--inc-out",
        type=Path,
        default=GENERATED_INC,
        help=f"Generated asset include (default: relative to root: {GENERATED_INC.relative_to(ROOT)})",
    )
    parser.add_argument(
        "--fps-divider",
        type=int,
        default=4,
        help="VBlank frames per video frame (default: 4 = 15fps)",
    )
    parser.add_argument(
        "--max-frames",
        type=int,
        default=300,
        help="Maximum number of frames to encode (default: 300 = 20s at 15fps).",
    )
    parser.add_argument(
        "--re-extract",
        action="store_true",
        help="Force re-extraction from MP4 even if cached frames exist",
    )
    args = parser.parse_args()

    if not VIDEO_DIR.is_dir() or not list(VIDEO_DIR.glob("*.mp4")):
        args.inc_out.parent.mkdir(parents=True, exist_ok=True)
        args.inc_out.write_text(generate_no_videos_inc())
        print("encode_video: no MP4s found, generated stub (VIDEO_COUNT=0)")
        return 0

    ffmpeg_bin = _find_ffmpeg()

    import zlib  # noqa: F401

    mp4s = sorted(VIDEO_DIR.glob("*.mp4"))
    video_blobs: list[tuple[str, bytes]] = []
    for mp4 in mp4s:
        print(f"encode_video: processing {mp4.name}...")
        frames = extract_frames(mp4, args.fps_divider, ffmpeg_bin, max_frames=args.max_frames)
        if not frames:
            print(f"encode_video: warning: {mp4.name} produced no frames, skipping")
            continue
        blob = build_video_blob(frames, args.fps_divider)
        video_blobs.append((mp4.stem, blob))
        pct = len(blob) / (10 * 1024 * 1024) * 100
        print(f"encode_video: {mp4.name}: {len(frames)} frames, {len(blob)} bytes blob ({pct:.0f}% of 10MB budget)")
        if len(blob) > 10 * 1024 * 1024:
            print("encode_video: WARNING: blob exceeds 10MB, ROM may exceed 32MB limit", file=sys.stderr)

    inc_text = generate_inc(video_blobs, GENERATED_INC.parent)
    args.inc_out.parent.mkdir(parents=True, exist_ok=True)
    args.inc_out.write_text(inc_text)
    print(f"encode_video: ok ({len(video_blobs)} video(s))")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
