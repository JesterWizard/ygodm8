#!/usr/bin/env python3
"""Split SESSION_LOG.md into dated files in documentation/session_logs/.

Usage: python3 tools/split_session_log.py [SESSION_LOG.md path]
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / "SESSION_LOG.md"
OUT_DIR = ROOT / "documentation" / "session_logs"

TEMPLATE = """# Session Log — {date}

{body}
"""


def main():
    text = SOURCE.read_text()

    # Strip top-level "# Session Log" header
    text = re.sub(r"^# Session Log\n{1,2}", "", text, count=1)

    # Find all date headings with their positions
    pattern = re.compile(r"^(## (\d{4}-\d{2}-\d{2}) .*)$", re.MULTILINE)

    entries = []
    prev_start = None
    prev_date = None

    for m in pattern.finditer(text):
        start = m.start()
        date = m.group(2)
        if prev_start is not None:
            entries.append((prev_date, text[prev_start:start].strip()))
        prev_start = start
        prev_date = date
    if prev_start is not None:
        entries.append((prev_date, text[prev_start:].strip()))

    # Group by date
    by_date: dict[str, list[str]] = {}
    for date, entry in entries:
        by_date.setdefault(date, []).append(entry)

    if not by_date:
        print("ERROR: no date entries found")
        return

    OUT_DIR.mkdir(parents=True, exist_ok=True)

    for date in sorted(by_date.keys()):
        body = ""
        for entry in by_date[date]:
            if body:
                body += "\n\n"
            body += entry
        content = TEMPLATE.format(date=date, body=body)
        out_path = OUT_DIR / f"{date}.md"
        out_path.write_text(content)
        n = len(by_date[date])
        print(f"  {out_path.name}  ({n} entr{'y' if n == 1 else 'ies'})")

    print(f"\nDone. {len(by_date)} files written to {OUT_DIR}")


if __name__ == "__main__":
    main()
