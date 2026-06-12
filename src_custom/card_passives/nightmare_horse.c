#include "global.h"
#include "constants/card_ids.h"
#include "nightmare_horse.h"

u8 CanNightmareHorseAttackDirectly(u16 cardId) {
  return cardId == NIGHTMARE_HORSE;
}
