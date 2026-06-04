import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
AI_C = ROOT / "src/duel/ai.c"
GENERATOR = ROOT / "tools/generate_ai_action_table.py"
GENERATED = ROOT / "src_custom/generated/ai_action_table_generated.inc"


class AiActionTableTests(unittest.TestCase):
    def test_generated_row_count(self):
        subprocess.run(["python3", str(GENERATOR)], cwd=ROOT, check=True)
        text = GENERATED.read_text(encoding="utf-8")
        self.assertIn("#define AI_ACTION_TABLE_COUNT 946", text)
        self.assertEqual(text.count("sAiActionTable[]"), 1)
        self.assertIn("  { 0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },", text)

    def test_first_discard_action_template(self):
        subprocess.run(["python3", str(GENERATOR)], cwd=ROOT, check=True)
        text = GENERATED.read_text(encoding="utf-8")
        self.assertIn("{ 1, { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00 } },", text)

    def test_generator_requires_ai_source(self):
        self.assertTrue(AI_C.is_file())


if __name__ == "__main__":
    unittest.main()
