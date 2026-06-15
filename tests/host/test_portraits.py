#!/usr/bin/env python3

import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from normalize_portrait_png import main as normalize_main, normalize_portrait  # noqa: E402
from offset_portrait_8bpp import offset_portrait_bytes  # noqa: E402
from validate_portrait import (  # noqa: E402
    PORTRAIT_DIR,
    discover_portrait_pngs,
    linear_to_tiled_8bpp,
    validate_portrait_png,
    validate_shifted_tiles,
)

PLAYER_PNG = PORTRAIT_DIR / "player.png"


class PortraitValidatorTests(unittest.TestCase):
    def test_player_portrait_passes(self):
        self.assertTrue(PLAYER_PNG.is_file(), f"missing {PLAYER_PNG}")
        errors = validate_portrait_png(PLAYER_PNG)
        self.assertEqual(errors, [], "\n".join(errors))

    def test_discover_portraits_includes_player(self):
        paths = discover_portrait_pngs()
        self.assertIn(PLAYER_PNG, paths)

    def test_rejects_wrong_dimensions(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "small.png"
            Image.new("P", (32, 32)).save(path)
            errors = validate_portrait_png(path)
        self.assertTrue(any("64x64" in message for message in errors))

    def test_rejects_black_not_at_index_zero(self):
        image = Image.new("P", (64, 64))
        palette = [128, 64, 32] * 256
        palette[0:3] = [255, 0, 0]
        palette[63 * 3 : 63 * 3 + 3] = [0, 0, 0]
        image.putpalette(palette)
        pixels = [0] * 32 + [63] * (64 * 64 - 32)
        image.putdata(pixels)

        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "bad.png"
            image.save(path)
            errors = validate_portrait_png(path)

        self.assertTrue(errors, errors)
        self.assertTrue(
            any(
                "index 0 must be black" in message or "reserve index 0" in message
                for message in errors
            ),
            errors,
        )

    def test_offset_keeps_zero_and_maps_colors(self):
        tiled = bytes([0, 1, 63, 0] + [0] * (64 * 64 - 4))
        shifted = offset_portrait_bytes(tiled)
        self.assertEqual(shifted[0], 0)
        self.assertEqual(shifted[1], 0xC1)
        self.assertEqual(shifted[2], 0xFF)
        self.assertNotIn(0xC0, shifted[:4])

    def test_shifted_tile_rules(self):
        pixels = [0] * (64 * 64)
        pixels[0] = 1
        pixels[1] = 63
        shifted = offset_portrait_bytes(linear_to_tiled_8bpp(pixels))
        self.assertEqual(validate_shifted_tiles(shifted, "fixture"), [])

    def test_shifted_rejects_opaque_zero_slot(self):
        pixels = [0] * (64 * 64)
        shifted = bytearray(offset_portrait_bytes(linear_to_tiled_8bpp(pixels)))
        shifted[100] = 0xC0
        errors = validate_shifted_tiles(bytes(shifted), "fixture")
        self.assertTrue(any("0xC0" in message for message in errors))

    def test_normalize_directory_in_place(self):
        image = Image.new("P", (64, 64))
        palette = [128, 64, 32] * 256
        palette[0:3] = [255, 0, 0]
        palette[63 * 3 : 63 * 3 + 3] = [0, 0, 0]
        image.putpalette(palette)
        image.putdata([63] * (64 * 64))

        with tempfile.TemporaryDirectory() as tmp:
            directory = Path(tmp)
            path = directory / "portrait.png"
            image.save(path)
            with patch.object(sys, "argv", ["normalize_portrait_png.py", str(directory)]):
                self.assertEqual(normalize_main(), 0)
            fixed = Image.open(path)
            self.assertEqual(fixed.getpalette()[0:3], [0, 0, 0])
            self.assertEqual(list(fixed.get_flattened_data()).count(0), 64 * 64)

    def test_normalize_swaps_black_to_index_zero(self):
        image = Image.new("P", (64, 64))
        palette = [128, 64, 32] * 256
        palette[0:3] = [255, 0, 0]
        palette[63 * 3 : 63 * 3 + 3] = [0, 0, 0]
        image.putpalette(palette)
        image.putdata([63] * (64 * 64))

        self.assertTrue(normalize_portrait(image))
        self.assertEqual(image.getpalette()[0:3], [0, 0, 0])
        pixels = list(image.get_flattened_data())
        self.assertEqual(pixels.count(0), len(pixels))


if __name__ == "__main__":
    unittest.main()
