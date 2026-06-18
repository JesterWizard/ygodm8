#include "global.h"
#include "constants/card_ids.h"
#include "servant_of_catabolism.h"

u8 CanServantOfCatabolismAttackDirectly(u16 cardId) {
  return cardId == SERVANT_OF_CATABOLISM;
}
