#include "global.h"
#include "constants/card_ids.h"
#include "reaper_on_the_nightmare.h"

u8 CanReaperOnTheNightmareAttackDirectly(u16 cardId) {
  return cardId == REAPER_ON_THE_NIGHTMARE;
}

u8 IsBattleIndestructibleMonster(u16 cardId) {
  return cardId == REAPER_ON_THE_NIGHTMARE;
}
