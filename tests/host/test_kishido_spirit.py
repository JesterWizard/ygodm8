import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SPELL = ROOT / "src_custom" / "spell_effects" / "kishido_spirit.c"
BACKROW = ROOT / "src_custom" / "duel_activated_backrow.c"
DUEL_HELPERS = ROOT / "src_custom" / "duel_helpers.c"
BATTLE_DAMAGE = ROOT / "src_custom" / "battle_damage_hooks.c"


def apply_kishido_equal_atk(flags, player_kishido, opponent_kishido, equal_atk):
    """Mirror ApplyKishidoSpiritEqualAtkProtection flag clears."""
    if not equal_atk:
        return flags
    if player_kishido:
        flags &= ~1
    if opponent_kishido:
        flags &= ~2
    return flags


def remap_mutual_destroy_anim(unk18, player_destroy, opponent_destroy, action_id=1):
    """Mirror Duel_RemapMutualDestroyBattleAnim."""
    if action_id not in (1, 2, 3, 5):
        return unk18
    if player_destroy and opponent_destroy:
        return 2
    if not player_destroy and not opponent_destroy:
        return 8
    if unk18 not in (2, 16, 17):
        return unk18
    if not player_destroy and opponent_destroy:
        return 1
    if player_destroy and not opponent_destroy:
        return 3
    return unk18


class KishidoSpiritTests(unittest.TestCase):
    def test_continuous_activation_locks_zone(self):
        source = SPELL.read_text()
        self.assertIn("Duel_ActivateContinuousZone(zone)", source)
        self.assertIn("Duel_ShowEffectText(KISHIDO_SPIRIT)", source)

    def test_activated_backrow_not_selectable(self):
        source = BACKROW.read_text()
        self.assertIn("IsActivatedKishidoSpiritZone(zone)", source)

    def test_battle_protection_via_destroy_api(self):
        helpers = DUEL_HELPERS.read_text()
        damage = BATTLE_DAMAGE.read_text()
        self.assertIn("IsKishidoSpiritActiveForDuelist", helpers)
        self.assertIn("CanMonsterBeDestroyedByBattle", helpers)
        self.assertIn("Duel_ApplyBattleDestroyProtection", helpers)
        self.assertIn("Duel_ApplyBattleDestroyProtection();", damage)

    def test_mutual_destroy_keeps_vanilla_anim_case(self):
        helpers = DUEL_HELPERS.read_text()
        self.assertIn("if (playerDestroy && opponentDestroy)", helpers)
        self.assertIn("gUnk2023EA0.unk18 = 2", helpers)
        self.assertIn("ApplyKishidoSpiritEqualAtkProtection", helpers)

    def test_kishido_protects_per_controller_side(self):
        helpers = DUEL_HELPERS.read_text()
        self.assertIn("sActionData.flags &= ~1u", helpers)
        self.assertIn("sActionData.flags &= ~2u", helpers)
        self.assertNotIn("sActionData.flags &= ~3u", helpers)

    def test_anim_remap_handles_protection_splits(self):
        helpers = DUEL_HELPERS.read_text()
        self.assertIn("gUnk2023EA0.unk18 = 8", helpers)
        self.assertIn("gUnk2023EA0.unk18 != 16", helpers)
        self.assertIn("gUnk2023EA0.unk18 = 1", helpers)
        self.assertIn("gUnk2023EA0.unk18 = 3", helpers)
        self.assertIn("IsMonsterVersusMonsterBattleAction", helpers)

    def test_direct_attack_anim_not_remapped(self):
        helpers = DUEL_HELPERS.read_text()
        self.assertIn("IsMonsterVersusMonsterBattleAction(sActionData.id)", helpers)
        self.assertEqual(remap_mutual_destroy_anim(15, False, False, action_id=6), 15)
        self.assertEqual(remap_mutual_destroy_anim(10, False, False, action_id=4), 10)

    def test_behavior_matrix_equal_atk_scenarios(self):
        # A: no Kishido — mutual destroy, case 2
        flags = apply_kishido_equal_atk(0x03, False, False, True)
        self.assertEqual(flags, 0x03)
        self.assertEqual(
            remap_mutual_destroy_anim(2, bool(flags & 1), bool(flags & 2)), 2)

        # B: player Kishido — you survive, enemy to GY, case 1
        flags = apply_kishido_equal_atk(0x03, True, False, True)
        self.assertEqual(flags, 0x02)
        self.assertEqual(
            remap_mutual_destroy_anim(2, bool(flags & 1), bool(flags & 2)), 1)

        # Opponent Kishido — you to GY, enemy survives, case 3
        flags = apply_kishido_equal_atk(0x03, False, True, True)
        self.assertEqual(flags, 0x01)
        self.assertEqual(
            remap_mutual_destroy_anim(2, bool(flags & 1), bool(flags & 2)), 3)

        # Both sides — neither to GY, case 8
        flags = apply_kishido_equal_atk(0x03, True, True, True)
        self.assertEqual(flags, 0x00)
        self.assertEqual(
            remap_mutual_destroy_anim(2, bool(flags & 1), bool(flags & 2)), 8)

        # C: unequal ATK — Kishido no-op; vanilla one-sided destroy unchanged
        flags = apply_kishido_equal_atk(0x02, True, False, False)
        self.assertEqual(flags, 0x02)
        self.assertEqual(
            remap_mutual_destroy_anim(1, bool(flags & 1), bool(flags & 2)), 1)


if __name__ == "__main__":
    unittest.main()
