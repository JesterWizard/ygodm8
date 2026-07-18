#!/usr/bin/env python3
"""Replace abbreviated manifest descriptions with full TCG/OCG text from YGOProDeck.

Fit check uses Emerald/Small reflow up to DESC_DISPLAY_PAGES_MAX (9) pages and
the gDescProseBuf ceiling. Cards that still overflow are left unchanged and listed.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from add_card_art import DESC_DISPLAY_PAGES_MAX, DESC_PROSE_MAX, paginate_description_text  # noqa: E402
from card_manifest import load_manifest_json, write_manifest  # noqa: E402
from desc_emerald_wrap import emerald_page_count, fits_emerald_pages  # noqa: E402

MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"
YGO_API = "https://db.ygoprodeck.com/api/v7/cardinfo.php"


def password_to_passcode(password: list[int]) -> int | None:
    if not password or len(password) != 8:
        return None
    if not all(isinstance(d, int) and 0 <= d <= 9 for d in password):
        return None
    if not any(password):
        return None
    return int("".join(str(d) for d in password))


def clean_tcg_text(text: str) -> str:
    """Normalize API card text for the in-game ASCII font."""
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    text = text.replace("\n", " ")
    # Font cannot render double quotes; drop them (card names stay readable).
    for q in ('"', "\u201c", "\u201d", "\u2018", "\u2019"):
        text = text.replace(q, "")
    text = text.replace("—", "-").replace("–", "-").replace("−", "-")
    text = text.replace("×", "x").replace("•", "-")
    # Drop leftover non-ASCII (Emerald maps unknown → ?).
    text = "".join(ch if ord(ch) < 128 else " " for ch in text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def api_description(card: dict) -> str:
    parts = []
    if card.get("pend_desc"):
        parts.append(card["pend_desc"])
    if card.get("desc"):
        parts.append(card["desc"])
    return clean_tcg_text(" ".join(parts))


def fetch_by_ids(ids: list[str], batch: int = 100) -> dict[str, dict]:
    out: dict[str, dict] = {}
    for i in range(0, len(ids), batch):
        chunk = ids[i : i + batch]
        url = f"{YGO_API}?{urllib.parse.urlencode({'id': ','.join(chunk)})}"
        req = urllib.request.Request(url, headers={"User-Agent": "ygodm8-refresh-descriptions/1.0"})
        try:
            with urllib.request.urlopen(req, timeout=120) as resp:
                data = json.load(resp).get("data") or []
        except urllib.error.HTTPError as exc:
            if len(chunk) > 1:
                out.update(fetch_by_ids(chunk, batch=max(1, len(chunk) // 2)))
                continue
            print(f"skip id {chunk}: {exc}", file=sys.stderr)
            continue
        except urllib.error.URLError as exc:
            raise SystemExit(f"YGOProDeck request failed: {exc}") from exc
        for card in data:
            out[str(card["id"])] = card
            for img in card.get("card_images") or []:
                out[str(img["id"])] = card
    return out


def fetch_by_name(name: str) -> dict | None:
    for key, value in (("name", name), ("fname", name)):
        url = f"{YGO_API}?{urllib.parse.urlencode({key: value})}"
        req = urllib.request.Request(url, headers={"User-Agent": "ygodm8-refresh-descriptions/1.0"})
        try:
            with urllib.request.urlopen(req, timeout=30) as resp:
                data = json.load(resp).get("data") or []
        except (urllib.error.HTTPError, urllib.error.URLError):
            continue
        if not data:
            continue
        lowered = name.lower()
        for card in data:
            if card.get("name", "").lower() == lowered:
                return card
        if len(data) == 1:
            return data[0]
    return None


def resolve_api_card(item: dict, api_by_id: dict[str, dict]) -> dict | None:
    pc = password_to_passcode(item.get("password") or [])
    if pc is not None:
        card = api_by_id.get(str(pc)) or api_by_id.get(f"{pc:08d}")
        if card is not None:
            return card
    name = item.get("card_name") or item.get("card_const", "")
    return fetch_by_name(name) if name else None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dry-run", action="store_true", help="Do not write the manifest")
    parser.add_argument(
        "--cache",
        type=Path,
        help="Optional JSON cache of passcode→API card (skip network if present)",
    )
    args = parser.parse_args()

    manifest = load_manifest_json(MANIFEST_PATH)
    cards = manifest["cards"]

    id_list: list[str] = []
    for item in cards:
        pc = password_to_passcode(item.get("password") or [])
        if pc is not None:
            id_list.append(f"{pc:08d}")
    id_list = list(dict.fromkeys(id_list))

    if args.cache and args.cache.is_file():
        raw = json.loads(args.cache.read_text())
        api_by_id = {str(k): v for k, v in raw.items()}
        print(f"Loaded {len(api_by_id)} cards from cache {args.cache}")
    else:
        print(f"Fetching {len(id_list)} passcodes from YGOProDeck…")
        api_by_id = fetch_by_ids(id_list)
        print(f"Fetched {len(api_by_id)} API entries")

    updated = 0
    unchanged = 0
    no_api: list[str] = []
    overflow: list[tuple[str, str, int, str]] = []  # name, const, pages_needed, reason

    for item in cards:
        const = item["card_const"]
        name = item.get("card_name", const)
        desc = item.get("description")
        if not isinstance(desc, dict):
            continue

        api_card = resolve_api_card(item, api_by_id)
        if api_card is None:
            no_api.append(name)
            continue

        prose = api_description(api_card)
        if not prose:
            no_api.append(name)
            continue

        if len(prose) > DESC_PROSE_MAX:
            overflow.append((name, const, -1, f"prose buffer ({len(prose)}>{DESC_PROSE_MAX})"))
            continue

        pages_needed = emerald_page_count(prose, max_pages=DESC_DISPLAY_PAGES_MAX)
        if not fits_emerald_pages(prose, DESC_DISPLAY_PAGES_MAX):
            overflow.append((name, const, pages_needed, f"needs {pages_needed}+ display pages"))
            continue

        try:
            paginate_description_text(prose)
        except SystemExit as exc:
            overflow.append((name, const, pages_needed, f"storage: {exc}"))
            continue

        old = desc.get("pages", "")
        if isinstance(old, list):
            old = " ".join(old)
        if old == prose:
            unchanged += 1
            continue

        desc["pages"] = prose
        updated += 1

    if not args.dry_run:
        write_manifest(MANIFEST_PATH, manifest)

    print(f"Updated: {updated}")
    print(f"Already full text: {unchanged}")
    print(f"No API match: {len(no_api)}")
    print(f"Overflow (unchanged): {len(overflow)}")

    if no_api:
        print("\nNo API match:")
        for n in sorted(no_api):
            print(f"  {n}")

    if overflow:
        print(f"\nRan out of space (display ≤{DESC_DISPLAY_PAGES_MAX} pages / prose buffer):")
        for name, const, pages, reason in sorted(overflow, key=lambda t: t[0].lower()):
            print(f"  {name} ({const}) — {reason}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
