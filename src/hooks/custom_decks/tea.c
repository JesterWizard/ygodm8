#include "global.h"
#include "common-chax.h"
#include "custom_decks.h"

typedef struct {
  u8 spriteId;
  u8 locationId;
  const u16 *deck;
  const u8 *dialogueText;
} CustomDeckEntry;

static const u8 sTeaCardShopDuelText[] APPEND_TEXT = {
  0x23, 0x34, PORTRAIT_TEA, 0x00, PORTRAIT_POSITION_AUTO,
  'I', ' ', 'm', 'a', 'd', 'e', ' ', 'a', ' ', 'd', 'e', 'c', 'k', '.',
  0x23, 0x30,
  'L', 'e', 't', '\'', 's', ' ', 'd', 'u', 'e', 'l', '.',
  0x23, 0x31, '@', '0', 0x0A, 0x00
};

static const u16 sTeaCustomDeck[DECK_SIZE] APPEND_RODATA = {
  MYSTICAL_ELF, MYSTICAL_ELF, MYSTICAL_ELF,
  PETIT_ANGEL, PETIT_ANGEL, PETIT_ANGEL,
  HAPPY_LOVER, HAPPY_LOVER, HAPPY_LOVER,
  HARPIE_LADY, HARPIE_LADY, HARPIE_LADY,
  MAGICIAN_OF_FAITH, MAGICIAN_OF_FAITH, MAGICIAN_OF_FAITH,
  WITCH_OF_THE_BLACK_FOREST, WITCH_OF_THE_BLACK_FOREST, WITCH_OF_THE_BLACK_FOREST,
  SANGAN, SANGAN, SANGAN,
  HANE_HANE, HANE_HANE, HANE_HANE,
  DANCING_ELF, DANCING_ELF, DANCING_ELF,
  FAITH_BIRD, FAITH_BIRD, FAITH_BIRD,
  NEMURIKO, NEMURIKO, NEMURIKO,
  KURIBOH, KURIBOH, KURIBOH,
  DARK_MAGICIAN_GIRL,
  SPIRIT_OF_THE_HARP,
  FAIRY_DRAGON,
  AQUA_MADOOR
};

static const CustomDeckEntry sCustomDeckEntries[] APPEND_RODATA = {
  {
    SPRITE_TEA,
    LOCATION_CARD_SHOP_INSIDE,
    sTeaCustomDeck,
    sTeaCardShopDuelText
  }
};

static const CustomDeckEntry *FindCustomDeckEntry(u8 spriteId, u8 locationId) {
  unsigned i;

  for (i = 0; i < ARRAY_COUNT(sCustomDeckEntries); i++) {
    if (sCustomDeckEntries[i].spriteId == spriteId && sCustomDeckEntries[i].locationId == locationId)
      return &sCustomDeckEntries[i];
  }

  return NULL;
}

u8 CustomDecks_IsEnabled(void) {
  return gRuntimeConfig.enable_custom_decks == TRUE;
}

const u16 *CustomDecks_GetNewGameDeck(void) {
  return sCustomDeckEntries[0].deck;
}

u8 CustomDecks_ShouldUseCardShopDuel(u8 spriteId, u8 locationId) {
  return FindCustomDeckEntry(spriteId, locationId) != NULL;
}

struct Script CustomDecks_BuildCardShopDuelScript(u8 spriteId, u8 locationId, const struct Script *fallbackScript) {
  const CustomDeckEntry *entry = FindCustomDeckEntry(spriteId, locationId);
  struct Script script;

  script.start = entry == NULL ? NULL : (u8 *)entry->dialogueText;
  script.unk4 = (struct Script *)fallbackScript;
  script.unk8 = (struct Script *)fallbackScript;
  return script;
}
