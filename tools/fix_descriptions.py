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
    "HARPIE_DANCER": [
        "Target 1 WIND you control; return it,",
        "then you can Normal Summon 1 WIND. OPT.",
        "Name becomes Harpie Lady on field/GY.",
    ],
    "HARPIE_HARPIST": [
        "Name becomes Harpie Lady on field/GY.",
        "On NS: return 1 other Winged Beast to",
        "hand; add 1 Lv4- Winged Beast from Deck.",
        "If sent to GY this turn: add 1 Harpie",
        "from Deck during End Phase. Each OPT.",
    ],
    "HARPIE_LADY_ELEGANCE": [
        "Shuffle 1 Harpie Lady Sisters into Deck;",
        "SS 3 different Harpies from hand/Deck/GY.",
        "Harpie SS lock rest of turn. If destroyed",
        "by opp or own effect: add 1 Harpie from",
        "Deck. You can activate this from hand.",
    ],
    "HARPIE_ORACLE": [
        "Name becomes Harpie Lady on field/GY.",
        "If you control Lv5+ Harpie: SS this from",
        "hand. If SS: add 1 Spell/Trap from GY",
        "that lists Harpie Lady Sisters. Each OPT.",
    ],
    "HARPIE_PERFUMER": [
        "Name becomes Harpie Lady on field/GY.",
        "On NS/SS: add 1 Spell/Trap that lists",
        "Harpie Lady Sisters from Deck. If you",
        "controlled a Dragon, add another with",
        "a different name. OPT.",
    ],
    "HARPIE_QUEEN": [
        "Name becomes Harpie Lady on field/GY.",
        "Discard this; add 1 Harpies' Hunting",
        "Ground from your Deck to your hand.",
    ],
    "HARPIES_FEATHER_REST": [
        "Target 3 Harpie Lady and/or Sisters in",
        "GY; shuffle them, draw 1 (or 2 if you",
        "controlled Lv5+ Harpie). Then WIND SS",
        "lock. Activate only 1 Feather Rest/turn.",
    ],
    "HARPIES_FEATHER_STORM": [
        "If you control WIND Winged Beast: negate",
        "opp monster effects this turn. Can activate",
        "from hand with a Harpie. If destroyed by",
        "opp: add 1 Harpie's Feather Duster from",
        "Deck to hand.",
    ],
    "HARPIES_HUNTING_GROUND": [
        "Winged Beasts gain 200 ATK/DEF. When",
        "Harpie Lady or Sisters is NS/SS: that",
        "player targets and destroys 1 Spell/Trap.",
    ],
    "HARPIES_PET_PHANTASMAL_DRAGON": [
        "3 Lv4 WIND. Needs material to apply.",
        "Can attack directly. Opp can't target",
        "Harpies with effects/attacks. Each your",
        "End Phase: detach 1 material from this.",
    ],
    "HELSHADDOLL_HOLLOW": [
        "FLIP: target 1 face-up opp; send 1",
        "Shaddoll with same Attribute from Extra",
        "to GY, banish that monster. If sent to",
        "GY by effect: mill Extra equal to field",
        "monster count. Use only 1 effect/turn.",
    ],
    "HERALD_OF_PERFECTION": [
        "Ritual with Dawn of the Herald. When",
        "opp activates Spell/Trap/monster effect:",
        "send 1 Fairy from hand to GY; negate",
        "and destroy it.",
    ],
    "HERALD_OF_ULTIMATENESS": [
        "Ritual with Oracle of the Herald. Must",
        "be Ritual Summoned. When opp would SS",
        "or activate Spell/Trap/monster effect:",
        "send 1 Fairy from hand to GY; negate",
        "and destroy that card.",
    ],
    "HERO_KID": [
        "When this card is Special Summoned: You",
        "can SS any number of Hero Kid from Deck.",
    ],
    "HUMID_WINDS": [
        "Pay 1000 LP; add 1 Aroma from Deck.",
        "If your LP is lower: gain 500 LP.",
        "Each effect OPT.",
    ],
    "HYSTERIC_PARTY": [
        "Discard 1; SS as many Harpie Lady from",
        "GY as possible. When this leaves the",
        "field, destroy those monsters.",
    ],
    "HYSTERIC_SIGN": [
        "On activate: add 1 Elegant Egotist from",
        "Deck or GY. If sent from hand/field to",
        "GY this turn: at End Phase add up to 3",
        "Harpies with different names from Deck.",
        "Use only 1 effect per turn.",
    ],
    "ILLUSION_MAGIC": [
        "Tribute 1 Spellcaster; add up to 2 Dark",
        "Magician from Deck and/or GY to hand.",
        "Activate only 1 Illusion Magic per turn.",
    ],
    "ILLUSION_OF_CHAOS": [
        "Ritual with Chaos Form. Reveal in hand:",
        "add Dark Magician or a non-Ritual that",
        "mentions it; place 1 hand card on Deck.",
        "When opp activates monster effect: return",
        "this; SS Dark Magician from GY, negate.",
    ],
    "IPIRIA": [
        "If this card is Summoned: Draw 1 card.",
        "You can only use this effect once per turn.",
    ],
}

FIXED_POPUPS = {
    "HARPIE_DANCER": "Return 1 WIND; then Normal Summon 1 WIND. Name Lady. OPT.",
    "HARPIE_HARPIST": "Name Lady. On NS: bounce/search Winged Beast. GY: search Harpie.",
    "HARPIE_LADY_ELEGANCE": "Shuffle Sisters; SS 3 Harpies. Hand-activatable. Search if destroyed.",
    "HARPIE_ORACLE": "Name Lady. SS from hand with Lv5+ Harpie; GY search S/T. OPT.",
    "HARPIE_PERFUMER": "Name Lady. On summon: search S/T listing Sisters (+extra w/ Dragon).",
    "HARPIE_QUEEN": "Name Lady. Discard this; add Harpies' Hunting Ground from Deck.",
    "HARPIES_FEATHER_REST": "Shuffle 3 Harpies from GY; draw 1 (or 2). Then WIND SS lock.",
    "HARPIES_FEATHER_STORM": "Negate opp monster effects. Hand-activatable. GY: search Duster.",
    "HARPIES_HUNTING_GROUND": "Winged Beast +200. On Harpie Lady/Sisters summon: destroy 1 S/T.",
    "HARPIES_PET_PHANTASMAL_DRAGON": "Direct attack. Protect Harpies. End Phase: detach 1 material.",
    "HELSHADDOLL_HOLLOW": "FLIP: banish via Shaddoll mill. GY: mill Extra = field count.",
    "HERALD_OF_PERFECTION": "Send Fairy from hand; negate opp Spell/Trap/monster and destroy.",
    "HERALD_OF_ULTIMATENESS": "Send Fairy from hand; negate opp SS or Spell/Trap/monster.",
    "HERO_KID": "On Special Summon: SS any number of Hero Kid from your Deck.",
    "HUMID_WINDS": "Pay 1000: search Aroma. If LP lower: gain 500. Each OPT.",
    "HYSTERIC_PARTY": "Discard 1; SS Harpie Lady from GY. Leaving field destroys them.",
    "HYSTERIC_SIGN": "Search Elegant Egotist. If sent: End Phase search up to 3 Harpies.",
    "ILLUSION_MAGIC": "Tribute Spellcaster; add up to 2 Dark Magician from Deck/GY.",
    "ILLUSION_OF_CHAOS": "Hand reveal: search DM. Opp monster effect: bounce; SS DM, negate.",
    "IPIRIA": "If Summoned: draw 1. Once per turn.",
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
