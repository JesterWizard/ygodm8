#!/usr/bin/env python3
"""Keep in sync with RecoverProseFromLargePages / WrapProseToSmallPages in
src_custom/code_801EF30_hooks.c — fails if small-font reflow packing regresses."""

import unittest

LARGE_WIDTHS = (12, 14, 14, 14, 12)
SMALL_WIDTHS = (12, 14, 14, 14, 14, 14, 14, 14, 14, 12)


def recover_prose(pages: list[str]) -> str:
    parts: list[str] = []
    for page in pages:
        pos = 0
        for width in LARGE_WIDTHS:
            if pos >= len(page):
                break
            take = min(width, len(page) - pos)
            chunk = page[pos : pos + take].rstrip()
            pos += take
            if chunk:
                parts.append(chunk)
    return " ".join(parts)


def wrap_small_pages(prose: str) -> list[str]:
    words = prose.split()
    pages: list[str] = []
    wi = 0

    while wi < len(words):
        page_chars: list[str] = []
        for width in SMALL_WIDTHS:
            if wi >= len(words):
                break
            col = 0
            row_words: list[str] = []
            while wi < len(words):
                word = words[wi]
                need = len(word) if col == 0 else len(word) + 1
                if need > width - col:
                    if col == 0 and len(word) > width:
                        row_words.append(word[:width])
                        words[wi] = word[width:]
                        col = width
                    break
                row_words.append(word)
                col += need
                wi += 1
            if not row_words and wi >= len(words):
                break
            if wi >= len(words):
                page_chars.append(" ".join(row_words))
                break
            page_chars.append(" ".join(row_words).ljust(width))
        pages.append("".join(page_chars))
    return pages


class CardDescriptionReflowTests(unittest.TestCase):
    def test_sangan_two_large_pages_become_one_small_page(self):
        # Stored large-layout bodies (row-padded / concatenated), as in ROM data.
        pages = [
            "A fiend thatlooks like a  black sphere  with eyes.    ",
            "When sent   from the fieldto the        graveyard,    draw 1 card.",
        ]
        prose = recover_prose(pages)
        self.assertEqual(
            prose,
            "A fiend that looks like a black sphere with eyes. "
            "When sent from the field to the graveyard, draw 1 card.",
        )
        small = wrap_small_pages(prose)
        self.assertEqual(len(small), 1)
        self.assertLessEqual(len(small[0]), sum(SMALL_WIDTHS))
        self.assertIn("graveyard", small[0])
        self.assertIn("draw 1 card.", small[0])

    def test_long_prose_fills_pages_before_breaking(self):
        words = [f"w{i:02d}" for i in range(40)]  # 40 * ~4 chars + spaces >> 136
        prose = " ".join(words)
        small = wrap_small_pages(prose)
        self.assertGreaterEqual(len(small), 2)
        # First page should be packed to the full small content budget.
        self.assertEqual(len(small[0]), sum(SMALL_WIDTHS))


if __name__ == "__main__":
    unittest.main()
