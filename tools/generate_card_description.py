#!/usr/bin/env python3

import argparse
import ast
import pathlib
import re


ROW_WIDTHS = (27, 27, 27, 27, 27)
GENERATED_INCLUDE_NAME = "card_description_data_generated.inc"
CONTROL_CODE_RE = re.compile(r"\s*(#[0-8]|\\^|\\\$)\s*")


def wrap_page(text: str) -> list[str]:
    text = CONTROL_CODE_RE.sub(lambda match: match.group(1), text).lstrip()
    words = text.split()
    lines = []
    word_index = 0

    for width in ROW_WIDTHS:
        if word_index >= len(words):
            lines.append("")
            continue

        line_words = []
        line_len = 0

        while word_index < len(words):
            word = words[word_index]
            word_len = len(word)

            if word_len > width:
                raise ValueError(f"Word does not fit in width {width!r}: {word!r}")

            next_len = word_len if not line_words else line_len + 1 + word_len
            if next_len > width:
                break

            line_words.append(word)
            line_len = next_len
            word_index += 1

        if not line_words:
            raise ValueError(f"Could not fit text into width {width!r}")

        line = " ".join(line_words)
        lines.append(line)

    if word_index < len(words):
        remaining = " ".join(words[word_index:])
        raise ValueError(f"Text does not fit in one page: {remaining!r}")

    return lines


def emit_runtime_symbol(symbol: str, pages: list[str]) -> str:
    if len(pages) not in (2, 3):
        raise ValueError(f"Expected 2 or 3 pages, got {len(pages)}")

    payload = ["  ", f"^{len(pages)}"]
    for page in pages:
        payload.extend(wrap_page(page))
        payload.append("^")
    data = "".join(payload).encode("ascii") + b"\0"

    out = [f"const u8 {symbol}Data[] APPEND_TEXT = {{"]

    for i in range(0, len(data), 12):
        chunk = data[i:i + 12]
        out.append("    " + ", ".join(f"0x{byte:02X}" for byte in chunk) + ",")

    out.append("};")
    return "\n".join(out)


def update_description_file(path: pathlib.Path) -> None:
    src = path.read_text()

    entries = re.findall(
        r'static const char \*const ([A-Za-z0-9_]+)\[\] = \{\s*'
        r'"((?:[^"\\]|\\.)*)",\s*'
        r'"((?:[^"\\]|\\.)*)",\s*'
        r'(?:\s*"((?:[^"\\]|\\.)*)",\s*)?'
        r'\};',
        src,
        flags=re.S,
    )

    runtime_blocks = []
    for symbol, page1, page2, page3 in entries:
        page1_text = ast.literal_eval(f'"{page1}"')
        page2_text = ast.literal_eval(f'"{page2}"')
        pages = [page1_text, page2_text]
        if page3 is not None:
            pages.append(ast.literal_eval(f'"{page3}"'))
        runtime_blocks.append(emit_runtime_symbol(symbol, pages))

    generated_include = path.with_name(GENERATED_INCLUDE_NAME)
    generated_include.write_text("\n\n".join(runtime_blocks) + ("\n" if runtime_blocks else ""))


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Wrap two or three human-readable card description strings into the repo's card format."
    )
    parser.add_argument("--update-file", dest="update_file", help="Update a card_description_data.c-style file in place")
    parser.add_argument("symbol", nargs="?", help="C symbol name, e.g. gMilusRadiantDescription")
    parser.add_argument("page1", nargs="?", help="Plain text for page 1")
    parser.add_argument("page2", nargs="?", help="Plain text for page 2")
    parser.add_argument("page3", nargs="?", help="Plain text for page 3")
    args = parser.parse_args()

    if args.update_file:
        update_description_file(pathlib.Path(args.update_file))
        return 0

    if args.symbol is None or args.page1 is None or args.page2 is None:
        parser.error("page1 and page2 are required unless --update-file is used")

    pages = [args.page1, args.page2]
    if args.page3 is not None:
        pages.append(args.page3)
    print(emit_runtime_symbol(args.symbol, pages))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
