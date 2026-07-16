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
    "REPTILIANNE_SCYLLA": [
        "If this destroys a monster with 0 ATK",
        "by battle, you can Special Summon that",
        "monster to your side of the field in",
        "face-up Defense Position.",
    ],
    "REPTILIANNE_SERVANT": [
        "Destroy this if there are face-up",
        "monsters on the field other than this",
        "card. Your opponent cannot select this",
        "as an attack target.",
    ],
    "REPTILIANNE_SPAWN": [
        "Banish 1 Reptilianne from your GY;",
        "Special Summon 2 Reptilianne Tokens",
        "(Reptile/EARTH/Lv1/ATK 0/DEF 0).",
    ],
    "REPTILIANNE_VASKII": [
        "Cannot be Normal Summoned/Set. Must",
        "first be Special Summoned by Tributing",
        "2 face-up monsters with 0 ATK. OPT:",
        "destroy 1 face-up monster your",
        "opponent controls.",
    ],
    "REPTILIANNE_VIPER": [
        "When this is Normal Summoned: you can",
        "target 1 face-up monster with 0 ATK",
        "your opponent controls; take control",
        "of that target.",
    ],
    "RETURN_OF_THE_DRAGON_LORDS": [
        "Target 1 Level 7 or 8 Dragon in your",
        "GY; Special Summon it. If a Dragon you",
        "control would be destroyed by battle",
        "or card effect while this is in GY:",
        "you can banish this instead.",
    ],
    "RISE_OF_THE_SNAKE_DEITY": [
        "When a face-up Vennominon the King of",
        "Poisonous Snakes you control is",
        "destroyed, except by its own effect:",
        "Special Summon 1 Vennominaga the Deity",
        "of Poisonous Snakes from hand/Deck.",
    ],
    "SECRETS_OF_DARK_MAGIC": [
        "Activate 1: Fusion Summon 1 Fusion",
        "using monsters from hand/field,",
        "including a DARK Spellcaster. Or",
        "Ritual Summon 1 Ritual using monsters",
        "from hand/field including a DARK Spellcaster.",
    ],
    "SERPENT_SUPPRESSION": [
        "Face-up Attack Position monsters with",
        "0 ATK your opponent controls cannot be",
        "destroyed by battle.",
    ],
    "SHADDOLL_BEAST": [
        "FLIP: You can draw 2 cards, then",
        "discard 1. If this card is sent to the",
        "GY by a card effect: you can draw 1",
        "card. You can only use 1 Shaddoll",
        "Beast effect per turn, and only once that turn.",
    ],
    "SHADDOLL_CORE": [
        "Special Summon this as an Effect",
        "Monster (Spellcaster/DARK/Lv9/ATK",
        "1450/DEF 1950). (This card is also",
        "still a Trap.) If Tributed: target 1",
        "Shaddoll in GY; add it to your hand.",
    ],
    "SHADDOLL_DRAGON": [
        "FLIP: Target 1 card your opponent",
        "controls; return it to the hand. If",
        "this is sent to GY by a card effect:",
        "you can target 1 Spell/Trap your",
        "opponent controls; destroy it. 1 effect/turn.",
    ],
    "SHADDOLL_FALCO": [
        "FLIP: Target 1 Shaddoll in your GY,",
        "except Falco; Special Summon it in",
        "face-down Defense. If sent to GY by",
        "a card effect: you can Special Summon",
        "this in face-down Defense. 1 effect/turn.",
    ],
    "SHADDOLL_FUSION": [
        "Fusion Summon 1 Shaddoll Fusion from",
        "your Extra Deck, using monsters from",
        "hand or field as Fusion Material. If",
        "your opponent controls a monster from",
        "Extra Deck, you can also use from Deck.",
    ],
    "SHADDOLL_HEDGEHOG": [
        "FLIP: You can add 1 Shaddoll Spell/",
        "Trap from your Deck to your hand. If",
        "this is sent to GY by a card effect:",
        "you can add 1 Shaddoll monster from",
        "Deck to hand. 1 effect per turn.",
    ],
    "SHADDOLL_HOUND": [
        "FLIP: Target 1 Shaddoll in your GY;",
        "add it to your hand. If this is sent",
        "to GY by a card effect: you can target",
        "1 monster on the field; change it to",
        "face-up Attack or face-down Defense.",
    ],
    "SHADDOLL_SCHISM": [
        "Main Phase: Fusion Summon 1 Shaddoll",
        "Fusion from Extra, banishing Fusion",
        "Materials from field and/or GY, but",
        "it cannot attack this turn. Then you",
        "can send 1 monster your opponent controls to GY.",
    ],
    "SHADDOLL_SQUAMATA": [
        "FLIP: Target 1 monster on the field;",
        "destroy it. If this is sent to GY by",
        "a card effect: you can send 1 Shaddoll",
        "card from Deck to GY, except Squamata.",
        "You can only use 1 effect per turn.",
    ],
    "SILVERS_CRY": [
        "Target 1 Dragon Normal Monster in",
        "your GY; Special Summon that target.",
        "You can only activate 1 Silver's Cry",
        "per turn.",
    ],
    "SNAKE_DEITYS_COMMAND": [
        "Activate by revealing 1 Venom monster",
        "in your hand. Negate the activation",
        "of an opponent's Spell Card and",
        "destroy it.",
    ],
}

FIXED_POPUPS = {
    "REPTILIANNE_SCYLLA": "If destroys 0 ATK by battle: SS that monster in Defense.",
    "REPTILIANNE_SERVANT": "Self-destroy if other face-up. Opp cannot attack this.",
    "REPTILIANNE_SPAWN": "Banish 1 Reptilianne from GY; SS 2 Tokens (ATK/DEF 0).",
    "REPTILIANNE_VASKII": "SS by Tributing 2 with 0 ATK. OPT: destroy 1 face-up opp.",
    "REPTILIANNE_VIPER": "On NS: take control of 1 face-up opp monster with 0 ATK.",
    "RETURN_OF_THE_DRAGON_LORDS": "SS Lv7/8 Dragon from GY. GY: banish instead of destroy Dragon.",
    "RISE_OF_THE_SNAKE_DEITY": "When Vennominon destroyed: SS Vennominaga from hand/Deck.",
    "SECRETS_OF_DARK_MAGIC": "Fusion or Ritual Summon using DARK Spellcaster materials.",
    "SERPENT_SUPPRESSION": "Opp Attack Position 0 ATK monsters cannot be destroyed by battle.",
    "SHADDOLL_BEAST": "FLIP: draw 2, discard 1. Sent by effect: draw 1. 1/turn.",
    "SHADDOLL_CORE": "SS as monster. If Tributed: add 1 Shaddoll from GY to hand.",
    "SHADDOLL_DRAGON": "FLIP: bounce 1 opp. Sent by effect: destroy 1 opp S/T.",
    "SHADDOLL_FALCO": "FLIP: SS Shaddoll face-down. Sent by effect: SS this face-down.",
    "SHADDOLL_FUSION": "Fusion Summon Shaddoll. If opp Extra: can use materials from Deck.",
    "SHADDOLL_HEDGEHOG": "FLIP: add Shaddoll S/T. Sent by effect: add Shaddoll monster.",
    "SHADDOLL_HOUND": "FLIP: add Shaddoll from GY. Sent by effect: change battle position.",
    "SHADDOLL_SCHISM": "Fusion Summon banishing mats; then send 1 opp monster to GY.",
    "SHADDOLL_SQUAMATA": "FLIP: destroy 1. Sent by effect: send 1 Shaddoll from Deck to GY.",
    "SILVERS_CRY": "Target 1 Dragon Normal in GY; Special Summon it. 1/turn.",
    "SNAKE_DEITYS_COMMAND": "Reveal Venom in hand; negate opp Spell activation and destroy it.",
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
                item["effect_texts"]["popup_1"] = FIXED_POPUPS[const]
            else:
                item["effect_texts"]["popup_1"] = FIXED_POPUPS[const]
    write_manifest(MANIFEST_PATH, manifest)
    print(f"Updated {len(FIXED_DESCRIPTIONS)} descriptions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
