#include "global.h"
#include "configs/runtime.h"

LYN_REPLACE_CHECK(NumFaceUpMatchingAttributeInRow);
unsigned NumFaceUpMatchingAttributeInRow__Replacement(unsigned char turnRow, unsigned char attribute) {
  u8 i, count = 0;

  if (gRuntimeConfig.disable_element_system == TRUE)
    return 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[turnRow][i]->id == CARD_NONE || !gTurnZones[turnRow][i]->isFaceUp)
      continue;
    SetCardInfo(gTurnZones[turnRow][i]->id);
    if (gCardInfo.attribute == attribute)
      count++;
  }

  return count;
}
