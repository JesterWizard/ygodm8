#include "global.h"
#include "configs/runtime.h"

extern unsigned char gTrunkCardQty[];
extern u8 sub_801F098(u16);
extern u8 GetPlayerDeckSize(void);
extern unsigned GetDuelistLevel(void);
extern void SetCardInfo(u16);
extern struct CardInfo gCardInfo;
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
  if (!gTrunkCardQty[id] || sub_801F098(id) != TRUE || GetPlayerDeckSize() >= GetRuntimeDeckLimit())
    return 0x4000;
  SetCardInfo(id);
  if (GetDuelistLevel() < gCardInfo.cost)
    return 0x4000;
  return 0x5000;
}

LYN_REPLACE_CHECK(sub_800A528);
unsigned short sub_800A528__Replacement(void) {
  if (GetPlayerDeckSize() < GetRuntimeDeckLimit())
    return 0x4000;
  return 0x5000;
}
