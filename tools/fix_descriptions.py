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
    "EBON_ILLUSION_MAGICIAN": [
        "Rank 6 Spellcaster Xyz can become this;",
        "materials transfer. OPT: detach 1; SS 1",
        "Spellcaster Normal from hand or Deck.",
        "When Spellcaster Normal attacks: OPT",
        "banish 1 opp card.",
    ],
    "EL_SHADDOLL_ANOYATYLLIS": [
        "Shaddoll + WATER. Must first be FS.",
        "Neither player can SS from hand/GY",
        "via Spell/Trap effects. If sent to GY:",
        "add 1 Shaddoll S/T from GY to hand.",
    ],
    "EL_SHADDOLL_APKALLONE": [
        "2 Shaddoll different Attr. Must FS.",
        "Can't be destroyed by battle. OPT each:",
        "On SS: negate 1 face-up card. If sent",
        "to GY: add 1 Shaddoll from Deck/GY,",
        "then discard 1.",
    ],
    "EL_SHADDOLL_CONSTRUCT": [
        "Shaddoll + LIGHT. Must first be FS.",
        "On SS: send 1 Shaddoll from Deck to GY.",
        "Damage Step vs SS monster: destroy it.",
        "GY: add 1 Shaddoll S/T from GY to hand.",
    ],
    "EL_SHADDOLL_FUSION": [
        "Fusion Summon 1 Shaddoll Fusion from",
        "Extra Deck using monsters from hand",
        "or field. Once per turn.",
    ],
    "EL_SHADDOLL_GRYSTA": [
        "Shaddoll + FIRE. Must first be FS.",
        "Quick: negate opp SS while you have",
        "Shaddoll in hand; destroy it, then",
        "send 1 Shaddoll from hand to GY. OPT.",
        "GY: add 1 Shaddoll S/T from GY.",
    ],
    "EL_SHADDOLL_MESHAHRAIL": [
        "Shaddoll + DARK + EARTH. Must be FS.",
        "Unaffected by opp activated S/T and",
        "monsters with lower Level/Rank. OPT:",
        "pay 800 LP; add 1 Shaddoll or Void",
        "S/T from Deck. GY: SS 1 Shaddoll.",
    ],
    "EL_SHADDOLL_SHEKHINAGA": [
        "Shaddoll + EARTH. Must first be FS.",
        "Quick: negate SS monster effect while",
        "Shaddoll in hand; destroy it, then",
        "send 1 Shaddoll from hand to GY. OPT.",
        "GY: add 1 Shaddoll S/T from GY.",
    ],
    "EL_SHADDOLL_WENDIGO": [
        "Shaddoll + WIND. Must first be FS.",
        "Quick OPT: target 1 monster you control;",
        "it can't be destroyed by battle with",
        "opp SS monster this turn. GY: add 1",
        "Shaddoll S/T from GY to hand.",
    ],
    "EL_SHADDOLL_WINDA": [
        "Shaddoll + DARK. Must first be FS.",
        "Can't be destroyed by opp effects.",
        "Each player can only SS once per turn",
        "while this is face-up. GY: add 1",
        "Shaddoll S/T from GY to hand.",
    ],
}

FIXED_POPUPS = {
    "EBON_ILLUSION_MAGICIAN": "OPT detach: SS Spellcaster Normal. When it attacks: banish 1 opp card.",
    "EL_SHADDOLL_ANOYATYLLIS": "Lock SS from hand/GY via S/T. GY: add Shaddoll S/T from GY.",
    "EL_SHADDOLL_APKALLONE": "On SS: negate face-up. GY: add Shaddoll, discard 1.",
    "EL_SHADDOLL_CONSTRUCT": "On SS: mill Shaddoll. Battle vs SS: destroy. GY: add S/T.",
    "EL_SHADDOLL_FUSION": "Fusion Summon 1 Shaddoll Fusion using hand/field materials. Once/turn.",
    "EL_SHADDOLL_GRYSTA": "Negate opp SS; destroy, send Shaddoll from hand. GY: add S/T.",
    "EL_SHADDOLL_MESHAHRAIL": "Pay 800: add Shaddoll or Void. Unaffected by lower Lv/R. GY: SS Shaddoll.",
    "EL_SHADDOLL_SHEKHINAGA": "Negate SS monster effect; destroy, send Shaddoll. GY: add S/T.",
    "EL_SHADDOLL_WENDIGO": "Protect monster from battle vs opp SS. GY: add Shaddoll S/T.",
    "EL_SHADDOLL_WINDA": "Opp can't destroy this. SS lock once/turn each. GY: add S/T.",
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
