#!/usr/bin/env python3
"""Validate duel B menu option label placement hooks."""

from __future__ import annotations

import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
HOOKS = ROOT / "src_custom" / "duel_b_menu_hooks.c"
BASEROM = ROOT / "baserom.gba"
GBA = ROOT / "ygodm8.gba"

TEMPLATE_ROM_OFF = 0x80F13D0 - 0x08000000
G8DF811C_ROM_OFF = 0xDF811C
TEMPLATE_ROWS = 18
TEMPLATE_ROW_BYTES = 64
LABEL_TILE_MIN = 88
PALETTE_BITS = 0x0000

# Visible baked surrender on the left side of the template tilemap.
GOLDEN_TEMPLATE_SURRENDER_CELLS = frozenset(
    {
        (9, 0),
        (9, 1),
        (9, 2),
        (9, 3),
        (9, 4),
        (9, 5),
        (9, 6),
        (9, 27),
        (9, 28),
        (9, 29),
        (9, 30),
        (9, 31),
        (10, 0),
        (10, 1),
        (10, 2),
        (10, 3),
        (10, 4),
    }
)


@dataclass(frozen=True)
class OptionLabelSpec:
    name: str
    col: int
    row_top: int
    row_bottom: int
    width: int
    tile_top: int
    tile_bottom: int


LABEL_COL_LEFT = 5
LABEL_COL_RIGHT = 17
LABEL_WIDTH = 10
SURRENDER_WIDTH = 9

EXPECTED_OPTION_LABELS = (
    OptionLabelSpec("Details", LABEL_COL_LEFT, 1, 2, LABEL_WIDTH, 88, 90),
    OptionLabelSpec("Discard", LABEL_COL_RIGHT, 1, 2, LABEL_WIDTH, 128, 130),
    OptionLabelSpec("Turn end", LABEL_COL_LEFT, 3, 4, LABEL_WIDTH, 108, 110),
    OptionLabelSpec("Surrender", LABEL_COL_RIGHT, 3, 4, SURRENDER_WIDTH, 148, 150),
)


def read_template_cells(gba_path: Path) -> dict[tuple[int, int], int]:
    data = gba_path.read_bytes()
    blob = data[TEMPLATE_ROM_OFF : TEMPLATE_ROM_OFF + TEMPLATE_ROWS * TEMPLATE_ROW_BYTES]
    cells: dict[tuple[int, int], int] = {}
    for row in range(TEMPLATE_ROWS):
        row_bytes = blob[row * TEMPLATE_ROW_BYTES : (row + 1) * TEMPLATE_ROW_BYTES]
        entries = struct.unpack_from("<32H", row_bytes)
        for col, entry in enumerate(entries):
            cells[(row, col)] = entry & 0x3FF
    return cells


def read_g8df811c(baserom_path: Path = BASEROM) -> list[int]:
    data = baserom_path.read_bytes()
    return list(data[G8DF811C_ROM_OFF : G8DF811C_ROM_OFF + 0x20])


def parse_define(source: str, name: str) -> int:
    match = re.search(rf"#define\s+{re.escape(name)}\s+(\d+)", source)
    if not match:
        raise ValueError(f"missing #define {name}")
    return int(match.group(1))


def resolve_table_value(source: str, token: str) -> int:
    token = token.strip()
    if re.fullmatch(r"\d+", token):
        return int(token)
    return parse_define(source, token)


def parse_option_labels_table(source: str) -> list[OptionLabelSpec]:
    block = re.search(
        r"static const struct BMenuOptionLabel sBMenuOptionLabels\[\].*?\{(.*?)\};",
        source,
        re.S,
    )
    if not block:
        raise ValueError("missing sBMenuOptionLabels table")

    names = ("Details", "Discard", "Turn end", "Surrender")
    rows = re.findall(
        r"\[B_MENU_\w+\]\s*=\s*\{([^,]+),\s*(\d+),\s*(\d+),\s*([^,]+),\s*([^,]+),\s*([^,}]+)\}",
        block.group(1),
    )
    if len(rows) != 4:
        raise ValueError(f"expected 4 sBMenuOptionLabels entries, found {len(rows)}")

    return [
        OptionLabelSpec(
            name=names[i],
            col=resolve_table_value(source, col),
            row_top=int(row_top),
            row_bottom=int(row_bottom),
            width=resolve_table_value(source, width),
            tile_top=resolve_table_value(source, tile_top),
            tile_bottom=resolve_table_value(source, tile_bottom),
        )
        for i, (col, row_top, row_bottom, width, tile_top, tile_bottom) in enumerate(rows)
    ]


def simulate_post_draw_tilemap(template_cells: dict[tuple[int, int], int]) -> dict[tuple[int, int], int]:
    """Mirror ClearBMenuOptionLabelCells + DrawBMenuAllOptionLabels."""
    cells = dict(template_cells)
    g8 = read_g8df811c()

    for row in list(range(1, 5)) + list(range(8, 11)) + list(range(14, 17)):
        for col in range(32):
            cells[(row, col)] = 0

    for (row, col), tile in list(cells.items()):
        if tile >= LABEL_TILE_MIN:
            cells[(row, col)] = 0

    for spec in EXPECTED_OPTION_LABELS:
        for i in range(spec.width):
            cells[(spec.row_top, spec.col + i)] = (spec.tile_top + g8[i]) | PALETTE_BITS
            cells[(spec.row_bottom, spec.col + i)] = (spec.tile_bottom + g8[i]) | PALETTE_BITS

    return cells


def validate(*, gba_path: Path = GBA, hooks_path: Path = HOOKS) -> None:
    if not hooks_path.is_file():
        raise SystemExit(f"validate_duel_b_menu: missing {hooks_path}")
    if not gba_path.is_file():
        raise SystemExit(f"validate_duel_b_menu: missing {gba_path} (run make first)")
    if not BASEROM.is_file():
        raise SystemExit(f"validate_duel_b_menu: missing {BASEROM}")

    source = hooks_path.read_text(encoding="utf-8")

    if "sBMenuOptionLabels" not in source:
        raise SystemExit("validate_duel_b_menu: missing sBMenuOptionLabels table")
    if "DrawBMenuAllOptionLabels" not in source:
        raise SystemExit("validate_duel_b_menu: missing DrawBMenuAllOptionLabels")
    if "ClearBMenuOptionLabelCells" not in source:
        raise SystemExit("validate_duel_b_menu: missing ClearBMenuOptionLabelCells")
    if "DrawBMenuFixedLabels" in source:
        raise SystemExit("validate_duel_b_menu: remove legacy DrawBMenuFixedLabels")
    if "DrawBMenuSurrenderLabel" in source:
        raise SystemExit("validate_duel_b_menu: remove legacy DrawBMenuSurrenderLabel")

    draw_fn = re.search(
        r"static void DrawBMenuOptionLabel\(.*?\n\}",
        source,
        re.S,
    )
    if not draw_fn:
        raise SystemExit("validate_duel_b_menu: missing DrawBMenuOptionLabel")
    draw_body = draw_fn.group(0)
    if "BMenuWriteTile" not in draw_body or "g8DF811C[i]" not in draw_body:
        raise SystemExit("validate_duel_b_menu: DrawBMenuOptionLabel must use BMenuWriteTile and g8DF811C[i]")

    if parse_define(source, "B_MENU_LABEL_TILE_TURN_END_TOP") != 108:
        raise SystemExit("validate_duel_b_menu: Turn end tiles must start at 108 for 4-label CHR layout")
    if parse_define(source, "B_MENU_LABEL_TILE_DISCARD_TOP") != 128:
        raise SystemExit("validate_duel_b_menu: Discard tiles must start at 128 for 4-label CHR layout")
    if parse_define(source, "B_MENU_LABEL_TILE_SURRENDER_TOP") != 148:
        raise SystemExit("validate_duel_b_menu: Surrender tiles must start at 148 for 4-label CHR layout")

    parsed = parse_option_labels_table(source)
    if parsed != list(EXPECTED_OPTION_LABELS):
        raise SystemExit(
            "validate_duel_b_menu: sBMenuOptionLabels does not match expected 2x2 layout:\n"
            + "\n".join(f"  parsed {p}" for p in parsed)
        )

    surrender = parsed[3]
    if "HighlightBMenuOption(highlightedOption)" not in source:
        raise SystemExit("validate_duel_b_menu: RefreshOverlay must re-apply cursor highlight after label draw")
    if surrender.col != LABEL_COL_RIGHT or surrender.row_top != 3:
        raise SystemExit("validate_duel_b_menu: surrender label must align with highlight at row 3 col 14")

    template_cells = read_template_cells(gba_path)
    baked = {
        (row, col)
        for (row, col), tile in template_cells.items()
        if tile >= 168
    }
    if not GOLDEN_TEMPLATE_SURRENDER_CELLS.issubset(baked):
        missing = sorted(GOLDEN_TEMPLATE_SURRENDER_CELLS - baked)
        raise SystemExit(
            "validate_duel_b_menu: template surrender cells changed in ROM; update goldens: "
            + ", ".join(f"({r},{c})" for r, c in missing)
        )

    draw_cells = {(surrender.row_top, surrender.col), (surrender.row_bottom, surrender.col)}
    overlap = draw_cells & baked
    if overlap:
        raise SystemExit(
            "validate_duel_b_menu: draw coordinates overlap baked template surrender cells: "
            + ", ".join(f"({r},{c})" for r, c in sorted(overlap))
        )

    simulated = simulate_post_draw_tilemap(template_cells)
    for stale_row, stale_col in GOLDEN_TEMPLATE_SURRENDER_CELLS:
        if simulated[(stale_row, stale_col)] >= 168:
            raise SystemExit(
                "validate_duel_b_menu: simulated tilemap still has surrender tile at stale "
                f"({stale_row},{stale_col})"
            )

    for spec in EXPECTED_OPTION_LABELS:
        if simulated[(spec.row_top, spec.col)] < spec.tile_top:
            raise SystemExit(
                f"validate_duel_b_menu: simulated draw missing {spec.name} at ({spec.row_top},{spec.col})"
            )
        if simulated[(spec.row_bottom, spec.col)] < spec.tile_bottom:
            raise SystemExit(
                f"validate_duel_b_menu: simulated draw missing {spec.name} at ({spec.row_bottom},{spec.col})"
            )

    stale_left = simulated[(9, 0)]
    new_top = simulated[(surrender.row_top, surrender.col)]
    if stale_left == new_top:
        raise SystemExit("validate_duel_b_menu: draw coordinates match stale template left cell")


def main() -> None:
    try:
        validate()
    except SystemExit as exc:
        print(exc, file=sys.stderr)
        raise SystemExit(1) from exc
    print("validate_duel_b_menu: ok")


if __name__ == "__main__":
    main()
