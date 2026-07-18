"""Guard: manifest collision reads real ROM grids, not hardcoded garbage offsets."""
from __future__ import annotations

import importlib.util
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def _load_build_custom_maps():
    path = ROOT / "tools" / "build_custom_maps.py"
    spec = importlib.util.spec_from_file_location("build_custom_maps", path)
    mod = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod


class TestCustomMapsCollision(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.bcm = _load_build_custom_maps()

    def test_read_base_collision_uses_pointer_table(self):
        if not (ROOT / "baserom.gba").exists():
            self.skipTest("baserom.gba missing")
        grid = self.bcm._read_base_collision(0)
        self.assertIsNotNone(grid)
        self.assertEqual(len(grid), 120 * 80)
        # Vanilla border walls are 1; the old hardcoded offset returned 0x4153 ("SAL ").
        self.assertEqual(grid[0], 1)
        house = self.bcm._read_base_collision(9)
        self.assertEqual(house[38 * 120 + 59], 0x1000)

    def test_generated_spawn_unused_slots_are_ff(self):
        text = (ROOT / "src_custom/generated/maps/manifest_spawn_overrides.inc").read_text()
        self.assertIn("{ 59, 0xFF, 0xFF, 0xFF, 0xFF }", text)

    def test_no_vanilla_collision_overrides_by_default(self):
        text = (ROOT / "src_custom/generated/maps/manifest_collision_overrides.inc").read_text()
        # Only maps with custom connection rects (e.g. map 11 → graveyard) emit overrides.
        self.assertIn("CUSTOM_COLLISION_OVERRIDE_COUNT 1", text)
        self.assertIn("0x2100", text)  # slot 1 | connected-map bit

    def test_graveyard_collision_has_exit(self):
        text = (ROOT / "src_custom/generated/maps/collision_graveyard.inc").read_text()
        self.assertIn("0x2000", text)
        # Bottom exit strip [20,79,100,1] — red-line width across the south edge.
        vals = [int(x, 16) for x in __import__("re").findall(r"0x([0-9a-fA-F]+)", text)]
        row79 = vals[79 * 120:80 * 120]
        exits = [i for i, v in enumerate(row79) if v & 0x2000]
        self.assertEqual(exits[0], 20)
        self.assertEqual(exits[-1], 119)
        self.assertEqual(len(exits), 100)

    def test_lz77_size_header_is_little_endian(self):
        # Size 0xBA40 (745 tiles) exposed the old big-endian header bug.
        data = bytes(range(256)) * 186 + bytes(range(64))  # 47680 bytes
        self.assertEqual(len(data), 0xBA40)
        blob = self.bcm.lz77_compress(data)
        self.assertEqual(blob[0], 0x10)
        size = blob[1] | (blob[2] << 8) | (blob[3] << 16)
        self.assertEqual(size, len(data))

    def test_lz77_roundtrips_under_bios_disp_plus_one(self):
        # BIOS: Disp = stored + 1. Storing raw distance wrote OOB zeros → stripes.
        data = b"AAAA" + b"BBBB" + b"AAAA" + bytes(range(64)) * 40
        blob = self.bcm.lz77_compress(data)
        size = blob[1] | (blob[2] << 8) | (blob[3] << 16)
        self.assertEqual(size, len(data))
        dst = bytearray()
        pos = 4
        while len(dst) < size:
            flags = blob[pos]
            pos += 1
            for i in range(8):
                if len(dst) >= size:
                    break
                if flags & (0x80 >> i):
                    b1, b2 = blob[pos], blob[pos + 1]
                    pos += 2
                    length = (b1 >> 4) + 3
                    disp = (((b1 & 0x0F) << 8) | b2) + 1
                    for _ in range(length):
                        dst.append(dst[-disp])
                else:
                    dst.append(blob[pos])
                    pos += 1
        self.assertEqual(bytes(dst[:size]), data)

    def test_tileset_prefer_roof_keeps_roof_exact(self):
        zero = b"\x00" * 64
        roof_a = b"\x14" * 64
        roof_b = b"\x15" * 64
        ground = [b"\x20" * 64] * 10 + [b"\x21" * 64] * 3
        roof = [zero, roof_a, roof_b, zero]
        ts, g_remap, r_remap = self.bcm._tileset_prefer_roof(ground, roof, 4)
        self.assertEqual(len(ts) // 64, 4)
        self.assertEqual(ts[:64], zero)
        # Roof tiles resolve exactly
        for tb, idx in zip(roof, r_remap):
            self.assertEqual(ts[idx * 64:(idx + 1) * 64], tb)

    def test_stamp_roof_behind_sprites_sets_passable_bit(self):
        from PIL import Image
        img = Image.new("P", (256, 256), 0)
        img.putpalette([0] * 768)
        # Opaque blob covering collision cell (10, 20) → pixels 28..29, 48..49
        for y in range(48, 50):
            for x in range(28, 30):
                img.putpixel((x, y), 1)
        flat = [0] * (120 * 80)
        n = self.bcm._stamp_roof_behind_sprites(flat, img)
        self.assertGreater(n, 0)
        self.assertEqual(flat[20 * 120 + 10] & 0x1000, 0x1000)


if __name__ == "__main__":
    unittest.main()
