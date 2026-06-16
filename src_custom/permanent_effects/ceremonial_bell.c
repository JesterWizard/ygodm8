#include "global.h"
#include "duel_helpers.h"

static void RevealAllHands(void) {
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id != CARD_NONE)
      gTurnHands[ACTIVE_DUELIST][i]->isFaceUp = TRUE;
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      gTurnHands[INACTIVE_DUELIST][i]->isFaceUp = TRUE;
  }
}

unsigned char ShouldActivateCeremonialBell(void) {
  if (gActiveEffect.turnRow != 1 && gActiveEffect.turnRow != 2)
    return FALSE;

  return gActiveEffect.cardId == CEREMONIAL_BELL;
}

void ActivateCeremonialBell(void) {
  FlipCardFaceUp(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);
  RevealAllHands();
  Duel_ShowEffectTextTyped(CEREMONIAL_BELL, 8);
}
