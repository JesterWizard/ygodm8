#include "global.h"
#include "constants/card_ids.h"
#include "card_passives.h"

u8 IsImmuneToControlSwitch(u16 cardId) {
  return cardId == MATAZA_THE_ZAPPER || cardId == LYRILUSC_INDEPENDENT_NIGHTINGALE;
}
