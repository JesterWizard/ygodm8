import tempfile
import unittest
from pathlib import Path

from tools.vanilla_events import (
    generate_story_skeleton,
    parse_story_sequence_file,
    parse_story_sequence_scene_comments,
    render_story_sequence_text,
)


class StorySequenceCommentTests(unittest.TestCase):
    def test_parse_scene_comments_from_story_section(self) -> None:
        comments = parse_story_sequence_scene_comments(Path("events/story_sequence.txt"))
        self.assertEqual(comments["map_09_state_01"], "Player's house")
        self.assertEqual(comments["map_56_state_01"], "Duels with Hall of Eternity duelists")
        self.assertNotIn("map_00_state_00", comments)

    def test_render_story_sequence_text_uses_custom_comments(self) -> None:
        scenes = [
            type("Scene", (), {
                "scene_id": "map_09_state_01",
                "map_id": 9,
                "map_state": 1,
                "enter_addr": 0x08E62160,
            })(),
        ]
        text = render_story_sequence_text(
            scenes,
            {"map_09_state_01"},
            scene_comments={"map_09_state_01": "Player's house"},
        )
        self.assertIn("map_09_state_01  # Player's house", text)
        self.assertNotIn("enter=0x08E62160", text.splitlines()[6])

    def test_generate_story_skeleton_preserves_dual_format(self) -> None:
        catalog = Path("events/vanilla/vanilla_event_catalog.md")
        scripts_dir = Path("events/scripts")
        source = Path("events/story_sequence.txt")
        with tempfile.TemporaryDirectory() as tmp_dir:
            sequence_path = Path(tmp_dir) / "story_sequence.txt"
            sequence_path.write_text(source.read_text())
            before_story = parse_story_sequence_file(sequence_path).story_section
            before_comments = parse_story_sequence_scene_comments(sequence_path)

            generate_story_skeleton(
                catalog,
                scripts_dir,
                sequence_path,
                preserve_active=True,
            )

            after_story = parse_story_sequence_file(sequence_path).story_section
            after_comments = parse_story_sequence_scene_comments(sequence_path)
            self.assertEqual(before_story, after_story)
            self.assertEqual(before_comments, after_comments)
            self.assertIn("# Chapter 01 - Millenium Necklace", sequence_path.read_text())


if __name__ == "__main__":
    unittest.main()
