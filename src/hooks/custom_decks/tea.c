#include "global.h"
#include "common-chax.h"
#include "custom_decks.h"

#define CUSTOM_DIALOGUE_BODY(line1, line2) line1 "#0" line2 "#1@0\x0A"

static const u8 sTeaCardShopDuelBody[] APPEND_TEXT =
  CUSTOM_DIALOGUE_BODY("I made a deck.", "Let's duel.");

static const u16 sTeaCustomDeck[40] APPEND_RODATA = {
  MYSTICAL_ELF,
  MYSTICAL_ELF,
  MYSTICAL_ELF,
  PETIT_ANGEL,
  PETIT_ANGEL,
  PETIT_ANGEL,
  HAPPY_LOVER,
  HAPPY_LOVER,
  HAPPY_LOVER,
  HARPIE_LADY,
  HARPIE_LADY,
  HARPIE_LADY,
  MAGICIAN_OF_FAITH,
  MAGICIAN_OF_FAITH,
  MAGICIAN_OF_FAITH,
  WITCH_OF_THE_BLACK_FOREST,
  WITCH_OF_THE_BLACK_FOREST,
  WITCH_OF_THE_BLACK_FOREST,
  SANGAN,
  SANGAN,
  SANGAN,
  HANE_HANE,
  HANE_HANE,
  HANE_HANE,
  DANCING_ELF,
  DANCING_ELF,
  DANCING_ELF,
  FAITH_BIRD,
  FAITH_BIRD,
  FAITH_BIRD,
  NEMURIKO,
  NEMURIKO,
  NEMURIKO,
  KURIBOH,
  KURIBOH,
  KURIBOH,
  DARK_MAGICIAN_GIRL,
  SPIRIT_OF_THE_HARP,
  FAIRY_DRAGON,
  AQUA_MADOOR
};

static const CustomDeckEntry sTeaCardShopEntries[] APPEND_RODATA = {
  {
    SPRITE_TEA,
    LOCATION_CARD_SHOP_INSIDE,
    PORTRAIT_TEA,
    sTeaCustomDeck,
    sTeaCardShopDuelBody
  }
};

const u16 *TeaCustomDeck_GetNewGameDeck(void) {
  return NULL;
}

const u16 *TeaCustomDeck_GetDuelDeck(void) {
  return sTeaCustomDeck;
}

const CustomDeckEntry *TeaCustomDeck_GetCardShopEntries(unsigned *count) {
  if (count != NULL)
    *count = ARRAY_COUNT(sTeaCardShopEntries);
  return sTeaCardShopEntries;
}
