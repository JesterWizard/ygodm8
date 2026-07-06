#!/usr/bin/env python3
"""
PickZone migration tool — converts legacy DUEL_CURSOR_* targeting cards
to the shared PickZone API.

Usage:
    python3 tools/migrate_to_pickzone.py <card_name> [--yes]

Limitations (complex cards detected + skipped):
  Creature Swap, Diffusion Wave Motion, Cannon Soldier, Man-Thro-Tro,
  Fire Reaper, Ring of Destruction, Book of Moon, Book of Taiyou,
  Ryu Kishin Clown, Kaiser Glider, Breaker the Magical Warrior,
  Jowls of Dark Demise, Invader of the Throne, Dark Magician Knight,
  Monarchs (Zaborg/Caius/Mobius), Nightmare Wheel, Dust Tornado,
  Ectoplasmer, Tribute Doll, Soul Exchange, Block Attack, De-Fusion,
  Negative Energy
"""

import os
import re
import sys

REPO_ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), ".."))

COMPLEX = {
    "creature_swap", "diffusion_wave_motion", "cannon_soldier",
    "man_thro_tro", "fire_reaper", "ring_of_destruction",
    "book_of_moon", "book_of_taiyou", "ryu_kishin_clown",
    "kaiser_glider", "breaker_the_magical_warrior",
    "jowls_of_dark_demise", "invader_of_the_throne",
    "dark_magician_knight", "zaborg_the_thunder_monarch",
    "caius_the_shadow_monarch", "mobius_the_frost_monarch",
    "nightmare_wheel", "dust_tornado",
    "tribute_doll", "soul_exchange", "block_attack",
    "de_fusion", "negative_energy", "ectoplasmer",
}


def die(msg):
    print(f"error: {msg}", file=sys.stderr)
    sys.exit(1)


def snake_to_pascal(s):
    return "".join(w.capitalize() for w in s.split("_"))


def find_files(card_name):
    for d in ["spell_effects", "activated_effects", "trap_effects", "permanent_effects"]:
        p = os.path.join(REPO_ROOT, "src_custom", d, f"{card_name}.c")
        if os.path.exists(p):
            return p, d
    die(f"effect file not found for '{card_name}'")
    return None, None


def read(path):
    with open(path) as f:
        return f.read()


def write(path, text):
    with open(path, "w") as f:
        f.write(text)


def collapse_blanks(lines):
    out = []
    prv = False
    for ln in lines:
        bl = ln.strip() == ""
        if bl and prv:
            continue
        out.append(ln)
        prv = bl
    return out


def find_func_end(lines, start):
    """Given a line index pointing at a function signature, find the
    index of the line AFTER the closing brace. Returns len(lines) if
    no closing brace found."""
    depth = 0
    for i in range(start, len(lines)):
        depth += lines[i].count("{")
        depth -= lines[i].count("}")
        if depth == 0 and "{" in lines[start:i + 1]:
            return i + 1
    return len(lines)


def is_func_start(line, fn_names):
    """Check if a line looks like the start of a function with the given name."""
    for fn in fn_names:
        pat = rf"^(?:static\s+)?(?:u8|void|unsigned char|s8|u16|s16)\s+{re.escape(fn)}\s*\("
        if re.search(pat, line):
            return True
    return False


def remove_funcs(lines, fn_names):
    """Return new list with function bodies for any fn_name removed."""
    i = 0
    out = []
    while i < len(lines):
        if is_func_start(lines[i], fn_names):
            i = find_func_end(lines, i)
        else:
            out.append(lines[i])
            i += 1
    return collapse_blanks(out)


def remove_hooks_card_block(hooks_text, prefix, upper):
    """Remove the IsXxxCard(if) { ... } targeting block from hooks."""
    pat = (
        r"  if \(Is" + re.escape(prefix) + r"Card\(id\)\) \{\n"
        r"    if \(!FieldHas" + re.escape(prefix) + r"Target\(gDuelCursor\.currentY, gDuelCursor\.currentX\)\) \{\n"
        r"      PlayMusic\(SFX_FORBIDDEN\);\n"
        r"      gDuelCursor\.state = 0;\n"
        r"      DisplayCardInfoBar\(\);\n"
        r"      sub_8041E70\(gDuelCursor\.destY, gDuelCursor\.currentY\);\n"
        r"      return;\n"
        r"    \}\n"
        r"\n"
        r"    Begin" + re.escape(prefix) + r"Targeting\(gDuelCursor\.currentY, gDuelCursor\.currentX\);\n"
        r"    DisplayCardInfoBar\(\);\n"
        r"    sub_8041E70\(gDuelCursor\.destY, gDuelCursor\.currentY\);\n"
        r"    return;\n"
        r"  \}"
    )
    return re.sub(pat, "", hooks_text)


def generate_pickzone_code(prefix, upper, target_row, has_resolve_body):
    lines = []
    lines.append("")
    lines.append("// --- PickZone callbacks ---")
    lines.append("")
    lines.append(f"static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)")
    lines.append("{")
    lines.append(f"  return fixedRow == {target_row} && gFixedZones[fixedRow][fixedCol]->id != CARD_NONE;")
    lines.append("}")
    lines.append("")

    if has_resolve_body:
        lines.append(f"static void ResolveTarget(u8 fixedRow, u8 fixedCol)")
        lines.append("{")
        lines.append(f"  gSpellEffectData.id = {upper};")
        lines.append("  gSpellEffectData.row1 = fixedRow;")
        lines.append("  gSpellEffectData.col1 = fixedCol;")
        lines.append("  gSpellEffectData.row2 = gDuelCursor.destY;")
        lines.append("  gSpellEffectData.col2 = gDuelCursor.destX;")
        lines.append("  ActivateSpellEffect();")
        lines.append("}")
    else:
        lines.append(f"static void ResolveTarget(u8 fixedRow, u8 fixedCol)")
        lines.append("{")
        lines.append(f"  gSpellEffectData.id = {upper};")
        lines.append("  gSpellEffectData.row1 = fixedRow;")
        lines.append("  gSpellEffectData.col1 = fixedCol;")
        lines.append("  ActivateSpellEffect();")
        lines.append("}")

    lines.append("")
    lines.append("static void CancelTargeting(void)")
    lines.append("{")
    lines.append("  PlayMusic(SFX_CANCEL);")
    lines.append("}")
    lines.append("")
    lines.append(f"static u8 AiPickTarget(u8 *outRow, u8 *outCol)")
    lines.append("{")
    lines.append("  u8 col;")
    lines.append(f"  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {{")
    lines.append(f"    if (!IsValidTarget({target_row}, col))")
    lines.append("      continue;")
    lines.append(f"    *outRow = {target_row};")
    lines.append("    *outCol = col;")
    lines.append("    return TRUE;")
    lines.append("  }")
    lines.append("  return FALSE;")
    lines.append("}")
    lines.append("")

    # New effect function body
    lines.append(f"APPEND_TEXT void Effect{prefix}(void)")
    lines.append("{")
    lines.append("  gDuelCursor.destY = gSpellEffectData.row1;")
    lines.append("  gDuelCursor.destX = gSpellEffectData.col1;")
    lines.append("")
    lines.append("  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);")
    lines.append("  if (WhoseTurn() == DUEL_PLAYER)")
    lines.append("    Duel_EnterPickZoneTargeting();")
    lines.append("  else {")
    lines.append("    u8 aiRow, aiCol;")
    lines.append("    if (AiPickTarget(&aiRow, &aiCol))")
    lines.append("      ResolveTarget(aiRow, aiCol);")
    lines.append("  }")
    lines.append("}")
    lines.append("")

    return lines


def main():
    if len(sys.argv) < 2:
        print(__doc__.strip())
        sys.exit(1)

    card_name = sys.argv[1]
    auto_yes = "--yes" in sys.argv
    prefix = snake_to_pascal(card_name)
    upper = card_name.upper()
    c_path, effect_dir = find_files(card_name)
    h_path = os.path.join(REPO_ROOT, "include", f"{card_name}.h")
    hooks_path = os.path.join(REPO_ROOT, "src_custom", "code_8043EF4_hooks.c")

    c_text, h_text = read(c_path), read(h_path)
    hooks_text = read(hooks_path)
    c_lines = c_text.split("\n")

    # Parse cursor constant from header
    cursor_const, cursor_val = None, None
    m = re.search(r"#define\s+(DUEL_CURSOR_\w+)\s+(\d+)", h_text)
    if m:
        cursor_const, cursor_val = m.group(1), int(m.group(2))
    if cursor_const is None:
        die(f"no DUEL_CURSOR_* #define found in {h_path}")

    is_complex = card_name in COMPLEX
    has_resolve_body = "ResolveBody" in c_text
    has_lyreplace = "LYN_REPLACE_CHECK" in c_text

    # Determine target row
    target_row = "OPPONENT_MONSTER_ROW"
    for r in ["OPPONENT_MONSTER_ROW", "ACTIVE_DUELIST_MONSTER_ROW",
              "INACTIVE_DUELIST_MONSTER_ROW"]:
        if r in c_text:
            target_row = r
            break

    print(f"=== Migrating {card_name} ({effect_dir}) ===")
    print(f"  Cursor: {cursor_const} = {cursor_val}  Target row: {target_row}")
    print(f"  ResolveBody: {has_resolve_body}  LYN_REPLACE: {has_lyreplace}")
    print(f"  Complex: {is_complex}")

    if is_complex and not auto_yes:
        ans = input("\nComplex card — continue anyway? (y/N): ").strip().lower()
        if ans != "y":
            print("Skipped.")
            return

    # ---- HEADER changes ----
    h_lines = h_text.split("\n")
    h_lines = [
        l for l in h_lines
        if not re.search(
            rf"(?:#define\s+DUEL_CURSOR_{upper}_TARGET|"
            rf"(?:void|u8|unsigned char)\s+(?:FieldHas|Begin|TrySelect|Cancel|Is){prefix}\w*\s*\()",
            l,
        )
    ]
    h_lines = collapse_blanks(h_lines)
    new_h = "\n".join(h_lines)

    # ---- HOOKS changes: 3 removals ----
    # 1) Remove card ID targeting block
    hooks_text = remove_hooks_card_block(hooks_text, prefix, upper)

    # 2+3) Remove A-button and B-button dispatch cases (case, call, break)
    hooks_text = re.sub(
        rf"    case {re.escape(cursor_const)}:\n"
        rf"      \w[\w(), <>_*\[\]]+;\n"
        rf"      break;\n",
        "",
        hooks_text,
    )

    # ---- C FILE changes ----
    # 1. Remove legacy targeting function bodies
    legacy_fns = [
        f"FieldHas{prefix}Target",
        f"Begin{prefix}Targeting",
        f"TrySelect{prefix}Target",
        f"Cancel{prefix}Targeting",
        f"FindFirst{prefix}Target",
        f"Is{prefix}Card",
    ]
    c_lines = remove_funcs(c_lines, legacy_fns)

    # 2. Remove LYN_REPLACE_CHECK line
    c_lines = [l for l in c_lines
               if not re.match(rf"^LYN_REPLACE_CHECK\(Effect{prefix}\);\s*$", l)]

    # 3. Find and remove the old effect function body
    effect_start = None
    for i, ln in enumerate(c_lines):
        if re.match(rf"^APPEND_TEXT\s+void\s+Effect{prefix}(?:__Replacement)?\s*\(", ln):
            effect_start = i
            break

    if effect_start is None:
        die(f"could not find Effect{prefix} function in cleaned file")

    effect_end = find_func_end(c_lines, effect_start)

    # 4. Split: keep lines before effect, generate new code, keep lines after effect
    before = c_lines[:effect_start]
    after = c_lines[effect_end:]

    pickzone_lines = generate_pickzone_code(prefix, upper, target_row, has_resolve_body)

    new_c_lines = before + pickzone_lines + after
    final_c = "\n".join(collapse_blanks(new_c_lines))

    # Print summary
    print(f"\nChanges:")
    print(f"  {h_path}: remove cursor #define + targeting decls")
    print(f"  {hooks_path}: remove {cursor_const} dispatch cases + targeting block")
    print(f"  {c_path}: replace targeting functions + effect body with PickZone callbacks")

    ans = "y" if auto_yes else input("\nApply? (y/N): ").strip().lower()
    if ans != "y":
        print("Aborted.")
        return

    write(h_path, new_h)
    write(c_path, final_c)
    write(hooks_path, hooks_text)
    print(f"Migrated {card_name}. Run `make test-cards-build` to verify.")


if __name__ == "__main__":
    main()
