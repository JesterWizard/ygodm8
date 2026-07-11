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
    "LEGENDARY_KNIGHT_CRITIAS": [
        "Special Summon with Legend of",
        "Heart. When SS: target 1 face-up",
        "S/T; banish it. When attacked:",
        "target 1 Trap in GY; Set it. It",
        "can be activated this turn.",
    ],
    "LEGENDARY_KNIGHT_HERMOS": [
        "Special Summon with Legend of",
        "Heart. When SS: target 1 face-up",
        "S/T; banish it. When attacked:",
        "target 1 Effect Monster in GY;",
        "copy its name and effects.",
    ],
    "LEGENDARY_KNIGHT_TIMAEUS": [
        "Special Summon with Legend of",
        "Heart. When SS: target 1 face-up",
        "S/T; banish it. When attacked:",
        "target 1 Spell in GY; Set that",
        "target.",
    ],
    "LEKUNGA": [
        "Banish 2 WATER from your GY;",
        "Special Summon 1 Lekunga Token",
        "(Plant/WATER/Lv2/700/700) in",
        "Attack Position.",
    ],
    "LIGHT_AND_DARKNESS_DRAGON": [
        "Can't be SS. DARK while face-up.",
        "Once per Chain: -500 ATK/DEF",
        "to negate anything. When",
        "destroyed: destroy your field,",
        "SS a GY monster.",
    ],
    "LORD_OF_THE_RED": [
        "Ritual Summon with Red-Eyes",
        "Transmigration. Once per turn,",
        "when a card or effect activates:",
        "target 1 monster; destroy it, or",
        "target 1 S/T; destroy it.",
    ],
    "MA_AT": [
        "Can't be Normal Summoned/Set.",
        "SS: send 1 LIGHT Dragon + 1",
        "LIGHT Fairy to GY. Once per",
        "turn: declare 3 names, excavate",
        "top 3 of Deck, add declared names to hand.",
    ],
    "MAGICAL_DIMENSION": [
        "If you control a Spellcaster:",
        "Tribute 1 monster; Special Summon",
        "1 Spellcaster from your hand,",
        "then you can destroy 1 monster",
        "on the field.",
    ],
    "MAGICAL_HATS": [
        "Opponent BP: pick 2 S/T from",
        "Deck + 1 monster you control.",
        "SS as Normal 0/0 face-down.",
        "Set the chosen monster.",
        "Shuffle. Destroy Deck S/T at end of BP.",
    ],
    "MAGICAL_PLANT_MANDRAGOLA": [
        "FLIP: Place 1 Spell Counter on",
        "each face-up card on the field",
        "that you can place a Spell",
        "Counter on.",
    ],
}

FIXED_POPUPS = {
    "LEGENDARY_KNIGHT_CRITIAS": "Must be SS by Legend of Heart. When SS: banish face-up S/T. When attacked: Set a Trap from GY.",
    "LEGENDARY_KNIGHT_HERMOS": "Must be SS by Legend of Heart. When SS: banish face-up S/T. When attacked: copy a GY monster.",
    "LEGENDARY_KNIGHT_TIMAEUS": "Must be SS by Legend of Heart. When SS: banish face-up S/T. When attacked: Set a Spell from GY.",
    "LEKUNGA": "Banish 2 WATER from GY; SS a Lekunga Token (Plant/WATER/Lv2/700/700) in ATK position.",
    "LIGHT_AND_DARKNESS_DRAGON": "Once/Chain: when activated, -500 ATK/DEF to negate. On destruction: clear field, SS GY monster.",
    "LORD_OF_THE_RED": "Once per turn, when a card/effect activates: destroy 1 monster or 1 S/T on the field.",
    "MA_AT": "SS: send 1 LIGHT Dragon + Fairy to GY. Once/turn: name 3, excavate 3, add matches.",
    "MAGICAL_DIMENSION": "If you control a Spellcaster: Tribute 1 monster; SS 1 from hand, then destroy 1 monster.",
    "MAGICAL_HATS": "Opponent BP: pick 2 S/T from Deck + 1 monster. SS as 0/0 face-down. Destroy Deck cards at end of BP.",
    "MAGICAL_PLANT_MANDRAGOLA": "FLIP: Place 1 Spell Counter on each face-up card you can place a Spell Counter on.",
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
