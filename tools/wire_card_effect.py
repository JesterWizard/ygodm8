#!/usr/bin/env python3
"""Wire a card effect into the correct dispatcher, create hook file, update tally.

Usage:
  python3 tools/wire_card_effect.py CAIUS_THE_SHADOW_MONARCH --type permanent
  python3 tools/wire_card_effect.py MY_SPELL --type spell
  python3 tools/wire_card_effect.py MY_TRAP --type trap
  python3 tools/wire_card_effect.py MY_ACTIVATED --type activated
  python3 tools/wire_card_effect.py MY_BATTLE --type battle
  python3 tools/wire_card_effect.py MY_TURN --type turn
  python3 tools/wire_card_effect.py MY_PASSIVE --type passive

--type values:
  spell       src_custom/spell_effects/ + spell_effect_hooks.c
  trap        src_custom/trap_effects/ + trap_effect_hooks.c
  activated   src_custom/activated_effects/ + monster_effect_hooks.c
  permanent   src_custom/permanent_effects/ + permanent_effect_hooks.c
  battle      src_custom/battle_effects/ + battle_damage_hooks.c
  turn        src_custom/turn_effects/ + turn_effect_hooks.c
  passive     src_custom/card_passives/ (no dispatcher edit)
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Map effect type -> (subdirectory, dispatcher path, effect-category label)
EFFECT_CONFIG = {
    "spell": {
        "dir": "src_custom/spell_effects",
        "dispatcher": None,
        "label": "spell_effects",
        "template": """#include "global.h"
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
""",
        "dispatcher_decl": "void Effect{const}(void);",
        "dispatcher_entry": "  case {const}:\n    Effect{const}();\n    break;",
        "dispatcher_anchor": "default:",
    },
    "trap": {
        "dir": "src_custom/trap_effects",
        "dispatcher": "src_custom/trap_effect_hooks.c",
        "label": "trap_effects",
        "template": """#include "global.h"
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
""",
        "dispatcher_decl": "/* {const} trap effect */",
        "dispatcher_entry": "  /* TODO: wire {const} in trap dispatcher */",
        "dispatcher_anchor": None,
    },
    "activated": {
        "dir": "src_custom/activated_effects",
        "dispatcher": "src_custom/monster_effect_hooks.c",
        "label": "activated_effects",
        "template": """#include "global.h"
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
""",
        "dispatcher_decl": "unsigned char CanActivate{const}(void);\nvoid Activate{const}Effect(void);",
        "dispatcher_entry": "    if (gMonEffect.id == {const}) {{\n      Activate{const}Effect();\n      return;\n    }}",
        "dispatcher_anchor": "/* END MONSTER EFFECT DISPATCH */",
    },
    "permanent": {
        "dir": "src_custom/permanent_effects",
        "dispatcher": "src_custom/permanent_effect_hooks.c",
        "label": "permanent_effects",
        "template": """#include "global.h"
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
""",
        "dispatcher_decl": "unsigned char ShouldActivate{const}(void);\nvoid Activate{const}(void);",
        "dispatcher_entry": "  {{\n    .cardId = {const},\n    .shouldActivate = ShouldActivate{const},\n    .activate = Activate{const},\n  }},",
        "dispatcher_anchor": "/* END PERMANENT EFFECT OVERRIDES */",
    },
    "battle": {
        "dir": "src_custom/battle_effects",
        "dispatcher": "src_custom/battle_damage_hooks.c",
        "label": "battle_effects",
        "template": """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

/* TODO: implement battle effect for {const} */
""",
        "dispatcher_decl": "/* {const} battle effect */",
        "dispatcher_entry": "  /* TODO: wire {const} in battle damage hooks */",
        "dispatcher_anchor": None,
    },
    "turn": {
        "dir": "src_custom/turn_effects",
        "dispatcher": "src_custom/turn_effect_hooks.c",
        "label": "turn_effects",
        "template": """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

/* TODO: implement turn effect for {const} */
""",
        "dispatcher_decl": "/* {const} turn effect */",
        "dispatcher_entry": "  /* TODO: wire {const} in turn effect hooks */",
        "dispatcher_anchor": None,
    },
    "passive": {
        "dir": "src_custom/card_passives",
        "dispatcher": None,
        "label": "card_passives",
        "template": """#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

/* TODO: implement passive/immunity effect for {const} */
""",
        "dispatcher_decl": None,
        "dispatcher_entry": None,
        "dispatcher_anchor": None,
    },
}


def const_to_stem(card_const: str) -> str:
    return card_const.lower()


def const_to_display_name(card_const: str) -> str:
    return card_const.replace("_", " ").title()


def find_insertion_point(content: str, anchor: str | None) -> int | None:
    if anchor is None:
        return None
    # Try exact anchor first
    pos = content.find(anchor)
    if pos >= 0:
        return pos
    # Fall back to the last extern declaration or the end of the file
    return len(content)


def find_tally_insertion(content: str, category: str) -> int:
    """Find where to insert a new tally row."""
    # Find the table header
    table_header = "| Category | Card | Hook file |"
    header_pos = content.find(table_header)
    if header_pos < 0:
        return len(content)

    # Find the first separator line after header
    sep_end = content.find("\n", header_pos) + 1
    sep_end = content.find("\n", sep_end) + 1

    # Find the first row of the category we want, or the first row of the next category
    lines = content[sep_end:].split("\n")
    for i, line in enumerate(lines):
        stripped = line.strip()
        if not stripped.startswith("| `"):
            continue
        cat = stripped.split("`")[1] if "`" in stripped else ""
        if cat > category:  # next category alphabetically
            return sep_end + sum(len(l) + 1 for l in lines[:i])
        if cat == category:
            # Find the last entry in this category
            for j in range(i + 1, len(lines)):
                next_stripped = lines[j].strip()
                if not next_stripped.startswith("| `"):
                    return sep_end + sum(len(l) + 1 for l in lines[:j])
            return sep_end + sum(len(l) + 1 for l in lines)

    return len(content)


def regenerate_spell_dispatch() -> None:
    script = ROOT / "tools" / "generate_spell_effect_dispatch.py"
    if not script.is_file():
        print(f"  Warning: {script} not found", file=sys.stderr)
        return
    import subprocess

    subprocess.run([sys.executable, str(script)], check=True)
    print("  Regenerated spell effect dispatch tables", file=sys.stderr)


def patch_dispatcher(dispatcher_path: Path, card_const: str, config: dict) -> bool:
    if config["dispatcher"] is None:
        return True  # No dispatcher to patch

    content = dispatcher_path.read_text()

    # Check if already wired
    if card_const in content:
        print(f"  Already wired in {dispatcher_path}", file=sys.stderr)
        return True

    # Add extern declaration
    if config["dispatcher_decl"]:
        decl = config["dispatcher_decl"].format(const=card_const)
        # Insert before the anchor or at end
        anchor = config.get("dispatcher_anchor")
        if anchor and anchor in content:
            insert_pos = content.rfind(anchor)
            # Insert before the anchor
            content = content[:insert_pos] + decl + "\n" + content[insert_pos:]
        else:
            # Append to end
            content += "\n" + decl

    # Add dispatch entry
    if config["dispatcher_entry"]:
        entry = config["dispatcher_entry"].format(const=card_const)
        anchor = config.get("dispatcher_anchor")
        if anchor and anchor in content:
            insert_pos = content.rfind(anchor)
            content = content[:insert_pos] + entry + "\n" + content[insert_pos:]
        else:
            content += "\n" + entry

    dispatcher_path.write_text(content)
    print(f"  Patched {dispatcher_path}", file=sys.stderr)
    return True


def update_tally(category: str, card_const: str, hook_file: str) -> bool:
    tally_path = ROOT / "src_custom" / "card_effect_tally.md"
    if not tally_path.is_file():
        print(f"  Warning: {tally_path} not found, skipping tally update", file=sys.stderr)
        return False

    content = tally_path.read_text()

    # Check if already tallied
    if card_const in content:
        print(f"  Already in tally", file=sys.stderr)
        return True

    card_name = const_to_display_name(card_const)

    # Build the new row
    new_row = f"| `{category}` | `{card_name}` | `{hook_file}` |"

    # Update total count
    total_match = re.search(r"- `(\d+)` effects", content)
    if total_match:
        current = int(total_match.group(1))
        content = content.replace(
            total_match.group(0), f"- `{current + 1}` effects", 1
        )

    # Insert the row in the correct category position
    insert_pos = find_tally_insertion(content, category)
    content = content[:insert_pos] + new_row + "\n" + content[insert_pos:]

    tally_path.write_text(content)
    print(f"  Updated tally: {current + 1} effects", file=sys.stderr)
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description="Wire a card effect into the dispatcher, create hook file, and update tally.")
    parser.add_argument("card_const", help="CARD_CONST (e.g. CAIUS_THE_SHADOW_MONARCH)")
    parser.add_argument("--type", required=True, choices=list(EFFECT_CONFIG.keys()),
                        help="Effect type")
    parser.add_argument("--no-tally", action="store_true", help="Skip tally update")
    parser.add_argument("--no-file", action="store_true", help="Skip creating the hook file (dispatcher + tally only)")
    parser.add_argument("--dry-run", action="store_true", help="Print what would be done without writing")
    args = parser.parse_args()

    card_const = args.card_const.upper()
    config = EFFECT_CONFIG[args.type]
    stem = const_to_stem(card_const)

    # 1. Create hook file
    hook_dir = ROOT / config["dir"]
    hook_file = hook_dir / f"{stem}.c"

    if not args.no_file:
        if hook_file.is_file() and not args.dry_run:
            print(f"  Warning: {hook_file} already exists, skipping", file=sys.stderr)
        else:
            if args.dry_run:
                print(f"  Would create {hook_file}", file=sys.stderr)
            else:
                hook_file.parent.mkdir(parents=True, exist_ok=True)
                hook_file.write_text(config["template"].format(const=card_const))
                print(f"  Created {hook_file}", file=sys.stderr)

    # 2. Patch dispatcher (spell dispatch is generated — see generate_spell_effect_dispatch.py)
    if config["dispatcher"]:
        dispatcher_path = ROOT / config["dispatcher"]
        if dispatcher_path.is_file():
            if args.dry_run:
                print(f"  Would patch {dispatcher_path}", file=sys.stderr)
            else:
                if not patch_dispatcher(dispatcher_path, card_const, config):
                    return 1
    elif args.type == "spell" and not args.dry_run:
        regenerate_spell_dispatch()
    elif args.type == "spell" and args.dry_run:
        print("  Would regenerate spell effect dispatch tables", file=sys.stderr)

    # 3. Update tally
    if not args.no_tally:
        relative_hook = str(hook_file.relative_to(ROOT))
        if args.dry_run:
            print(f"  Would update tally: {config['label']} / {card_const} / {relative_hook}", file=sys.stderr)
        else:
            update_tally(config["label"], card_const, relative_hook)

    print(f"Done. Next steps:", file=sys.stderr)
    print(f"  1. Edit {hook_file.relative_to(ROOT)} with the effect logic", file=sys.stderr)
    print(f"  2. In manifest, set card's type fields appropriately", file=sys.stderr)
    if args.type in ("activated",):
        print(f"  3. Add MONSTER_EFFECT_* to include/constants/monster_effects.h if not already present", file=sys.stderr)
    print(f"  4. Run: make test-cards-link", file=sys.stderr)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
