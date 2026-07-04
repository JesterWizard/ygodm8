"""Host checks for AI normal-spell activation target gating."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestAiSpellTargets(unittest.TestCase):
    def test_feather_duster_requires_opponent_backrow(self):
        source = read("src_custom/ai_spell_targets.c")
        self.assertIn("SPELL_EFFECT_HARPIES_FEATHER_DUSTER", source)
        self.assertIn("INACTIVE_DUELIST_BACKROW", source)

    def test_force_activation_uses_shared_helper(self):
        hooks = read("src_custom/ai_hooks.c")
        self.assertIn("AiNormalSpellHasActivationTargets(zone->id)", hooks)
        self.assertNotIn("SetNormalSpellHasActivationTargets", hooks)

    def test_fast_ai_rejects_targetless_normal_spell_activation(self):
        source = read("src_custom/ai_sim_fast.c")
        self.assertIn("AiNormalSpellHasActivationTargets(cardId)", source)
        self.assertIn("ACTIVE_DUELIST_BACKROW", source)


if __name__ == "__main__":
    unittest.main()
