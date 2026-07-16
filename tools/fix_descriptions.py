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
    "NEPHE_SHADDOLL_FUSION": [
        "Declare 1 Attribute; Equip only to",
        "a Shaddoll; it becomes that Attribute.",
        "Main Phase: Fusion Summon 1 Shaddoll",
        "Fusion from Extra using monsters from",
        "hand/field including equipped. OPT.",
    ],
    "NEUTRON_BLAST": [
        "Target 1 Fusion Summoned Blue-Eyes",
        "Ultimate Dragon you control; this turn",
        "it can attack 2nd and 3rd times each",
        "Battle Phase, also when it attacks,",
        "opp cards/effects cannot activate.",
    ],
    "OFFERING_TO_THE_SNAKE_DEITY": [
        "Target 1 face-up Reptile you control",
        "and 2 cards your opponent controls;",
        "destroy all three targets.",
    ],
    "OSHALEON": [
        "While face-up Attack Position, opp",
        "must attack this if able. If destroyed",
        "by battle and sent to GY: add 1 Reptile",
        "with 500 or less ATK from Deck to hand.",
    ],
    "POWER_TOOL_DRAGON": [
        "1 Tuner + 1+ non-Tuner.",
        "OPT: reveal 3 Equip Spells from Deck;",
        "opp randomly adds 1 to your hand,",
        "shuffle the rest. If would be destroyed",
        "while equipped: send 1 Equip instead.",
    ],
    "PREDAPLANT_VERTE_ANACONDA": [
        "2 Effect Monsters.",
        "Target 1 face-up monster; it becomes",
        "DARK until EOT. Pay 2000 LP and send",
        "1 Fusion/Poly Normal/Quick from Deck",
        "to GY; copy its effect. Extra lock. OPT.",
    ],
    "QADSHADDOLL_KEIOS": [
        "FLIP: SS 1 Shaddoll from hand in",
        "face-up or face-down Defense.",
        "If sent to GY by effect: send 1",
        "Shaddoll from hand to GY; Shaddolls",
        "you control gain ATK = Lv x 100.",
    ],
    "RED_DRAGON_ARCHFIEND": [
        "1 Tuner + 1+ non-Tuner.",
        "After damage calc, if this attacks a",
        "Defense Position monster: destroy all",
        "opp Defense Position monsters.",
        "End Phase: destroy your other Attackers.",
    ],
    "RED_REBOOT": [
        "When opp activates a Trap: negate,",
        "Set that card, then they can Set 1",
        "other Trap from Deck. Rest of turn,",
        "they cannot activate Traps. Can activate",
        "from hand by paying half your LP.",
    ],
    "REESHADDOLL_WENDI": [
        "FLIP: SS 1 Shaddoll from Deck in",
        "face-up or face-down Defense,",
        "except Wendi. If sent to GY by",
        "effect: SS 1 Shaddoll from Deck",
        "face-down. Use only 1 effect per turn.",
    ],
    "REESHADDOLL_WENDIKURUHU": [
        "1 Shaddoll + 1 WIND. Must first be",
        "Fusion Summoned. Quick: flip face-down",
        "monsters face-up Defense; then flip",
        "up to that many Flip monsters' count",
        "face-down. Sent to GY: add 1 Shaddoll.",
    ],
    "REPTILANNE_RAGE": [
        "Equipped becomes Reptile and gains",
        "800 ATK. If this is destroyed and sent",
        "to GY: target 1 face-up opp monster;",
        "it loses 800 ATK.",
    ],
    "REPTILIANNE_ECHIDNA": [
        "2 monsters including a Reptile.",
        "If Link Summoned: target 1 face-up",
        "opp monster; its ATK becomes 0.",
        "Main Phase if you control a 0 ATK:",
        "add Reptiles from Deck. Extra lock.",
    ],
    "REPTILIANNE_GARDNA": [
        "When this card you control is",
        "destroyed and sent to the GY,",
        "add 1 Reptilianne monster from",
        "your Deck to your hand.",
    ],
    "REPTILIANNE_GORGON": [
        "If this card attacks a monster,",
        "after damage calculation: that",
        "monster's ATK becomes 0, also it",
        "cannot change its battle position.",
    ],
    "REPTILIANNE_HYDRA": [
        "1 Reptilianne Tuner + 1+ non-Tuner.",
        "When Synchro Summoned: destroy all",
        "face-up opp monsters with 0 ATK,",
        "and draw 1 for each destroyed.",
    ],
    "REPTILIANNE_LAMIA": [
        "If in hand and all your monsters are",
        "face-up Reptiles: target 1 face-up",
        "opp; ATK to 0, SS this, take damage",
        "equal to its original ATK. If Synchro",
        "Material: target monsters; ATK to 0.",
    ],
    "REPTILIANNE_MEDUSA": [
        "Send 1 card from your hand to the GY",
        "and select 1 face-up monster your",
        "opponent controls. Its ATK becomes 0,",
        "and it cannot change battle position.",
    ],
    "REPTILIANNE_NAGA": [
        "Cannot be destroyed by battle.",
        "ATK of any monster that battles this",
        "becomes 0 at end of that Battle Phase.",
        "During your End Phase, change this",
        "face-up Defense Position to Attack.",
    ],
    "REPTILIANNE_POISON": [
        "If you control a face-up Reptilianne:",
        "change 1 Defense Position opp monster",
        "to face-up Attack Position and reduce",
        "its ATK to 0.",
    ],
}

FIXED_POPUPS = {
    "NEPHE_SHADDOLL_FUSION": "Equip Shaddoll; set Attribute. Fusion Summon Shaddoll Fusion using equipped. OPT.",
    "NEUTRON_BLAST": "BEUD attacks 2nd/3rd; opp cannot activate cards/effects when it attacks.",
    "OFFERING_TO_THE_SNAKE_DEITY": "Target 1 Reptile you control + 2 opp cards; destroy all three.",
    "OSHALEON": "Opp must attack this. If destroyed by battle: add Reptile ATK 500-.",
    "POWER_TOOL_DRAGON": "OPT: reveal 3 Equips; opp adds 1. Destroy protect via Equip.",
    "PREDAPLANT_VERTE_ANACONDA": "Make monster DARK. Pay 2000; copy Fusion/Poly from Deck. OPT.",
    "QADSHADDOLL_KEIOS": "FLIP: SS Shaddoll from hand. Sent by effect: mill; gain ATK.",
    "RED_DRAGON_ARCHFIEND": "Attacks Defense: destroy all opp Defense. EP: destroy other Attackers.",
    "RED_REBOOT": "Negate Trap; Set it. Opp cannot activate Traps. Hand: pay half LP.",
    "REESHADDOLL_WENDI": "FLIP: SS Shaddoll from Deck. Sent by effect: SS face-down.",
    "REESHADDOLL_WENDIKURUHU": "Quick: flip monsters. Sent to GY: add 1 Shaddoll from GY.",
    "REPTILANNE_RAGE": "Equip: Reptile +800 ATK. If destroyed: opp monster loses 800 ATK.",
    "REPTILIANNE_ECHIDNA": "Link: set ATK to 0. If control 0 ATK: add Reptiles from Deck.",
    "REPTILIANNE_GARDNA": "If destroyed: add 1 Reptilianne from Deck to hand.",
    "REPTILIANNE_GORGON": "After attack damage calc: that monster ATK becomes 0.",
    "REPTILIANNE_HYDRA": "On Synchro: destroy opp 0 ATK monsters; draw 1 each.",
    "REPTILIANNE_LAMIA": "Hand: set ATK 0, SS this. Synchro Material: set ATK to 0.",
    "REPTILIANNE_MEDUSA": "Discard 1; select face-up opp monster; its ATK becomes 0.",
    "REPTILIANNE_NAGA": "Battle immune. Battler ATK to 0. EP: Defense to Attack.",
    "REPTILIANNE_POISON": "If control Reptilianne: flip Defense to Attack; ATK to 0.",
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
