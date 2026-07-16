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
    "EVIL_HERO_INFERNAL_SNIPER": [
        "Clayman + Burstinatrix. Must SS with Dark",
        "Fusion. Can't be destroyed by Spells.",
        "Each your Standby: burn opp 1000. Must be",
        "face-up Defense to use/resolve burn.",
    ],
    "EVIL_HERO_INFERNO_WING": [
        "Avian + Burstinatrix. Must SS with Dark",
        "Fusion. Piercing. If destroys by battle:",
        "burn opp equal to destroyed monster's",
        "higher ATK or DEF in GY.",
    ],
    "EVIL_HERO_INFERNO_WING_BACKFIRE": [
        "Avian or Burstinatrix + 1 HERO. Must SS",
        "with Dark Fusion. On SS: add Dark Fusion",
        "or a card that mentions it from Deck/GY",
        "(not Fusion). If your HERO destroys by",
        "battle: burn 2100. Each OPT.",
    ],
    "EVIL_HERO_LIGHTNING_GOLEM": [
        "Sparkman + Clayman. Must SS with Dark",
        "Fusion. OPT: target 1 monster on field;",
        "destroy it.",
    ],
    "EVIL_HERO_MALICIOUS_BANE": [
        "1 Evil HERO + 1 Lv5+. Must SS with Dark",
        "Fusion. Can't be destroyed by battle/effects.",
        "Main Phase OPT: destroy all opp monsters",
        "with ATK <= this; gain 200 ATK each. Only",
        "HERO can attack rest of turn.",
    ],
    "EVIL_HERO_MALICIOUS_EDGE": [
        "If opp controls a monster, Tribute Summon",
        "face-up with 1 Tribute. Piercing battle",
        "damage vs Defense Position monsters.",
    ],
    "EVIL_HERO_MALICIOUS_FIEND": [
        "Malicious Edge + 1 Lv6+ Fiend. Must SS",
        "with Dark Fusion. During opp Battle Phase,",
        "all their monsters switch to Attack, and",
        "must attack this if able.",
    ],
    "EVIL_HERO_NEOS_LORD": [
        "Neos (or Fusion that lists it) + 1 Effect",
        "on field. Must SS with Dark Fusion. Can't",
        "be destroyed by battle/effects. On SS, or",
        "when monster(s) sent to opp GY while this",
        "is up: take control of 1 face-up opp. OPT.",
    ],
    "EVIL_HERO_SINISTER_NECROM": [
        "Banish this from GY; SS 1 Evil HERO from",
        "hand or Deck, except this. OPT.",
    ],
    "EVIL_HERO_TOXIC_BUBBLE": [
        "You can SS this from hand, but can't SS",
        "except HERO rest of turn (OPT this way).",
        "If SS while you control a Dark Fusion",
        "Fusion: draw 2. OPT.",
    ],
    "EVIL_HERO_VICIOUS_CLAWS": [
        "Target 1 HERO on field; SS this from hand",
        "in Defense; that monster gains 300 ATK. OPT.",
        "If your monster is destroyed while this is",
        "in GY: SS this; if a monster that mentions",
        "Dark Fusion is in your GY, destroy 1 card.",
    ],
    "EVIL_HERO_WILD_CYCLONE": [
        "Avian + Wildheart. Must SS with Dark",
        "Fusion. If this attacks, opp can't activate",
        "Spells/Traps until end of Damage Step.",
        "When this deals battle damage: destroy all",
        "face-down Spells/Traps your opponent controls.",
    ],
    "EVIL_MIND": [
        "If you control a Fiend: based on monsters",
        "in opp GY - 1+: draw 1; 4+: add 1 HERO or",
        "Dark Fusion from Deck; 10+: add 1",
        "Polymerization or Fusion Spell from Deck.",
        "Activate only 1 Evil Mind per turn.",
    ],
    "FUSION_DEPLOYMENT": [
        "Reveal 1 Fusion in Extra Deck; SS from",
        "hand or Deck 1 Fusion Material specifically",
        "listed on it. Can't Special Summon from",
        "Extra Deck the turn you activate this,",
        "except Fusion Monsters.",
    ],
    "GANDORA_G_THE_DRAGON_OF_DESTRUCTION": [
        "Gains 300 ATK per banished card. Each OPT.",
        "If you control Shining Sarcophagus: SS",
        "this from hand. Pay half LP; destroy/banish",
        "as many other field cards as possible, then",
        "SS Lv7- that mentions Sarcophagus; raise Lv.",
    ],
    "GANDORA_X_THE_DRAGON_OF_DEMOLITION": [
        "On NS/SS from hand: destroy as many other",
        "monsters as possible; burn opp = highest",
        "original ATK among destroyed. This ATK",
        "becomes that damage. Each your End Phase:",
        "halve your LP.",
    ],
    "GOYO_GUARDIAN": [
        "1 EARTH Tuner + 1+ non-Tuner. When this",
        "destroys an opp monster by battle and sends",
        "it to GY: you can SS that monster to your",
        "field in Defense Position.",
    ],
    "GRINDER_GOLEM": [
        "Can't NS/Set. Must first SS from hand to",
        "opp field by SS 2 Grinder Tokens (Fiend/",
        "DARK/Lv1/0/0) in Attack on your field.",
        "If you SS this, can't NS/Set same turn.",
    ],
    "HARPIE_CHANNELER": [
        "Discard 1 Harpie; SS 1 Harpie from Deck",
        "in Defense except this. OPT. While you",
        "control a Dragon, this Level becomes 7.",
        "Name becomes Harpie Lady on field/GY.",
    ],
    "HARPIE_CONDUCTOR": [
        "2 WIND. Name becomes Harpie Lady on",
        "field/GY. Each OPT: if your Harpie would",
        "be destroyed, destroy 1 your S/T instead;",
        "if another face-up Harpie returns to hand:",
        "return 1 opp Special Summoned to hand.",
    ],
}

FIXED_POPUPS = {
    "EVIL_HERO_INFERNAL_SNIPER": "Dark Fusion. Spell immune. Standby: burn 1000 if face-up Defense.",
    "EVIL_HERO_INFERNO_WING": "Dark Fusion. Piercing. On battle destroy: burn higher ATK/DEF.",
    "EVIL_HERO_INFERNO_WING_BACKFIRE": "On SS: search Dark Fusion. HERO battle destroy: burn 2100.",
    "EVIL_HERO_LIGHTNING_GOLEM": "Dark Fusion. OPT: destroy 1 monster on the field.",
    "EVIL_HERO_MALICIOUS_BANE": "Destroy opp with ATK <= this; gain 200 each. HERO attack lock.",
    "EVIL_HERO_MALICIOUS_EDGE": "1 Tribute if opp has a monster. Piercing battle damage.",
    "EVIL_HERO_MALICIOUS_FIEND": "Opp Battle Phase: their monsters must attack this if able.",
    "EVIL_HERO_NEOS_LORD": "Indestructible. OPT: take control of 1 face-up opp monster.",
    "EVIL_HERO_SINISTER_NECROM": "Banish from GY: SS 1 Evil HERO from hand or Deck.",
    "EVIL_HERO_TOXIC_BUBBLE": "SS from hand (HERO lock). If Dark Fusion Fusion up: draw 2.",
    "EVIL_HERO_VICIOUS_CLAWS": "SS from hand; HERO +300. GY: SS when destroyed; maybe destroy 1.",
    "EVIL_HERO_WILD_CYCLONE": "On attack: lock S/T. On battle damage: destroy face-down S/T.",
    "EVIL_MIND": "If Fiend: draw / search HERO or Dark Fusion / search Poly by GY count.",
    "FUSION_DEPLOYMENT": "Reveal Fusion; SS 1 listed material. ED lock except Fusions.",
    "GANDORA_G_THE_DRAGON_OF_DESTRUCTION": "+300 ATK/banished. Pay half LP: nuke field, SS Sarcophagus monster.",
    "GANDORA_X_THE_DRAGON_OF_DEMOLITION": "On summon from hand: nuke monsters, gain ATK = burn. End: half LP.",
    "GOYO_GUARDIAN": "If destroys by battle: SS that monster to your field in Defense.",
    "GRINDER_GOLEM": "SS to opp field; make 2 Tokens on yours. No NS/Set that turn.",
    "HARPIE_CHANNELER": "Discard Harpie; SS Harpie from Deck. Lv7 with Dragon. Name Lady.",
    "HARPIE_CONDUCTOR": "Name Lady. Protect Harpie / bounce opp SS when Harpie returns.",
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
