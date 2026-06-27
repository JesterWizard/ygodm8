#!/usr/bin/env python3
"""Append a structured entry to the session log.

Usage:
  python3 tools/log_session.py --task "Added Mobius the Frost Monarch" \\
    --files "tools/card_data_manifest.json,configs/runtime.c" \\
    --outcome "make test-cards-build passes" \\
    --next "Create 80x80 art"

Flags:
  --task       Summary of what was done (required)
  --files      Comma-separated relative file paths
  --outcome    Build/test result
  --next       Open / next items (comma-separated)
  --date       Override date (default: today)
"""

from __future__ import annotations

import argparse
import sys
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LOGS_DIR = ROOT / "documentation" / "session_logs"
CARD_STATE_PATH = ROOT / "documentation" / "CARD_STATE.md"


def write_card_state_md(args: argparse.Namespace, today: str) -> None:
    """Write a rolling one-entry CARD_STATE.md (overwrites, never appends)."""
    lines = ["# CARD_STATE — latest session"]
    lines.append("")
    lines.append(f"**Last worked on:** {today} — {args.task}")
    lines.append("")

    if args.files:
        files = [f.strip() for f in args.files.split(",") if f.strip()]
        lines.append("**Files touched:**")
        for f in files:
            lines.append(f"- `{f}`")
        lines.append("")

    if args.outcome:
        lines.append(f"**Outcome:** {args.outcome}")
        lines.append("")

    if args.next:
        next_items = [n.strip() for n in args.next.split(",") if n.strip()]
        lines.append("**Open / next:**")
        for item in next_items:
            lines.append(f"- {item}")
        lines.append("")

    CARD_STATE_PATH.write_text("\n".join(lines).strip() + "\n")



def main() -> int:
    parser = argparse.ArgumentParser(description="Append a structured session log entry.")
    parser.add_argument("--task", required=True, help="Summary of what was done")
    parser.add_argument("--files", default="", help="Comma-separated relative file paths")
    parser.add_argument("--outcome", default="", help="Build/test result")
    parser.add_argument("--next", default="", help="Comma-separated next items")
    parser.add_argument("--date", default=None, help="Override date (YYYY-MM-DD)")
    args = parser.parse_args()

    today = args.date if args.date else date.today().isoformat()
    log_file = LOGS_DIR / f"{today}.md"
    LOGS_DIR.mkdir(parents=True, exist_ok=True)

    lines = []
    if log_file.is_file():
        lines.append(log_file.read_text().rstrip())
        lines.append("")
    else:
        lines.append(f"# Session Log — {today}")
        lines.append("")

    lines.append(f"## {today} — {args.task}")
    lines.append("")

    if args.files:
        files = [f.strip() for f in args.files.split(",") if f.strip()]
        lines.append("**Files:**")
        for f in files:
            lines.append(f"- `{f}`")
        lines.append("")

    if args.outcome:
        lines.append(f"**Outcome:** {args.outcome}")
        lines.append("")

    if args.next:
        next_items = [n.strip() for n in args.next.split(",") if n.strip()]
        lines.append("**Open / next:**")
        for item in next_items:
            lines.append(f"- {item}")
        lines.append("")

    lines.append("---")
    lines.append("")

    log_file.write_text("\n".join(lines).strip() + "\n")
    print(f"Logged to {log_file}", file=sys.stderr)
    write_card_state_md(args, today)
    print(f"Updated {CARD_STATE_PATH.relative_to(ROOT)}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
