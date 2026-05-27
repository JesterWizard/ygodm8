#!/usr/bin/env python3
import argparse
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def load_duelist_ids():
    text = (ROOT / "include/overworld.h").read_text()
    match = re.search(r"\benum\s+DuelistId\s*\{(.*?)\};", text, re.DOTALL)
    if not match:
        raise SystemExit("enum DuelistId not found in include/overworld.h")

    constants = {}
    value = 0
    for raw_item in match.group(1).split(","):
        item = raw_item.strip()
        if not item:
            continue
        name, _, explicit = item.partition("=")
        name = name.strip()
        if explicit:
            value = int(explicit.strip(), 0)
        constants[name] = value
        value += 1
    return constants


def resolve_duelist_id(raw_id, duelist_ids):
    if isinstance(raw_id, int):
        return raw_id, str(raw_id), str(raw_id)
    if raw_id not in duelist_ids:
        raise SystemExit(f"unknown duelist_id {raw_id!r}")
    return duelist_ids[raw_id], raw_id, raw_id


def render_drop_table(symbol, cards):
    lines = [f"static const struct CardDrop {symbol}[] APPEND_RODATA = {{"]
    if cards:
        for index, card in enumerate(cards):
            chance = ((index + 1) * 2048 // len(cards)) - 1
            lines.append(f"  {{{card}, {chance}}},")
    lines.append("  {CARD_NONE, 0},")
    lines.append("};")
    return lines


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--out", required=True, type=Path)
    args = parser.parse_args()

    manifest = json.loads(args.manifest.read_text())
    duelist_ids = load_duelist_ids()
    max_duelists = int(manifest.get("max_duelists", 192))
    lines = [
        "typedef struct CustomDuelistRewardEntry {",
        "  u8 enabled;",
        "  u32 capacityYield;",
        "  u16 minDomino;",
        "  u16 maxDomino;",
        "  u8 dominoScalePower;",
        "  const struct CardDrop *normalDrops;",
        "  const struct CardDrop *lowDrops;",
        "} CustomDuelistRewardEntry;",
        "",
    ]

    for entry in manifest["duelist_rewards"]:
        _, duelist_ref, symbol_suffix = resolve_duelist_id(entry["duelist_id"], duelist_ids)
        lines.extend(render_drop_table(f"sDuelist{symbol_suffix}NormalAnteRewards", entry["normal_ante_rewards"]))
        lines.append("")
        lines.extend(render_drop_table(f"sDuelist{symbol_suffix}LowAnteRewards", entry["low_ante_rewards"]))
        lines.append("")

    lines.append(f"static const CustomDuelistRewardEntry gCustomDuelistRewards[{max_duelists}] APPEND_RODATA = {{")
    seen = set()
    for entry in manifest["duelist_rewards"]:
        duelist_id, duelist_ref, symbol_suffix = resolve_duelist_id(entry["duelist_id"], duelist_ids)
        domino = entry["domino"]
        if duelist_id < 0 or duelist_id >= max_duelists:
            raise SystemExit(f"duelist_id {duelist_ref} outside max_duelists {max_duelists}")
        if duelist_id in seen:
            raise SystemExit(f"duplicate duelist_id {duelist_ref}")
        seen.add(duelist_id)
        lines.append(
            f"  [{duelist_ref}] = {{TRUE, {entry['capacity_reward']}, {domino['min']}, {domino['max']}, "
            f"{domino.get('scale_power', 0)}, sDuelist{symbol_suffix}NormalAnteRewards, "
            f"sDuelist{symbol_suffix}LowAnteRewards}},"
        )
    lines.append("};")
    lines.append("")

    args.out.parent.mkdir(parents=True, exist_ok=True)
    content = "\n".join(lines)
    if args.out.exists() and args.out.read_text() == content:
        return
    args.out.write_text(content)


if __name__ == "__main__":
    main()
