#!/usr/bin/env python3
"""Retry failed cards by adding them to the manifest using exact API names."""

from __future__ import annotations

import json
import re
import sys
import time
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import (
    load_manifest_json,
    order_card_entry,
    write_manifest,
)

MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"
YGO_API = "https://db.ygoprodeck.com/api/v7/cardinfo.php"

ATTRIBUTE_MAP = {
    "DARK": "ATTRIBUTE_SHADOW",
    "LIGHT": "ATTRIBUTE_LIGHT",
    "FIRE": "ATTRIBUTE_FIRE",
    "WATER": "ATTRIBUTE_WATER",
    "WIND": "ATTRIBUTE_WIND",
    "EARTH": "ATTRIBUTE_EARTH",
    "DIVINE": "ATTRIBUTE_DIVINE",
}

RACE_MAP = {
    "Dragon": "TYPE_DRAGON",
    "Spellcaster": "TYPE_SPELLCASTER",
    "Zombie": "TYPE_ZOMBIE",
    "Warrior": "TYPE_WARRIOR",
    "Beast-Warrior": "TYPE_BEAST_WARRIOR",
    "Beast": "TYPE_BEAST",
    "Winged Beast": "TYPE_WINGED_BEAST",
    "Fiend": "TYPE_FIEND",
    "Fairy": "TYPE_FAIRY",
    "Insect": "TYPE_INSECT",
    "Dinosaur": "TYPE_DINOSAUR",
    "Fish": "TYPE_FISH",
    "Reptile": "TYPE_REPTILE",
    "Sea Serpent": "TYPE_SEA_SERPENT",
    "Machine": "TYPE_MACHINE",
    "Thunder": "TYPE_THUNDER",
    "Aqua": "TYPE_AQUA",
    "Pyro": "TYPE_PYRO",
    "Rock": "TYPE_ROCK",
    "Plant": "TYPE_PLANT",
    "Cyberse": "TYPE_CYBERSE",
    "Psychic": "TYPE_PSYCHIC",
    "Wyrm": "TYPE_WYRM",
}

COLOR_BY_FRAME = {
    "normal": "NORMAL_CARD",
    "effect": "EFFECT_CARD",
    "fusion": "FUSION_CARD",
    "ritual": "RITUAL_CARD",
    "spell": "SPELL_CARD",
    "trap": "TRAP_CARD",
}

STUB_DESC = "Custom card."


def card_name_to_const(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9]+", "_", name.strip()).strip("_").upper()


def passcode_to_password(passcode: int | str) -> list[int] | None:
    try:
        val = int(str(passcode).strip())
        if val <= 0 or val > 99999999:
            return None
        digits = [int(d) for d in f"{val:08d}"]
        if len(digits) == 8 and all(0 <= d <= 15 for d in digits):
            return digits
        return None
    except (ValueError, TypeError):
        return None


def wrap_to_pages(text: str, page_count: int = 2, width: int = 27) -> list[str]:
    import textwrap
    wrapped = textwrap.wrap(text.strip(), width=width)
    if not wrapped:
        return [STUB_DESC, STUB_DESC]
    if len(wrapped) <= page_count:
        result = wrapped[:]
        while len(result) < page_count:
            result.append(STUB_DESC)
        return result
    chunk = max(1, (len(wrapped) + page_count - 1) // page_count)
    pages = []
    for start in range(0, len(wrapped), chunk):
        pages.append(" ".join(wrapped[start:start + chunk]))
    while len(pages) < page_count:
        pages.append(STUB_DESC)
    return pages[:page_count]


def fetch_exact(name: str) -> list[dict]:
    params = urllib.parse.urlencode({"name": name})
    url = f"{YGO_API}?{params}"
    req = urllib.request.Request(url, headers={"User-Agent": "ygodm8-retry/1.0"})
    with urllib.request.urlopen(req, timeout=15) as r:
        return json.load(r).get("data", [])


def frame_kind(card_type: str) -> str:
    lowered = card_type.lower()
    for key in ("normal", "effect", "fusion", "ritual", "spell", "trap", "synchro"):
        if key in lowered:
            return "effect" if key == "synchro" else key
    return "effect"


def suggest_cost(manifest: dict, entry: dict) -> int:
    best_cost = 150
    best_score = None
    for item in manifest["cards"]:
        score = 0
        if item.get("color") != entry["color"]:
            score += 100
        score += abs(item.get("level", 0) - entry["level"]) * 10
        score += abs(item.get("atk", 0) - entry["atk"]) // 100
        score += abs(item.get("def", 0) - entry["def"]) // 100
        if best_score is None or score < best_score:
            best_score = score
            best_cost = item["cost"]
    return best_cost


def build_entry(api_card: dict, manifest: dict, override_const: str | None = None) -> dict | None:
    frame = frame_kind(api_card["type"])
    color = COLOR_BY_FRAME[frame]
    card_name = api_card["name"]
    card_const = override_const if override_const else card_name_to_const(card_name)

    passcode_raw = api_card.get("id", "0")
    password = passcode_to_password(passcode_raw)
    if password is None:
        name_hash = sum(ord(c) for c in card_name) % 99999999
        password = passcode_to_password(name_hash)
        if password is None:
            password = [1, 5, 0, 0, 0, 0, 0, 0]

    desc_text = api_card.get("desc", "")
    if desc_text:
        pages = wrap_to_pages(desc_text, 2)
    else:
        pages = ["Custom card.", "Custom card."]

    if frame in ("spell", "trap"):
        entry = order_card_entry({
            "card_const": card_const,
            "card_name": card_name,
            "atk": 65535,
            "def": 65535,
            "level": 0,
            "attribute": 0,
            "type": "TYPE_TRAP" if frame == "trap" else "TYPE_SPELL",
            "color": color,
            "monsterEffect": 0,
            "spellEffect": 2,
            "trapEffect": 0,
            "cost": suggest_cost(manifest, {"color": color, "level": 0, "atk": 65535, "def": 65535}),
            "password": password,
            "description": {"pages": pages},
            "effect_texts": {"popup_1": STUB_DESC},
        })
        return entry

    race = api_card.get("race", "")
    card_type = RACE_MAP.get(race)
    if card_type is None:
        print(f"  WARNING: Unknown race {race!r} for {card_const}, using TYPE_WARRIOR", file=sys.stderr)
        card_type = "TYPE_WARRIOR"

    attribute = ATTRIBUTE_MAP.get(api_card.get("attribute", ""))
    if attribute is None:
        attribute = "ATTRIBUTE_EARTH"

    atk = int(api_card["atk"]) if api_card.get("atk") is not None else 0
    def_ = int(api_card["def"]) if api_card.get("def") is not None else 0
    level = int(api_card.get("level", 0))

    is_normal = frame == "normal"
    entry = order_card_entry({
        "card_const": card_const,
        "card_name": card_name,
        "atk": atk,
        "def": def_,
        "level": level,
        "attribute": attribute,
        "type": card_type,
        "color": color,
        "monsterEffect": 0,
        "spellEffect": 2,
        "trapEffect": 0,
        "cost": suggest_cost(manifest, {"color": color, "level": level, "atk": atk, "def": def_}),
        "password": password,
        "description": {"pages": pages},
    })

    if color == "EFFECT_CARD" and not is_normal:
        entry["effect_texts"] = {"popup_1": STUB_DESC}

    return entry


def create_stub_and_wire(card_const: str, effect_type: str) -> None:
    import subprocess
    lower = card_const.lower()
    if effect_type == "spell":
        hook_dir = ROOT / "src_custom" / "spell_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(STUB_SPELL_TEMPLATE.format(const=card_const))
            print(f"  Created spell stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)
        return

    if effect_type in ("activated", "permanent"):
        template = STUB_ACTIVATED_TEMPLATE if effect_type == "activated" else STUB_PERMANENT_TEMPLATE
        hook_dir = ROOT / "src_custom" / f"{effect_type}_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(template.format(const=card_const))
            print(f"  Created {effect_type} stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)

        script = ROOT / "tools" / "wire_card_effect.py"
        subprocess.run([sys.executable, str(script), card_const, "--type", effect_type],
                       capture_output=True)

        # Add monster effect const
        me_path = ROOT / "include" / "constants" / "monster_effects.h"
        me_text = me_path.read_text()
        me_const = f"MONSTER_EFFECT_{card_const}"
        if me_const not in me_text:
            insert_pos = me_text.rfind("};")
            if insert_pos >= 0:
                me_text = me_text[:insert_pos] + f"  {me_const},\n" + me_text[insert_pos:]
                me_path.write_text(me_text)
                print(f"  Added {me_const} to monster_effects.h", file=sys.stderr)

    if effect_type == "trap":
        hook_dir = ROOT / "src_custom" / "trap_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(STUB_TRAP_TEMPLATE.format(const=card_const))
            print(f"  Created trap stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)
        script = ROOT / "tools" / "wire_card_effect.py"
        subprocess.run([sys.executable, str(script), card_const, "--type", "trap"],
                       capture_output=True)


def classify_effect_type(api_card: dict) -> str | None:
    ct = api_card.get("type", "").lower()
    if "spell" in ct:
        return "spell"
    if "trap" in ct:
        return "trap"
    if "normal" in ct:
        return None
    desc = api_card.get("desc", "")
    if not desc:
        return None
    has_ignition = any(kw in desc.lower() for kw in [
        "you can", "once per turn", "activate", "when this card",
        "if this card", "flip:", "this card gains", "this card can",
        "cannot be", "is unaffected", "cannot be destroyed",
        "negate", " tribute", "special summon", "add to your hand",
    ])
    if has_ignition:
        return "activated"
    return "permanent"


STUB_SPELL_TEMPLATE = """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static void {const}_ResolveBody(void)
{{
  Duel_ShowEffectText({const});

  /* TODO: implement effect */
}}

APPEND_TEXT void Effect{const}(void)
{{
  if (Duel_TryResolveSpellThroughTraps({const}, {const}_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}}
"""

STUB_TRAP_TEMPLATE = """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

/* TODO: implement trap effect for {const} */
"""

STUB_ACTIVATED_TEMPLATE = """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{{
  /* TODO: implement target validation */
  (void)fixedRow;
  (void)fixedCol;
  return FALSE;
}}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{{
  /* TODO: implement target resolution */
  (void)fixedRow;
  (void)fixedCol;
}}

static void CancelTargeting(void)
{{
  PlayMusic(SFX_CANCEL);
}}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{{
  /* TODO: implement AI target selection */
  (void)outRow;
  (void)outCol;
  return FALSE;
}}

unsigned char CanActivate{const}(void)
{{
  if (gMonEffect.id != {const})
    return FALSE;
  return TRUE; /* TODO: add additional activation conditions */
}}

void Activate{const}Effect(void)
{{
  Duel_ShowEffectTextTyped({const}, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}}
"""

STUB_PERMANENT_TEMPLATE = """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "summon_tribute.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void SetCursorToCardDest(void);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{{
  /* TODO: implement target validation */
  (void)fixedRow;
  (void)fixedCol;
  return FALSE;
}}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{{
  /* TODO: implement target resolution */
  (void)fixedRow;
  (void)fixedCol;
}}

static void CancelTargeting(void)
{{
  PlayMusic(SFX_CANCEL);
}}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{{
  /* TODO: implement AI target selection */
  (void)outRow;
  (void)outCol;
  return FALSE;
}}

unsigned char ShouldActivate{const}(void)
{{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != {const})
    return FALSE;

  if (GetPendingTributeSummonCardId() != {const})
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  /* TODO: add field-has-target check */
  return TRUE;
}}

void Activate{const}(void)
{{
  u8 originRow = gActiveEffect.turnRow;
  u8 originCol = gActiveEffect.col;

  Duel_ShowEffectTextTyped({const}, 8);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER && originRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}}
"""


def main() -> int:
    manifest = load_manifest_json(MANIFEST_PATH)
    # Normalize: treat D_D_WARRIOR as D_D_WARRIOR for comparison
    def normalize_const(c):
        return c.replace(".", "_")
    existing_consts = {normalize_const(c["card_const"]) for c in manifest["cards"]}

    # Cards to retry: (card_const_from_todo, search_name, override_const)
    to_retry = [
        ("DESTINY_HERO_BLADE_MASTER", "Destiny HERO - Blade Master", None),
        ("DESTINY_HERO_CAPTAIN_TENACIOUS", "Destiny HERO - Captain Tenacious", None),
        ("DESTINY_HERO_CELESTIAL", "Destiny HERO - Celestial", None),
        ("DESTINY_HERO_DANGEROUS", "Destiny HERO - Dangerous", None),
        ("DESTINY_HERO_DARK_ANGEL", "Destiny HERO - Dark Angel", None),
        ("DESTINY_HERO_DASHER", "Destiny HERO - Dasher", None),
        ("DESTINY_HERO_DECIDER", "Destiny HERO - Decider", None),
        ("DESTINY_HERO_DEFENDER", "Destiny HERO - Defender", None),
        ("DESTINY_HERO_DENIER", "Destiny HERO - Denier", None),
        ("DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER", "Destiny HERO - Destroyer Phoenix Enforcer", None),
        ("DESTINY_HERO_DIAMOND_DUDE", "Destiny HERO - Diamond Dude", None),
        ("DESTINY_HERO_DISK_COMMANDER", "Destiny HERO - Disk Commander", None),
        ("DESTINY_HERO_DOGMA", "Destiny HERO - Dogma", None),
        ("DESTINY_HERO_DOMINANCE", "Destiny HERO - Dominance", None),
        ("DESTINY_HERO_DOOM_LORD", "Destiny HERO - Doom Lord", None),
        ("DESTINY_HERO_DOOM_OVERLORD", "Destiny HERO - Doom Overlord", None),
        ("DESTINY_HERO_DOUBLE_DUDE", "Destiny HERO - Double Dude", None),
        ("DESTINY_HERO_DRAWHAND", "Destiny HERO - Drawhand", None),
        ("DESTINY_HERO_DREAD_SERVANT", "Destiny HERO - Dread Servant", None),
        ("DESTINY_HERO_DREADMASTER", "Destiny HERO - Dreadmaster", None),
        ("DESTINY_HERO_DREADNOUGHT_MASTER", "Destiny HERO - Dreadnought Master", None),
        ("DESTINY_HERO_DREADNOUGHT_SERVANT", "Destiny HERO - Dreadnought Servant", None),
        ("DESTINY_HERO_DREAMER", "Destiny HERO - Dreamer", None),
        ("DESTINY_HERO_DRILLDARK", "Destiny HERO - Drilldark", None),
        ("DESTINY_HERO_DUNKER", "Destiny HERO - Dunker", None),
        ("DESTINY_HERO_DUSKTOPIA", "Destiny HERO - Dusktopia", None),
        ("DESTINY_HERO_DYNATAG", "Destiny HERO - Dynatag", None),
        ("DESTINY_HERO_DYSTOPIA", "Destiny HERO - Dystopia", None),
        ("DESTINY_HERO_FEAR_MONGER", "Destiny HERO - Fear Monger", None),
        ("DESTINY_HERO_MALICIOUS", "Destiny HERO - Malicious", None),
        ("DESTINY_HERO_PLASMA", "Destiny HERO - Plasma", None),
        ("D_D_WARRIOR", "D.D. Warrior", None),
        ("BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON", "Blue-Eyes Alternative Ultimate Dragon", None),
        ("CELESTIAL_SWORD_EATOS", "Celestial Sword - Eatos", None),
        ("EXODIUS_THE_ULTIMATE_FORBIDDEN_LORD", "Exodius the Ultimate Forbidden Lord", None),
        ("MAJESTIC_MECH_GORYU", "Majestic Mech - Goryu", None),
        ("NEO_BLUE_EYES_ULTIMATE_DRAGON", "Neo Blue-Eyes Ultimate Dragon", None),
        ("REAPER_SCYTHE_DREADSCYTHE", "Reaper Scythe - Dreadscythe", None),
        ("RED_EYES_BLACK_DRAGON_SWORD", "Red-Eyes Black Dragon Sword", None),
        ("RED_EYES_DARK_DRAGOON", "Red-Eyes Dark Dragoon", None),
        ("RED_EYES_DARKNESS_METAL_DRAGON", "Red-Eyes Darkness Metal Dragon", None),
        ("RED_EYES_TRANSMIGRATION", "Red-Eyes Transmigration", None),
        ("SKYSCRAPER_2_HERO_CITY", "Skyscraper 2 - Hero City", None),
        ("THE_AGENT_OF_JUDGMENT_SATURN", "The Agent of Judgment - Saturn", None),
        ("THE_AGENT_OF_WISDOM_MERCURY", "The Agent of Wisdom - Mercury", None),
        ("D_BURST", "D - Burst", None),
        ("D_FORCE", "D - Force", None),
        ("D_TACTICS", "D - Tactics", None),
        ("D_TIME", "D - Time", None),
        # Cards that need override const (API name differs from TODO const)
        ("ARMED_DRAGON_LEVEL_FIVE", "Armed Dragon LV5", "ARMED_DRAGON_LEVEL_FIVE"),
        ("ARMED_DRAGON_LEVEL_SEVEN", "Armed Dragon LV7", "ARMED_DRAGON_LEVEL_SEVEN"),
        ("ARMED_DRAGON_LEVEL_TEN", "Armed Dragon LV10", "ARMED_DRAGON_LEVEL_TEN"),
        ("ARMED_DRAGON_LEVEL_THREE", "Armed Dragon LV3", "ARMED_DRAGON_LEVEL_THREE"),
        ("HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_EIGHT", "Horus the Black Flame Dragon LV8", "HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_EIGHT"),
        ("HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_FOUR", "Horus the Black Flame Dragon LV4", "HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_FOUR"),
        ("HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_SIX", "Horus the Black Flame Dragon LV6", "HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_SIX"),
    ]

    added = 0
    skipped_existing = 0
    failed = 0

    for card_const, search_name, override_const in to_retry:
        if normalize_const(card_const) in existing_consts:
            print(f"SKIP (already in manifest): {card_const}", file=sys.stderr)
            skipped_existing += 1
            continue

        print(f"\n[{added+1}/{len(to_retry)}] {card_const}...", file=sys.stderr)
        try:
            cards = fetch_exact(search_name)
            if not cards:
                print(f"  NOT FOUND via API", file=sys.stderr)
                failed += 1
                continue

            api_card = cards[0]
            entry = build_entry(api_card, manifest, override_const=override_const)
            if entry is None:
                print(f"  FAILED to build entry", file=sys.stderr)
                failed += 1
                continue

            manifest["cards"].append(entry)
            existing_consts.add(normalize_const(card_const))
            added += 1

            # Create stub effect if needed
            effect_type = classify_effect_type(api_card)
            if effect_type:
                try:
                    create_stub_and_wire(card_const, effect_type)
                    # Update monsterEffect for activated/permanent
                    if effect_type in ("activated", "permanent"):
                        for c in manifest["cards"]:
                            if c["card_const"] == card_const:
                                c["monsterEffect"] = f"MONSTER_EFFECT_{card_const}"
                                break
                except Exception as e:
                    print(f"  ERROR creating stub: {e}", file=sys.stderr)

        except Exception as e:
            print(f"  ERROR: {e}", file=sys.stderr)
            failed += 1

        time.sleep(0.3)

    try:
        write_manifest(MANIFEST_PATH, manifest)
        print(f"\nManifest written!", file=sys.stderr)
    except Exception as e:
        print(f"ERROR writing manifest: {e}", file=sys.stderr)
        return 1

    print(f"\nResults: added={added}, skipped(existing)={skipped_existing}, failed={failed}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
