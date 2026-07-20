#!/usr/bin/env python3
"""Stub effect queue + top-5 pattern codegen.

List TODO effect stubs sorted for batch work (archetype + similar-card fingerprint),
with a suggested clone source and optional fillable pattern.

Usage:
  python3 tools/stub_effect_queue.py
  python3 tools/stub_effect_queue.py --limit 20
  python3 tools/stub_effect_queue.py --pattern draw_n
  python3 tools/stub_effect_queue.py --archetype GRAVEKEEPERS

  # Multi-card work packs (preferred long-term workflow):
  python3 tools/stub_effect_queue.py --work-pack 12 --kind spell
  python3 tools/stub_effect_queue.py --work-pack 24 --workers 3 --kind spell
  python3 tools/stub_effect_queue.py --work-pack 10 --archetype GRAVEKEEPERS

  # Template batch fill (spells only; review after):
  python3 tools/stub_effect_queue.py --fill-all --pattern burn --dry-run
  python3 tools/stub_effect_queue.py --fill-all --pattern draw_n --limit 6

  # Single fill:
  python3 tools/stub_effect_queue.py --fill burn OOKAZI --damage 800 --dry-run
  python3 tools/stub_effect_queue.py --write-list
  python3 tools/stub_effect_queue.py --self-check
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"

EFFECT_DIRS = (
    ("spell", "src_custom/spell_effects"),
    ("trap", "src_custom/trap_effects"),
    ("activated", "src_custom/activated_effects"),
    ("permanent", "src_custom/permanent_effects"),
    ("battle", "src_custom/battle_effects"),
    ("turn", "src_custom/turn_effects"),
)

TODO_MARKERS = (
    "/* TODO: implement effect */",
    "/* TODO: implement trap effect",
    "/* TODO: implement battle effect",
    "/* TODO: implement turn effect",
    "/* TODO: implement passive",
    "/* TODO: implement target validation */",
    "/* TODO: add additional activation conditions */",
    "/* TODO: implement target resolution */",
    "/* TODO: implement AI target selection */",
    "/* TODO: add field-has-target check */",
)

# Helper calls → fingerprint tags (for implemented clones).
HELPER_TAG_PATTERNS: list[tuple[str, str]] = [
    (r"Duel_DrawCards(?:UntilHandSize)?\s*\(", "draw"),
    (r"Duel_ResolveBurnSpell\s*\(|Duel_ChangeLp\s*\([^)]*-\s*", "burn"),
    (r"Duel_AddDeckCardToHand\s*\(|Duel_FindDeckCardIndex\s*\(|Duel_RemoveDeckCardAt\s*\(", "search"),
    (r"Duel_DestroyZone\s*\(|Duel_DestroyAll|Duel_DestroyMasked", "destroy"),
    (r"Duel_SetupPickZone\s*\(", "pickzone"),
    (r"Duel_SpecialSummon|Duel_NormalSummon", "ssummon"),
    (r"[Tt]ribute", "tribute"),
    (r"Duel_DiscardFromHand\s*\(", "discard"),
    (r"Duel_ReturnMonsterZoneToOwnerHand\s*\(", "bounce"),
    (r"Duel_Banish", "banish"),
    (r"Duel_MillTopDeckCards\s*\(", "mill"),
]

WORD_NUM = {
    "a": 1,
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
}

FILL_PATTERNS = ("draw_n", "burn", "destroy_zone", "search", "tribute_summon")


@dataclass
class CardMeta:
    card_const: str
    card_name: str = ""
    effect_text: str = ""


@dataclass
class EffectFile:
    path: Path
    card_const: str
    effect_kind: str  # spell/trap/...
    is_stub: bool
    text_tags: frozenset[str] = field(default_factory=frozenset)
    code_tags: frozenset[str] = field(default_factory=frozenset)
    archetype: str = ""
    suggested_pattern: str | None = None
    draw_count: int | None = None
    burn_damage: int | None = None
    clone_const: str | None = None
    clone_path: str | None = None
    clone_score: float = 0.0


def stem_to_const(stem: str) -> str:
    return stem.upper()


def load_manifest() -> dict[str, CardMeta]:
    data = json.loads(MANIFEST_PATH.read_text())
    out: dict[str, CardMeta] = {}
    for card in data.get("cards", []):
        const = card.get("card_const")
        if not const:
            continue
        desc = card.get("description") or {}
        pages = desc.get("pages", "") if isinstance(desc, dict) else ""
        if isinstance(pages, list):
            pages = " ".join(str(p) for p in pages)
        elif not isinstance(pages, str):
            pages = str(pages) if pages else ""
        popup = ""
        texts = card.get("effect_texts") or {}
        if isinstance(texts, dict):
            popup = texts.get("popup_1") or texts.get("popup") or ""
            if isinstance(popup, list):
                popup = " ".join(str(p) for p in popup)
            elif not isinstance(popup, str):
                popup = str(popup) if popup else ""
        effect_text = " ".join(p for p in (popup, pages) if p)
        out[const] = CardMeta(
            card_const=const,
            card_name=card.get("card_name") or const,
            effect_text=effect_text,
        )
    return out


def is_stub_source(source: str) -> bool:
    if "TODO" not in source:
        return False
    # Implemented files sometimes mention TODO in comments about ceilings — require stub markers
    # or a wire_card_effect-style empty body.
    for marker in TODO_MARKERS:
        if marker in source:
            return True
    # Activated/permanent skeletons with multiple TODO markers
    return source.count("TODO") >= 2 and "Duel_ShowEffectText" in source


def fingerprint_text(text: str) -> tuple[frozenset[str], int | None, int | None]:
    t = text.lower()
    tags: set[str] = set()
    draw_count: int | None = None
    burn_damage: int | None = None

    m = re.search(r"draw\s+(\d+|a|one|two|three|four|five)\s+cards?", t)
    if m:
        tags.add("draw")
        raw = m.group(1)
        draw_count = int(raw) if raw.isdigit() else WORD_NUM.get(raw, 1)

    if re.search(r"inflict\s+.+\s+damage|damage\s+to\s+your\s+opponent|lose\s+\d+\s+life\s+points", t):
        tags.add("burn")
        dm = re.search(r"(\d+)\s*(?:points?\s+of\s+)?damage|lose\s+(\d+)\s+life", t)
        if dm:
            burn_damage = int(dm.group(1) or dm.group(2))

    if re.search(r"add\s+.+\s+from\s+your\s+deck\s+to\s+your\s+hand", t):
        tags.add("search")

    if re.search(r"\bdestroy\b", t):
        tags.add("destroy")

    if re.search(r"\btribute\b", t):
        tags.add("tribute")

    if re.search(r"special\s+summon", t):
        tags.add("ssummon")

    if "spell/trap" in t or "spell or trap" in t:
        tags.add("st")
    if re.search(r"\bmonster\b", t):
        tags.add("monster")
    if re.search(r"\bhand\b", t):
        tags.add("hand")
    if re.search(r"\bgy\b|graveyard", t):
        tags.add("gy")
    if re.search(r"\bdeck\b", t):
        tags.add("deck")
    if re.search(r"face-up", t):
        tags.add("faceup")
    if re.search(r"target\s+1\b|target\s+one\b", t):
        tags.add("target1")

    return frozenset(tags), draw_count, burn_damage


def fingerprint_code(source: str) -> frozenset[str]:
    tags: set[str] = set()
    for pattern, tag in HELPER_TAG_PATTERNS:
        if re.search(pattern, source):
            tags.add(tag)
    return frozenset(tags)


def suggest_pattern(
    tags: frozenset[str],
    effect_kind: str,
    draw_count: int | None,
    burn_damage: int | None,
) -> str | None:
    """Only spell stubs get fillable patterns (--fill writes spell_effects/)."""
    if effect_kind != "spell":
        return None

    # Keep these strict so multi-step text does not look "one-liner fillable".
    if "burn" in tags and not (
        tags & {"destroy", "search", "tribute", "ssummon", "draw", "gy", "hand", "deck", "target1", "st"}
    ):
        return "burn"
    if "search" in tags and not (tags & {"destroy", "ssummon", "tribute", "draw", "burn"}):
        return "search"
    if "draw" in tags and not (
        tags & {"discard", "gy", "search", "destroy", "ssummon", "tribute", "burn"}
    ):
        return "draw_n"
    if "tribute" in tags and "ssummon" in tags and not (tags & {"search", "burn"}):
        return "tribute_summon"
    if "destroy" in tags and ("target1" in tags or "st" in tags) and not (
        tags & {"gy", "ssummon", "draw", "tribute", "burn", "search"}
    ):
        return "destroy_zone"
    _ = draw_count, burn_damage
    return None


def build_archetype_map(consts: list[str]) -> dict[str, str]:
    """Map card_const → shared prefix used by ≥2 cards (longest wins)."""
    prefix_counts: Counter[str] = Counter()
    for const in consts:
        parts = const.split("_")
        for n in range(1, len(parts)):
            prefix_counts["_".join(parts[:n])] += 1

    out: dict[str, str] = {}
    for const in consts:
        parts = const.split("_")
        best = parts[0]
        for n in range(len(parts) - 1, 0, -1):
            prefix = "_".join(parts[:n])
            if prefix_counts[prefix] >= 2:
                best = prefix
                break
        out[const] = best
    return out


def jaccard(a: frozenset[str], b: frozenset[str]) -> float:
    if not a and not b:
        return 0.0
    union = a | b
    if not union:
        return 0.0
    return len(a & b) / len(union)


def scan_effects(meta: dict[str, CardMeta]) -> list[EffectFile]:
    files: list[EffectFile] = []
    for kind, rel in EFFECT_DIRS:
        directory = ROOT / rel
        if not directory.is_dir():
            continue
        for path in sorted(directory.glob("*.c")):
            source = path.read_text(encoding="utf-8", errors="replace")
            const = stem_to_const(path.stem)
            card = meta.get(const)
            text = card.effect_text if card else ""
            text_tags, draw_count, burn_damage = fingerprint_text(text)
            code_tags = fingerprint_code(source)
            stub = is_stub_source(source)
            pattern = suggest_pattern(
                text_tags | (frozenset() if stub else code_tags),
                kind,
                draw_count,
                burn_damage,
            )
            files.append(
                EffectFile(
                    path=path,
                    card_const=const,
                    effect_kind=kind,
                    is_stub=stub,
                    text_tags=text_tags,
                    code_tags=code_tags,
                    suggested_pattern=pattern if stub else None,
                    draw_count=draw_count,
                    burn_damage=burn_damage,
                )
            )

    arch = build_archetype_map([f.card_const for f in files])
    for f in files:
        f.archetype = arch[f.card_const]
    return files


def assign_clones(files: list[EffectFile]) -> None:
    implemented = [f for f in files if not f.is_stub]
    by_arch: dict[str, list[EffectFile]] = defaultdict(list)
    for f in implemented:
        by_arch[f.archetype].append(f)

    for stub in files:
        if not stub.is_stub:
            continue
        stub_tags = stub.text_tags | stub.code_tags
        best: EffectFile | None = None
        best_score = -1.0

        candidates = by_arch.get(stub.archetype, []) + implemented
        seen: set[str] = set()
        for cand in candidates:
            if cand.card_const in seen or cand.effect_kind != stub.effect_kind:
                continue
            seen.add(cand.card_const)
            cand_tags = cand.code_tags or cand.text_tags
            score = jaccard(stub_tags, cand_tags)
            if cand.archetype == stub.archetype:
                score += 0.35
            if stub.suggested_pattern:
                # Prefer clones that already use the matching helpers.
                want = {
                    "draw_n": "draw",
                    "burn": "burn",
                    "destroy_zone": "destroy",
                    "search": "search",
                    "tribute_summon": "tribute",
                }.get(stub.suggested_pattern)
                if want and want in cand_tags:
                    score += 0.4
            if score > best_score:
                best_score = score
                best = cand

        if best and best_score > 0:
            stub.clone_const = best.card_const
            stub.clone_path = str(best.path.relative_to(ROOT))
            stub.clone_score = round(best_score, 2)


def sort_stubs(stubs: list[EffectFile]) -> list[EffectFile]:
    arch_sizes = Counter(s.archetype for s in stubs)

    def key(s: EffectFile) -> tuple:
        has_pattern = 0 if s.suggested_pattern else 1
        size = -arch_sizes[s.archetype]
        pattern = s.suggested_pattern or "zzz"
        return (has_pattern, size, s.archetype, pattern, s.effect_kind, s.card_const)

    return sorted(stubs, key=key)


def sort_stubs_easy_first(stubs: list[EffectFile], meta: dict[str, CardMeta]) -> list[EffectFile]:
    """Prefer short text + high clone score — better for multi-card batches."""

    def key(s: EffectFile) -> tuple:
        text_len = len((meta.get(s.card_const).effect_text if meta.get(s.card_const) else "") or "")
        has_pattern = 0 if s.suggested_pattern else 1
        # Shorter text first; stronger clone next; fillable patterns before hard clones.
        return (has_pattern, text_len, -s.clone_score, s.effect_kind, s.card_const)

    return sorted(stubs, key=key)


def format_tags(tags: frozenset[str]) -> str:
    return ",".join(sorted(tags)) if tags else "-"


def print_queue(stubs: list[EffectFile], limit: int | None) -> None:
    rows = stubs[:limit] if limit else stubs
    print(f"# stub queue: {len(stubs)} total" + (f" (showing {len(rows)})" if limit else ""))
    print(
        f"{'PATTERN':<16} {'ARCHETYPE':<28} {'CARD':<36} {'KIND':<10} "
        f"{'TAGS':<28} {'CLONE':<28} {'SCORE':>5}"
    )
    for s in rows:
        clone = s.clone_const or "-"
        print(
            f"{(s.suggested_pattern or '-'):<16} {s.archetype:<28} {s.card_const:<36} "
            f"{s.effect_kind:<10} {format_tags(s.text_tags):<28} {clone:<28} {s.clone_score:>5.2f}"
        )
        if s.clone_path:
            print(f"  clone: {s.clone_path}")


def const_to_pascal(card_const: str) -> str:
    return "".join(p.title() for p in card_const.split("_"))


# --- Codegen templates (spell-focused; overwrite existing stub .c) ---


def template_draw_n(card_const: str, draw_count: int) -> str:
    return f'''#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define {card_const}_DRAW_COUNT {draw_count}

static void {const_to_pascal(card_const)}_ResolveBody(void)
{{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText({card_const});

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, {card_const}_DRAW_COUNT, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}}

APPEND_TEXT void Effect{card_const}(void)
{{
  if (Duel_TryResolveSpellThroughTraps({card_const}, {const_to_pascal(card_const)}_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}}
'''


def template_burn(card_const: str, damage: int) -> str:
    return f'''#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define {card_const}_DAMAGE {damage}

static void {const_to_pascal(card_const)}_ResolveBody(void)
{{
  if (Duel_ResolveBurnSpell({card_const}, {card_const}_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}}

APPEND_TEXT void Effect{card_const}(void)
{{
  if (Duel_TryResolveSpellThroughTrapsEx({card_const}, {card_const}_DAMAGE,
                                         {const_to_pascal(card_const)}_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}}
'''


def template_destroy_zone(card_const: str, target: str) -> str:
    """target: opp_monster | any_monster | backrow | faceup_st"""
    pascal = const_to_pascal(card_const)

    if target == "opp_monster":
        row_check = """  if (fixedRow != (WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW))
    return FALSE;
"""
        zone_extra = "  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;\n"
    elif target == "any_monster":
        row_check = """  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;
"""
        zone_extra = "  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;\n"
    elif target == "backrow":
        row_check = """  if (fixedRow != PLAYER_BACKROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;
"""
        zone_extra = """  {
    u8 typeGroup = GetTypeGroup(zone->id);
    return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
  }
"""
    elif target == "faceup_st":
        row_check = """  if (fixedRow != PLAYER_BACKROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;
"""
        zone_extra = """  if (!zone->isFaceUp)
    return FALSE;
  {
    u8 typeGroup = GetTypeGroup(zone->id);
    return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
  }
"""
    else:
        raise SystemExit(f"Unknown --target {target!r} (use opp_monster|any_monster|backrow|faceup_st)")

    return f'''#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}}

static u8 IsValid{pascal}Target(u8 fixedRow, u8 fixedCol)
{{
  struct DuelCard *zone;

{row_check}
  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

{zone_extra}}}

static const u8 s{pascal}ScanRows[] = {{
  OPPONENT_BACKROW, OPPONENT_MONSTER_ROW, PLAYER_MONSTER_ROW, PLAYER_BACKROW
}};

static u8 Has{pascal}Target(void)
{{
  u8 i;
  u8 col;

  for (i = 0; i < 4; i++) {{
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {{
      if (IsValid{pascal}Target(s{pascal}ScanRows[i], col))
        return TRUE;
    }}
  }}

  return FALSE;
}}

static void Cancel{pascal}Targeting(void)
{{
  PlayMusic(SFX_CANCEL);
}}

static u8 AiPick{pascal}Target(u8 *outRow, u8 *outCol)
{{
  u8 i;
  u8 col;

  for (i = 0; i < 4; i++) {{
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {{
      if (!IsValid{pascal}Target(s{pascal}ScanRows[i], col))
        continue;
      *outRow = s{pascal}ScanRows[i];
      *outCol = col;
      return TRUE;
    }}
  }}

  return FALSE;
}}

static void Resolve{pascal}Target(u8 fixedRow, u8 fixedCol)
{{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (Duel_DestroyZone(target, GraveyardDuelistForFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  NotifyDynamicEquipFieldChanged();
}}

u8 CanActivate{pascal}(void)
{{
  return Has{pascal}Target();
}}

static void {pascal}_ResolveBody(void)
{{
  Duel_ShowEffectText({card_const});

  if (IsDuelOver() == TRUE || !Has{pascal}Target())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValid{pascal}Target, Resolve{pascal}Target, Cancel{pascal}Targeting,
                     AiPick{pascal}Target);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}}

APPEND_TEXT void Effect{card_const}(void)
{{
  if (!CanActivate{pascal}()) {{
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }}

  if (Duel_TryResolveSpellThroughTraps({card_const}, {pascal}_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}}
'''


def template_search(card_const: str, add_card: str | None) -> str:
    pascal = const_to_pascal(card_const)
    if add_card:
        return f'''#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 CanActivate{pascal}(void)
{{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, {add_card}) >= 0;
}}

static void {pascal}_ResolveBody(void)
{{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText({card_const});

  if (IsDuelOver() == TRUE || !CanActivate{pascal}())
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, {add_card}, FALSE) != DUEL_ACTION_OK)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}}

APPEND_TEXT void Effect{card_const}(void)
{{
  if (!CanActivate{pascal}()) {{
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }}

  if (Duel_TryResolveSpellThroughTraps({card_const}, {pascal}_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}}
'''

    # Predicate stub — agent fills IsMatch
    return f'''#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 Is{pascal}SearchMatch(u16 cardId)
{{
  /* TODO: tighten match (type/level/name). Default: any monster. */
  if (cardId == CARD_NONE)
    return FALSE;
  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}}

static s16 FindFirst{pascal}DeckIndex(u8 turnDuelist)
{{
  u8 fixedDuelist = gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
                        ? DUEL_PLAYER
                        : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {{
    if (Is{pascal}SearchMatch(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }}

  return -1;
}}

u8 CanActivate{pascal}(void)
{{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindFirst{pascal}DeckIndex(ACTIVE_DUELIST) >= 0;
}}

static void {pascal}_ResolveBody(void)
{{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  s16 deckIndex;
  u16 cardId;
  u8 fixedDuelist;

  Duel_ShowEffectText({card_const});

  if (IsDuelOver() == TRUE || !CanActivate{pascal}())
    return;

  deckIndex = FindFirst{pascal}DeckIndex(ACTIVE_DUELIST);
  if (deckIndex < 0)
    return;

  fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
                     ? DUEL_PLAYER
                     : DUEL_OPPONENT;
  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];

  /* AddDeckCardToHand finds the first matching id and removes it. */
  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, FALSE) != DUEL_ACTION_OK)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}}

APPEND_TEXT void Effect{card_const}(void)
{{
  if (!CanActivate{pascal}()) {{
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }}

  if (Duel_TryResolveSpellThroughTraps({card_const}, {pascal}_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}}
'''


def template_tribute_summon(card_const: str, summon_level: int) -> str:
    pascal = const_to_pascal(card_const)
    return f'''#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define {card_const}_SUMMON_LEVEL {summon_level}

static u8 ActiveMonsterFixedRow(void)
{{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}}

static u8 Is{pascal}SummonTarget(u16 cardId)
{{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level == {card_const}_SUMMON_LEVEL;
}}

static u8 IsValid{pascal}Tribute(u8 fixedRow, u8 fixedCol)
{{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}}

static u8 HandHas{pascal}SummonTarget(void)
{{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {{
    if (Is{pascal}SummonTarget(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }}

  return FALSE;
}}

static u8 Has{pascal}Tribute(void)
{{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {{
    if (IsValid{pascal}Tribute(ActiveMonsterFixedRow(), col))
      return TRUE;
  }}

  return FALSE;
}}

u8 CanActivate{pascal}(void)
{{
  if (!Has{pascal}Tribute())
    return FALSE;
  if (!HandHas{pascal}SummonTarget())
    return FALSE;
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0
      || Has{pascal}Tribute(); /* tribute frees a zone */
}}

static void Cancel{pascal}Targeting(void)
{{
  PlayMusic(SFX_CANCEL);
}}

static u8 AiPick{pascal}Tribute(u8 *outRow, u8 *outCol)
{{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {{
    if (!IsValid{pascal}Tribute(ActiveMonsterFixedRow(), col))
      continue;
    *outRow = ActiveMonsterFixedRow();
    *outCol = col;
    return TRUE;
  }}

  return FALSE;
}}

static void Resolve{pascal}Tribute(u8 fixedRow, u8 fixedCol)
{{
  struct DuelCard *tribute = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;

  if (Duel_DestroyZone(tribute, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], Is{pascal}SummonTarget);
  else {{
    handZone = -1;
    {{
      u8 i;
      for (i = 0; i < MAX_ZONES_IN_ROW; i++) {{
        if (Is{pascal}SummonTarget(gTurnHands[ACTIVE_DUELIST][i]->id)) {{
          handZone = i;
          break;
        }}
      }}
    }}
  }}

  if (handZone < 0)
    return;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}}

static void {pascal}_ResolveBody(void)
{{
  Duel_ShowEffectText({card_const});

  if (IsDuelOver() == TRUE || !CanActivate{pascal}())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValid{pascal}Tribute, Resolve{pascal}Tribute, Cancel{pascal}Targeting,
                     AiPick{pascal}Tribute);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}}

APPEND_TEXT void Effect{card_const}(void)
{{
  if (!CanActivate{pascal}()) {{
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }}

  if (Duel_TryResolveSpellThroughTraps({card_const}, {pascal}_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}}
'''


def render_fill(
    pattern: str,
    card_const: str,
    *,
    draw_count: int | None = None,
    damage: int | None = None,
    target: str | None = None,
    add_card: str | None = None,
    summon_level: int | None = None,
    meta: dict[str, CardMeta] | None = None,
) -> str:
    if pattern == "draw_n":
        count = draw_count
        if count is None:
            card = (meta or {}).get(card_const)
            _, inferred, _ = fingerprint_text(card.effect_text if card else "")
            count = inferred or 2
        return template_draw_n(card_const, count)
    if pattern == "burn":
        dmg = damage
        if dmg is None:
            card = (meta or {}).get(card_const)
            _, _, inferred = fingerprint_text(card.effect_text if card else "")
            dmg = inferred or 500
        return template_burn(card_const, dmg)
    if pattern == "destroy_zone":
        return template_destroy_zone(card_const, target or "faceup_st")
    if pattern == "search":
        return template_search(card_const, add_card.upper() if add_card else None)
    if pattern == "tribute_summon":
        return template_tribute_summon(card_const, summon_level or 7)
    raise ValueError(f"unknown pattern {pattern}")


def fill_one(
    pattern: str,
    card_const: str,
    *,
    dry_run: bool = False,
    draw_count: int | None = None,
    damage: int | None = None,
    target: str | None = None,
    add_card: str | None = None,
    summon_level: int | None = None,
    meta: dict[str, CardMeta] | None = None,
) -> int:
    card_const = card_const.upper()
    path = ROOT / "src_custom" / "spell_effects" / f"{card_const.lower()}.c"
    if not path.is_file():
        print(f"error: missing spell stub {path.relative_to(ROOT)}", file=sys.stderr)
        return 1

    body = render_fill(
        pattern,
        card_const,
        draw_count=draw_count,
        damage=damage,
        target=target,
        add_card=add_card,
        summon_level=summon_level,
        meta=meta,
    )
    if dry_run:
        print(body)
        return 0

    path.write_text(body)
    print(f"Wrote {path.relative_to(ROOT)} ({pattern})")
    return 0


def fill_template(args: argparse.Namespace) -> int:
    meta = load_manifest()
    rc = fill_one(
        args.fill,
        args.card_const,
        dry_run=args.dry_run,
        draw_count=args.draw_count,
        damage=args.damage,
        target=args.target,
        add_card=args.add_card,
        summon_level=args.summon_level,
        meta=meta,
    )
    if rc == 0 and not args.dry_run:
        print("Next: tighten predicates if needed, then make test-cards-link")
    return rc


def fill_all(args: argparse.Namespace) -> int:
    """Apply templates to every matching fillable spell stub."""
    meta = load_manifest()
    files = scan_effects(meta)
    stubs = [
        f
        for f in files
        if f.is_stub and f.effect_kind == "spell" and f.suggested_pattern
    ]
    if args.pattern:
        stubs = [s for s in stubs if s.suggested_pattern == args.pattern]
    if args.archetype:
        prefix = args.archetype.upper()
        stubs = [s for s in stubs if s.archetype == prefix or s.card_const.startswith(prefix)]
    stubs = sort_stubs(stubs)
    if args.limit:
        stubs = stubs[: args.limit]

    if not stubs:
        print("No fillable stubs matched.", file=sys.stderr)
        return 1

    wrote = 0
    for stub in stubs:
        pattern = stub.suggested_pattern
        assert pattern is not None
        target = args.target
        if pattern == "destroy_zone" and not target:
            if "faceup" in stub.text_tags and "st" in stub.text_tags:
                target = "faceup_st"
            elif "st" in stub.text_tags:
                target = "backrow"
            else:
                target = "opp_monster"

        if args.dry_run:
            print(
                f"would fill {stub.card_const} as {pattern}"
                + (f" target={target}" if pattern == "destroy_zone" else "")
                + (f" draw={stub.draw_count}" if pattern == "draw_n" else "")
                + (f" dmg={stub.burn_damage}" if pattern == "burn" else "")
            )
            wrote += 1
            continue

        rc = fill_one(
            pattern,
            stub.card_const,
            dry_run=False,
            draw_count=stub.draw_count,
            damage=stub.burn_damage,
            target=target,
            summon_level=args.summon_level,
            meta=meta,
        )
        if rc != 0:
            return rc
        wrote += 1

    print(f"{'Would fill' if args.dry_run else 'Filled'} {wrote} stubs"
          f"{' (dry-run)' if args.dry_run else ''}")
    if not args.dry_run:
        print("Review predicates, then: make test-cards-link")
    return 0


def stub_to_pack_entry(stub: EffectFile, meta: dict[str, CardMeta]) -> dict:
    card = meta.get(stub.card_const)
    return {
        "card_const": stub.card_const,
        "card_name": card.card_name if card else stub.card_const,
        "kind": stub.effect_kind,
        "archetype": stub.archetype,
        "path": str(stub.path.relative_to(ROOT)),
        "effect_text": (card.effect_text if card else "")[:500],
        "tags": sorted(stub.text_tags),
        "pattern": stub.suggested_pattern,
        "draw_count": stub.draw_count,
        "burn_damage": stub.burn_damage,
        "clone_const": stub.clone_const,
        "clone_path": stub.clone_path,
        "clone_score": stub.clone_score,
    }


def write_work_pack(
    stubs: list[EffectFile], meta: dict[str, CardMeta], out_dir: Path, workers: int
) -> int:
    out_dir.mkdir(parents=True, exist_ok=True)
    entries = [stub_to_pack_entry(s, meta) for s in stubs]
    workers = max(1, workers)

    chunks: list[list[dict]] = [[] for _ in range(workers)]
    for i, entry in enumerate(entries):
        chunks[i % workers].append(entry)

    instruction = (
        "Implement EVERY card in this pack. Clone from clone_path; match effect_text. "
        "Use duel_helpers.h. Spells: only edit the listed .c file. "
        "Activated/permanent may need monster_effects.h / dispatcher — serialize those. "
        "Do not leave TODO bodies. One make at the end of the whole batch."
    )
    manifest: dict = {
        "total": len(entries),
        "workers": workers,
        "instruction": instruction,
        "packs": [],
    }

    for w, chunk in enumerate(chunks):
        if not chunk:
            continue
        pack_path = out_dir / f"pack_{w:02d}.json"
        md_path = out_dir / f"pack_{w:02d}.md"
        pack_body = {
            "worker": w,
            "count": len(chunk),
            "instruction": instruction,
            "cards": chunk,
        }
        pack_path.write_text(json.dumps(pack_body, indent=2) + "\n")

        lines = [
            f"# Effect work pack {w:02d} ({len(chunk)} cards)",
            "",
            instruction,
            "",
        ]
        for card in chunk:
            lines.append(f"## {card['card_const']} ({card['kind']})")
            lines.append(f"- file: `{card['path']}`")
            if card.get("clone_path"):
                lines.append(f"- clone: `{card['clone_path']}` ({card.get('clone_const')})")
            if card.get("pattern"):
                lines.append(
                    f"- optional template: `--fill {card['pattern']} {card['card_const']}`"
                )
            lines.append(f"- text: {card.get('effect_text') or '(no text)'}")
            lines.append("")
        md_path.write_text("\n".join(lines))
        manifest["packs"].append(
            {
                "worker": w,
                "json": str(pack_path.relative_to(ROOT)),
                "md": str(md_path.relative_to(ROOT)),
                "count": len(chunk),
            }
        )

    index_path = out_dir / "index.json"
    index_path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(
        f"Wrote work pack: {index_path.relative_to(ROOT)} "
        f"({len(entries)} cards, {workers} workers)"
    )
    for p in manifest["packs"]:
        print(f"  worker {p['worker']}: {p['count']} cards → {p['md']}")
    return 0


def self_check() -> int:
    tags, draw, dmg = fingerprint_text("Draw 2 cards.")
    assert "draw" in tags and draw == 2, (tags, draw)
    tags, _, dmg = fingerprint_text("Inflict 500 damage to your opponent.")
    assert "burn" in tags and dmg == 500, (tags, dmg)
    tags, _, _ = fingerprint_text("Add 1 Level 5 or higher Normal Monster from your Deck to your hand.")
    assert "search" in tags, tags
    tags, _, _ = fingerprint_text("Target 1 face-up Spell/Trap on the field; destroy that target.")
    assert suggest_pattern(tags, "spell", None, None) == "destroy_zone", tags
    tags, _, _ = fingerprint_text("Tribute 1 monster; Special Summon 1 Level 7 monster from your hand.")
    assert suggest_pattern(tags, "spell", None, None) == "tribute_summon", tags
    tags, _, _ = fingerprint_text("Draw 2 cards. Destroy 1 monster.")
    assert suggest_pattern(tags, "spell", 2, None) is None, tags
    assert suggest_pattern(frozenset({"burn"}), "activated", None, 500) is None

    body = template_burn("SPARKS", 200)
    assert "Duel_ResolveBurnSpell(SPARKS, SPARKS_DAMAGE, TRUE)" in body
    body = template_draw_n("JAR_OF_GREED", 1)
    assert "JAR_OF_GREED_DRAW_COUNT 1" in body
    print("self-check OK")
    return 0


def write_stub_list(
    stubs: list[EffectFile],
    meta: dict[str, CardMeta],
    out_path: Path | None = None,
) -> Path:
    """Write living backlog of every stubbed effect. Rows vanish when TODOs are gone."""
    from datetime import datetime, timezone

    if out_path is None:
        out_path = ROOT / "documentation" / "STUB_EFFECTS.md"

    stubs = sorted(stubs, key=lambda s: (s.effect_kind, s.archetype, s.card_const))
    by_kind = Counter(s.effect_kind for s in stubs)
    stamp = datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M UTC")

    lines = [
        "# Stub Effects Backlog",
        "",
        "Auto-generated living list of effect files that still contain `TODO` stubs.",
        "Entries disappear when the effect body is implemented (re-run `--write-list`).",
        "",
        "```bash",
        "python3 tools/stub_effect_queue.py --write-list",
        "```",
        "",
        f"**Last updated:** {stamp}  ",
        f"**Remaining stubs:** `{len(stubs)}`",
        "",
        "## Counts by kind",
        "",
        "| Kind | Count |",
        "|------|------:|",
    ]
    for kind, _ in EFFECT_DIRS:
        if by_kind.get(kind):
            lines.append(f"| `{kind}` | {by_kind[kind]} |")
    lines.append(f"| **total** | **{len(stubs)}** |")
    lines.append("")

    for kind, _ in EFFECT_DIRS:
        kind_stubs = [s for s in stubs if s.effect_kind == kind]
        if not kind_stubs:
            continue
        lines.append(f"## {kind} ({len(kind_stubs)})")
        lines.append("")
        lines.append("| `card_const` | archetype | pattern | clone | path |")
        lines.append("|--------------|-----------|---------|-------|------|")
        for s in kind_stubs:
            name = meta.get(s.card_const).card_name if meta.get(s.card_const) else ""
            pattern = s.suggested_pattern or ""
            clone = s.clone_const or ""
            rel = str(s.path.relative_to(ROOT))
            # title attribute via name in first column tooltip-ish: keep const primary
            _ = name
            lines.append(
                f"| `{s.card_const}` | `{s.archetype}` | {pattern or '—'} | "
                f"{('`' + clone + '`') if clone else '—'} | `{rel}` |"
            )
        lines.append("")

    out_path.write_text("\n".join(lines).rstrip() + "\n")
    print(f"Wrote {out_path.relative_to(ROOT)} ({len(stubs)} stubs)", file=sys.stderr)
    return out_path


def filtered_stubs(args: argparse.Namespace) -> tuple[dict[str, CardMeta], list[EffectFile]]:
    meta = load_manifest()
    files = scan_effects(meta)
    assign_clones(files)
    stubs = [f for f in files if f.is_stub]

    if args.pattern:
        stubs = [s for s in stubs if s.suggested_pattern == args.pattern]
    if args.archetype:
        prefix = args.archetype.upper()
        stubs = [s for s in stubs if s.archetype == prefix or s.card_const.startswith(prefix)]
    if args.kind:
        stubs = [s for s in stubs if s.effect_kind == args.kind]
    if getattr(args, "fillable_only", False):
        stubs = [s for s in stubs if s.suggested_pattern]

    return meta, sort_stubs(stubs)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Stub effect queue + pattern codegen + batch packs"
    )
    parser.add_argument("--limit", type=int, default=None, help="Max rows / fill-all size")
    parser.add_argument("--pattern", choices=FILL_PATTERNS, help="Filter by suggested pattern")
    parser.add_argument("--archetype", help="Filter by archetype prefix (e.g. GRAVEKEEPERS)")
    parser.add_argument("--kind", choices=[k for k, _ in EFFECT_DIRS], help="Filter effect kind")
    parser.add_argument(
        "--fillable-only", action="store_true", help="Only stubs with a fill template"
    )
    parser.add_argument("--json", action="store_true", help="Emit JSON instead of table")
    parser.add_argument("--fill", choices=FILL_PATTERNS, help="Overwrite one spell stub")
    parser.add_argument(
        "--fill-all",
        action="store_true",
        help="Fill all matching fillable spell stubs (use with --pattern/--limit)",
    )
    parser.add_argument(
        "--work-pack",
        type=int,
        metavar="N",
        help="Write a multi-card work pack of N stubs for batch/parallel implement",
    )
    parser.add_argument(
        "--workers",
        type=int,
        default=1,
        help="Split --work-pack across N worker files (default 1)",
    )
    parser.add_argument(
        "--by-archetype",
        action="store_true",
        help="With --work-pack, sort by archetype batches instead of easy-first",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=None,
        help="Output dir for --work-pack (default documentation/effect_work_packs/YYYY-MM-DD)",
    )
    parser.add_argument("card_const", nargs="?", help="CARD_CONST for --fill")
    parser.add_argument("--draw-count", type=int, help="draw_n: cards to draw")
    parser.add_argument("--damage", type=int, help="burn: LP damage")
    parser.add_argument(
        "--target",
        choices=("opp_monster", "any_monster", "backrow", "faceup_st"),
        help="destroy_zone target filter",
    )
    parser.add_argument("--add-card", help="search: exact CARD_CONST to add")
    parser.add_argument("--summon-level", type=int, help="tribute_summon: hand monster level")
    parser.add_argument("--dry-run", action="store_true", help="With --fill/--fill-all, print only")
    parser.add_argument(
        "--write-list",
        action="store_true",
        help="Write documentation/STUB_EFFECTS.md (all remaining stubs; shrinks as implemented)",
    )
    parser.add_argument("--self-check", action="store_true", help="Run assert-based smoke check")
    args = parser.parse_args()

    if args.self_check:
        return self_check()

    if args.fill and args.fill_all:
        parser.error("use only one of --fill / --fill-all")

    if args.write_list and not (args.fill or args.fill_all or args.work_pack is not None):
        meta = load_manifest()
        files = scan_effects(meta)
        assign_clones(files)
        stubs = [f for f in files if f.is_stub]
        write_stub_list(stubs, meta)
        return 0

    if args.fill:
        if not args.card_const:
            parser.error("--fill requires CARD_CONST")
        rc = fill_template(args)
        if rc == 0 and args.write_list:
            meta = load_manifest()
            files = scan_effects(meta)
            assign_clones(files)
            write_stub_list([f for f in files if f.is_stub], meta)
        return rc

    if args.fill_all:
        rc = fill_all(args)
        if rc == 0 and not args.dry_run:
            meta = load_manifest()
            files = scan_effects(meta)
            assign_clones(files)
            write_stub_list([f for f in files if f.is_stub], meta)
        return rc

    if args.work_pack is not None:
        if args.work_pack < 1:
            parser.error("--work-pack N requires N >= 1")
        meta, stubs = filtered_stubs(args)
        # Work packs default to easy-first so batches finish; --by-archetype keeps old sort.
        if not getattr(args, "by_archetype", False):
            stubs = sort_stubs_easy_first(stubs, meta)
        stubs = stubs[: args.work_pack]
        if not stubs:
            print("No stubs matched for work pack.", file=sys.stderr)
            return 1
        from datetime import date

        out_dir = args.out
        if out_dir is None:
            out_dir = ROOT / "documentation" / "effect_work_packs" / date.today().isoformat()
        elif not out_dir.is_absolute():
            out_dir = ROOT / out_dir
        return write_work_pack(stubs, meta, out_dir, args.workers)

    meta, stubs = filtered_stubs(args)

    if args.json:
        payload = [stub_to_pack_entry(s, meta) for s in (stubs[: args.limit] if args.limit else stubs)]
        json.dump(payload, sys.stdout, indent=2)
        print()
        return 0

    print_queue(stubs, args.limit)
    by_pat = Counter(s.suggested_pattern for s in stubs if s.suggested_pattern)
    if by_pat:
        print("\n# fillable pattern counts:")
        for pat, n in by_pat.most_common():
            print(f"  {pat}: {n}")
    print("\n# batch next:")
    print("  python3 tools/stub_effect_queue.py --work-pack 12 --kind spell --workers 3")
    print("  python3 tools/stub_effect_queue.py --fill-all --pattern burn --dry-run")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
