#include "global.h"
#include "configs/runtime.h"

extern u8 GetPlayerDeckSize(void);
unsigned short sub_800DA88(void);

static u8 GetRuntimeDeckLimit(void) {
  u8 limit = gRuntimeConfig.max_deck_cards;

  if (limit == 0 || limit > DECK_SIZE)
    return DECK_SIZE;
  return limit;
}

LYN_REPLACE_CHECK(sub_800DA88);
unsigned short sub_800DA88__Replacement(void) {
  if (GetPlayerDeckSize() < GetRuntimeDeckLimit())
    return 0x4000;
  return 0x5000;
}
