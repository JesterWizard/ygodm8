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
    "SNAKE_RAIN": [
        "Discard 1 card. Select 4",
        "Reptile monsters from your",
        "Deck and send them to the",
        "Graveyard.",
    ],
    "SNAKE_WHISTLE": [
        "When a Reptile you control",
        "is destroyed: Special",
        "Summon 1 Level 4 or lower",
        "Reptile from your Deck.",
    ],
    "SOUL_SERVANT": [
        "Place 1 Dark Magician or",
        "card mentioning DM/DMG from",
        "hand, Deck, or GY on Deck.",
        "GY: draw for each different",
        "Palladium, DM, or DMG name",
    ],
    "STARDUST_DRAGON": [
        "1 Tuner + 1+ non-Tuners.",
        "Quick: Tribute this to",
        "negate a destroy effect and",
        "destroy that card. If used,",
        "SS this from GY at End Phase.",
    ],
    "SUPREME_KINGS_CASTLE": [
        "Fusion Summon Dark Fusion",
        "monsters with other effects.",
        "OPT if your Fiend battles:",
        "send 1 Evil HERO from Deck",
        "or ED to GY; gain Level x200.",
    ],
    "THAT_GRASS_LOOKS_GREENER": [
        "If you have more cards in",
        "your Deck than opponent:",
        "mill until both Decks have",
        "the same number of cards.",
    ],
    "THE_DARK_MAGICIANS": [
        "Dark Magician or Dark",
        "Magician Girl + Spellcaster.",
        "OPT if S/T activated: draw",
        "1, then you can Set it.",
        "If destroyed: SS DM and DMG.",
    ],
    "THE_GAZE_OF_TIMAEUS": [
        "Target 1 Dark Magician or",
        "Dark Magician Girl on field",
        "or GY; Fusion Summon 1 that",
        "mentions it by shuffling it",
        "in (banish next End Phase).",
    ],
    "THE_MELODY_OF_AWAKENING_DRAGON": [
        "Discard 1 card; add up to",
        "2 Dragons with 3000+ ATK",
        "and 2500 or less DEF from",
        "your Deck to your hand.",
    ],
    "THE_WHITE_STONE_OF_ANCIENTS": [
        "End Phase: if sent to GY",
        "this turn, SS 1 Blue-Eyes",
        "from your Deck.",
        "Banish from GY: add 1",
        "Blue-Eyes from GY to hand.",
    ],
    "THE_WHITE_STONE_OF_LEGEND": [
        "If this card is sent to",
        "the GY: add 1 Blue-Eyes",
        "White Dragon from your",
        "Deck to your hand.",
    ],
    "TIMEAEUS_THE_UNITED_MAGICAL_DRAGON": [
        "DM or DMG + Dragon/",
        "Spellcaster. After SS,",
        "unaffected until next turn.",
        "Battle: +100 ATK per Spell",
        "in GY/banish. Opp: destroy S/T.",
    ],
    "TIMEAUS_THE_UNITED_DRAGON": [
        "Send 1 Spellcaster or S/T",
        "mentioning Dark Magician",
        "from hand/field to GY; SS",
        "this from hand. Main: Fusion",
        "Summon including Spellcaster.",
    ],
    "TOHUSHADDOLL_GRYSTA": [
        "FLIP: target 1 non-Rock",
        "Shaddoll in GY; apply its",
        "FLIP effect.",
        "If sent to GY by effect:",
        "Fusion Summon Shaddoll Fusion.",
    ],
    "TRAP_TRICK": [
        "Banish 1 Normal Trap from",
        "Deck; Set 1 with same name",
        "from Deck, usable this turn.",
        "Only activate 1 Trap for",
        "the rest of this turn.",
    ],
    "TRIANGLE_ECSTASY_SPARK": [
        "Until end of turn, all",
        "Harpie Lady Sisters become",
        "2700 ATK, opponent cannot",
        "activate Traps, and negate",
        "their Trap effects on field.",
    ],
    "ULTRA_POLYMERIZATION": [
        "Pay 2000 LP; Fusion Summon",
        "using 2 monsters you",
        "control. Cannot respond.",
        "GY: SS materials of a",
        "Fusion made by this (0 ATK).",
    ],
    "VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES": [
        "Must first be SS with Rise",
        "of the Snake Deity. +500",
        "ATK per Reptile in GY.",
        "Immune/untargetable. Battle",
        "destroy: SS self. 3 Counters: win.",
    ],
    "VENNOMINON_THE_KING_OF_POISONOUS_SNAKES": [
        "Cannot be SS by another",
        "Effect Monster. Unaffected",
        "by Venom Swamp. +500 ATK",
        "per Reptile in GY. If",
        "destroyed by battle: SS self.",
    ],
    "VENOM_BOA": [
        "Once per turn: place 2",
        "Venom Counters on 1",
        "monster your opponent",
        "controls. If you do, this",
        "cannot attack this turn.",
    ],
}

FIXED_POPUPS = {
    "SNAKE_RAIN": "Discard 1; send 4 Reptiles from Deck to GY.",
    "SNAKE_WHISTLE": "If Reptile destroyed: SS Lv4- Reptile from Deck.",
    "SOUL_SERVANT": "Stack DM card on Deck. GY: draw for Palladium/DM.",
    "STARDUST_DRAGON": "Tribute to negate destruction; SS from GY later.",
    "SUPREME_KINGS_CASTLE": "Enable Dark Fusion. Fiend battle: send Evil HERO.",
    "THAT_GRASS_LOOKS_GREENER": "If Deck larger: mill until Deck sizes match.",
    "THE_DARK_MAGICIANS": "OPT draw on S/T. If destroyed: SS DM and DMG.",
    "THE_GAZE_OF_TIMAEUS": "Shuffle DM/DMG; Fusion Summon mentioning it.",
    "THE_MELODY_OF_AWAKENING_DRAGON": "Discard 1; add up to 2 high-ATK Dragons.",
    "THE_WHITE_STONE_OF_ANCIENTS": "End Phase: SS Blue-Eyes. Banish: add Blue-Eyes.",
    "THE_WHITE_STONE_OF_LEGEND": "If sent to GY: add Blue-Eyes White Dragon.",
    "TIMEAEUS_THE_UNITED_MAGICAL_DRAGON": "Unaffected after SS. ATK boost. Destroy S/T.",
    "TIMEAUS_THE_UNITED_DRAGON": "Send mat to SS. Main: Fusion with Spellcaster.",
    "TOHUSHADDOLL_GRYSTA": "FLIP: copy Shaddoll FLIP. GY: Shaddoll Fusion.",
    "TRAP_TRICK": "Banish Normal Trap; Set same name, usable now.",
    "TRIANGLE_ECSTASY_SPARK": "Sisters 2700 ATK; negate opponent Trap effects.",
    "ULTRA_POLYMERIZATION": "Pay 2000; Fusion 2. GY: SS used materials.",
    "VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES": "ATK per Reptile. Immune. 3 Hyper-Venom: win.",
    "VENNOMINON_THE_KING_OF_POISONOUS_SNAKES": "ATK per Reptile. If destroyed: banish; SS self.",
    "VENOM_BOA": "OPT: place 2 Venom Counters; cannot attack.",
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
