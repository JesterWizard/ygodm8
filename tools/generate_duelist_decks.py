#!/usr/bin/env python3
"""Generate opponent deck rodata from tools/duelist_deck_manifest.json."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from duelist_deck_validate import (  # noqa: E402
    DeckManifestValidationError,
    generate_deck_manifest_source,
    load_duelist_ids,
)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--out", required=True, type=Path)
    args = parser.parse_args()

    manifest = json.loads(args.manifest.read_text())
    try:
        content = generate_deck_manifest_source(manifest, load_duelist_ids())
    except DeckManifestValidationError as exc:
        raise SystemExit(str(exc)) from exc

    args.out.parent.mkdir(parents=True, exist_ok=True)
    if args.out.exists() and args.out.read_text() == content:
        return
    args.out.write_text(content)


if __name__ == "__main__":
    main()
