#!/usr/bin/env python3
"""Fix description and popup texts for newly added cards."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import load_manifest_json, write_manifest
from add_card_art import wrap_activation_page, wrap_description_page

MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"

FIXED_DESCRIPTIONS = {
    "JUNK_WARRIOR": [
        "Junk Synchron + 1+ non-Tuner.",
        "If Synchro Summoned: gains ATK",
        "equal to total ATK of all Lv2-",
        "monsters you currently control.",
    ],
    "KEEPER_OF_DRAGON_MAGIC": [
        "On NS/SS: discard 1; add 1 Poly",
        "or Fusion Normal Spell from Deck.",
        "Reveal 1 Fusion in Extra; SS 1",
        "listed material from GY face-down.",
        "Each OPT. Fusion Extra lock that turn.",
    ],
    "LEGENDARY_MAJU_GARZETT": [
        "Cannot be Normal Summoned/Set.",
        "SS from hand by Tributing all",
        "your monsters; ATK = their original",
        "ATK combined. Piercing damage.",
    ],
    "LEV_SHADDOLL_FUSION": [
        "On activate: send 1 Fusion from",
        "Extra to GY. Tribute 1 Fusion;",
        "Fusion Summon 1 Shaddoll Fusion",
        "with different Attribute from Extra",
        "(ATK 0). Each OPT. Shaddoll Extra lock.",
    ],
    "LIGHT_SERPENT": [
        "If sent from hand to GY: you can",
        "Special Summon it from the GY.",
        "Cannot be used as Synchro Material.",
    ],
    "LIGHTNING_WARRIOR": [
        "1 Tuner + 1+ non-Tuner.",
        "If destroys a monster by battle",
        "and sends it to GY: inflict 300",
        "damage per card in opp hand.",
    ],
    "LONEFIRE_BLOSSOM": [
        "Once per turn: Tribute 1 face-up",
        "Plant; Special Summon 1 Plant",
        "monster from your Deck.",
    ],
    "MAGICIAN_NAVIGATION": [
        "SS 1 Dark Magician from hand,",
        "then SS 1 Lv7- DARK Spellcaster",
        "from Deck. If you control DM,",
        "banish this from GY; negate 1",
        "face-up opp Spell/Trap until EOT.",
    ],
    "MAGICIAN_OF_DARK_ILLUSION": [
        "Name becomes Dark Magician on field.",
        "Opp turn, if you activate S/T:",
        "SS this from hand. OPT.",
        "If you activate S/T while this",
        "is face-up: SS 1 DM from GY. Once.",
    ],
    "MAGICIANS_COMBINATION": [
        "OPT when a card/effect activates:",
        "Tribute DM or DMG; SS the other",
        "from hand/GY, and if you do,",
        "negate that effect. If this leaves",
        "S/T Zone to GY: destroy 1 card.",
    ],
    "MAGICIANS_ROBE": [
        "Opp turn (Quick): discard 1 S/T;",
        "SS 1 Dark Magician from Deck.",
        "Opp turn, if you activate S/T",
        "while this is in GY: SS this,",
        "but banish when it leaves. Each OPT.",
    ],
    "MAGICIANS_ROD": [
        "On NS: add 1 S/T that lists Dark",
        "Magician from Deck to hand.",
        "Opp turn, if you activate S/T",
        "while this is in GY: Tribute 1",
        "Spellcaster; add this to hand. OPT.",
    ],
    "MAGICIANS_SOULS": [
        "Send up to 2 S/T from hand/field",
        "to GY; draw that many. From hand:",
        "send 1 Lv6+ Spellcaster from Deck",
        "to GY; SS this, or send this and",
        "SS DM/DMG from GY. Each OPT.",
    ],
    "MASTER_OF_CHAOS": [
        "Dark Magician + 1 Chaos/BLS Ritual.",
        "If Fusion Summoned: SS 1 LIGHT",
        "or DARK from GY. Tribute 1 LIGHT",
        "+ 1 DARK; banish all opp monsters.",
        "If destroyed: add 1 Spell from GY.",
    ],
    "METAVERSE": [
        "Take 1 Field Spell from your Deck,",
        "and either activate it or add it",
        "to your hand.",
    ],
    "MILLENNIUM_EYES_RESTRICT": [
        "Relinquished + 1 Effect Monster.",
        "OPT when opp activates monster",
        "effect: equip 1 Effect Monster",
        "they control or in their GY to this.",
        "Gains ATK/DEF; negate that name.",
    ],
    "MOLTING_ESCAPE": [
        "Equip only to a Reptile. OPT, if",
        "equipped would be destroyed by",
        "battle, it is not. Gains 300 ATK",
        "each time this is applied.",
    ],
    "MYSTIC_MINE": [
        "If opp controls more monsters:",
        "they cannot activate monster",
        "effects or attack. If you control",
        "more: you cannot. End Phase, if",
        "same count: destroy this card.",
    ],
    "NAELSHADDOLL_ARIEL": [
        "FLIP: SS 1 banished Shaddoll in",
        "face-up or face-down Defense.",
        "If sent to GY by effect: banish",
        "up to 3 cards from the GYs.",
        "Use only 1 effect per turn.",
    ],
    "NEHSHADDOLL_GENIUS": [
        "FLIP: target 1 Shaddoll you control;",
        "unaffected by monster effects",
        "this turn except its own. If sent",
        "to GY by effect: target 1 Effect",
        "Monster; neither can activate it.",
    ],
}

FIXED_POPUPS = {
    "JUNK_WARRIOR": "If Synchro Summoned: gains ATK equal to Lv2- monsters you control.",
    "KEEPER_OF_DRAGON_MAGIC": "On NS/SS: discard; add Poly/Fusion. Reveal Fusion; SS listed material. OPT.",
    "LEGENDARY_MAJU_GARZETT": "SS by Tributing all; ATK = their original ATK. Piercing.",
    "LEV_SHADDOLL_FUSION": "Send Fusion from Extra. Tribute Fusion; SS Shaddoll Fusion ATK 0. OPT.",
    "LIGHT_SERPENT": "If sent from hand to GY: SS it from GY. Not Synchro Material.",
    "LIGHTNING_WARRIOR": "If destroys by battle: 300 damage per card in opp hand.",
    "LONEFIRE_BLOSSOM": "OPT: Tribute 1 Plant; SS 1 Plant from Deck.",
    "MAGICIAN_NAVIGATION": "SS Dark Magician from hand, then Lv7- DARK Spellcaster from Deck.",
    "MAGICIAN_OF_DARK_ILLUSION": "Name = Dark Magician. Opp turn S/T: SS from hand. Field S/T: SS DM from GY.",
    "MAGICIANS_COMBINATION": "Tribute DM/DMG; SS the other and negate. Leaves S/T: destroy 1.",
    "MAGICIANS_ROBE": "Opp turn: discard S/T; SS DM from Deck. GY: SS self, banish later.",
    "MAGICIANS_ROD": "On NS: add S/T listing DM. GY: Tribute Spellcaster; add this.",
    "MAGICIANS_SOULS": "Send S/T; draw. Hand: mill Lv6+ Spellcaster; SS this or DM/DMG.",
    "MASTER_OF_CHAOS": "Fusion: SS LIGHT/DARK from GY. Tribute LIGHT+DARK; banish opp.",
    "METAVERSE": "Take 1 Field Spell from Deck; activate it or add to hand.",
    "MILLENNIUM_EYES_RESTRICT": "Opp monster effect: equip their Effect Monster; gain ATK/DEF.",
    "MOLTING_ESCAPE": "Equip Reptile. OPT battle protect; gains 300 ATK when applied.",
    "MYSTIC_MINE": "Player with fewer monsters: no monster effects/attacks. Tie: destroy.",
    "NAELSHADDOLL_ARIEL": "FLIP: SS banished Shaddoll. Sent by effect: banish up to 3 from GYs.",
    "NEHSHADDOLL_GENIUS": "FLIP: Shaddoll unaffected. Sent by effect: lock 1 Effect Monster.",
}


def main():
    for const, pages in FIXED_DESCRIPTIONS.items():
        if len(pages) < 2 or len(pages) > 5:
            print(f"FAIL page count {const}: {len(pages)} (need 2-5)")
            return 1
        for i, p in enumerate(pages):
            if p:
                try:
                    wrap_description_page(p)
                except SystemExit as e:
                    print(f"FAIL desc {const} page {i}: {e}")
                    return 1
    for const, text in FIXED_POPUPS.items():
        if text:
            result = wrap_activation_page(text)
            lines = result.split("#0")
            if len(lines) > 4:
                print(f"FAIL popup {const}: {len(lines)} lines (max 4)")
                return 1

    manifest = load_manifest_json(MANIFEST_PATH)
    for item in manifest["cards"]:
        const = item["card_const"]
        if const in FIXED_DESCRIPTIONS:
            item["description"]["pages"] = FIXED_DESCRIPTIONS[const]
        if const in FIXED_POPUPS and "effect_texts" in item:
            popup = item["effect_texts"].get("popup_1")
            if isinstance(popup, dict):
                item["effect_texts"]["popup_1"]["pages"] = [FIXED_POPUPS[const]]
            elif isinstance(popup, str):
                item["effect_texts"]["popup_1"] = FIXED_POPUPS[const]

    write_manifest(MANIFEST_PATH, manifest)
    print(f"Fixed {len(FIXED_DESCRIPTIONS)} descriptions and popups")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
