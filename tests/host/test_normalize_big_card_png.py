#!/usr/bin/env python3

import struct
import sys
import tempfile
import unittest
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from normalize_big_card_png import (  # noqa: E402
    normalize_png,
    pad_palette_to_64,
    remap_opaque_index_zero,
    trim_palette_to_64,
)


def plte_color_count(path: Path) -> int:
    data = path.read_bytes()
    marker = data.find(b"PLTE")
    if marker < 0:
        return 0
    return struct.unpack(">I", data[marker - 4 : marker])[0] // 3


class NormalizeBigCardPngTests(unittest.TestCase):
    def test_trim_oversized_palette_without_requantizing(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "card.png"
            source = Path(tmp) / "source.png"
            base = Image.new("P", (2, 2))
            base.putpalette([0, 0, 0, 10, 20, 30, 40, 50, 60] + [0, 0, 0] * 61)
            base.putdata([1, 2, 1, 2])
            base.save(source, format="PNG")

            # Pillow keeps Photoshop-style 256-slot PLTE when re-opened and saved.
            oversized = Image.open(source)
            oversized.putpalette(oversized.getpalette() + [0, 0, 0] * (256 - len(oversized.getpalette()) // 3))
            oversized.putdata(list(base.get_flattened_data()))
            oversized.save(path, format="PNG")

            self.assertGreater(plte_color_count(path), 64)
            before_pixels = list(Image.open(path).get_flattened_data())

            normalize_png(path, soften_halos=False, halo_radius=2, body_indices=frozenset(), glow_indices=frozenset())

            after = Image.open(path)
            self.assertEqual(plte_color_count(path), 64)
            self.assertEqual(list(after.get_flattened_data()), before_pixels)
            self.assertEqual(tuple(after.getpalette()[:3]), (0, 0, 0))
            self.assertEqual(tuple(after.getpalette()[3:6]), (10, 20, 30))

    def test_trim_rejects_pixels_above_index_63(self):
        image = Image.new("P", (1, 1))
        palette = [0, 0, 0] + [1, 2, 3] * 255
        image.putpalette(palette)
        image.putdata([64])

        with self.assertRaises(SystemExit):
            trim_palette_to_64(image)

    def test_pad_palette_to_64(self):
        image = Image.new("P", (1, 1))
        image.putpalette([0, 0, 0, 1, 2, 3])
        image.putdata([1])

        added = pad_palette_to_64(image)

        self.assertEqual(added, 62)
        self.assertEqual(len(image.getpalette()) // 3, 64)

    def test_remap_opaque_index_zero(self):
        image = Image.new("P", (2, 1))
        image.putpalette([5, 6, 7, 8, 9, 10] + [0, 0, 0] * 62)
        image.putdata([0, 1])

        remapped = remap_opaque_index_zero(image)

        self.assertEqual(remapped, 1)
        self.assertEqual(list(image.get_flattened_data()), [1, 1])
        self.assertEqual(tuple(image.getpalette()[:3]), (0, 0, 0))


if __name__ == "__main__":
    unittest.main()
