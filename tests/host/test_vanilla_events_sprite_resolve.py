import tempfile
import unittest
from pathlib import Path

from tools.vanilla_events import (
    ObjectSlotState,
    append_event_macro,
    compile_linear_map_event,
    load_script_constants,
    parse_macro_calls,
)


class VanillaEventsSpriteResolveTests(unittest.TestCase):
    def test_resolves_sprite_to_slot_after_load_sprite(self) -> None:
        path = Path("events/scripts/map_09_state_01.c")
        constants = load_script_constants(path)
        calls = [
            ("LOAD_SPRITE", ["14", "SPRITE_JOEY"]),
            ("MOVE_OBJECT", ["SPRITE_JOEY", "DIRECTION_LEFT", "32", "0"]),
        ]
        entry = compile_linear_map_event("map_09_state_01", calls, path, constants)
        self.assertEqual(entry.raw_bytes[2], 14)

    def test_errors_when_sprite_is_ambiguous(self) -> None:
        path = Path("events/scripts/map_57_state_03.c")
        constants = load_script_constants(path)
        calls = [
            ("LOAD_SPRITE", ["2", "SPRITE_BIG_FIVE"]),
            ("LOAD_SPRITE", ["3", "SPRITE_BIG_FIVE"]),
            ("MOVE_OBJECT", ["SPRITE_BIG_FIVE", "DIRECTION_LEFT", "0", "0"]),
        ]
        with self.assertRaisesRegex(ValueError, "multiple slots"):
            compile_linear_map_event("map_57_state_03", calls, path, constants)

    def test_errors_when_sprite_not_loaded(self) -> None:
        path = Path("events/scripts/map_09_state_01.c")
        constants = load_script_constants(path)
        calls = [("MOVE_OBJECT", ["SPRITE_JOEY", "DIRECTION_LEFT", "0", "0"])]
        with self.assertRaisesRegex(ValueError, "no prior LOAD_SPRITE"):
            compile_linear_map_event("map_09_state_01", calls, path, constants)

    def test_mid_script_sprite_reassignment_updates_resolution(self) -> None:
        path = Path("events/scripts/map_57_state_03.c")
        constants = load_script_constants(path)
        calls = [
            ("LOAD_SPRITE", ["5", "SPRITE_BIG_FIVE"]),
            ("LOAD_SPRITE", ["5", "SPRITE_ROBOTIC_KNIGHT"]),
            ("MOVE_OBJECT", ["SPRITE_ROBOTIC_KNIGHT", "DIRECTION_DOWN", "0", "0"]),
        ]
        entry = compile_linear_map_event("map_57_state_03", calls, path, constants)
        self.assertEqual(entry.raw_bytes[6], 5)

    def test_numeric_object_ids_remain_slots(self) -> None:
        raw_bytes: list[int] = []
        slot_state = ObjectSlotState()
        slot_state.assign(4, 999)
        append_event_macro(
            "MOVE_OBJECT",
            ["4", "DIRECTION_LEFT", "0", "0"],
            raw_bytes,
            Path("events/scripts/map_09_state_01.c"),
            None,
            slot_state,
        )
        self.assertEqual(raw_bytes[2], 4)

    def test_reaction_resolves_sprite_mask(self) -> None:
        path = Path("events/scripts/map_09_state_01.c")
        constants = load_script_constants(path)
        calls = [
            ("LOAD_SPRITE", ["14", "SPRITE_JOEY"]),
            ("REACTION", ["REACTION_ANGRY", "SPRITE_JOEY"]),
        ]
        entry = compile_linear_map_event("map_09_state_01", calls, path, constants)
        self.assertEqual(entry.raw_bytes[-2], 64)  # (1 << 14) >> 8
        self.assertEqual(entry.raw_bytes[-1], 0)

    def test_reaction_resolves_combined_sprite_mask(self) -> None:
        path = Path("events/scripts/map_09_state_01.c")
        constants = load_script_constants(path)
        calls = [
            ("LOAD_SPRITE", ["0", "SPRITE_PLAYER"]),
            ("LOAD_SPRITE", ["14", "SPRITE_JOEY"]),
            ("REACTION", ["REACTION_EXCLAMATION_MARK", "SPRITE_PLAYER | SPRITE_JOEY"]),
        ]
        entry = compile_linear_map_event("map_09_state_01", calls, path, constants)
        self.assertEqual(entry.raw_bytes[-3], 64)
        self.assertEqual(entry.raw_bytes[-2], 1)

    def test_object_effect_resolves_sprite_mask(self) -> None:
        path = Path("events/scripts/map_09_state_01.c")
        constants = load_script_constants(path)
        calls = [
            ("LOAD_SPRITE", ["14", "SPRITE_JOEY"]),
            ("OBJECT_EFFECT", ["SPRITE_JOEY", "OBJECT_EFFECT_JUMPING"]),
        ]
        entry = compile_linear_map_event("map_09_state_01", calls, path, constants)
        self.assertEqual(entry.raw_bytes[-4], 64)
        self.assertEqual(entry.raw_bytes[-3], 0)


if __name__ == "__main__":
    unittest.main()
