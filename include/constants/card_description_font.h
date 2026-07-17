#ifndef GUARD_CARD_DESCRIPTION_FONT_H
#define GUARD_CARD_DESCRIPTION_FONT_H

/* RuntimeConfig.card_description_font — card detail description renderer. */
enum CardDescriptionFont {
    CARD_DESC_FONT_VANILLA = 0,       /* Fixed 8x16 (flag 0x901), 5 authored rows */
    CARD_DESC_FONT_SMALL = 1,         /* Fixed 8x8 (flag 0x001), 10 reflowed rows */
    CARD_DESC_FONT_EMERALD_NARROW = 2, /* Pokemon Emerald small_narrow VWF */
    CARD_DESC_FONT_COUNT
};

#endif /* GUARD_CARD_DESCRIPTION_FONT_H */
