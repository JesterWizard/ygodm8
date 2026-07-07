#!/usr/bin/env python3
"""Batch-add all cards from CARD_PROGRESS.md TODO list with stub effects."""

from __future__ import annotations

import json
import re
import subprocess
import sys
import urllib.error
import urllib.parse
import urllib.request
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import (
    description_symbol,
    load_manifest_json,
    order_card_entry,
    write_manifest,
)

MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"
PROGRESS_PATH = ROOT / "src_custom" / "assets" / "cards" / "CARD_PROGRESS.md"
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
    "Divine-Beast": "TYPE_DIVINE_BEAST",
    "Creator-God": "TYPE_CREATOR_GOD",
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


def wrap_to_pages(text: str, page_count: int = 2, width: int = 27) -> list[str]:
    import textwrap
    wrapped = textwrap.wrap(text.strip(), width=width)
    if not wrapped:
        return [STUB_DESC, STUB_DESC]
    if len(wrapped) <= page_count:
        result = wrapped[:]
        while len(result) < page_count:
            result.append("")
        return result
    chunk = max(1, (len(wrapped) + page_count - 1) // page_count)
    pages = []
    for start in range(0, len(wrapped), chunk):
        pages.append(" ".join(wrapped[start:start + chunk]))
    while len(pages) < page_count:
        pages.append("")
    return pages[:page_count]


def card_name_to_const(name: str) -> str:
    slug = re.sub(r"[^A-Za-z0-9]+", "_", name.strip()).strip("_").upper()
    return slug


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


def frame_kind(card_type: str) -> str:
    lowered = card_type.lower()
    for key in ("normal", "effect", "fusion", "ritual", "spell", "trap", "synchro"):
        if key in lowered:
            return "effect" if key == "synchro" else key
    return "effect"


def fetch_card_by_const(card_const: str) -> dict | None:
    name = card_const.replace("_", " ")
    params = urllib.parse.urlencode({"fname": name})
    url = f"{YGO_API}?{params}"
    req = urllib.request.Request(url, headers={"User-Agent": "ygodm8-batch/1.0"})
    try:
        with urllib.request.urlopen(req, timeout=30) as r:
            payload = json.load(r)
    except Exception as exc:
        print(f"  API error for {card_const}: {exc}", file=sys.stderr)
        return None
    cards = payload.get("data", [])
    for card in cards:
        if card_name_to_const(card["name"]) == card_const:
            return card
    if len(cards) == 1:
        return cards[0]
    # Try exact name match
    params2 = urllib.parse.urlencode({"name": name})
    url2 = f"{YGO_API}?{params2}"
    req2 = urllib.request.Request(url2, headers={"User-Agent": "ygodm8-batch/1.0"})
    try:
        with urllib.request.urlopen(req2, timeout=30) as r2:
            payload2 = json.load(r2)
        cards2 = payload2.get("data", [])
        if cards2:
            return cards2[0]
    except:
        pass
    print(f"  WARNING: Could not find {card_const} via API", file=sys.stderr)
    return None


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


def build_entry(api_card: dict, manifest: dict) -> dict:
    frame = frame_kind(api_card["type"])
    color = COLOR_BY_FRAME[frame]
    card_name = api_card["name"]
    card_const = card_name_to_const(card_name)
    passcode_raw = api_card.get("id", "0")
    password = passcode_to_password(passcode_raw)
    if password is None:
        # Generate a deterministic password from the card name
        name_hash = sum(ord(c) for c in card_name) % 99999999
        password = passcode_to_password(name_hash)
        if password is None:
            password = [1, 5, 0, 0, 0, 0, 0, 0]  # fallback

    desc_text = api_card.get("desc", "")
    is_normal = frame == "normal"

    if frame in ("spell", "trap"):
        desc_text_actual = api_card.get("desc", "")
        if desc_text_actual:
            pages = wrap_to_pages(desc_text_actual, 2)
        else:
            pages = ["Custom card.", "Custom card."]
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
            "effect_texts": {
                "popup_1": STUB_DESC,
            },
        })
        return entry

    race = api_card.get("race", "")
    card_type = RACE_MAP.get(race)
    if card_type is None:
        print(f"  WARNING: Unknown race {race!r} for {card_const}, using TYPE_WARRIOR", file=sys.stderr)
        card_type = "TYPE_WARRIOR"

    attribute = ATTRIBUTE_MAP.get(api_card.get("attribute", ""))
    if attribute is None:
        print(f"  WARNING: Unknown attribute for {card_const}, using ATTRIBUTE_EARTH", file=sys.stderr)
        attribute = "ATTRIBUTE_EARTH"

    atk = int(api_card["atk"]) if api_card.get("atk") is not None else 0
    def_ = int(api_card["def"]) if api_card.get("def") is not None else 0
    level = int(api_card.get("level", 0))

    desc_text_actual = api_card.get("desc", "")
    if desc_text_actual:
        pages = wrap_to_pages(desc_text_actual, 2)
    else:
        pages = ["Custom card.", "Custom card."]

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
        if desc_text:
            first_120 = desc_text[:120]
        else:
            first_120 = STUB_DESC
        entry["effect_texts"] = {"popup_1": first_120}

    return entry


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


def create_stub_effect(card_const: str, effect_type: str, manifest: dict) -> None:
    """Create a stub effect file and wire it."""
    lower = card_const.lower()

    if effect_type == "spell" and manifest.get("type") == "TYPE_SPELL":
        hook_dir = ROOT / "src_custom" / "spell_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(STUB_SPELL_TEMPLATE.format(const=card_const))
            print(f"  Created spell stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)
        return  # Spell dispatch is auto-generated

    if effect_type == "activated":
        hook_dir = ROOT / "src_custom" / "activated_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(STUB_ACTIVATED_TEMPLATE.format(const=card_const))
            print(f"  Created activated stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)
        # Wire through monster_effect_hooks.c
        wire_card_effect(card_const, "activated")
        return

    if effect_type == "permanent":
        hook_dir = ROOT / "src_custom" / "permanent_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(STUB_PERMANENT_TEMPLATE.format(const=card_const))
            print(f"  Created permanent stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)
        wire_card_effect(card_const, "permanent")
        return

    if effect_type == "trap":
        hook_dir = ROOT / "src_custom" / "trap_effects"
        hook_file = hook_dir / f"{lower}.c"
        if not hook_file.is_file():
            hook_file.parent.mkdir(parents=True, exist_ok=True)
            hook_file.write_text(STUB_TRAP_TEMPLATE.format(const=card_const))
            print(f"  Created trap stub: {hook_file.relative_to(ROOT)}", file=sys.stderr)
        wire_card_effect(card_const, "trap")
        return


def wire_card_effect(card_const: str, effect_type: str) -> None:
    """Run wire_card_effect.py for the given card."""
    script = ROOT / "tools" / "wire_card_effect.py"
    result = subprocess.run(
        [sys.executable, str(script), card_const, "--type", effect_type],
        capture_output=True, text=True,
    )
    for line in result.stdout.splitlines():
        print(f"  wire: {line}", file=sys.stderr)
    for line in result.stderr.splitlines():
        print(f"  wire: {line}", file=sys.stderr)


def classify_effect_type(api_card: dict) -> str | None:
    """Determine what type of effect file to create."""
    ct = api_card.get("type", "")
    ct_lower = ct.lower()
    if "spell" in ct_lower:
        return "spell"
    if "trap" in ct_lower:
        return "trap"
    if "normal" in ct_lower:
        return None  # Normal monster, no effect needed
    # Effect monster / fusion / ritual / synchro with effect
    desc = api_card.get("desc", "")
    if not desc:
        return None  # Vanilla fusion/ritual with no effect text
    # Check if it has an ignition effect (can activate)
    has_ignition = any(kw in desc.lower() for kw in [
        "you can", "once per turn", "activate", "when this card",
        "if this card", "flip:", "this card gains", "this card can",
        "cannot be", "is unaffected", "cannot be destroyed",
        "negate", " tribute", "special summon", "add to your hand",
    ])
    if has_ignition:
        return "activated"
    return "permanent"


def main() -> int:
    manifest = load_manifest_json(MANIFEST_PATH)
    if not isinstance(manifest, dict):
        print("ERROR: manifest not a dict", file=sys.stderr)
        return 1

    existing_consts = {c["card_const"] for c in manifest["cards"]}

    # Parse TODO list
    todo_text = PROGRESS_PATH.read_text()
    todo_items = re.findall(
        r"- \[ \] `([A-Z0-9_]+)` — `[a-z0-9_]+\.png`",
        todo_text,
    )
    print(f"Found {len(todo_items)} cards in TODO list", file=sys.stderr)

    to_add = [c for c in todo_items if c not in existing_consts]
    print(f"Need to add: {len(to_add)} cards", file=sys.stderr)
    print(f"Already in manifest: {len(todo_items) - len(to_add)}", file=sys.stderr)

    if not to_add:
        print("Nothing to do!", file=sys.stderr)
        return 0

    added_count = 0
    error_count = 0
    effect_wired = 0

    for i, card_const in enumerate(to_add):
        print(f"\n[{i+1}/{len(to_add)}] {card_const}...", file=sys.stderr)

        # Fetch from API
        api_card = fetch_card_by_const(card_const)
        if api_card is None:
            print(f"  SKIP (API failed)", file=sys.stderr)
            error_count += 1
            continue

        # Build manifest entry
        try:
            entry = build_entry(api_card, manifest)
        except Exception as e:
            print(f"  ERROR building entry: {e}", file=sys.stderr)
            error_count += 1
            continue

        # Add to manifest
        if any(item.get("card_const") == entry["card_const"] for item in manifest["cards"]):
            print(f"  Already in manifest (race condition), skipping", file=sys.stderr)
            continue

        manifest["cards"].append(entry)
        added_count += 1

        # Determine effect type and create stub
        effect_type = classify_effect_type(api_card)
        if effect_type:
            try:
                create_stub_effect(entry["card_const"], effect_type, entry)
                if effect_type in ("activated", "permanent"):
                    # Add MONSTER_EFFECT_* to monster_effects.h
                    add_monster_effect_const(entry["card_const"])
                    # Update manifest monsterEffect
                    for c in manifest["cards"]:
                        if c["card_const"] == entry["card_const"]:
                            c["monsterEffect"] = f"MONSTER_EFFECT_{entry['card_const']}"
                            c = order_card_entry(c)
                            break
                effect_wired += 1
            except Exception as e:
                print(f"  ERROR creating effect stub: {e}", file=sys.stderr)

        # Rate limit
        if i < len(to_add) - 1:
            time.sleep(0.3)

    # Write manifest
    try:
        write_manifest(MANIFEST_PATH, manifest)
        print(f"\nManifest written!", file=sys.stderr)
    except Exception as e:
        print(f"ERROR writing manifest: {e}", file=sys.stderr)
        return 1

    print(f"\n{'='*60}", file=sys.stderr)
    print(f"Results:", file=sys.stderr)
    print(f"  Added to manifest: {added_count}", file=sys.stderr)
    print(f"  Effect stubs wired: {effect_wired}", file=sys.stderr)
    print(f"  Errors/skips: {error_count}", file=sys.stderr)
    print(f"{'='*60}", file=sys.stderr)

    return 0


def add_monster_effect_const(card_const: str) -> None:
    """Add MONSTER_EFFECT_* to monster_effects.h if not present."""
    path = ROOT / "include" / "constants" / "monster_effects.h"
    content = path.read_text()
    me_const = f"MONSTER_EFFECT_{card_const}"
    if me_const in content:
        return
    # Insert before the closing of the enum
    insert_pos = content.rfind("};")
    if insert_pos >= 0:
        content = content[:insert_pos] + f"  {me_const},\n" + content[insert_pos:]
        path.write_text(content)
        print(f"  Added {me_const} to monster_effects.h", file=sys.stderr)


if __name__ == "__main__":
    raise SystemExit(main())
