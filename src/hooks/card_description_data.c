#include "global.h"
#include "configs/runtime.h"
#include "constants/card_descriptions.h"
/*
 * Vanilla card descriptions are parsed as text, not copied from raw tile data:
 * the first 2 bytes are skipped, ^N declares the page count, ^ separates
 * pages, and the game inserts line breaks automatically every 12 characters.
 *
 * To avoid words being split across lines, author each visual line as an
 * exact-width chunks. Edit the human-readable source strings below, then run:
 * python3 tools/generate_card_description.py --update-file src/hooks/card_description_data.c
 */

static const char *const gMilusRadiantDescription[] = {
    "A deceptive beast that appears to be the picture of cuteness.",
    "It empowers FOREST monsters and weakens WIND monsters.",
};

#include "card_description_data_generated.inc"
