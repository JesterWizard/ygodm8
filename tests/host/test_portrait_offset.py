import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "tools" / "offset_portrait_8bpp.py"


class PortraitOffsetTests(unittest.TestCase):
    def test_keeps_zero_and_offsets_nonzero(self):
        src = bytes([0, 1, 63, 0] + [0] * (64 * 64 - 4))

        with tempfile.TemporaryDirectory() as tmp:
            src_path = Path(tmp) / "in.8bpp"
            dst_path = Path(tmp) / "out.8bpp"
            src_path.write_bytes(src)
            subprocess.run(
                ["python3", str(SCRIPT), str(src_path), str(dst_path)],
                check=True,
            )
            out = dst_path.read_bytes()

        self.assertEqual(out[0], 0)
        self.assertEqual(out[1], 0xC1)
        self.assertEqual(out[2], 0xFF)
        self.assertEqual(out[3], 0)
        self.assertNotIn(0xC0, out[:4])


if __name__ == "__main__":
    unittest.main()
