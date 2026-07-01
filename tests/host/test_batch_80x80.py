#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from batch_80x80 import process_image  # noqa: E402


class Batch80x80Tests(unittest.TestCase):
    def test_palette_index_zero_is_transparent(self):
        source = Image.new("RGBA", (8, 8), (0, 0, 0, 0))
        source.paste((40, 80, 120, 255), (2, 2, 6, 6))
        source.paste((0, 0, 0, 255), (3, 3, 5, 5))  # opaque black must not use index 0

        result = process_image(source, (8, 8), 64)
        pixels = list(result.get_flattened_data())
        palette = result.getpalette()

        self.assertEqual(tuple(palette[:3]), (0, 0, 0))
        self.assertGreater(pixels.count(0), 0)
        self.assertTrue(all(pixel == 0 or pixel > 0 for pixel in pixels))
        self.assertEqual(result.info.get("transparency"), 0)
        self.assertEqual(len(palette) // 3, 64)

    def test_opaque_pixels_never_use_index_zero(self):
        source = Image.new("RGBA", (4, 4), (10, 20, 30, 255))

        result = process_image(source, (4, 4), 64)
        pixels = list(result.get_flattened_data())

        self.assertNotIn(0, pixels)
        self.assertEqual(tuple(result.getpalette()[:3]), (0, 0, 0))


if __name__ == "__main__":
    unittest.main()
