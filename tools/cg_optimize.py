#!/usr/bin/env python3
"""Clean indexed CG pixels before palette/tile export."""

from __future__ import annotations

from cg_remap import rgb888_to_bgr555

CG_WIDTH = 240
CG_HEIGHT = 160


def _bgr555_dist(c1: tuple[int, int, int], c2: tuple[int, int, int]) -> int:
    def quantize(r: int, g: int, b: int) -> tuple[int, int, int]:
        hw = rgb888_to_bgr555(r, g, b)
        return (hw & 0x1F) * 8, ((hw >> 5) & 0x1F) * 8, ((hw >> 10) & 0x1F) * 8

    hr1, hg1, hb1 = quantize(*c1)
    hr2, hg2, hb2 = quantize(*c2)
    return (hr1 - hr2) ** 2 + (hg1 - hg2) ** 2 + (hb1 - hb2) ** 2


def is_blue_palette_color(r: int, g: int, b: int) -> bool:
    return b > r + 5 and b > g - 15


def is_background_cleanup_zone(x: int, y: int, width: int, height: int) -> bool:
    if y < int(height * 0.55) and x < int(width * 0.49):
        return True
    if x < int(width * 0.12) and y < int(height * 0.50):
        return True
    if y > int(height * 0.925):
        return True
    return False


def optimize_cg_pixels(
    pixels: list[int],
    palette: list[int],
    width: int = CG_WIDTH,
    height: int = CG_HEIGHT,
) -> list[int]:
    """Remap warm dither speckles in open background areas to nearest blue tones."""
    if len(pixels) != width * height:
        raise ValueError(f"expected {width * height} pixels, got {len(pixels)}")

    used = set(pixels)
    blue_indices = sorted(
        author
        for author in used
        if is_blue_palette_color(*palette[author * 3 : author * 3 + 3])
    )
    if not blue_indices:
        return pixels[:]

    nearest_blue = {
        author: min(
            blue_indices,
            key=lambda blue: _bgr555_dist(
                tuple(palette[author * 3 : author * 3 + 3]),
                tuple(palette[blue * 3 : blue * 3 + 3]),
            ),
        )
        for author in used
    }

    out = pixels[:]
    for y in range(height):
        for x in range(width):
            if not is_background_cleanup_zone(x, y, width, height):
                continue

            index = y * width + x
            author = out[index]
            r, g, b = palette[author * 3 : author * 3 + 3]
            if is_blue_palette_color(r, g, b):
                continue

            out[index] = nearest_blue[author]

    return out
