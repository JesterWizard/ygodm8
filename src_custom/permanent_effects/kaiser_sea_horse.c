#include "global.h"

unsigned char GetKaiserSeaHorseTributeCount(u16 cardId) {
  if (cardId == KAISER_SEA_HORSE)
    return 2;

  return 1;
}
