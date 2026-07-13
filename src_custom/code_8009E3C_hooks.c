#include "global.h"
#include "card.h"
#include "configs/runtime.h"

extern u8 sub_801F098(u16);
extern u8 GetPlayerDeckSize(void);
extern u8 TrunkMenu_GetTrunkQty(u16 cardId);
unsigned short sub_800A4B0(unsigned short);
unsigned short sub_800A528(void);

static u8 GetRuntimeDeckLimit(void) {
  u8 limit = gRuntimeConfig.max_deck_cards;

  if (limit == 0 || limit > DECK_SIZE)
    return DECK_SIZE;
  return limit;
}

LYN_REPLACE_CHECK(sub_800A4B0);
unsigned short sub_800A4B0__Replacement(unsigned short id) {
  /* sub_8009A94: palette for trunk row digits/ATK/DEF. Do not gate on deck full here. */
  if (!TrunkMenu_GetTrunkQty(id))
    return 0x4000;
  if (CardExceedsCurrentDuelistLevel(id))
    return 0x4000;
  return 0x5000;
}

LYN_REPLACE_CHECK(sub_800A528);
unsigned short sub_800A528__Replacement(void) {
  /* Use main-deck-only count for palette coloring (deck size), not the
   * GetPlayerDeckSize override which also counts extra deck cards. */
  if (gDeckMenu.cardCount < GetRuntimeDeckLimit())
    return 0x4000;
  return 0x5000;
}
