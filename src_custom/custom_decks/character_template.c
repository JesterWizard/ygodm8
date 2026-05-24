#include "global.h"
#include "common-chax.h"
#include "custom_decks.h"

/*
Copy this file to add a new custom-deck character module.

Shape:

  static const u8 sNameCardShopDuelBody[] APPEND_TEXT =
    "Line one.#0"
    "Line two.#1@0\x0A";

  static const u16 sNameCustomDeck[40] APPEND_RODATA = {
    // 40 cards
  };

  static const CustomDeckEntry sNameCardShopEntries[] APPEND_RODATA = {
    {
      SPRITE_NAME,
      LOCATION_CARD_SHOP_INSIDE,
      PORTRAIT_NAME,
      sNameCustomDeck,
      sNameCardShopDuelBody
    }
  };

  static const CustomDuelRewardEntry sNameCardShopRewards[] APPEND_RODATA = {
    {
      SPRITE_NAME,
      LOCATION_CARD_SHOP_INSIDE,
      // normalDrops
      // normalDropCount
      // lowDrops
      // lowDropCount
      // capacityYield
      // minDomino
      // maxDomino
    }
  };

  const u16 *NameCustomDeck_GetNewGameDeck(void) {
    return sNameCustomDeck;
  }

  const CustomDeckEntry *NameCustomDeck_GetCardShopEntries(unsigned *count) {
    if (count != NULL)
      *count = ARRAY_COUNT(sNameCardShopEntries);
    return sNameCardShopEntries;
  }

  const CustomDuelRewardEntry *NameCustomDeck_GetCardShopRewards(unsigned *count) {
    if (count != NULL)
      *count = ARRAY_COUNT(sNameCardShopRewards);
    return sNameCardShopRewards;
  }
*/

static const u8 sCustomDeckTemplateUnused[] APPEND_RODATA = {0};
