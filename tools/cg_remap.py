#!/usr/bin/env python3
"""Shared CG palette-index remapping for the event CG pipeline."""

from __future__ import annotations

PALETTE_OFFSET = 32
MAX_CG_AUTHOR_INDEX = 223
MAX_CG_COLORS = MAX_CG_AUTHOR_INDEX + 1


def rgb888_to_bgr555(r: int, g: int, b: int) -> int:
    return ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3)


def build_cg_index_remap(used_indices: list[int] | set[int]) -> dict[int, int]:
    used = sorted(set(used_indices))
    if not used:
        return {}

    max_author = used[-1]
    if max_author > MAX_CG_AUTHOR_INDEX:
        raise ValueError(
            f"CG uses palette index {max_author}; max supported author index is "
            f"{MAX_CG_AUTHOR_INDEX}"
        )
    if len(used) > MAX_CG_COLORS:
        raise ValueError(
            f"CG uses {len(used)} palette indices; max supported is {MAX_CG_COLORS}"
        )

    return {author: PALETTE_OFFSET + slot for slot, author in enumerate(used)}


def remap_cg_bytes(data: bytes, remap: dict[int, int]) -> bytes:
    unknown = sorted(set(data) - set(remap))
    if unknown:
        raise ValueError(f"tile bytes use unknown palette indices: {unknown[:8]}")
    return bytes(remap[pixel] for pixel in data)
