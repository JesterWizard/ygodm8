/*
 * Card detail descriptions use the vanilla parser format:
 * - Prefix with CARD_DESC_PREFIX.
 * - Add CARD_DESC_PAGES_2 / _3 / ... if needed.
 * - Separate pages with CARD_DESC_PAGE_BREAK.
 * - In the current observed layout, row widths are effectively 12/14/14/14/12.
 * - For easier authoring, use tools/generate_card_description.py to convert
 *   two to five normal strings into the exact CARD_DESC_LINE(...) output.
 */
#define CARD_DESC_PREFIX "  "
#define CARD_DESC_PAGES_2 "^2"
#define CARD_DESC_PAGES_3 "^3"
#define CARD_DESC_PAGES_4 "^4"
#define CARD_DESC_PAGES_5 "^5"
#define CARD_DESC_PAGE_BREAK "^"
#define CARD_DESC_LINE(text_12_chars) text_12_chars
