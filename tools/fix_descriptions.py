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
    "VENOM_BURN": [
        "Select 1 monster with a",
        "Venom Counter(s). Remove",
        "all Venom Counters from it;",
        "inflict 700 damage to your",
        "opponent for each removed.",
    ],
    "VENOM_COBRA": [
        "Hard scales cover this",
        "gigantic cobra. It hunts by",
        "shooting venom, but its",
        "large size makes its attack",
        "pattern easy to predict.",
    ],
    "VENOM_SERPENT": [
        "Once per turn: place 1",
        "Venom Counter on 1 monster",
        "your opponent controls.",
        " ",
    ],
    "VENOM_SHOT": [
        "If you control a Venom",
        "monster, Vennominaga, or",
        "Vennominon: send 1 Reptile",
        "from Deck to GY; place 2",
        "Venom Counters on 1 monster.",
    ],
    "VENOM_SNAKE": [
        "Once per turn: place 1",
        "Venom Counter on 1 monster",
        "your opponent controls. If",
        "you do, this cannot attack",
        "this turn.",
    ],
    "VENOM_SWAMP": [
        "Each End Phase: place 1",
        "Venom Counter on each",
        "face-up non-Venom monster.",
        "Lose 500 ATK per Counter;",
        "destroy if ATK becomes 0.",
    ],
    "VIPERS_REBIRTH": [
        "If all monsters in your GY",
        "are Reptile: Special Summon",
        "1 non-Tuner from your GY.",
        "Destroy it during the End",
        "Phase.",
    ],
    "YAMORIMORI": [
        "Banish from GY; target 1",
        "Reptile you control and 1",
        "face-up opponent monster:",
        "set both face-down Def, or",
        "destroy yours; opp ATK to 0.",
    ],
    "YOWIE": [
        "If Summoned alone: opponent",
        "skips their next Draw Phase.",
        "You can only SS once the",
        "turn you activate this.",
        "Once per Duel.",
    ],
}

FIXED_POPUPS = {
    "VENOM_BURN": "Remove Venom Counters; 700 damage each.",
    "VENOM_SERPENT": "OPT: place 1 Venom Counter on opp monster.",
    "VENOM_SHOT": "Send Reptile; place 2 Venom Counters.",
    "VENOM_SNAKE": "OPT: place 1 Venom Counter; cannot attack.",
    "VENOM_SWAMP": "End Phase: Venom Counters; -500 ATK each.",
    "VIPERS_REBIRTH": "SS non-Tuner Reptile from GY; destroy later.",
    "YAMORIMORI": "Banish from GY: set both, or destroy + ATK 0.",
    "YOWIE": "If Summoned alone: opp skips next Draw Phase.",
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
            item["effect_texts"]["popup_1"] = FIXED_POPUPS[const]
    write_manifest(MANIFEST_PATH, manifest)
    print(f"Updated {len(FIXED_DESCRIPTIONS)} descriptions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
