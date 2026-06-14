import re
import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
AI_C = ROOT / "src/duel/ai.c"
AI_ACTIONS_H = ROOT / "include/ai_actions.h"
GENERATOR = ROOT / "tools/generate_ai_action_table.py"
GENERATED = ROOT / "src_custom/generated/ai_action_table_generated.inc"


def load_ai_c_enum():
    text = AI_C.read_text(encoding="utf-8")
    match = re.search(r"\benum\s+AI_Action\s*\{(.*?)\};", text, re.DOTALL)
    if not match:
        raise AssertionError("enum AI_Action not found in src/duel/ai.c")
    constants = {}
    value = 0
    for raw_item in match.group(1).split(","):
        item = re.sub(r"//.*", "", raw_item).strip()
        if not item:
            continue
        name, _, explicit = item.partition("=")
        name = name.strip()
        if explicit:
            value = int(explicit.strip().split()[0], 0)
        constants[name] = value
        if not explicit:
            value += 1
    return constants


def load_ai_actions_h():
    text = AI_ACTIONS_H.read_text(encoding="utf-8")
    return {
        match.group(1): int(match.group(2), 0)
        for match in re.finditer(
            r"#define\s+(AI_ACTION_\w+)\s+(0x[0-9A-Fa-f]+|\d+)", text
        )
    }


# ai.c still names the perm face-down attack slots AI_ACTION_36/37.
AI_ACTION_ENUM_ALIASES = {
    "AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_NO_TRAP": "AI_ACTION_36",
    "AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_WITH_TRAP": "AI_ACTION_37",
}


class AiActionTableTests(unittest.TestCase):
    def test_ai_actions_h_matches_ai_c_enum(self):
        ai_c = load_ai_c_enum()
        header = load_ai_actions_h()
        for name, expected in header.items():
            ai_c_name = AI_ACTION_ENUM_ALIASES.get(name, name)
            self.assertIn(ai_c_name, ai_c, msg=f"{name} missing from ai.c enum")
            self.assertEqual(
                ai_c[ai_c_name],
                expected,
                msg=f"{name}: ai.c={ai_c[ai_c_name]} header={expected}",
            )

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
