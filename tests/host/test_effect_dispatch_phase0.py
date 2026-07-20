"""Phase 0 effect-system dispatcher: always legacy + hook wiring."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectDispatchPhase0(unittest.TestCase):
    def test_dispatch_always_legacy(self):
        src = read("src_custom/effect_system/effect_dispatch.c")
        self.assertIn("EffectDispatch_TryActivate", src)
        self.assertIn("EffectDispatch_QueryShouldActivate", src)
        self.assertIn("return EFFECT_DISPATCH_LEGACY", src)
        self.assertIn("return EFFECT_SHOULD_LEGACY", src)
        # Phase 0: no converted-card table yet
        self.assertNotIn("sConvertedEffects", src)

    def test_hooks_call_dispatch(self):
        cases = [
            ("src_custom/spell_effect_hooks.c", "EFFECT_KIND_SPELL"),
            ("src_custom/trap_effects_hooks.c", "EFFECT_KIND_TRAP"),
            ("src_custom/monster_effect_hooks.c", "EFFECT_KIND_ACTIVATED"),
            ("src_custom/permanent_effect_hooks.c", "EFFECT_KIND_PERMANENT"),
            ("src_custom/turn_effect_hooks.c", "EFFECT_KIND_TURN"),
        ]
        for path, kind in cases:
            with self.subTest(path=path):
                text = read(path)
                self.assertIn('#include "effect_system.h"', text)
                self.assertIn("EffectDispatch_TryActivate", text)
                self.assertIn(kind, text)

    def test_header_api(self):
        hdr = read("include/effect_system.h")
        self.assertIn("EFFECT_DISPATCH_LEGACY", hdr)
        self.assertIn("EFFECT_SHOULD_LEGACY", hdr)
        self.assertIn("EffectDispatch_TryActivate", hdr)
        self.assertIn("EffectDispatch_QueryShouldActivate", hdr)


if __name__ == "__main__":
    unittest.main()
