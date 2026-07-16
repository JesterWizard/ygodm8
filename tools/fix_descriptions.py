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
    "ETERNAL_SOUL": [
        "Your Dark Magicians are unaffected by opp",
        "effects. If this leaves the field: destroy",
        "all your monsters. OPT: SS 1 Dark Magician",
        "from hand/GY, OR add Dark Magic Attack or",
        "Thousand Knives from Deck to hand.",
    ],
    "EVIL_ASSAULT": [
        "Discard 1; take 1 Lv4 or lower Evil HERO",
        "from Deck; add to hand or SS it. Can't ED",
        "SS except HERO this turn. GY (not turn",
        "sent): banish this; add Dark Fusion from",
        "GY to hand. Each OPT.",
    ],
    "EVIL_DRAGON_ANANTA": [
        "Can't NS/Set. SS only by banishing all",
        "your Reptiles from field and GY. ATK/DEF",
        "= number banished x 600. During each of",
        "your End Phases, destroy 1 card on field.",
    ],
    "EVIL_HERO_ADUSTED_GOLD": [
        "Discard this; add 1 Dark Fusion, or 1 card",
        "that lists Dark Fusion, from Deck (except",
        "this). OPT. Cannot attack unless you",
        "control a Fusion Monster.",
    ],
    "EVIL_HERO_DARK_GAIA": [
        "Fiend + Rock. Must SS with Dark Fusion.",
        "Original ATK = sum of materials' original",
        "ATK. When this attacks: change all opp",
        "Defense monsters to face-up Attack (no",
        "Flip Effects).",
    ],
    "EVIL_HERO_DARKEST_KNIGHT": [
        "Fiend + Warrior. Must SS with Dark Fusion.",
        "Opp monsters lose ATK equal to materials'",
        "total original ATK. Can attack twice.",
        "If this leaves by opp card: SS 1 Fiend or",
        "Warrior from GY in Defense.",
    ],
    "EVIL_HERO_DEAD_END_PRISON": [
        "If you control a Dark Fusion Fusion: you",
        "can SS this from hand (OPT this way).",
        "Send 1 HERO from Deck to GY; this can",
        "substitute for 1 named Fusion material",
        "this turn. OPT.",
    ],
    "EVIL_HERO_INFERNAL_GAINER": [
        "Main Phase 1: banish this; target 1 Fiend",
        "you control; it can attack twice while",
        "face-up. During your 2nd Standby after",
        "that: SS this in Attack Position.",
    ],
    "EVIL_HERO_INFERNAL_PRODIGY": [
        "If you control no monsters, you can SS",
        "this from hand in Attack. End Phase: if",
        "this was Tributed this turn to Tribute",
        "Summon a HERO: draw 1.",
    ],
    "EVIL_HERO_INFERNAL_RIDER": [
        "On NS/SS: add Dark Fusion from Deck/GY.",
        "Banish this + 4 other GY monsters; Set",
        "Super Polymerization from Deck. Can't SS",
        "except HERO, but can Dark Fusion via other",
        "effects, until opp End Phase. Each OPT.",
    ],
}

FIXED_POPUPS = {
    "ETERNAL_SOUL": "Protect Dark Magician. OPT: SS it from hand/GY, or search Dark Magic Attack / Thousand Knives.",
    "EVIL_ASSAULT": "Discard 1; add or SS Lv4- Evil HERO from Deck. GY: banish; add Dark Fusion.",
    "EVIL_DRAGON_ANANTA": "SS by banishing Reptiles; ATK/DEF = count x 600. End Phase: destroy 1 card.",
    "EVIL_HERO_ADUSTED_GOLD": "Discard: search Dark Fusion or related. Can't attack without a Fusion.",
    "EVIL_HERO_DARK_GAIA": "Dark Fusion. ATK = materials. On attack: flip opp Defense to Attack.",
    "EVIL_HERO_DARKEST_KNIGHT": "Opp lose ATK by materials. Attack twice. Leaves: SS Fiend/Warrior from GY.",
    "EVIL_HERO_DEAD_END_PRISON": "SS if you have Dark Fusion Fusion. Mill HERO: substitute for named material.",
    "EVIL_HERO_INFERNAL_GAINER": "Banish: Fiend you control can attack twice. Returns on 2nd Standby.",
    "EVIL_HERO_INFERNAL_PRODIGY": "SS from hand if empty field. If Tributed for HERO: draw 1 at End Phase.",
    "EVIL_HERO_INFERNAL_RIDER": "On summon: add Dark Fusion. Banish 5 GY: Set Super Poly; HERO lock.",
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
