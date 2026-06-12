#!/usr/bin/env python3
"""Regenerate src_custom/assets/cards/CARD_PROGRESS.md from manifest + 80x80 PNGs."""

from __future__ import annotations

import json
import re
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "tools" / "card_data_manifest.json"
ART_DIR = ROOT / "src_custom/assets/cards/80x80"
PROGRESS = ROOT / "src_custom/assets/cards/CARD_PROGRESS.md"
CUSTOM_START = "SORCERER_OF_DARK_MAGIC"
MARKER_BEGIN = "<!-- card-art-progress:auto:begin -->"
MARKER_END = "<!-- card-art-progress:auto:end -->"


def const_to_stem(card_const: str) -> str:
    return card_const.lower()


def load_custom_cards() -> list[dict]:
    with MANIFEST.open(encoding="utf-8") as f:
        cards = json.load(f)["cards"]
    started = False
    custom: list[dict] = []
    for card in cards:
        if card["card_const"] == CUSTOM_START:
            started = True
        if started:
            custom.append(card)
    return custom


def load_pngs() -> dict[str, str]:
    return {p.stem.lower(): p.name for p in ART_DIR.glob("*.png")}


def render_auto_section(custom_cards: list[dict], pngs: dict[str, str]) -> str:
    manifest_stems = {const_to_stem(c["card_const"]): c for c in custom_cards}

    in_game: list[tuple[dict, str]] = []
    missing_art: list[dict] = []
    for card in custom_cards:
        stem = const_to_stem(card["card_const"])
        if stem in pngs:
            in_game.append((card, pngs[stem]))
        else:
            missing_art.append(card)

    art_only = sorted(
        (stem, pngs[stem])
        for stem in pngs
        if stem not in manifest_stems
    )

    lines: list[str] = []
    lines.append(MARKER_BEGIN)
    lines.append("# Custom Card Progress")
    lines.append("")
    lines.append(
        "Tracks **80×80 big art** in `80x80/` against cards wired in "
        "`tools/card_data_manifest.json` (from `SORCERER_OF_DARK_MAGIC` onward)."
    )
    lines.append("")
    lines.append(
        "Full workflow: "
        "[documentation/adding-custom-cards.md](../../../documentation/adding-custom-cards.md)"
    )
    lines.append("")
    lines.append(
        f"Regenerate the summary and tables: `python3 tools/card_art_progress.py` "
        f"(last run: {date.today().isoformat()})."
    )
    lines.append("")
    lines.append("## Summary")
    lines.append("")
    lines.append("| Status | Count |")
    lines.append("|--------|------:|")
    lines.append(f"| In game (manifest + art) | {len(in_game)} |")
    lines.append(f"| Art ready, needs manifest | {len(art_only)} |")
    lines.append(f"| In manifest, missing art | {len(missing_art)} |")
    lines.append(f"| **Total PNGs in `80x80/`** | **{len(pngs)}** |")
    lines.append("")
    lines.append("## In game")
    lines.append("")
    lines.append("Manifest entry exists and `80x80/<stem>.png` is present.")
    lines.append("")
    lines.append("| `card_const` | Card name | Art file |")
    lines.append("|--------------|-----------|----------|")
    for card, png in in_game:
        name = card.get("card_name", "")
        lines.append(f"| `{card['card_const']}` | {name} | `{png}` |")
    lines.append("")
    lines.append("## Todo — art ready, needs manifest")
    lines.append("")
    lines.append("PNG is in `80x80/`; append a manifest entry and run `make`.")
    lines.append("")
    for stem, png in art_only:
        const = stem.upper()
        lines.append(f"- [ ] `{const}` — `{png}`")
    lines.append("")
    lines.append("## Todo — in manifest, missing art")
    lines.append("")
    if missing_art:
        lines.append("Manifest entry exists but `80x80/<stem>.png` is missing.")
        lines.append("")
        for card in missing_art:
            stem = const_to_stem(card["card_const"])
            lines.append(f"- [ ] `{card['card_const']}` — needs `80x80/{stem}.png`")
    else:
        lines.append("_No manifest entries are missing art right now._")
    lines.append(MARKER_END)
    return "\n".join(lines) + "\n"


def merge_manual_tail(existing: str, auto: str) -> str:
    match = re.search(
        rf"{re.escape(MARKER_END)}\s*(.*)\Z",
        existing,
        flags=re.DOTALL,
    )
    manual = match.group(1).strip() if match else ""
    if not manual:
        manual = (
            "\n## Backlog — needs art\n\n"
            "Planned cards with no `80x80/<stem>.png` yet. "
            "Add lines here; they are preserved when you rerun this script.\n\n"
            "```text\n"
            "# CARD_CONST — optional note\n"
            "```\n"
        )
    elif not manual.startswith("\n"):
        manual = "\n" + manual
    return auto + manual


def main() -> None:
    custom_cards = load_custom_cards()
    pngs = load_pngs()
    auto = render_auto_section(custom_cards, pngs)

    if PROGRESS.exists():
        content = merge_manual_tail(PROGRESS.read_text(encoding="utf-8"), auto)
    else:
        content = auto + (
            "\n## Backlog — needs art\n\n"
            "Planned cards with no `80x80/<stem>.png` yet. "
            "Add lines here; they are preserved when you rerun this script.\n\n"
            "```text\n"
            "# CARD_CONST — optional note\n"
            "```\n"
        )

    PROGRESS.write_text(content, encoding="utf-8")
    print(f"Wrote {PROGRESS.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
