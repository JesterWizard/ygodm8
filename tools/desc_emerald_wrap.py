"""Emerald narrow-font page count — mirrors NarrowFontWrapProse in narrow_font.c."""

from __future__ import annotations

from build_narrow_font import ASCII_TO_CHAR, NARROW_PERCENT_WIDTH, SMALL_NARROW_WIDTHS

NARROW_ROW_PX = 112
NARROW_DESC_ROWS = 5
NARROW_ARROW_GAP = 1
ARROW_UP_WIDTH = 8
ARROW_DOWN_WIDTH = 8


def char_width(c: str) -> int:
    if c == "%":
        return NARROW_PERCENT_WIDTH
    if len(c) != 1 or ord(c) < 32 or ord(c) > 126:
        return 5
    idx = ASCII_TO_CHAR.get(c)
    if idx is None:
        return 5
    w = SMALL_NARROW_WIDTHS[idx] if idx < len(SMALL_NARROW_WIDTHS) else 5
    return w if w else 5


def row_budget(page_index: int, row: int) -> int:
    budget = NARROW_ROW_PX
    if page_index > 0 and row == 0:
        budget -= ARROW_UP_WIDTH + NARROW_ARROW_GAP
    # Wrap always reserves down-arrow on last row (matches C).
    if row == NARROW_DESC_ROWS - 1:
        budget -= ARROW_DOWN_WIDTH + NARROW_ARROW_GAP
    return budget


def emerald_page_count(prose: str, max_pages: int = 9) -> int:
    """Return how many Emerald detail pages prose needs (1..max_pages+ leftovers as max+1)."""
    text = " ".join(prose.split())
    if not text:
        return 1

    pos = 0
    page_count = 0
    n = len(text)

    while pos < n and page_count < max_pages:
        for row in range(NARROW_DESC_ROWS):
            budget = row_budget(page_count, row)
            used = 0
            while pos < n and text[pos] == " ":
                pos += 1
            if pos >= n:
                break
            while pos < n and text[pos] != " ":
                end = pos
                while end < n and text[end] != " ":
                    end += 1
                word = text[pos:end]
                word_px = sum(char_width(c) for c in word)
                need = word_px if used == 0 else word_px + char_width(" ")
                if need > budget - used:
                    if used == 0:
                        # Hard-split overlong token by pixel budget.
                        for ch in word:
                            cw = char_width(ch)
                            if used + cw > budget:
                                break
                            used += cw
                            pos += 1
                    break
                if used > 0:
                    used += char_width(" ")
                used += word_px
                pos = end
                while pos < n and text[pos] == " ":
                    pos += 1
        page_count += 1

    if pos < n:
        return max_pages + 1
    return max(page_count, 1)


def fits_emerald_pages(prose: str, max_pages: int = 5) -> bool:
    return emerald_page_count(prose, max_pages=max_pages) <= max_pages


if __name__ == "__main__":
    sample = (
        "Once per turn: You can target 1 monster your opponent controls; "
        "destroy that target, and if you do, Special Summon 1 Level 4 or lower "
        "monster from your hand."
    )
    print(emerald_page_count(sample), "pages for sample,", len(sample), "chars")
    assert fits_emerald_pages(sample, 5)
    print("desc_emerald_wrap self-check OK")
