#include "global.h"
#include "duel_helpers.h"

static unsigned char CountMukaMukaStages(void) {
  unsigned char handCards;

  if (gActiveEffect.turnRow == 1)
    handCards = Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]);
  else if (gActiveEffect.turnRow == 2)
    handCards = Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]);
  else
    return 0;

  return handCards / 2;
}

unsigned char ShouldActivateMukaMuka(void) {
  if (gActiveEffect.turnRow != 1 && gActiveEffect.turnRow != 2)
    return FALSE;

  return gActiveEffect.cardId == MUKA_MUKA;
}

void ActivateMukaMuka(void) {
  unsigned char stages;
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  FlipCardFaceUp(zone);

  stages = CountMukaMukaStages();
  while (stages--)
    IncrementTempStage(zone);

  Duel_ShowEffectTextTyped(MUKA_MUKA, 8);
}
